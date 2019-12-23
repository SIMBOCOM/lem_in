/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_with_matrix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flogan <flogan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 14:30:37 by flogan            #+#    #+#             */
/*   Updated: 2019/12/23 14:41:10 by flogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		reverse_ones(t_total_data *data)
{
	int i;
	int j;

	i = -1;
	while (++i < data->size_matrix)
	{
		j = -1;
		while (++j < data->size_matrix)
			if (data->matrix[i][j] == -1)
				data->matrix[i][j] = 1;
	}
}

void		reverse_matrix(int size, int u, t_path *path)
{
	int i;
	int temp;

	i = 0;
	size--;
	while (i < size)
	{
		temp = path->matrix_path[u][i];
		path->matrix_path[u][i] = path->matrix_path[u][size];
		path->matrix_path[u][size] = temp;
		i++;
		size--;
	}
}

void		push_matrix_path(t_total_data *data, t_path *path)
{
	int i;
	int shift;

	i = 0;
	shift = data->end;
	while (1)
	{
		path->matrix_path[path->numb_path][i++] = shift;
		shift = data->dist[shift].index_parent;
		if (shift == data->start)
		{
			path->matrix_path[path->numb_path][i] = shift;
			reverse_matrix(i + 1, path->numb_path, path);
			break ;
		}
	}
}

void		copy_matrix(int **first, int **second, int size)
{
	int i;
	int j;

	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size)
			first[i][j] = second[i][j];
	}
}

int			**copy_create_matrix(int n, int **matrix)
{
	int **new_matrix;
	int i;
	int j;

	i = -1;
	if (!(new_matrix = malloc(sizeof(int*) * n)))
		print_error(E_MALLOC);
	while (++i < n)
	{
		if (!(new_matrix[i] = malloc(sizeof(int) * n)))
			print_error(E_MALLOC);
		j = -1;
		while (++j < n)
			new_matrix[i][j] = matrix[i][j];
	}
	return (new_matrix);
}
