/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozinedd <mozinedd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:18:43 by mozinedd          #+#    #+#             */
/*   Updated: 2025/02/20 15:57:28 by mozinedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	chek(int fd)
{
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) == -1)
		return (1);
	return (-1);
}

static int	allocation(char **buf)
{
	*buf = (char *)malloc(((size_t)BUFFER_SIZE + 1) * sizeof(char));
	if (!*buf)
		return (1);
	return (-1);
}

static char	*extract_left(char *left_ch)
{
	size_t	i;
	char	*new_left_char;

	i = 0;
	while (left_ch[i] != '\0' && left_ch[i] != '\n')
		i++;
	if (left_ch[i] == '\n')
		i++;
	new_left_char = ft_strsub(left_ch, i, ft_lenstr(left_ch) - i);
	free (left_ch);
	left_ch = NULL;
	if (!new_left_char)
		return (NULL);
	return (new_left_char);
}

static char	*extract_line(char *buffer)
{
	int		i;
	char	*line;

	i = 0;
	if (buffer == NULL || buffer[0] == '\0')
		return (NULL);
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = ft_strsub(buffer, 0, i);
	if (!line)
		return (NULL);
	return (line);
}

char	*get_next_line(int fd)
{
	ssize_t		bytes;
	char		*line;
	char		*buf;
	static char	*rest;

	if (chek(fd) == 1 || allocation(&buf) == 1)
		return (free(rest), rest = NULL, NULL);
	bytes = 1;
	while (bytes > 0)
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes == -1)
			return (free(buf), free(rest), buf = NULL, rest = NULL, NULL);
		buf[bytes] = '\0';
		rest = ft_joinstr(rest, buf);
		if (ft_chrstr(buf, '\n'))
			break ;
	}
	free (buf);
	buf = NULL;
	line = extract_line(rest);
	if (line == NULL)
		return (free(rest), rest = NULL, NULL);
	rest = extract_left(rest);
	return (line);
}
