/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flogan <flogan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 14:30:32 by flogan            #+#    #+#             */
/*   Updated: 2019/12/23 14:40:45 by flogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			get_num_path(t_total_data *data)
{
	int i;
	int num;

	num = 0;
	i = -1;
	while (++i < data->size_matrix)
		if (data->matrix[data->start][i])
			num++;
	return (num);
}

void		get_cross(t_total_data *data)
{
	int i;
	int j;

	i = -1;
	while (++i < data->size_matrix)
	{
		j = -1;
		while (++j < data->size_matrix)
		{
			if (data->matrix[i][j] == -1 && data->matrix[j][i] == -1)
			{
				data->matrix[i][j] = 0;
				data->matrix[j][i] = 0;
			}
		}
	}
}

void		search_path_first(t_total_data *data)
{
	int size;

	size = get_num_path(data);
	create_matrix(&(data->path_first.matrix_path), size, data->size_matrix);
	data->path_first.numb_path = 0;
	while (djkstra(data))
	{
		push_matrix_path(data, &(data->path_first));
		delete_node(data, &(data->path_first));
		push_null_matrix(data);
		data->path_first.numb_path++;
	}
}

void		search_path_second(t_total_data *data)
{
	int size;

	size = get_num_path(data);
	create_matrix(&data->path_second.matrix_path, size, data->size_matrix);
	data->path_second.numb_path = 0;
	while (djkstra(data))
		push_null_matrix(data);
	get_cross(data);
	reverse_ones(data);
	while (djkstra(data))
	{
		push_matrix_path(data, &(data->path_second));
		delete_node(data, &(data->path_second));
		push_null_matrix(data);
		data->path_second.numb_path++;
	}
}
