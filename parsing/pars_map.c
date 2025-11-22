/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozinedd <mozinedd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:44:32 by mozinedd          #+#    #+#             */
/*   Updated: 2025/10/15 16:15:57 by mozinedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_line_start(char *line)
{
	int	j;

	j = 0;
	while (line[j] == ' ')
		j++;
	if (line[j] != '1' && line[j] != '\0')
		return (0);
	return (1);
}

int	check_line_end(char *line)
{
	int	j;

	j = ft_strlen(line) - 1;
	while (j >= 0 && line[j] == ' ')
		j--;
	if (line[j] != '1' && line[j] != ' ')
		return (0);
	return (1);
}

int	check_walls(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		if (!check_line_start(map[i]) || !check_line_end(map[i]))
			return (0);
		while (map[i][j])
		{
			if ((i == 0 || !map[i + 1]) && (map[i][j] != '1' && map[i][j] != ' '))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int check_num_character(char **map)
{
	int i;
	int j;
	int sum;
	
	i = 0;
	sum = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'W' || map[i][j] == 'S' || map[i][j] == 'E')
				sum++;
			j++;
		}
		i++;
	}
	return (sum);
}

int check_space(char **map, int y, int x)
{
	if (is_char_or_zero(map[y][x]))
	{
		if (!map[y-1] || map[y-1][x] == ' ')
			return (printf("check1\n"), 0);
		if (!map[y+1] || map[y+1][x] == ' ')
			return (printf("check2\n"), 0);
		if (map[y][x-1] == ' ')
			return (printf("check3\n"), 0);
		if (map[y][x+1] == '\0' || map[y][x+1] == ' ')
			return (printf("check4\n"), 0);
	}
	return (1);
}

int	check_space_in_map(char **map)
{
	int y;
	int x;

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
		return (printf("hello11\n"), 0);
	if (check_num_character(map) != 1 )
		return (printf("hello22\n"), 0);
	if (!check_space_in_map(map))
		return (printf("hello33\n"), 0);
	return (1);
}

