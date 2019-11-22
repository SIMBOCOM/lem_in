/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flogan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 00:25:39 by flogan            #+#    #+#             */
/*   Updated: 2019/09/05 15:41:08 by flogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *string, int symbol)
{
	int i;

	i = 0;
	while (string[i])
		i++;
	while (i >= 0)
	{
		if (string[i] == (char)symbol)
			return ((char*)string + i);
		i--;
	}
	return (NULL);
}
