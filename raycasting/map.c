/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouaf <ysouaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 16:34:19 by ysouaf            #+#    #+#             */
/*   Updated: 2025/12/05 16:34:20 by ysouaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_background(t_cub3d *cub)
{
	size_t	x;
	size_t	y;
	int		color;

	x = 0;
	while (x < WIN_W)
	{
		y = 0;
		while (y < WIN_H)
		{
			if (y <= WIN_H / 2)
				color = cub->map.color_c;
			else
				color = cub->map.color_f;
			mlx_put_pixel(cub->img.img, x, y, color);
			y++;
		}
		x++;
	}
}

void	render_map(void *ptr)
{
	t_cub3d	*cub;

	cub = (t_cub3d *)ptr;
	update_player_position(cub);
	draw_background(cub);
	cast_all_rays(cub);
	mlx_image_to_window(cub->mlx, cub->img.img, 0, 0);
}
