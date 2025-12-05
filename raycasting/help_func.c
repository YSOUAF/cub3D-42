/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouaf <ysouaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 16:13:15 by ysouaf            #+#    #+#             */
/*   Updated: 2025/12/05 16:13:16 by ysouaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	normlize_angle(double angle)
{
	while (angle < 0)
		angle += 2 * M_PI;
	while (angle >= 2 * M_PI)
		angle -= 2 * M_PI;
	return (angle);
}

double	calculate_distance(t_point p1, t_point p2)
{
	double	dx;
	double	dy;

	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	return (sqrt(dx * dx + dy * dy));
}

int	is_wall(t_cub3d *cub, int map_x, int map_y)
{
	if (map_x < 0 || map_x >= cub->map.width)
		return (1);
	if (map_y < 0 || map_y >= cub->map.height)
		return (1);
	if (cub->map.data[map_y][map_x] == '1')
		return (1);
	return (0);
}
