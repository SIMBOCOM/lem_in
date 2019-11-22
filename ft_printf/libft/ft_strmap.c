/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flogan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 19:51:17 by flogan            #+#    #+#             */
/*   Updated: 2019/09/08 00:33:53 by flogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*n;
	int		i;

	i = 0;
	if (s == NULL)
		return (NULL);
	n = (char*)malloc(sizeof(char) * (ft_strlen((char*)s) + 1));
	if (n == NULL)
		return (NULL);
	while (s[i])
	{
		n[i] = f(s[i]);
		i++;
	}
	n[i] = '\0';
	return (n);
}
