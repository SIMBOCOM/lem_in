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

int 	get_num_path(t_total_data *data)
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

void	create_arr_path(t_total_data *data, t_top_djks djks[data->size_matrix], int *arr_path)
{
	int i;
	t_lem_list	arr[data->size_matrix];

	get_array_room(data, arr);
	i = data->end;
	*arr_path = djks[i].index_parent;
	while (i != -1)
	{
		if (djks[i].index_parent != -1)
			data->matrix[djks[i].index_parent][i] *= -1;
		ft_printf("%s ", arr[i].room.name);
		i = djks[i].index_parent;
	}
}

void	print_path(t_total_data *data, t_top_djks djks[data->size_matrix], int *arr_path)
{
	int j;
	int i;

	j = -1;
	t_lem_list	arr[data->size_matrix];
	get_array_room(data, arr);
	while (++j < get_num_path(data))
	{
		ft_printf("llll\n");
		ft_printf("%s ", arr[data->end].room.name);
		ft_printf("%s ", arr[arr_path[j]].room.name);
		i = djks[arr_path[j]].index_parent;
		while (i != -1)
		{
			ft_printf("%s ", arr[i].room.name);
			i = djks[i].index_parent;
		}
		write (1, "\n", 1);
	}
}

void	get_cross(t_total_data *data)
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

void	search_path(int visit, t_total_data *data, t_top_djks djks[data->size_matrix], int path, int *arr_path)
{
	int i;
	int res;

	res = 1;
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
			create_arr_path(data, djks,arr_path);
		}
	}
}

void	dijkstra(t_total_data *data)
{
	int i;
	int res;
	int visit;
	int path;
	int j;
	int arr_path[get_num_path(data)];
	t_top_djks djks[data->size_matrix];

	i = -1;
	path = 1;
	visit = 0;
	j = -1;
	while (++i < data->size_matrix)
	{
		djks[i].distance = INT_MAX;
		djks[i].visit = 0;
		djks[i].index_parent = -1;
	}
	djks[data->start].distance = 0;
	bypass(data, djks, data->start, visit, path);
	create_arr_path(data, djks,arr_path);
	search_path(visit, data, djks, path, arr_path);
	get_cross(data);
	res = 1;
	path = -path;
	visit = !visit;
	write (1, "\n", 1);
	while (res)
	{
		visit = !visit;
		i = -1;
		while (++i < data->size_matrix)
			djks[i].distance = INT_MAX;
		djks[data->start].distance = 0;
		res = bypass(data, djks, data->start, visit, path);
		if (res && (++j || 1))
			create_arr_path(data, djks,arr_path + j);
		write (1, "\n", 1);
	}
	print_path(data, djks, arr_path);
}