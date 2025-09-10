/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozinedd <mozinedd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:44:32 by mozinedd          #+#    #+#             */
/*   Updated: 2025/08/27 16:17:42 by mozinedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int check_walls(char **map)
{
	int i;
	int j;
	
	i = 0;
	while (map[i])
	{
		j = 0;
		if (map[i][j] != '1')
			return (0);
		while (map[i][j])
		{
			if ((i == 0 || map[i + 1] == NULL ) && map[i][j] != '1')
				return (0);
			j++;
		}
		if (map[i][j - 1] != '1')
			return (0);
		i++;
	}
	return (1);
}

int check_character(char *line)
{
	int i;
	
	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != 'N'
			&& line[i] != 'W' && line[i] != 'S' && line[i] != 'E' && line[i] != ' ' && line[i] != '\n')
			return (0);
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

int check_ext(char *str)
{
	int len;
	
	len = ft_strlen(str);
	if (ft_strncmp((str + (len - 4)), ".cub", 4) != 0)
		return (0);
	return (1);
}

int	map_line(char *map, t_map **cub)
{
	int 	fd;
	char 	*line;
	int		cm;

	cm = 0;
	fd = open(map, O_RDONLY);
	if (fd < 0)
		return (printf("hnaaa22\n"), 0);
	line = get_next_line(fd);
	(*cub)->width = ft_strlen(line);
	while (line)
	{
		if (cm < 7)
		{
			line = get_next_line(fd);
			cm++;
			continue ;
		}
		if (!check_character(line))
			return (printf("hnaaa33\n"), 0);
		if (ft_strlen(line) > (size_t)(*cub)->width)
			(*cub)->width = ft_strlen(line);
		free(line);
		line = get_next_line(fd);
		(*cub)->height++;
	}
	close (fd);
	return (1);
}

char *new_line(char *line, t_map **data)
{
	int	i;
	char *new_line;

	i = 0;
	new_line = malloc(sizeof(char *) *  ((*data)->width));
	if (!new_line)
		return (NULL);
	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	while ((size_t)i < ft_strlen(line))
	{
		new_line[i] = line[i];
		i++;
	}
	if (i < (*data)->width)
	{
		while (i < (*data)->width)
		{
			new_line[i] = ' ';
			i++;
		}
	}
	new_line[i] = '\0';
	return (new_line);
}

int	allocate_map(char *map, t_map **data)
{

	int fd;
	char *line;
	int cm = 1;
	int	i = 0;
	if (!map_line(map, data))
		return (printf("hnaaa11\n"), 0);
	(*data)->data = malloc(sizeof(char *) * ((*data)->height + 1));
	if (!(*data)->data)
		return (printf("hnaaa12\n"), 0);
	fd = open(map, O_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	while (line)
	{
		if (cm < 7 || line[0] == '\n')
		{
			line = get_next_line(fd);
			cm++;
			continue ;
		}
		(*data)->data[i] = new_line(line, data);
		if (!(*data)->data[i])
			return (printf("hnaaa13\n"), 0);
		i++;
		free(line);
		line = get_next_line(fd);
	}
	(*data)->data[(*data)->height] = NULL;
	close (fd);
	return (1);
}
