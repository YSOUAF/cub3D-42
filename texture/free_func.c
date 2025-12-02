/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozinedd <mozinedd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 21:23:42 by mozinedd          #+#    #+#             */
/*   Updated: 2025/12/02 21:25:36 by mozinedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_arr(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_map(t_map *map)
{
	int		i;

	i = 0;
	if (!map || !map->data)
		return ;
	while (map->data[i])
	{
		free(map->data[i]);
		i++;
	}
	free(map->data);
}

void	free_paths(t_map *map)
{
	free(map->path_ea);
	free(map->path_no);
	free(map->path_so);
	free(map->path_we);
}

void	cleanup(t_cub3d *cub)
{
	t_map	map;
	int		i;

	i = 0;
	map = cub->map;
	free_map(&map);
	if (cub->mlx)
	{
		if (cub->img.img)
			mlx_delete_image(cub->mlx, cub->img.img);
		mlx_terminate(cub->mlx);
	}
	free_paths(&map);
	destroy_texture(cub);
	free(cub);
}
