/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozinedd <mozinedd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 15:38:15 by mozinedd          #+#    #+#             */
/*   Updated: 2025/12/02 21:27:45 by mozinedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*pointer;
	pointer = malloc(count * size);
	if (pointer == NULL)
		return (NULL);
	ft_memset(pointer, 0, (count * size));
	return (pointer);
}
