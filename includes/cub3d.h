/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouaf <ysouaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 16:54:10 by ysouaf            #+#    #+#             */
/*   Updated: 2025/12/05 17:05:46 by ysouaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdint.h>
# include <math.h>
# include "../lib/get_next_line/get_next_line.h"
# include <MLX42.h>

# define TILE_SIZE 32
# define WIN_W 1600
# define WIN_H 640
# define MOVE_SPEED 4
# define ROTATE_SPEED 0.05
# define COLLISION_WALL 6
# define FOV 1.0471975512

typedef struct s_data
{
	mlx_image_t	*img;
	mlx_image_t	*img_mini;
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

typedef struct s_flags
{
	int	hor_found;
	int	ver_found;
}	t_flags;

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
	double	pos_x;
	double	pos_y;
	double	angle;
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

typedef enum e_drct
{
	NORTH,
	SOUTH,
	EAST,
	WEST
}	t_drct;

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
	mlx_t			*mlx;
	t_map			map;
	t_data			img;
	t_keys			keys;
	t_ray			ray;
	t_data			*data;
	t_flags			flags;
	mlx_texture_t	*tex_no;
	mlx_texture_t	*tex_so;
	mlx_texture_t	*tex_we;
	mlx_texture_t	*tex_ea;
}	t_cub3d;

typedef struct s_draw_walls
{
	double			wall_top;
	double			wall_buttom;
	mlx_texture_t	*tex;
	int				tx;
	int				y;
	int				top;
	int				buttom;
	int				ty;
	uint32_t		color;
	double			from_top;
	double			calc;
}	t_draw_wals;

/* Rendering functions */
void		render_map(void *ptr);
void		draw_player(t_cub3d *cub);
void		draw_ray(t_cub3d *cub, int x);

/* Raycasting functions */
void		cast_all_rays(t_cub3d *cub);
void		cast_ray(t_cub3d *cub, double ray_angle);
t_point		find_hor_inter(t_cub3d *cub, double ray_angle, int *found_wall);
t_point		find_vert_inter(t_cub3d *cub, double ray_angle, int *found_wall);

/* Ray direction helpers */
double		max_ray_distance(double angle);
int			is_ray_facing_down(double angle);
int			is_ray_facing_up(double angle);
int			is_ray_facing_right(double angle);
int			is_ray_facing_left(double angle);

/* Player functions */
void		init_player(t_cub3d *cub);
void		update_player_position(t_cub3d *cub);
void		handle_forward_backward(t_cub3d *cub, double *new_x, double *new_y);
void		handle_strafe(t_cub3d *cub, double *new_x, double *new_y);
void		handle_rotation(t_cub3d *cub);
int			is_valid_position(t_cub3d *cub, double new_x, double new_y);

/* Map functions */
int			is_wall(t_cub3d *cub, int map_x, int map_y);
int			allocate_map(char *map, t_map *data);
int			parss_map(char **map);
int			is_map_star(char *line);
int			check_character(char *line);
int			check_num_character(char **map);
int			check_walls(char **map);

/* MLX and hooks */
int			init_mlx(t_cub3d *cub);
void		setup_hooks(t_cub3d *cub);
void		key_press(mlx_key_data_t keydata, void *ptr);
void		close_hook(void *ptr);

/* Utility functions */
double		normlize_angle(double angle);
double		calculate_distance(t_point p1, t_point p2);
int			check_ext(char *str);
int			is_char_or_zero(char c);
int			parse_texture(char *line, t_map *conf, int i);
char		*remove_newline(char *line);

/* Libft functions */
size_t		ft_strlen(const char *s);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_atoi(const char *str);
char		**ft_split(char const *s, char c);
char		*ft_strdup(const char *s1);
void		*ft_calloc(size_t count, size_t size);
void		*ft_memset(void *b, int c, size_t len);
int			count(char const *str, char c);
int			ft_isdigit(int c);
int			valid_num(const char *str);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		free_arr(char **str);
uint32_t	prgba(uint32_t r, uint32_t g, uint32_t b, uint32_t a);
void		draw_walls(t_cub3d *cub, int screen_x, double line_height);
int			load_texture(t_cub3d *data);
void		destroy_texture(t_cub3d *data);
void		free_map(t_map *map);
void		cleanup(t_cub3d *cub);
void		free_paths(t_map *map);

#endif
