/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozinedd <mozinedd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:43:16 by mozinedd          #+#    #+#             */
/*   Updated: 2025/01/22 18:23:19 by mozinedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_joinstr(char *s1, char *s2)
{
	int		i;
	int		j;
	int		lentofs1s2;
	char	*allstr;

	i = 0;
	j = 0;
	if (!s1)
		return (free(s1), s1 = NULL, ft_dupstr(s2));
	lentofs1s2 = ft_lenstr(s1) + ft_lenstr(s2);
	allstr = malloc(lentofs1s2 + 1);
	if (!allstr)
		return (free(s1), s1 = NULL, NULL);
	while (s1 != NULL && s1[i])
	{
		allstr[j++] = s1[i++];
	}
	i = 0;
	while (s2 != NULL && s2[i])
	{
		allstr[j++] = s2[i++];
	}
	allstr[j] = '\0';
	return (free(s1), s1 = NULL, allstr);
}

char	*ft_strsub(char *s, unsigned int start, size_t len)
{
	size_t			i;
	char			*substr;
	unsigned int	sizeofs;
	unsigned int	lent;

	if (!s)
		return (NULL);
	sizeofs = (unsigned int)ft_lenstr(s);
	lent = (unsigned int ) len;
	if (start > sizeofs || sizeofs == 0)
		return (ft_dupstr(""));
	if (lent > sizeofs - start)
		lent = sizeofs - start;
	substr = (char *)malloc(lent + 1);
	if (substr == NULL)
		return (NULL);
	i = 0;
	while (i < lent)
	{
		substr[i] = s[start];
		i++;
		start++;
	}
	substr[i] = '\0';
	return (substr);
}

size_t	ft_lenstr(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_chrstr(char *s, int c)
{
	size_t			i;
	unsigned char	ch;

	ch = (unsigned char) c;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == ch)
		{
			return ((char *)&s[i]);
		}
		i++;
	}
	if (ch == '\0' && s[i] == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

char	*ft_dupstr(char *s1)
{
	int		i;
	int		len;
	char	*copys1;
	char	*src;

	len = ft_lenstr(s1) + 1;
	src = (char *) s1;
	copys1 = (char *) malloc(len);
	if (copys1 == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		copys1[i] = src[i];
		i++;
	}
	return (copys1);
}
