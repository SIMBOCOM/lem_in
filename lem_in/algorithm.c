/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   djkstra.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flogan <flogan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 16:26:46 by rthai             #+#    #+#             */
/*   Updated: 2019/12/15 17:00:48 by flogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		push_null_matrix(t_total_data *data)
{
	int i;

	i = data->end;
	while (1)
	{
		data->matrix[data->dist[i].index_parent][i] = -1;
		i = data->dist[i].index_parent;
		if (i == data->start)
			break ;
	}
}

void		delete_node(t_total_data *data, t_path *path)
{
	int i;
	int j;

	i = 0;
	while (path->matrix_path[path->numb_path][++i] != data->end)
	{
		j = -1;
		while (++j < data->size_matrix)
		{
			data->matrix[path->matrix_path[path->numb_path][i]][j] = 0;
			data->matrix[j][path->matrix_path[path->numb_path][i]] = 0;
		}
	}
}

void		length_roads(t_total_data *data, t_path *path)
{
	int i;
	int j;
	int length;

	i = -1;
	if (!(path->tarakan = malloc(sizeof(t_path_tarakan) * path->numb_path)))
		print_error(E_MALLOC);
	while (++i < path->numb_path)
	{
		length = 0;
		path->tarakan[i].size_of_tarakan = 0;
		j = -1;
		while (path->matrix_path[i][++j] != data->end)
			length++;
		path->tarakan[i].size_of_road = length;
	}
}

void		algorithm(t_total_data *data)
{
	int **matrix_save;

	matrix_save = copy_create_matrix(data->size_matrix, data->matrix);
	if (!(data->dist = malloc(sizeof(t_top_djks) * data->size_matrix)))
		print_error(E_MALLOC);
	search_path_first(data);
	if (!data->path_first.numb_path)
		return (print_error(E_PATH));
	copy_matrix(data->matrix, matrix_save, data->size_matrix);
	search_path_second(data);
	tarakan_create(data, &(data->path_second));
	tarakan_create(data, &(data->path_first));
	if (data->path_first.size_of_step >= data->path_second.size_of_step)
		run_ants(data, &(data->path_second));
	else
		run_ants(data, &(data->path_first));
	free_matrix(&matrix_save, data->size_matrix);
	freez(data);
}
