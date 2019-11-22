/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flogan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 12:49:00 by flogan            #+#    #+#             */
/*   Updated: 2019/09/05 13:17:34 by flogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *string1, const char *string2)
{
	unsigned int i;
	unsigned int j;

	i = 0;
	if (*string1 == '\0' && *string2 == '\0')
		return ((char*)string1);
	while (string1[i])
	{
		j = 0;
		while (string2[j] && string1[i + j] == string2[j])
			j++;
		if (string2[j] == '\0')
			return ((char*)string1 + i);
		i++;
	}
	return (NULL);
}
