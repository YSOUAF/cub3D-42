/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozinedd <mozinedd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 11:42:19 by ysouaf            #+#    #+#             */
/*   Updated: 2025/11/27 19:39:08 by mozinedd         ###   ########.fr       */
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
	map->data[i][j] = '0';
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

void	print_map(char **map_data)
{
	int	i;

	i = 0;
	if (!map_data)
	{
		printf("map_data is NULL\n");
		return ;
	}
	while (map_data[i])
	{
		printf("[%s]\n", map_data[i]);
		i++;
	}
	printf("-- end of map (%d lines) --\n", i);
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

void	cleanup(t_cub3d *cub)
{
	int	i;

	i = 0;
	t_map map = cub->map;
	free_map(&map);
	if (cub->mlx)
	{
		if (cub->img.img)
			mlx_delete_image(cub->mlx, cub->img.img);
		mlx_terminate(cub->mlx);
	}
	
}

static int	inits_map(t_map **map, char *path)
{
	ft_memset(*map, 0, sizeof(t_map));
	if (!allocate_map(path, map) || !(*map)->height)
		return (printf("Error:\ninvalid map - failed to load\n"), 0);
	if (!parss_map((*map)->data))
		return (printf("Error:\ninvalid map - validation failed\n"), 0);
	if (!find_player_position(*map))
		return (printf("Error:\nno player position found in map\n"), 0);
	return (1);
}

int	main(int ac, char **av)
{
	t_map		*map;
	t_cub3d		cub;

	if (ac != 2 || !check_ext(av[1]))
		return (printf("Error:\ninvalid ext or num arg\n"), 1);
	map = malloc(sizeof(t_map));
	if (!map)
		return (printf("Error:\nallocation struct failed\n"), 1);
	if (!inits_map(&map, av[1]))
		return (free_map(map), free(map), 1);
	ft_memset(&cub, 0, sizeof(t_cub3d));
	cub.map = *map;
	init_player(&cub);
	init_mlx(&cub);
	if (!cub.mlx)
	{
		free(map);
		return (printf("Error:\nMLX initialization failed\n"), 1);
	}
	setup_hooks(&cub);
	mlx_loop(cub.mlx);
	cleanup(&cub);
	free(map);
	return (0);
}
