/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozinedd <mozinedd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 15:51:36 by mozinedd          #+#    #+#             */
/*   Updated: 2025/10/11 15:52:23 by mozinedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*ft_memcpy(void *dst, const void* src, size_t n)
{
	size_t i;
	unsigned char *dest;
	const char *srrc;
	
	i = 0;
	dest = (unsigned char *) dst;
	srrc = (const char *) src;
	if (dest == (NULL) && srrc == (NULL))
	return (dest);
	while (i < n)
	{
		dest[i] = srrc[i];
		i++;
	}
	return (dest);
	
}
