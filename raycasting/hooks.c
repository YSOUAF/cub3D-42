/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouaf <ysouaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 16:12:52 by ysouaf            #+#    #+#             */
/*   Updated: 2025/12/05 16:15:14 by ysouaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_key(t_cub3d *cub, int key, int value)
{
	if (key == MLX_KEY_W)
		cub->keys.w = value;
	else if (key == MLX_KEY_S)
		cub->keys.s = value;
	else if (key == MLX_KEY_A)
		cub->keys.a = value;
	else if (key == MLX_KEY_D)
		cub->keys.d = value;
	else if (key == MLX_KEY_UP)
		cub->keys.up = value;
	else if (key == MLX_KEY_DOWN)
		cub->keys.down = value;
	else if (key == MLX_KEY_LEFT)
		cub->keys.left = value;
	else if (key == MLX_KEY_RIGHT)
		cub->keys.right = value;
}

void	key_press(mlx_key_data_t keydata, void *ptr)
{
	t_cub3d	*cub;

	cub = (t_cub3d *)ptr;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(cub->mlx);
	else if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
		set_key(cub, keydata.key, 1);
	else if (keydata.action == MLX_RELEASE)
		set_key(cub, keydata.key, 0);
}

void	close_hook(void *ptr)
{
	t_cub3d	*cub;

	cub = (t_cub3d *)ptr;
	mlx_close_window(cub->mlx);
}

void	setup_hooks(t_cub3d *cub)
{
	mlx_key_hook(cub->mlx, key_press, cub);
	mlx_loop_hook(cub->mlx, render_map, cub);
	mlx_close_hook(cub->mlx, close_hook, cub);
}
