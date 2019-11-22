/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flogan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 10:50:31 by flogan            #+#    #+#             */
/*   Updated: 2019/09/08 22:14:58 by flogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *destination, int c, size_t n)
{
	unsigned char	*v;
	size_t			i;

	i = 0;
	v = (unsigned char*)destination;
	while (i < n)
		v[i++] = c;
	return (destination);
}
