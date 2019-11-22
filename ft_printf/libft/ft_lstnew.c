/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flogan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 11:17:47 by flogan            #+#    #+#             */
/*   Updated: 2019/09/08 15:32:43 by flogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *t;

	if (!(t = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	if (content == NULL)
	{
		t->content = NULL;
		t->content_size = 0;
	}
	else
	{
		if (!(t->content = (void*)malloc(sizeof(void) * content_size)))
			return (NULL);
		t->content = ft_memcpy(t->content, content, content_size);
		t->content_size = content_size;
	}
	t->next = NULL;
	return (t);
}
