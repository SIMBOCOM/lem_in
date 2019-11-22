/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flogan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 23:14:19 by flogan            #+#    #+#             */
/*   Updated: 2019/09/07 09:41:18 by flogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char *c;

	if ((len + 1) == 0 || s == NULL)
		return (NULL);
	c = (char*)malloc(sizeof(char) * (len + 1));
	if (c == NULL)
		return (NULL);
	c[len] = '\0';
	return (ft_strncpy(c, s + start, len));
}
