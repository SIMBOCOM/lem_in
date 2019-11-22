/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flogan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 20:40:21 by flogan            #+#    #+#             */
/*   Updated: 2019/09/08 16:34:32 by flogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *memptr, int val, size_t num)
{
	size_t i;

	i = 0;
	while (i < num)
	{
		if (((unsigned char*)memptr)[i] == (unsigned char)val)
			return ((unsigned char*)memptr + i);
		i++;
	}
	return (NULL);
}
