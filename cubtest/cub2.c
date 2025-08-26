#include <stdio.h>
#include <stdlib.h>
#include "mlx.h"
#include <math.h>

#define TILE_SIZE 32
#define WIN_W (50 * TILE_SIZE)
#define WIN_H (20 * TILE_SIZE)
#define ESC 53
#define UP 126
#define W 13
#define DOWN 125
#define S 1
#define LEFT 123
#define A 0
#define RIGHT 124
#define D 2
#define MOVE_SPEED 2
#define ROTATE_SPEED 0.05
#define COLLISION_WALL 8
#define FOV PI/3
#define NUM_RAYS WIN_W
#define MAX_RAY_DISTANCE 1000

#define isRayFacingDown(angle)	(angle > 0 && angle < M_PI)
#define isRayFacingUp(angle)	(!isRayFacingDown(angle))
#define isRayFacingRight(angle) (angle < (0.5 * M_PI) || angle > (1.5 * M_PI))
#define isRayFacingLeft(angle)  (!isRayFacingRight(angle))

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		lines_len;
	int		end;
}	t_data;

typedef struct s_point
{
	double	x;
	double	y;
}	t_point;

typedef struct s_player
{
	t_point	pos;
	double	angle;
}	t_player;

typedef struct s_map
{
	char	**data;
	int		width;
	int		height;
}	t_map;

typedef struct s_keys
{
	int	w;
	int	s;
	int	a;
	int	d;
	int	up;
	int	down;
	int	left;
	int	right;
}	t_keys;

typedef struct s_ray
{
	double	angle;
	double	distance;
	t_point	hit_point;
	int		hit_wall;
}	t_ray;

typedef struct s_cub3d
{
	t_player	player;
	void		*mlx;
	void		*win;
	t_map		map;
	t_data		img;
	t_keys		keys;
	t_ray		*rays;
}	t_cub3d;

/*
** Puts a pixel at coordinates (x, y) with given color
** Includes bounds checking to prevent segfaults
*/
void	my_mlx_pixel_put(t_cub3d *cub, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_W || y < 0 || y >= WIN_H)
		return ;
	dst = cub->img.addr + (y * cub->img.lines_len + x * (cub->img.bpp / 8));
	*(unsigned int *)dst = color;
}

