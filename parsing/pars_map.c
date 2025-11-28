/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozinedd <mozinedd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:44:32 by mozinedd          #+#    #+#             */
/*   Updated: 2025/11/28 15:41:35 by mozinedd         ###   ########.fr       */
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
	if (line[j] != '1' && line[j] != ' ' && j > 0)
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
		if (!check_line_start(map[i]))
			return (0);
		if (!check_line_end(map[i]))
			return (0);
		while (map[i][j])
		{
			if ((i == 0 || !map[i + 1]) && (map[i][j] != '1'
				&& map[i][j] != ' '))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	check_num_character(char **map)
{
	int	i;
	int	j;
	int	sum;

	i = 0;
	sum = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'W'
				|| map[i][j] == 'S' || map[i][j] == 'E')
				sum++;
			j++;
		}
		i++;
	}
	return (sum);
}
