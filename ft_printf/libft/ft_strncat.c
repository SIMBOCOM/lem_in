/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flogan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 22:18:40 by flogan            #+#    #+#             */
/*   Updated: 2019/09/08 16:44:55 by flogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *destptr, const char *srcptr, size_t num)
{
	size_t	j;
	int		i;
	char	*srcptr1;

	srcptr1 = (char*)srcptr;
	i = 0;
	j = 0;
	while (destptr[i])
		i++;
	while (*srcptr1 && j < num)
	{
		destptr[i] = *srcptr1;
		i++;
		j++;
		srcptr1++;
	}
	destptr[i] = '\0';
	return (destptr);
}
