/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozinedd <mozinedd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 21:40:37 by mozinedd          #+#    #+#             */
/*   Updated: 2025/10/17 17:01:10 by mozinedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

int	is_map_star(char *line)
{
	int i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] =='\0' || line[i] == '\n')
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



int	map_line(char *map, t_map **cub)
{
	int 	fd;
	char 	*line;
	int		map_star;
	
	if (!map || !cub || !*cub)
		return (0);
	map_star = 0;
	fd = open(map, O_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	(*cub)->width = 0;
	while (line)
	{
		if (is_map_star(line) == 1 && map_star == 0)
			map_star = 1;
		if (is_map_star(line) == 0 && map_star == 0)
		{
			if (!parse_texture(remove_newline(line), *(cub)))
			{
				free(line);
				return(close(fd), 0);
			}
			line = get_next_line(fd);
			continue;
		}
		if (!check_character(line))
		{
			free(line);
			return (close(fd), 0);
		}
		if (ft_strlen(line) > (size_t)(*cub)->width)
			(*cub)->width = ft_strlen(line);
		free(line);
		line = get_next_line(fd);
		(*cub)->height++;
	}
	close (fd);
	return (1);
}

char	*new_line(char *line, t_map **data)
{
	size_t	i;
	char	*new_line;

	i = 0;
	new_line = malloc((size_t)(*data)->width + 1);
	if (!new_line)
		return (NULL);
	line = remove_newline(line);
	if (line[0] == '\0')
		return (NULL);
	while (i < ft_strlen(line))
	{
		new_line[i] = line[i];
		i++;
	}
	if ((int)i < (*data)->width)
	{
		while ((int)i < (*data)->width - 1)
		{
			new_line[i] = ' ';
			i++;
		}
	}
	new_line[i] = '\0';
	return (new_line);
}

int	 allocate_map(char *map, t_map **data)
{
	int		fd;
	int		i;
	char	*line;
	int		map_star;

	map_star = 0;
	i = 0;
	(*data)->color_c = -1;
	(*data)->color_f = -1;
	if (!map_line(map, data))
		return (printf("Error :\ninvalid map\n"), 0);
	if ((*data)->color_c == -1 || (*data)->color_f == -1 || !(*data)->path_ea || !(*data)->path_no || !(*data)->path_so || !(*data)->path_we )
		return (0);
	(*data)->data = malloc(sizeof(char *) * ((*data)->height + 1));
	if (!(*data)->data)
		return (0);
	fd = open(map, O_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	while (line)
	{
		if (is_map_star(line) == 1 && map_star == 0)
			map_star = 1;
		if (is_map_star(line) == 0 && map_star == 0)
		{
			line = get_next_line(fd);
			continue;
		}
		
		(*data)->data[i] = new_line(line, data);
		if (!(*data)->data[i])
			return (close(fd), 0);
		i++;
		free(line);
		line = get_next_line(fd);
	}
	(*data)->data[(*data)->height] = NULL;
	close (fd);
	return (1);
}

