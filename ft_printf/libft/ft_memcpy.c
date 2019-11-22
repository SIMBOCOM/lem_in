/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flogan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 15:31:24 by flogan            #+#    #+#             */
/*   Updated: 2019/09/05 15:33:37 by flogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *destination, const void *source, size_t n)
{
	size_t i;

	i = 0;
	if (destination == NULL && source == NULL)
		return (NULL);
	while (i < n)
	{
		((unsigned char*)destination)[i] = ((unsigned char*)source)[i];
		i++;
	}
	return (destination);
}
