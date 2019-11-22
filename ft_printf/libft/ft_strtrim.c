/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flogan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 10:05:14 by flogan            #+#    #+#             */
/*   Updated: 2019/09/07 13:56:36 by flogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		lenspace(char *s)
{
	int i;

	i = ft_strlen(s);
	i--;
	while (i >= 0)
	{
		if (!(s[i] == ' ' || s[i] == '\n' || s[i] == '\t'))
			return (i + 1);
		i--;
	}
	return (i + 1);
}

char			*ft_strtrim(char const *s)
{
	int		len;
	char	*n;

	if (s)
	{
		n = (char*)s;
		while (*n == ' ' || *n == '\n' || *n == '\t')
			n++;
		len = lenspace(n);
		return (ft_strsub(n, 0, len));
	}
	return (NULL);
}
