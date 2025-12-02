/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozinedd <mozinedd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 11:42:19 by ysouaf            #+#    #+#             */
/*   Updated: 2025/12/02 21:24:21 by mozinedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_player_angle(t_map *map, char c)
{
	if (c == 'N')
		map->angle = 3 * M_PI_2;
	else if (c == 'S')
		map->angle = M_PI_2;
	else if (c == 'E')
		map->angle = 0;
	else if (c == 'W')
		map->angle = M_PI;
}

static void	set_player_position(t_map *map, int i, int j)
{
	map->posX = (j * TILE_SIZE) + (TILE_SIZE / 2.0);
	map->posY = (i * TILE_SIZE) + (TILE_SIZE / 2.0);
	set_player_angle(map, map->data[i][j]);
}

int	find_player_position(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->data[i])
	{
		j = 0;
		while (map->data[i][j])
		{
			if (map->data[i][j] == 'N' || map->data[i][j] == 'S'
				|| map->data[i][j] == 'E' || map->data[i][j] == 'W')
			{
				set_player_position(map, i, j);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

static int	inits_map(t_map *map, char *path)
{
	ft_memset(map, 0, sizeof(t_map));
	if (!allocate_map(path, map) || !map->height)
		return (printf("Error:\ninvalid map - failed to load\n"), 0);
	if (!parss_map(map->data))
		return (printf("Error:\ninvalid map - validation failed\n"), 0);
	if (!find_player_position(map))
		return (printf("Error:\nno player position found in map\n"), 0);
	return (1);
}

int	main(int ac, char **av)
{
	t_map		*map;
	t_cub3d		*cub;

	if (ac != 2 || !check_ext(av[1]))
		return (printf("Error:\ninvalid ext or num arg\n"), 1);
	map = malloc(sizeof(t_map));
	if (!map)
		return (printf("Error:\nallocation struct failed\n"), 1);
	if (!inits_map(map, av[1]))
		return (free_paths(map), free_map(map), free(map), 1);
	cub = malloc(sizeof(t_cub3d));
	if (!cub)
		return (printf("Error:\nallocation struct failed\n"),
			free_map(map), free(map), 1);
	ft_memset(cub, 0, sizeof(t_cub3d));
	cub->map = *map;
	if (!load_texture(cub))
		return (cleanup(cub), 1);
	init_player(cub);
	if (!init_mlx(cub))
		return (printf("Error:\nMLX initialization failed\n"), cleanup(cub), 1);
	setup_hooks(cub);
	mlx_loop(cub->mlx);
	cleanup(cub);
	return (0);
}
