/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_tex_fc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozinedd <mozinedd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 17:28:56 by mozinedd          #+#    #+#             */
/*   Updated: 2025/10/28 20:07:50 by mozinedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	prgba(uint32_t r, uint32_t g, uint32_t b, uint32_t a)
{
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

int	char_count(char *line, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == c)
			count++;
		i++;
	}
	return (count);
}

int	parse_color(char *line, t_map *map)
{
	uint32_t	r;
	uint32_t	g;
	uint32_t	b;
	uint32_t	alpha;
	char		**splited_str;
	char		**rgb;

	splited_str = ft_split(line, ' ');
	alpha = 255;
	rgb = ft_split(splited_str[1], ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || char_count(line, ',') > 2)
		return (printf("Error\ninvalid format\n"), 0);
	r = valid_num(rgb[0]);
	g = valid_num(rgb[1]);
	b = valid_num(rgb[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (printf("Error\ninvalid valu RGB\n"), 0);
	if (ft_strncmp(splited_str[0], "F", 1) == 0)
		map->color_f = prgba(r, g, b, alpha);
	else if (ft_strncmp(splited_str[0], "C", 1) == 0)
		map->color_c = prgba(r, g, b, alpha);
	return (1);
}

int	parse_texture(char *line, t_map *conf)
{
	char	**splite_str;
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '\0')
		return (1);
	splite_str = ft_split(&line[i], ' ');
	if (count(line, ' ') != 2)
		return (0);
	if (!conf->path_no && ft_strncmp(&line[i], "NO ", 3) == 0)
		conf->path_no = splite_str[1];
	else if (!conf->path_so && ft_strncmp(&line[i], "SO ", 3) == 0)
		conf->path_so = splite_str[1];
	else if (!conf->path_we && ft_strncmp(&line[i], "WE ", 3) == 0)
		conf->path_we = splite_str[1];
	else if (!conf->path_ea && ft_strncmp(&line[i], "EA ", 3) == 0)
		conf->path_ea = splite_str[1];
	else if (conf->color_f == -1 && ft_strncmp(&line[i], "F ", 2) == 0)
		parse_color(&line[i], conf);
	else if (conf->color_c == -1 && ft_strncmp(line, "C ", 2) == 0)
		parse_color(&line[i], conf);
	else
		return (0);
	return (1);
}
