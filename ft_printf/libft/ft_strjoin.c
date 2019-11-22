/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flogan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 09:41:52 by flogan            #+#    #+#             */
/*   Updated: 2019/09/08 00:33:28 by flogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len;
	char	*c;

	if (s1 && s2)
	{
		len = ft_strlen((char*)s1) + ft_strlen((char*)s2) + 1;
		c = (char*)malloc(sizeof(char) * len);
		if (!c)
			return (NULL);
		*c = '\0';
		return (ft_strcat(ft_strcat(c, (char*)s1), (char*)s2));
	}
	return (NULL);
}
