/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flogan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 00:03:21 by flogan            #+#    #+#             */
/*   Updated: 2019/09/05 15:38:17 by flogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *string, int symbol)
{
	while (*string)
	{
		if (*string == (char)symbol)
			return ((char*)string);
		string++;
	}
	if ((char)symbol == '\0')
		return ((char*)string);
	return (NULL);
}
