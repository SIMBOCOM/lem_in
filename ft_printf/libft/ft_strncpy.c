/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flogan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 21:18:31 by flogan            #+#    #+#             */
/*   Updated: 2019/09/05 15:40:49 by flogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *destptr, const char *srcptr, size_t num)
{
	size_t i;

	i = 0;
	while (srcptr[i] && i < num)
	{
		destptr[i] = srcptr[i];
		i++;
	}
	while (i < num)
	{
		destptr[i] = '\0';
		i++;
	}
	return (destptr);
}
