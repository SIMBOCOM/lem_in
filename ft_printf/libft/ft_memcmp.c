/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flogan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 20:55:04 by flogan            #+#    #+#             */
/*   Updated: 2019/09/05 23:52:23 by flogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *mem1, const void *mem2, size_t num)
{
	size_t i;

	i = 0;
	while (i < num)
	{
		if (((unsigned char*)mem1)[i] != ((unsigned char*)mem2)[i])
			return (((unsigned char*)mem1)[i] - ((unsigned char*)mem2)[i]);
		i++;
	}
	return (0);
}
