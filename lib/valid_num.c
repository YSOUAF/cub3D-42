/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_num.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozinedd <mozinedd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 16:57:20 by mozinedd          #+#    #+#             */
/*   Updated: 2025/10/14 20:32:56 by mozinedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	valid_num(const char *str)
{
	long	nb;
	size_t	i;

	if (!str || str[0] == '\0')
		return (-1);
	if (!(*str))
		return (-1);
	i = 0;
	nb = 0;
	while (str[i] == ' ')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (-1);
		nb = nb * 10 + (str[i++] - '0');
		if (nb > INT_MAX)
			return (-1);
	}
	return (nb);
}
