/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_rays2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouaf <ysouaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 15:45:03 by ysouaf            #+#    #+#             */
/*   Updated: 2025/12/05 15:46:53 by ysouaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_ray(t_cub3d *cub, int x)
{
	double	angle_diff;
	double	win_d;
	double	h;

	angle_diff = fabs(cub->ray.angle - cub->player.angle);
	win_d = (WIN_W / 2.0) / tan(FOV / 2.0);
	h = (win_d / cos(angle_diff)) * TILE_SIZE;
	h /= cub->ray.distance;
	draw_walls(cub, x, h);
}

void	cast_all_rays(t_cub3d *cub)
{
	double	ray_angle;
	double	step;
	int		x;

	step = FOV / WIN_W;
	ray_angle = cub->player.angle - (FOV / 2);
	x = 0;
	while (x < WIN_W)
	{
		cast_ray(cub, ray_angle);
		draw_ray(cub, x);
		ray_angle += step;
		x++;
	}
}
