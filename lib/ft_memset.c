/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozinedd <mozinedd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 15:53:44 by mozinedd          #+#    #+#             */
/*   Updated: 2025/10/11 15:54:14 by mozinedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	h;
	unsigned char	*as;

	h = (unsigned char)c;
	as = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		as[i] = h;
		i++;
	}
	return (as);
}
