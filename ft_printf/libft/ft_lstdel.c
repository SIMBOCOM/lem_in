/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flogan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 12:39:14 by flogan            #+#    #+#             */
/*   Updated: 2019/09/08 15:32:21 by flogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *g;

	g = *alst;
	if (del && g)
	{
		while (g)
		{
			del(g->content, g->content_size);
			free(g);
			g = g->next;
		}
		*alst = NULL;
	}
}
