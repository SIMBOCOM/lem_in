/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flogan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 17:26:43 by flogan            #+#    #+#             */
/*   Updated: 2019/09/04 19:58:36 by flogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *destptr, const void *srcptr, size_t num)
{
	if (destptr == NULL && srcptr == NULL)
		return (NULL);
	if (srcptr < destptr)
		while (num--)
			((unsigned char*)destptr)[num] = ((unsigned char*)srcptr)[num];
	else
		ft_memcpy(destptr, srcptr, num);
	return (destptr);
}
