/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouaf <ysouaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 11:36:47 by ysouaf            #+#    #+#             */
/*   Updated: 2025/11/26 11:36:53 by ysouaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_mlx(t_cub3d *cub)
{
	cub->mlx = mlx_init(WIN_W, WIN_H, "cube3d", false);
	cub->img.img = mlx_new_image(cub->mlx, WIN_W, WIN_H);
	cub->img.img_mini = mlx_new_image(cub->mlx, 400, 200);
}
