/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palyer_mov.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouaf <ysouaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 15:51:00 by ysouaf            #+#    #+#             */
/*   Updated: 2025/12/05 15:53:21 by ysouaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_collision(t_cub3d *cub, int cx, int cy)
{
	if (is_wall(cub, (cx - COLLISION_WALL) / TILE_SIZE,
			(cy - COLLISION_WALL) / TILE_SIZE))
		return (0);
	if (is_wall(cub, (cx + COLLISION_WALL) / TILE_SIZE,
			(cy - COLLISION_WALL) / TILE_SIZE))
		return (0);
	if (is_wall(cub, (cx - COLLISION_WALL) / TILE_SIZE,
			(cy + COLLISION_WALL) / TILE_SIZE))
		return (0);
	if (is_wall(cub, (cx + COLLISION_WALL) / TILE_SIZE,
			(cy + COLLISION_WALL) / TILE_SIZE))
		return (0);
	return (1);
}

int	is_valid_position(t_cub3d *cub, double x, double y)
{
	int	cx;
	int	cy;

	cx = (int)x;
	cy = (int)y;
	return (check_collision(cub, cx, cy));
}

void	handle_forward_backward(t_cub3d *cub, double *x, double *y)
{
	double	a;

	a = cub->player.angle;
	if (cub->keys.up || cub->keys.w)
	{
		*x += cos(a) * MOVE_SPEED;
		*y += sin(a) * MOVE_SPEED;
	}
	if (cub->keys.down || cub->keys.s)
	{
		*x -= cos(a) * MOVE_SPEED;
		*y -= sin(a) * MOVE_SPEED;
	}
}

void	handle_strafe(t_cub3d *cub, double *x, double *y)
{
	double	a;

	a = cub->player.angle;
	if (cub->keys.a)
	{
		*x += cos(a - M_PI_2) * MOVE_SPEED;
		*y += sin(a - M_PI_2) * MOVE_SPEED;
	}
	if (cub->keys.d)
	{
		*x += cos(a + M_PI_2) * MOVE_SPEED;
		*y += sin(a + M_PI_2) * MOVE_SPEED;
	}
}

void	handle_rotation(t_cub3d *cub)
{
	if (cub->keys.left)
		cub->player.angle -= ROTATE_SPEED;
	if (cub->keys.right)
		cub->player.angle += ROTATE_SPEED;
	cub->player.angle = normlize_angle(cub->player.angle);
}