/*
** Draws a square tile at position (x, y) with specified color
*/
void	draw_square(t_cub3d *cub, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
            if (j == TILE_SIZE -1 || i == TILE_SIZE - 1)
            		my_mlx_pixel_put(cub, x + j, y + i, 0);
            else
			my_mlx_pixel_put(cub, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

/*
** Draws a circle for the player at current position
*/
void	draw_player_circle(t_cub3d *cub, int px, int py)
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = 0;
	while (i < 20)
	{
		j = 0;
		while (j < 20)
		{
			x = px - 10 + i;
			y = py - 10 + j;
			if (pow(x - px, 2) + pow(y - py, 2) <= pow(10, 2))
				my_mlx_pixel_put(cub, x, y, 0x660B05);
			j++;
		}
		i++;
	}
}

/*
** Draws a direction line showing where player is facing
*/
void	draw_direction_line(t_cub3d *cub, int px, int py)
{
	int	i;
	int	line_x;
	int	line_y;

	i = 0;
	while (i < 40)
	{
		line_x = px + cos(cub->player.angle ) * i;
		line_y = py + sin(cub->player.angle ) * i;
		my_mlx_pixel_put(cub, line_x, line_y, 0x0012FD00);
		i++;
	}
}

/*
** Checks if position is a wall
*/
int	is_wall(t_cub3d *cub, int map_x, int map_y)
{
	if (map_x < 0 || map_x >= cub->map.width ||
		map_y < 0 || map_y >= cub->map.height)
		return (1);
	return (cub->map.data[map_y][map_x] == '1');
}

/*
** Checks if a point in pixel coordinates hits a wall
*/
int	is_wall_at_point(t_cub3d *cub, double x, double y)
{
	int map_x = (int)(x / TILE_SIZE);
	int map_y = (int)(y / TILE_SIZE);
	return (is_wall(cub, map_x, map_y));
}

/*
** Find horizontal wall intersection for a ray
*/
t_point	find_horizontal_intersection(t_cub3d *cub, double ray_angle)
{
	t_point intersection;
	double xa, ya;
	double first_inter_x, first_inter_y;

	intersection.x = -1;
	intersection.y = -1;

	// Normaliser l’angle entre 0 et 2π
	ray_angle = fmod(ray_angle, 2 * M_PI);
	if (ray_angle < 0)
		ray_angle += 2 * M_PI;

	// Étape en Y (haut ou bas)
	if (isRayFacingDown(ray_angle))
	{
		first_inter_y = floor(cub->player.pos.y / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
		ya = TILE_SIZE;
	}
	else // isRayFacingUp
	{
		first_inter_y = floor(cub->player.pos.y / TILE_SIZE) * TILE_SIZE - 1;
		ya = -TILE_SIZE;
	}

	// Étape en X
	first_inter_x = cub->player.pos.x + (first_inter_y - cub->player.pos.y) / tan(ray_angle);
	xa = ya / tan(ray_angle);
    

	// Boucle pour trouver le mur
	while (first_inter_x >= 0 && first_inter_x < WIN_W &&
	       first_inter_y >= 0 && first_inter_y < WIN_H)
	{
		double check_y = first_inter_y;
		if (isRayFacingUp(ray_angle))
			check_y = first_inter_y; // parfois check_y = first_inter_y - 1 selon ta logique de map

		if (is_wall_at_point(cub, first_inter_x, check_y))
		{
			intersection.x = first_inter_x;
			intersection.y = first_inter_y;
			break;
		}
		else
		{
			first_inter_x += xa;
			first_inter_y += ya;
		}
	}
	return intersection;
}

/*
** Find vertical wall intersection for a ray
*/
t_point	find_vertical_intersection(t_cub3d *cub, double ray_angle)
{
	t_point	intersection;
	double	x_step;
	double	y_step;
	double	x_inter;
	double	y_inter;

	intersection.x = -1;
	intersection.y = -1;

	/* --- 1. Find first vertical intersection --- */
	if (isRayFacingRight(ray_angle))
	{
		x_inter = floor(cub->player.pos.x / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
		x_step = TILE_SIZE;
	}
	else
	{
		x_inter = floor(cub->player.pos.x / TILE_SIZE) * TILE_SIZE - 0.0001;
		x_step = -TILE_SIZE;
	}
	y_inter = cub->player.pos.y + (x_inter - cub->player.pos.x) * tan(ray_angle);

	y_step = TILE_SIZE * tan(ray_angle);
	if ((isRayFacingUp(ray_angle) && y_step > 0)
		|| (isRayFacingDown(ray_angle) && y_step < 0))
		y_step *= -1;

	/* --- 2. Increment until wall or out of bounds --- */
	while (x_inter >= 0 && x_inter < WIN_W && y_inter >= 0 && y_inter < WIN_H)
	{
		double check_x = x_inter;
		double check_y = y_inter;

		// ⚠️ petit ajustement : si on regarde vers la gauche, on teste la case précédente
		if (isRayFacingLeft(ray_angle))
			check_x = x_inter - 1;

		if (is_wall_at_point(cub, check_x, check_y))
		{
			intersection.x = x_inter;
			intersection.y = y_inter;
			return (intersection);
		}
		x_inter += x_step;
		y_inter += y_step;
	}
	return (intersection);
}


/*
** Calculate distance between two points
*/
double	calculate_distance(t_point p1, t_point p2)
{
	return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

/*
** Cast a single ray and find the closest wall hit
*/
t_ray	cast_ray(t_cub3d *cub, double ray_angle)
{
	t_ray ray;
	t_point horizontal_hit, vertical_hit;
	double horizontal_distance, vertical_distance;
	
	ray.angle = ray_angle;
	ray.hit_wall = 0;
	ray.distance = MAX_RAY_DISTANCE;
	
	// Normalize angle
	if (ray_angle < 0)
		ray_angle += 2 * PI;
	if (ray_angle >= 2 * PI)
		ray_angle -= 2 * PI;
	
	// Find horizontal and vertical intersections
	horizontal_hit = find_horizontal_intersection(cub, ray_angle);
	vertical_hit = find_vertical_intersection(cub, ray_angle);
	
	// Calculate distances
	horizontal_distance = MAX_RAY_DISTANCE;
	vertical_distance = MAX_RAY_DISTANCE;
	
	if (horizontal_hit.x != -1)
		horizontal_distance = calculate_distance(cub->player.pos, horizontal_hit);
	
	if (vertical_hit.x != -1)
		vertical_distance = calculate_distance(cub->player.pos, vertical_hit);
	
	// Choose the closest intersection
	if (horizontal_distance < vertical_distance)
	{
		ray.distance = horizontal_distance;
		ray.hit_point = horizontal_hit;
		ray.hit_wall = 1;
	}
	else if (vertical_distance < horizontal_distance)
	{
		ray.distance = vertical_distance;
		ray.hit_point = vertical_hit;
		ray.hit_wall = 1;
	}
	
	return ray;
}

/*
** Draw FOV rays that stop at walls
*/
void	draw_fov_with_walls(t_cub3d *cub)
{
	double ray_angle;
	double angle_step;
	int ray_count;
	int i;
	
	ray_count = 100; // Number of rays to cast for FOV visualization
	angle_step = FOV / ray_count;
	ray_angle = cub->player.angle - (FOV / 2);
	
	for (i = 0; i < ray_count; i++)
	{
		t_ray ray = cast_ray(cub, ray_angle);
		
		if (ray.hit_wall)
		{
			// Draw line from player to wall hit point
			double dx = ray.hit_point.x - cub->player.pos.x;
			double dy = ray.hit_point.y - cub->player.pos.y;
			int steps = (int)ray.distance;
			
			for (int j = 0; j < steps; j++)
			{
				int x = (int)(cub->player.pos.x + (dx * j / steps));
				int y = (int)(cub->player.pos.y + (dy * j / steps));
				my_mlx_pixel_put(cub, x, y, 0x0000FF00);
			}
			
			// Draw hit point
			my_mlx_pixel_put(cub, (int)ray.hit_point.x, (int)ray.hit_point.y, 0xFF0000);
		}
		
		ray_angle += angle_step;
	}
}

/*
** Cast all rays for 3D rendering (preparation for future 3D view)
*/
void	cast_all_rays(t_cub3d *cub)
{
	double ray_angle;
	double angle_step;
	int i;
	
	angle_step = FOV / NUM_RAYS;
	ray_angle = cub->player.angle - (FOV / 2);
	
	for (i = 0; i < NUM_RAYS; i++)
	{
		cub->rays[i] = cast_ray(cub, ray_angle);
		ray_angle += angle_step;
	}
}

/*
** Draws the player (circle + direction line)
*/
void	draw_player(t_cub3d *cub)
{
	int	px;
	int	py;

	px = (int)(cub->player.pos.x);
	py = (int)(cub->player.pos.y);
	draw_player_circle(cub, px, py);
	draw_direction_line(cub, px, py);
}

/*
** Checks if new position is valid with collision COLLISION_WALL
*/
int	is_valid_position(t_cub3d *cub, double new_x, double new_y)
{
	int		player_x;
	int		player_y;

	player_x = (int)new_x;
	player_y = (int)new_y;
	if (is_wall(cub, (player_x - COLLISION_WALL) / TILE_SIZE,
			(player_y - COLLISION_WALL) / TILE_SIZE))
		return (0);
	if (is_wall(cub, (player_x + COLLISION_WALL) / TILE_SIZE,
			(player_y - COLLISION_WALL) / TILE_SIZE))
		return (0);
	if (is_wall(cub, (player_x - COLLISION_WALL) / TILE_SIZE,
			(player_y + COLLISION_WALL) / TILE_SIZE))
		return (0);
	if (is_wall(cub, (player_x + COLLISION_WALL) / TILE_SIZE,
			(player_y + COLLISION_WALL) / TILE_SIZE))
		return (0);
	return (1);
}

/*
** Handles forward/backward movement
*/
void	handle_forward_backward(t_cub3d *cub, double *new_x, double *new_y)
{
	if (cub->keys.up || cub->keys.w)
	{
		*new_x += cos(cub->player.angle) * MOVE_SPEED;
		*new_y += sin(cub->player.angle) * MOVE_SPEED;
	}
	if (cub->keys.down || cub->keys.s)
	{
		*new_x -= cos(cub->player.angle) * MOVE_SPEED;
		*new_y -= sin(cub->player.angle) * MOVE_SPEED;
	}
}

/*
** Handles left/right strafing movement
*/
void	handle_strafe(t_cub3d *cub, double *new_x, double *new_y)
{
	if (cub->keys.a)
	{
		*new_x += cos(cub->player.angle - PI / 2) * MOVE_SPEED;
		*new_y += sin(cub->player.angle - PI / 2) * MOVE_SPEED;
	}
	if (cub->keys.d)
	{
		*new_x += cos(cub->player.angle + PI / 2) * MOVE_SPEED;
		*new_y += sin(cub->player.angle + PI / 2) * MOVE_SPEED;
	}
}

/*
** Handles player rotation
*/
void	handle_rotation(t_cub3d *cub)
{
	if (cub->keys.left)
	{
		cub->player.angle -= ROTATE_SPEED;
		if (cub->player.angle < 0)
			cub->player.angle += 2 * PI;
	}
	if (cub->keys.right)
	{
		cub->player.angle += ROTATE_SPEED;
		if (cub->player.angle >= 2 * PI)
			cub->player.angle -= 2 * PI;
	}
}

/*
** Updates player position with separate X and Y collision checking
*/
void	update_player_position(t_cub3d *cub)
{
	double	new_x;
	double	new_y;
	double	temp_x;
	double	temp_y;

	new_x = cub->player.pos.x;
	new_y = cub->player.pos.y;
	temp_x = new_x;
	temp_y = new_y;
	handle_forward_backward(cub, &new_x, &new_y);
	handle_strafe(cub, &new_x, &new_y);
	handle_rotation(cub);
	if (is_valid_position(cub, new_x, temp_y))
		cub->player.pos.x = new_x;
	if (is_valid_position(cub, temp_x, new_y))
		cub->player.pos.y = new_y;
}

/*
** Renders the map tiles
*/
void	render_tiles(t_cub3d *cub)
{
	int	i;
	int	j;

	i = 0;
	while (cub->map.data[i])
	{
		j = 0;
		while (cub->map.data[i][j])
		{
			if (cub->map.data[i][j] == '1')
				draw_square(cub, j * TILE_SIZE, i * TILE_SIZE, 0xFF2DD1);
			else if (cub->map.data[i][j] == '0')
				draw_square(cub, j * TILE_SIZE, i * TILE_SIZE, 0xFDFFB8);
            else 
                draw_square(cub, j * TILE_SIZE, i * TILE_SIZE, 0);
			j++;
		}
		i++;
	}
}

/*
** Main rendering function called by mlx_loop_hook
*/
int	render_map(void *ptr)
{
	t_cub3d	*cub;

	cub = (t_cub3d *)ptr;
	update_player_position(cub);
	render_tiles(cub);
	draw_player(cub);
	
	// Cast all rays and draw FOV that stops at walls
	cast_all_rays(cub);
	draw_fov_with_walls(cub);
	
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img.img, 0, 0);
	return (0);
}

/*
** Handles key press events (when key is pressed down)
*/
int	key_press(int keycode, t_cub3d *cub)
{
	if (keycode == W)
		cub->keys.w = 1;
	else if (keycode == S)
		cub->keys.s = 1;
	else if (keycode == A)
		cub->keys.a = 1;
	else if (keycode == D)
		cub->keys.d = 1;
	else if (keycode == UP)
		cub->keys.up = 1;
	else if (keycode == DOWN)
		cub->keys.down = 1;
	else if (keycode == LEFT)
		cub->keys.left = 1;
	else if (keycode == RIGHT)
		cub->keys.right = 1;
	else if (keycode == ESC)
	{
		mlx_destroy_window(cub->mlx, cub->win);
		exit(0);
	}
	return (0);
}

/*
** Handles key release events (when key is released)
*/
int	key_release(int keycode, t_cub3d *cub)
{
	if (keycode == W)
		cub->keys.w = 0;
	else if (keycode == S)
		cub->keys.s = 0;
	else if (keycode == A)
		cub->keys.a = 0;
	else if (keycode == D)
		cub->keys.d = 0;
	else if (keycode == UP)
		cub->keys.up = 0;
	else if (keycode == DOWN)
		cub->keys.down = 0;
	else if (keycode == LEFT)
		cub->keys.left = 0;
	else if (keycode == RIGHT)
		cub->keys.right = 0;
	return (0);
}

/*
** Handles window close event
*/
int	close_hook(t_cub3d *cub)
{
	mlx_destroy_window(cub->mlx, cub->win);
	exit(0);
	return (0);
}

/*
** Initializes the map data
*/
void	init_map(t_cub3d *cub)
{
	static char *map_data[] = {
		"11111111111111111111111111111111111111111111111111",
		"10000000000000000000000000000000000000000000000001",
		"10000000000000000000000000000000000000000000000001",
		"10000000000000000000011111000000000000000000000001",
		"10000000000000000000010001000000000000000000000001",
		"10000011111100000000011111000000001111000000000001",
		"10000010000100000000000000000000001000100000000001",
		"10000010000100000000000000000000001000100000000001",
		"10000010000100000000000000000000001000100000000001",
		"10000011111100000000000000000000001111000000000001",
		"10000000000000000000000000000000000000000000000001",
		"10000000000000000000011111110000000000000000000001",
		"10000000000000000000010000010000000000000000000001",
		"10000000000000000000010000010000000000000000000001",
		"10000000000000000000011111110000000000000000000001",
		"10000000000000000000000000000000000000000000000001",
		"10000000000000000000000000000000000000000000000001",
		"10000000000000000000000000111000000000000000000001",
		"10000000000000000000000000000000000000000000000001",
		"11111111111111111111111111111111111111111111111111",
		NULL};

	cub->map.data = map_data;
	cub->map.width = 50;
	cub->map.height = 20;
}

/*
** Initializes player position and angle
*/
void	init_player(t_cub3d *cub)
{
	cub->player.angle = 0;
	cub->player.pos.x = 1.5 * TILE_SIZE;
	cub->player.pos.y = 1.5 * TILE_SIZE;
}

/*
** Initializes all MLX components
*/
void	init_mlx(t_cub3d *cub)
{
	cub->mlx = mlx_init();
	cub->win = mlx_new_window(cub->mlx, WIN_W, WIN_H, "cub3D");
	cub->img.img = mlx_new_image(cub->mlx, WIN_W, WIN_H);
	cub->img.addr = mlx_get_data_addr(cub->img.img, &cub->img.bpp,
			&cub->img.lines_len, &cub->img.end);
}

/*
** Initialize rays array
*/
void	init_rays(t_cub3d *cub)
{
	cub->rays = malloc(sizeof(t_ray) * NUM_RAYS);
	if (!cub->rays)
	{
		printf("Error: Failed to allocate memory for rays\n");
		exit(1);
	}
}

/*
** Sets up all event hooks
*/
void	setup_hooks(t_cub3d *cub)
{
	mlx_hook(cub->win, 2, 1L << 0, key_press, cub);
	mlx_hook(cub->win, 3, 1L << 1, key_release, cub);
	mlx_hook(cub->win, 17, 0, close_hook, cub);
	mlx_loop_hook(cub->mlx, render_map, cub);
}

/*
** Main function
*/
int	main(void)
{
	t_cub3d	cub;

	cub.keys = (t_keys){0};
	init_map(&cub);
	init_player(&cub);
	init_mlx(&cub);
	init_rays(&cub);
	setup_hooks(&cub);
	mlx_loop(cub.mlx);
	return (0);
}