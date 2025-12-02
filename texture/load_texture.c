/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozinedd <mozinedd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 19:52:22 by mozinedd          #+#    #+#             */
/*   Updated: 2025/12/02 21:19:57 by mozinedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

mlx_texture_t	*choose_tex(t_ray ray, t_cub3d *data)
{
	if (ray.is_vertical)
	{
		if (ray.drction == NORTH)
			return (data->tex_no);
		else
			return (data->tex_so);
	}
	else
	{
		if (ray.drction == EAST)
			return (data->tex_ea);
		else
			return (data->tex_we);
	}
}

int	find_textur_x(mlx_texture_t *tex, t_ray ray)
{
	int		textur_x;
	double	modelu;

	if (ray.is_vertical)
		modelu = fmod(ray.hit_point.y, (double)TILE_SIZE);
	else
		modelu = fmod(ray.hit_point.x, (double)TILE_SIZE);
	textur_x = (int)((modelu / (double)TILE_SIZE) * (double)tex->width);
	if (textur_x < 0)
		textur_x = 0;
	if (textur_x >= (int)tex->width)
		textur_x = (int)tex->width - 1;
	return (textur_x);
}

uint32_t	sample_rgba(mlx_texture_t *tex, int x, int y)
{
	uint8_t	*p;

	p = tex->pixels + (y * tex->width + x) * tex->bytes_per_pixel;
	return (prgba(p[0], p[1], p[2], p[3]));
}

void	put_pixel(t_cub3d *cub, int x, int y, int color)
{
	if (x < 0 || y < 0 || x >= WIN_W || y >= WIN_H)
		return ;
	mlx_put_pixel(cub->img.img, x, y, color);
}

void	draw_walls(t_cub3d *cub, int screen_x, double line_height)
{
	t_draw_wals	dr;

	dr.wall_top = (WIN_H / 2) - (line_height / 2);
	dr.wall_buttom = dr.wall_top + line_height;
	dr.top = (int)dr.wall_top;
	dr.buttom = (int)dr.wall_buttom;
	dr.tex = choose_tex(cub->ray, cub);
	dr.tx = find_textur_x(dr.tex, cub->ray);
	dr.y = dr.top;
	while (dr.y < dr.buttom)
	{
		dr.from_top = (double)dr.y - dr.wall_top;
		dr.calc = dr.from_top / line_height;
		dr.ty = (int)(dr.calc * (double)dr.tex->height);
		if (dr.ty < 0)
			dr.ty = 0;
		if (dr.ty >= (int)dr.tex->height)
			dr.ty = (int)dr.tex->height - 1;
		dr.color = sample_rgba(dr.tex, dr.tx, dr.ty);
		if (screen_x < 0)
			screen_x = 0;
		put_pixel(cub, screen_x, dr.y, dr.color);
		dr.y++;
	}
}
