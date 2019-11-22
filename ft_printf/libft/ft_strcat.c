/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flogan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 22:08:50 by flogan            #+#    #+#             */
/*   Updated: 2019/09/04 22:17:20 by flogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strcat(char *destptr, const char *srcptr)
{
	int i;

	i = 0;
	while (destptr[i])
		i++;
	while (*srcptr)
	{
		destptr[i] = *srcptr;
		i++;
		srcptr++;
	}
	destptr[i] = '\0';
	return (destptr);
}
