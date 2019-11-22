/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flogan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 20:42:04 by flogan            #+#    #+#             */
/*   Updated: 2019/09/08 00:34:25 by flogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
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
		n[i] = f(i, s[i]);
		i++;
	}
	n[i] = '\0';
	return (n);
}
