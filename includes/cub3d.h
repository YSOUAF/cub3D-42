
#ifndef CUB3D_H
#define CUB3D_H



#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <unistd.h>
# include "../lib/get_next_line/get_next_line.h"

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
#define COLLISION_WALL 6
#define FOV M_PI/3


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
	char	*path_no;
	char	*path_so;
	char	*path_we;
	char	*path_ea;
	int32_t	color_f;
	int32_t	color_c;
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

typedef enum s_drct {
	NORTH,
	SOUTH,
	EAST,
	WEST
} t_drct;

typedef struct s_ray
{
	double	angle;
	double	distance;
	t_point	hit_point;
	int		hit_wall;
	int		is_vertical;
	t_drct	drction;
}	t_ray;

typedef struct s_cub3d
{
	t_player		player;
	void			*mlx;
	void			*win;
	t_map			map;
	t_data			img;
	t_keys			keys;
	t_ray			ray;
	t_data			data;
	// mlx_texture_t	tex_no;
	// mlx_texture_t	tex_so;
	// mlx_texture_t	tex_we;
	// mlx_texture_t	tex_no;

	// t_data		tex_no;
	// t_data		tex_so;
	// t_data		tex_we;
	// t_data		tex_ea;
}	t_cub3d;


int	render_map(void *ptr);
int is_wall(t_cub3d *cub, int map_x, int map_y);
t_point find_hor_inter(t_cub3d *cub, double ray_angle, int *found_wall);
t_point find_vert_inter(t_cub3d *cub, double ray_angle, int *found_wall);
void draw_player_circle(t_cub3d *cub, int px, int py, int size);
void draw_direction_line(t_cub3d *cub, int px, int py, int dis);
void draw_player(t_cub3d *cub);
void init_player(t_cub3d *cub);
int is_valid_position(t_cub3d *cub, double new_x, double new_y);
void handle_forward_backward(t_cub3d *cub, double *new_x, double *new_y);
void handle_strafe(t_cub3d *cub, double *new_x, double *new_y);
void handle_rotation(t_cub3d *cub);
void update_player_position(t_cub3d *cub);
void	init_mlx(t_cub3d *cub);
void	my_mlx_pixel_put(t_cub3d *cub, int x, int y, int color);
void	init_map(t_cub3d *cub);
void draw_square(t_cub3d *cub, int x, int y, int color);
int	render_map(void *ptr);
double normlize_angle(double angle);
double calculate_distance(t_point p1, t_point p2);
void cast_all_rays(t_cub3d *cub);
void draw_fov_with_walls(t_cub3d *cub);
void cast_ray(t_cub3d *cub, double ray_angle);
void	setup_hooks(t_cub3d *cub);
int	close_hook(t_cub3d *cub);
int	key_release(int keycode, t_cub3d *cub);
int	key_press(int keycode, t_cub3d *cub);
double max_ray_distance(double angle);
int is_ray_facing_down(double angle);
int is_ray_facing_up(double angle);
int is_ray_facing_right(double angle);
int is_ray_facing_left(double angle);


size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *str);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s1);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memset(void *b, int c, size_t len);
int		count(char const  *str, char c);
int		ft_isdigit(int c);
int		valid_num(const char *str);
void	*ft_memcpy(void *dst, const void* src, size_t n);


int		check_ext(char *str);
int		allocate_map(char *map, t_map **data);
int		parss_map(char **map);
int		is_char_or_zero(char c);
int		parse_texture(char *line, t_map *conf);
char	*remove_newline(char *line);






////
void print_map(char **map_data);
#endif 