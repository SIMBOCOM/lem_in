/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freez.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthai <rthai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 17:12:24 by rthai             #+#    #+#             */
/*   Updated: 2019/12/21 17:13:00 by rthai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	free_matrix(int ***matrix, int size)
{
	int i;

	i = -1;
	if (!*matrix)
		return ;
	while (++i < size)
		free((*matrix)[i]);
	free(*matrix);
	*matrix = NULL;
}

void	free_list(t_lem_list **list)
{
	t_lem_list *shift;
	t_lem_list *temp;

	shift = *list;
	while (shift)
	{
		temp = shift;
		shift = shift->next;
		ft_strdel(&(temp->room.name));
		free(temp);
	}
	*list = NULL;
}

void	freez(t_total_data *data)
{
	int size;

	size = get_num_path(data);
	free_list(&(data->rooms));
	free_matrix(&(data->matrix), data->size_matrix);
	free_matrix(&(data->path_first.matrix_path), size);
	free_matrix(&(data->path_second.matrix_path), size);
	free(data->path_second.tarakan);
	data->path_second.tarakan = NULL;
	free(data->dist);
	data->dist = NULL;
	free(data->path_first.tarakan);
	data->path_first.tarakan = NULL;
}
