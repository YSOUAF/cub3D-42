/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozinedd <mozinedd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 19:52:22 by mozinedd          #+#    #+#             */
/*   Updated: 2025/11/30 18:40:01 by mozinedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	destroy_texture(t_cub3d *data)
{
	if (data->tex_no)
	{
		mlx_delete_texture(data->tex_no);
		data->tex_no = NULL;
	}
	if (data->tex_so)
	{
		mlx_delete_texture(data->tex_so);
		data->tex_so = NULL;
	}
	if (data->tex_we)
	{
		mlx_delete_texture(data->tex_we);
		data->tex_we = NULL;
	}
	if (data->tex_ea)
	{
		mlx_delete_texture(data->tex_ea);
		data->tex_ea = NULL;
	}
}
int load_texture(t_cub3d *data)
{
	if (!data->map.path_no || !data->map.path_so || !data->map.path_we || !data->map.path_ea )
	{
		printf("failed load texture");
		return (0);
	}
	data->tex_no = mlx_load_png(data->map.path_no);
	if (!data->tex_no)
		return (destroy_texture(data), 0);
	data->tex_so = mlx_load_png(data->map.path_so);
	if (!data->tex_so)
		return (destroy_texture(data), 0);
		
	data->tex_we = mlx_load_png(data->map.path_we);
	if (!data->tex_we)
		return (destroy_texture(data), 0);
	data->tex_ea = mlx_load_png(data->map.path_ea);
	if (!data->tex_ea)
		return (destroy_texture(data), 0);
	return (1);
}


mlx_texture_t   *choose_tex(t_ray ray, t_cub3d *data)
{
    mlx_texture_t *tex = NULL;

    if (ray.is_vertical)
        tex = (ray.drction == NORTH) ? data->tex_no : data->tex_so;
    else
        tex = (ray.drction == EAST) ? data->tex_ea : data->tex_we;

    // CRITICAL CHECK: If texture loading failed, this prevents a crash.
    // You should have already exited gracefully in main if textures failed,
    // but this is a final defensive check.
    if (tex == NULL)
    {
        // Handle error (e.g., return a default placeholder texture, or log an error)
        fprintf(stderr, "Error: Selected texture is NULL for direction %d.\n", ray.drction);
        // In a production environment, you would typically exit or return a default texture here.
        // Since this is a SEGV, your main loop is running with failed textures.
        exit(1); // Exit gracefully if you know the texture should be loaded.
    }
    return (tex);
}

int	find_textur_x(mlx_texture_t *tex, t_ray ray)
{
	int 	textur_x;
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

void	draw_walls(t_cub3d *cub, int screen_x, double line_height)
{
	double wall_top;
	double wall_buttom;
	mlx_texture_t *tex;
	int tx;
	int y;
	int top;
	int buttom;
	double	from_top;
	int	ty;
	uint32_t color;

	wall_top = (WIN_H / 2) - (line_height / 2);
	wall_buttom = wall_top + line_height;
	top = (int)wall_top;
	buttom = (int)wall_buttom;
	
	tex = choose_tex(cub->ray, cub);
	tx = find_textur_x(tex, cub->ray);
	y = top;
	while (y < buttom)
	{
		from_top = (double)y - wall_top;
		double calc = from_top / line_height;
		ty = (int)(calc * (double)tex->height);
		color = sample_rgba(tex, tx, ty);
		mlx_put_pixel(cub->img.img, screen_x, y, color);
		printf("%d\n", (int)tex->height);
		y++;
	}
}
