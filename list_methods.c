/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_methods.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthai <rthai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 17:37:53 by rthai             #+#    #+#             */
/*   Updated: 2019/11/22 21:26:35 by rthai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	my_copy(t_room *in, t_room *out)
{
	in->name = out->name;
	in->x = out->x;
	in->y = out->y;	
}

t_lem_list		*lst_create(int index, t_room *room)
{
	t_lem_list	*new;
	
	
	new = (t_lem_list*)malloc(sizeof(t_lem_list));
	new->index = index;
	new->next = NULL;
	my_copy(&new->room, room);
	return (new);
}

void	push_front(t_lem_list **list, int index, t_room *room)
{
	t_lem_list *new;

	new = lst_create(index, room);
	new->next  = *list;
	*list = new;
}

int		search_room(t_lem_list **list, char *str)
{
	t_lem_list *shift;

	shift = *list;
	while (shift && ft_strcmp(shift->room.name, str))
		shift = shift->next;
	if (shift)
		return (shift->index);
	else
		return (-1);
}
