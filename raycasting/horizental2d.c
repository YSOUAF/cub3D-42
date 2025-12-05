/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizental2d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouaf <ysouaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 16:11:06 by ysouaf            #+#    #+#             */
/*   Updated: 2025/12/05 16:11:07 by ysouaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_hor(t_cub3d *cub, double a, t_point *cur, t_point *step)
{
	cur->y = floor(cub->player.pos.y / TILE_SIZE) * TILE_SIZE;
	if (is_ray_facing_down(a))
		cur->y += TILE_SIZE;
	cur->x = cub->player.pos.x + (cur->y - cub->player.pos.y) / tan(a);
	step->y = TILE_SIZE;
	if (is_ray_facing_up(a))
		step->y *= -1;
	step->x = step->y / tan(a);
	if (is_ray_facing_left(a) && step->x > 0)
		step->x *= -1;
	if (is_ray_facing_right(a) && step->x < 0)
		step->x *= -1;
}

t_point	find_hor_inter(t_cub3d *cub, double a, int *found)
{
	t_point	inter;
	t_point	cur;
	t_point	step;
	t_point	map;

	*found = 0;
	inter.x = -1;
	inter.y = -1;
	init_hor(cub, a, &cur, &step);
	while (cur.x >= 0 && cur.x < WIN_W && cur.y >= 0 && cur.y < WIN_H)
	{
		map.x = cur.x / TILE_SIZE;
		map.y = cur.y / TILE_SIZE;
		if (is_ray_facing_up(a))
			map.y--;
		if (is_wall(cub, map.x, map.y))
		{
			inter = cur;
			*found = 1;
			break ;
		}
		cur.x += step.x;
		cur.y += step.y;
	}
	return (inter);
}
