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
#define PI 3.14159265358979323846
#define COLLISION_WALL 8
#define FOV  PI/3
#define isRayFacingDown(angle)	(angle > 0 && angle < PI)
#define isRayFacingUp(angle)	(!isRayFacingDown(angle))
#define isRayFacingRight(angle) (angle < (0.5 * PI) || angle > (1.5 * PI))
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

typedef struct s_cub3d
{
	t_player	player;
	void		*mlx;
	void		*win;
	t_map		map;
	t_data		img;
	t_keys		keys;
}	t_cub3d;

void	my_mlx_pixel_put(t_cub3d *cub, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_W || y < 0 || y >= WIN_H)
		return ;
	dst = cub->img.addr + (y * cub->img.lines_len + x * (cub->img.bpp / 8));
	*(unsigned int *)dst = color;
}
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
void	draw_fov(t_cub3d *cub, int px, int py)
{
	double angle;
	int i;
	int line_x, line_y;

	angle = cub->player.angle - (float)(FOV / 2);
	while (angle <= cub->player.angle + (float)(FOV / 2))
	{
		i = 0;
		while (i < 100)
		{
			line_x = px + cos(angle) * i;
			line_y = py + sin(angle) * i;
			my_mlx_pixel_put(cub, line_x, line_y, 0x0000FF00);
			i++;
		}
		angle += (FOV / 100.0);
	}
}
int	is_wall(t_cub3d *cub, int map_x, int map_y)
{
	if (map_x < 0 || map_x >= cub->map.width ||
		map_y < 0 || map_y >= cub->map.height)
		return (1);
	return (cub->map.data[map_y][map_x] == '1');
}
int	is_wall_at_point(t_cub3d *cub, double x, double y)
{
	int map_x = (int)(x / TILE_SIZE);
	int map_y = (int)(y / TILE_SIZE);
	return (is_wall(cub, map_x, map_y));
}
void	draw_player(t_cub3d *cub)
{
	int	px;
	int	py;

	px = (int)(cub->player.pos.x);
	py = (int)(cub->player.pos.y);
	draw_player_circle(cub, px, py);
	draw_direction_line(cub, px, py);
}
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
void	handle_strafe(t_cub3d *cub, double *new_x, double *new_y)
{
	if (cub->keys.a)
	{
		*new_x += cos(cub->player.angle - M_PI_2) * MOVE_SPEED;
		*new_y += sin(cub->player.angle - M_PI_2) * MOVE_SPEED;
	}
	if (cub->keys.d)
	{
		*new_x += cos(cub->player.angle + M_PI_2) * MOVE_SPEED;
		*new_y += sin(cub->player.angle + M_PI_2) * MOVE_SPEED;
	}
}
void	handle_rotation(t_cub3d *cub)
{
	if (cub->keys.left)
	{
		cub->player.angle -= ROTATE_SPEED;
		if (cub->player.angle < 0)
			cub->player.angle += 2 * M_PI;
	}
	if (cub->keys.right)
	{
		cub->player.angle += ROTATE_SPEED;
		if (cub->player.angle >= 2 * M_PI)
			cub->player.angle -= 2 * M_PI;
	}
}
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
// void rays_horizontal_wall(t_cub3d *cub)
// {
	 
// 	// int isRayFacingDown  = cub->player.angle > 0 && cub->player.angle < PI;
//     // int isRayFacingUp    = !isRayFacingDown;
//     // int isRayFacingRight = cub->player.angle < (0.5 * PI) || cub->player.angle > (1.5 * PI);
//     // int isRayFacingLeft  = !isRayFacingRight;
// 	int wall_hit_x = 0;
// 	int wall_hit_y = 0;
// 	int fount_hori_wall = 0;
// 	int hori_wall_x = 0;
// 	int hori_wall_y = 0;
// 	int f1_inter_x = 0;
// 	int f1_inter_y = 0;
// 	if(isRayFacingUp)
// 		f1_inter_y = (cub->player.pos.y / TILE_SIZE)*TILE_SIZE - 1;
// 	else if (isRayFacingDown)
// 		f1_inter_y = (cub->player.pos.y / TILE_SIZE)*TILE_SIZE + TILE_SIZE;
// 	f1_inter_x = cub->player.pos.x + ((f1_inter_y - cub->player.pos.y) / tan(cub->player.angle)); 
// 	int next_horiz_x = f1_inter_x;
// 	int next_horiz_y = f1_inter_y;
// 	int xa = 0;
// 	int ya = 0;
// 	if(isRayFacingUp)
// 		ya = -TILE_SIZE;
// 	else if(isRayFacingDown)
// 		ya = TILE_SIZE;
// 	xa = ya / tan(cub->player.angle);
// 	while (next_horiz_x < WIN_W && next_horiz_y < WIN_H)
// 	{
		
// 	}
	
// }
int	render_map(void *ptr)
{
	t_cub3d	*cub;

	cub = (t_cub3d *)ptr;
	update_player_position(cub);
	render_tiles(cub);
	draw_player(cub);
	for (int x = 0; x < WIN_W; x++)
	{
		float ang = ((cub->player.angle + (float)FOV / 2) * x) / WIN_W;
		
	}
	draw_fov(cub,cub->player.pos.x, cub->player.pos.y);
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
	setup_hooks(&cub);
	mlx_loop(cub.mlx);
	return (0);
}
// void draw_fov_with_walls(t_cub3d *cub)
// {
//     double ray_angle;
//     double angle_step;
//     int j;
//     t_point dis;
//     t_point drw;
//     int step;

//     angle_step = (double)(FOV/WIN_W);
//     ray_angle = cub->player.angle - (FOV/2);
//     while(ray_angle <= cub->player.angle + (FOV/2))
//     {
//         cast_ray(cub, ray_angle);
//         if(cub->ray.hit_wall)
//         {
//             dis.x = cub->ray.hit_point.x - cub->player.pos.x;
//             dis.y = cub->ray.hit_point.y - cub->player.pos.y;
//             step = (int)cub->ray.distance;
//             j = 0;
//             while(j < step)
//             {
//                 drw.x = (int)(cub->player.pos.x + (dis.x * j / step));
//                 drw.y = (int)(cub->player.pos.y + (dis.y * j / step));
//                  my_mlx_pixel_put(cub, drw.x, drw.y, 0x253900);
//                  j++;
//             }
//         }
//         ray_angle+=angle_step;
//     }
// }

// void	init_rays(t_cub3d *cub)
// {
// 	cub->rays = malloc(sizeof(t_ray) * WIN_W);
// 	if (!cub->rays)
// 	{
// 		write(2, "Error: Failed to allocate memory for rays\n", 43);
// 		exit(1);
// 	}
// }