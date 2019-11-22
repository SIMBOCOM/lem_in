/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flogan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 16:02:24 by flogan            #+#    #+#             */
/*   Updated: 2019/09/05 20:41:01 by flogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *destination, const void *source, int c, size_t n)
{
	size_t i;

	i = 0;
	while (i < n)
	{
		((unsigned char*)destination)[i] = ((unsigned char*)source)[i];
		if (((unsigned char*)destination)[i] == (unsigned char)c)
			return ((unsigned char*)destination + i + 1);
		i++;
	}
	return (NULL);
}
