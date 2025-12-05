/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical2d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouaf <ysouaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 16:00:11 by ysouaf            #+#    #+#             */
/*   Updated: 2025/12/05 16:00:12 by ysouaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_vert_inter(t_cub3d *cub, double a, t_point *cur, t_point *step)
{
	cur->x = floor(cub->player.pos.x / TILE_SIZE) * TILE_SIZE;
	if (is_ray_facing_right(a))
		cur->x += TILE_SIZE;
	cur->y = (tan(a) * (cur->x - cub->player.pos.x)) + cub->player.pos.y;
	if (is_ray_facing_left(a))
		step->x = -TILE_SIZE;
	else
		step->x = TILE_SIZE;
	step->y = step->x * tan(a);
	if (is_ray_facing_up(a) && step->y > 0)
		step->y *= -1;
	if (is_ray_facing_down(a) && step->y < 0)
		step->y *= -1;
}

static int	check_vert_wall(t_cub3d *cub, t_point cur, double a, t_point *inter)
{
	t_point	map;

	if (is_ray_facing_left(a))
		map.x = cur.x / TILE_SIZE - 1;
	else
		map.x = cur.x / TILE_SIZE;
	map.y = cur.y / TILE_SIZE;
	if (is_wall(cub, map.x, map.y))
	{
		*inter = cur;
		return (1);
	}
	return (0);
}

t_point	find_vert_inter(t_cub3d *cub, double a, int *found)
{
	t_point	inter;
	t_point	cur;
	t_point	step;

	*found = 0;
	inter.x = -1;
	inter.y = -1;
	init_vert_inter(cub, a, &cur, &step);
	while (cur.x >= 0 && cur.x < WIN_W && cur.y >= 0 && cur.y < WIN_H)
	{
		if (check_vert_wall(cub, cur, a, &inter))
		{
			*found = 1;
			break ;
		}
		cur.x += step.x;
		cur.y += step.y;
	}
	return (inter);
}
