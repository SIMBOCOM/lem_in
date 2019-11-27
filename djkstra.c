/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   djkstra.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flogan <flogan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 16:26:46 by rthai             #+#    #+#             */
/*   Updated: 2019/11/25 23:46:42 by flogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		get_cross(t_total_data *data)
{
	int i;
	int j;
	int merge;

	i = -1;
	merge = 0;
	while (++i < data->size_matrix)
	{
		j = -1;
		while (++j < data->size_matrix)
		{
			if (data->matrix[i][j] == -1 && data->matrix[j][i] == -1)
			{
				data->matrix[i][j] = 0;
				data->matrix[j][i] = 0;
				merge = 1;
			}
		}
	}
	return (merge);
}

void	print_path(t_total_data *data, t_top_djks djks[data->size_matrix], int path)
{
	int i;
	t_lem_list	arr[data->size_matrix];
	get_array_room(data, arr);

	i = data->end;
	while (i != -1)
	{
		if (djks[i].index_parent != -1)
			data->matrix[arr[djks[i].index_parent].index][arr[i].index] = -path;
		ft_printf("%s ", arr[i].room.name);
		i = djks[i].index_parent;
	}
}

int		bypass(t_total_data *data, t_top_djks djks[data->size_matrix], int start, int visit, int path)
{
	int res;
	int i;

	i = -1;
	res = 0;
	djks[start].visit = !visit;
	while (++i < data->size_matrix)
	{
		if (i == start)
			continue;
		else if (data->matrix[start][i] == path && djks[i].visit == visit && djks[start].distance + 1 < djks[i].distance)
		{
			djks[i].distance = djks[start].distance + 1;
			djks[i].index_parent = start;
		}
		//ft_printf("true %d   %d\n", data->matrix[start][i], djks[i].visit == visit);
	}
	i = -1;
	while (++i < data->size_matrix)
	{
		if (i == start)
			continue;
		if (data->matrix[start][i] == path && djks[i].visit == visit)
			res += bypass(data, djks, i, visit, path);
	}
	if (start == data->end)
		return (1);
	return (res);
}

void	dijkstra(t_total_data *data)
{
	int i;
	int res;
	int visit;
	int path;
	t_top_djks djks[data->size_matrix];

	i = -1;
	res = 1;
	path = 1;
	visit = 0;
	while (++i < data->size_matrix)
	{
		djks[i].distance = INT_MAX;
		djks[i].visit = 0;
		djks[i].index_parent = -1;
	}
	djks[data->start].distance = 0;
	bypass(data, djks, data->start, visit, path);
	print_path(data, djks, path);
	while (res)
	{
		visit = !visit;
		i = -1;
		while (++i < data->size_matrix)
			djks[i].distance = INT_MAX;
		djks[data->start].distance = 0;
		res = bypass(data, djks, data->start, visit, path);
		if (res)
		{
			write(1, "\n\n", 2);
			print_path(data, djks, path);
		}
		get_cross(data);
	}
	res = 1;
	path = -path;
	while (res)
	{
		ft_printf("HHHHHH\n");
		i = -1;
		while (++i < data->size_matrix)
			djks[i].distance = INT_MAX;
		djks[data->start].distance = 0;
		res = bypass(data, djks, data->start, visit, path);
		//ft_printf("visit = %d\n",path);
		if (res)
		{
			write(1, "\n\n", 2);
			print_path(data, djks, path);
		}
		visit = !visit;
	}
}