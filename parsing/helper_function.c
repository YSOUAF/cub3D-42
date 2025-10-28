/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozinedd <mozinedd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 22:32:34 by mozinedd          #+#    #+#             */
/*   Updated: 2025/10/13 22:35:06 by mozinedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*remove_newline(char *line)
{
	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	return (line);
}

int check_ext(char *str)
{
	int len;
	
	len = ft_strlen(str);
	if (ft_strncmp((str + (len - 4)), ".cub", 4) != 0)
		return (0);
	return (1);
}

int	is_char_or_zero(char c)
{
	if (c == '0' || c == 'N' || c == 'W' || c == 'S' || c == 'E')
		return (1);
	return (0);
}