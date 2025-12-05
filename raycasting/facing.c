/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   facing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouaf <ysouaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 16:14:17 by ysouaf            #+#    #+#             */
/*   Updated: 2025/12/05 16:14:18 by ysouaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	max_ray_distance(double angle)
{
	return ((double)(WIN_W / 2) / tan(angle));
}

int	is_ray_facing_down(double angle)
{
	if (angle > 0 && angle < M_PI)
		return (1);
	return (0);
}

int	is_ray_facing_up(double angle)
{
	if (is_ray_facing_down(angle))
		return (0);
	return (1);
}

int	is_ray_facing_right(double angle)
{
	if (angle < (0.5 * M_PI) || angle > (1.5 * M_PI))
		return (1);
	return (0);
}

int	is_ray_facing_left(double angle)
{
	if (is_ray_facing_right(angle))
		return (0);
	return (1);
}
