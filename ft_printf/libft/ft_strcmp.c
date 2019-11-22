/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flogan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 12:52:40 by flogan            #+#    #+#             */
/*   Updated: 2019/09/08 16:28:11 by flogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_strcmp(char *s1, const char *s2)
{
	int i;

	i = 0;
	while (((unsigned char*)s1)[i] && ((unsigned char*)s2)[i] &&
			((unsigned char*)s1)[i] == ((unsigned char*)s2)[i])
		i++;
	return (((unsigned char*)s1)[i] - ((unsigned char*)s2)[i]);
}
