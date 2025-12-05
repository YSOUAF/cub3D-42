/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouaf <ysouaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 15:48:36 by ysouaf            #+#    #+#             */
/*   Updated: 2025/12/05 17:06:19 by ysouaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	put_player_pixel(t_cub3d *cub, int x, int y)
{
	mlx_put_pixel(cub->img.img, x, y, 0x660B05);
}

void	draw_player_circle(t_cub3d *cub, int px, int py, int size)
{
	int	i;
	int	j;

	i = -size;
	while (i <= size)
	{
		j = -size;
		while (j <= size)
		{
			if (i * i + j * j <= size * size)
				put_player_pixel(cub, px + i, py + j);
			j++;
		}
		i++;
	}
}

void	draw_direction_line(t_cub3d *cub, int px, int py, int dist)
{
	int		i;
	double	dx;
	double	dy;

	i = 0;
	while (i < dist)
	{
		dx = cos(cub->player.angle) * i;
		dy = sin(cub->player.angle) * i;
		mlx_put_pixel(cub->img.img, px + dx, py + dy, 0x0012FD00);
		i++;
	}
}

void	draw_player(t_cub3d *cub)
{
	int	px;
	int	py;

	px = (int)cub->player.pos.x;
	py = (int)cub->player.pos.y;
	draw_direction_line(cub, px, py, 40);
}

void	init_player(t_cub3d *cub)
{
	cub->player.angle = cub->map.angle;
	cub->player.pos.x = cub->map.pos_x;
	cub->player.pos.y = cub->map.pos_y;
}
