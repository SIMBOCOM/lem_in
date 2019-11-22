/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flogan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 13:49:06 by flogan            #+#    #+#             */
/*   Updated: 2019/09/08 01:28:51 by flogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *string1, const char *string2, size_t num)
{
	size_t i;

	i = 0;
	while (i < num && string1[i] && string2[i])
	{
		if (string1[i] != string2[i])
			return ((unsigned char)string1[i] - (unsigned char)string2[i]);
		i++;
	}
	if (i == num)
		i--;
	return ((unsigned char)string1[i] - (unsigned char)string2[i]);
}
