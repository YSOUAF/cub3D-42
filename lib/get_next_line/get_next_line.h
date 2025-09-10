/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozinedd <mozinedd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:42:36 by mozinedd          #+#    #+#             */
/*   Updated: 2025/02/20 16:16:50 by mozinedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

char	*ft_joinstr(char *s1, char *s2);
char	*ft_strsub(char *s, unsigned int start, size_t len);
size_t	ft_lenstr(char *s);
char	*ft_chrstr(char *s, int c);
char	*ft_dupstr(char *s1);
char	*get_next_line(int fd);

#endif