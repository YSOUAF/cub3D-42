/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_rays.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouaf <ysouaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 15:38:05 by ysouaf            #+#    #+#             */
/*   Updated: 2025/12/05 15:45:00 by ysouaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_hor_hit(t_cub3d *cub, double d, t_point hit, double ang)
{
	cub->ray.distance = d;
	cub->ray.hit_point = hit;
	cub->ray.hit_wall = 1;
	cub->ray.is_vertical = 0;
	if (sin(ang) < 0)
		cub->ray.drction = NORTH;
	else
		cub->ray.drction = SOUTH;
}

static void	set_ver_hit(t_cub3d *cub, double d, t_point hit, double ang)
{
	cub->ray.distance = d;
	cub->ray.hit_point = hit;
	cub->ray.hit_wall = 1;
	cub->ray.is_vertical = 1;
	if (cos(ang) > 0)
		cub->ray.drction = EAST;
	else
		cub->ray.drction = WEST;
}

static void	select_hit(t_cub3d *cub, t_point hor, t_point ver,
		double angle)
{
	double	hd;
	double	vd;

	hd = 0;
	vd = 0;
	if (cub->flags.hor_found)
		hd = calculate_distance(cub->player.pos, hor);
	if (cub->flags.ver_found)
		vd = calculate_distance(cub->player.pos, ver);
	if (cub->flags.hor_found && (!cub->flags.ver_found || hd < vd))
		set_hor_hit(cub, hd, hor, angle);
	else if (cub->flags.ver_found)
		set_ver_hit(cub, vd, ver, angle);
}

void	cast_ray(t_cub3d *cub, double angle)
{
	t_point	hor;
	t_point	ver;

	cub->ray.hit_wall = 0;
	angle = normlize_angle(angle);
	cub->ray.angle = angle;
	hor = find_hor_inter(cub, angle, &cub->flags.hor_found);
	ver = find_vert_inter(cub, angle, &cub->flags.ver_found);
	select_hit(cub, hor, ver, angle);
}
