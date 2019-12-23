/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_method_vis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flogan <flogan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 14:26:31 by flogan            #+#    #+#             */
/*   Updated: 2019/12/23 14:42:24 by flogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual_header.h"

t_room		*search_room_name_elem(t_total_data *data, char *str)
{
	t_lem_list *shift;

	shift = data->rooms;
	while (shift && ft_strcmp(shift->room.name, str))
		shift = shift->next;
	if (shift)
		return (&shift->room);
	else
		return (NULL);
}

t_lem_list	*search_room_index_list(t_total_data *data, int index)
{
	t_lem_list *shift;

	shift = data->rooms;
	while (shift && shift->index != index)
		shift = shift->next;
	return (shift);
}
