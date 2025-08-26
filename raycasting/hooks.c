#include "cub3d.h"

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

int	close_hook(t_cub3d *cub)
{
	mlx_destroy_window(cub->mlx, cub->win);
	exit(0);
	return (0);
}

void	setup_hooks(t_cub3d *cub)
{
	mlx_hook(cub->win, 2, 1L << 0, key_press, cub);
	mlx_hook(cub->win, 3, 1L << 1, key_release, cub);
	mlx_hook(cub->win, 17, 0, close_hook, cub);
	mlx_loop_hook(cub->mlx, render_map, cub);
}