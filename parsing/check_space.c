/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozinedd <mozinedd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 15:40:17 by mozinedd          #+#    #+#             */
/*   Updated: 2025/11/28 15:50:49 by mozinedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_space(char **map, int y, int x)
{
	if (is_char_or_zero(map[y][x]))
	{
		if (!map[y - 1] || map[y - 1][x] == ' ')
			return (0);
		if (!map[y + 1] || map[y + 1][x] == ' ')
			return (0);
		if (map[y][x - 1] == ' ')
			return (0);
		if (map[y][x + 1] == '\0' || map[y][x + 1] == ' ')
			return (0);
	}
	return (1);
}

int	check_space_in_map(char **map)
{
	int	y;
	int	x;

	y = 1;
	while (map[y] && map[y + 1])
	{
		x = 0;
		while (map[y][x])
		{
			if (!check_space(map, y, x))
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

int	parss_map(char **map)
{
	if (!check_walls(map))
		return (0);
	if (check_num_character(map) != 1)
		return (0);
	if (!check_space_in_map(map))
		return (0);
	return (1);
}

int	is_map_star(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] == '\0' || line[i] == '\n')
		return (0);
	while (line[i] && line[i] != '\n')
	{
		if (line[i] == '1' || line[i] == '0' || line[i] == 'N'
			|| line[i] == 'W' || line[i] == 'S' || line[i] == 'E')
			i++;
		else
			return (0);
	}
	return (1);
}

int	check_character(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != 'N'
			&& line[i] != 'W' && line[i] != 'S' && line[i] != 'E'
			&& line[i] != ' ' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}
