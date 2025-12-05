/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_mov2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouaf <ysouaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 15:51:49 by ysouaf            #+#    #+#             */
/*   Updated: 2025/12/05 15:51:53 by ysouaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_player_position(t_cub3d *cub)
{
	double	nx;
	double	ny;
	double	px;
	double	py;

	px = cub->player.pos.x;
	py = cub->player.pos.y;
	nx = px;
	ny = py;
	handle_forward_backward(cub, &nx, &ny);
	handle_strafe(cub, &nx, &ny);
	handle_rotation(cub);
	if (is_valid_position(cub, nx, py))
		cub->player.pos.x = nx;
	if (is_valid_position(cub, px, ny))
		cub->player.pos.y = ny;
}
