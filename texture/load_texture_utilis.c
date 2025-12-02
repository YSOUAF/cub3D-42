/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture_utilis.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozinedd <mozinedd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 21:19:08 by mozinedd          #+#    #+#             */
/*   Updated: 2025/12/02 21:20:08 by mozinedd         ###   ########.fr       */
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

int	load_texture(t_cub3d *data)
{
	if (!data->map.path_no || !data->map.path_so
		|| !data->map.path_we || !data->map.path_ea)
	{
		printf("Error:\nFailed load texture");
		return (0);
	}
	data->tex_no = mlx_load_png(data->map.path_no);
	if (!data->tex_no)
		return (printf("Error:\nFailed load texture"), 0);
	data->tex_so = mlx_load_png(data->map.path_so);
	if (!data->tex_so)
		return (printf("Error:\nFailed load texture"), 0);
	data->tex_we = mlx_load_png(data->map.path_we);
	if (!data->tex_we)
		return (printf("Error:\nFailed load texture"), 0);
	data->tex_ea = mlx_load_png(data->map.path_ea);
	if (!data->tex_ea)
		return (printf("Error:\nFailed load texture"), 0);
	return (1);
}
