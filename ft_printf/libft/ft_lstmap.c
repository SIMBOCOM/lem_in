/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flogan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 13:14:12 by flogan            #+#    #+#             */
/*   Updated: 2019/09/08 17:54:54 by flogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *head;
	t_list *result;

	if (!f || !lst)
		return (NULL);
	if (!(head = f(lst)))
		return (NULL);
	result = head;
	lst = lst->next;
	while (lst)
	{
		if (!(head->next = f(lst)))
			return (NULL);
		lst = lst->next;
		head = head->next;
	}
	return (result);
}
