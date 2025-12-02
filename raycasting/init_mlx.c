/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozinedd <mozinedd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 11:36:47 by ysouaf            #+#    #+#             */
/*   Updated: 2025/12/02 21:11:30 by mozinedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_mlx(t_cub3d *cub)
{
	cub->mlx = mlx_init(WIN_W, WIN_H, "cube3d", false);
	if (!cub->mlx)
		return (0);
	cub->img.img = mlx_new_image(cub->mlx, WIN_W, WIN_H);
	if (!cub->img.img)
		return (0);
	cub->img.img_mini = mlx_new_image(cub->mlx, 400, 200);
	if (!cub->img.img_mini)
		return (0);
	return (1);
}
