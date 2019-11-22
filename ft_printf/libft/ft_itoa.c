/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flogan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 18:06:09 by flogan            #+#    #+#             */
/*   Updated: 2019/09/07 23:09:51 by flogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(int n)
{
	int i;

	i = 1;
	if (n == 0)
		return (2);
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char		*ft_itoa(int n)
{
	char	*s;
	int		flag;
	int		len;
	long	n1;

	n1 = n;
	len = ft_len(n1);
	flag = (n1 < 0 && (n1 *= -1)) ? 1 : 0;
	if (!(s = (char*)malloc(sizeof(char) * (len += flag))))
		return (NULL);
	if (n1 == 0 && (s[0] = '0'))
		return (s);
	s[--len] = '\0';
	while (n1 != 0)
	{
		s[--len] = n1 % 10 + '0';
		n1 /= 10;
	}
	if (flag == 1)
		s[--len] = '-';
	return (s);
}
