/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   djkstra.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthai <rthai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 16:26:46 by rthai             #+#    #+#             */
/*   Updated: 2019/12/05 19:32:49 by rthai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	start_djkstra(t_total_data *data, int *used)
{
	int i;

	i = -1;
	while (++i < data->size_matrix)
	{
		used[i] = 0;
		data->dist[i].distance = INT_MAX;
	}
}

int		djkstra(t_total_data *data)
{
	int used[data->size_matrix];
	int n;
	int u;

	n = data->size_matrix;
	start_djkstra(data, used);
	data->dist[data->start].distance = 0;
	for (int it = 0; it < n; ++it)
	{
		int u = -1;
		for (int i = 0; i < n; ++i)
		{
			if (!used[i] && (u == -1 || data->dist[i].distance < data->dist[u].distance))
				u = i;
		}	
		if (data->dist[u].distance == INT_MAX)
			break;
		used[u] = 1;
		int i;
		i = 0;
		while (i < n)
		{
			if(data->matrix[u][i] != 0 && data->matrix[u][i] != -1 && data->dist[u].distance + data->matrix[u][i] < data->dist[i].distance)
			{
				data->dist[i].distance = data->dist[u].distance + data->matrix[u][i];
				data->dist[i].index_parent = u;
			}
			i++;
		}
	}
	return (data->dist[data->end].distance == INT_MAX ? 0 : 1);

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

void	reverse_ones(t_total_data *data)
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

void	push_null_matrix(t_total_data *data)
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

void	reverse_matrix(t_total_data *data, int size, int u)
{
	int i;
	int temp;

	i = 0;
	size--;
	while (i < size)
	{
		temp = data->matrix_path[u][i];
		data->matrix_path[u][i] = data->matrix_path[u][size];
		data->matrix_path[u][size] = temp;
		i++;
		size--;
	}
}

void	push_matrix_path(t_total_data *data)
{
	int temp[data->size_matrix];
	int i;
	int shift;

	i = 0;
	shift = data->end;
	while (1)
	{
		data->matrix_path[data->numb_path][i++] = shift;
		shift = data->dist[shift].index_parent;
		if (shift == data->start)
		{
			data->matrix_path[data->numb_path][i] = shift;
			reverse_matrix(data, i + 1, data->numb_path);
			break ;
		}
	}
}

void	delete_node(t_total_data *data)
{
	int i;
	int j;

	i = 0;
	while (data->matrix_path[data->numb_path][++i] != data->end)
	{
		j = -1;
		while (++j < data->size_matrix)
		{
			data->matrix[data->matrix_path[data->numb_path][i]][j] = 0;
			data->matrix[j][data->matrix_path[data->numb_path][i]] = 0;
		}
	}
}

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

void	algorithm(t_total_data *data)
{
	int size;
	int i;
	
	size = get_num_path(data);
	data->matrix_path = (int**)malloc(sizeof(int*) * get_num_path(data));
	i = -1;
	while (++i < size)
		data->matrix_path[i] = (int*)malloc(sizeof(int) * data->size_matrix);
	data->dist = malloc(sizeof(t_top_djks) * data->size_matrix);
	data->numb_path = 0;
	while (djkstra(data))
		push_null_matrix(data);
	get_cross(data);
	reverse_ones(data);
	while (djkstra(data))
	{
		push_matrix_path(data);
		delete_node(data);
		push_null_matrix(data);
		data->numb_path++;
	}
}

void	print_one_step(t_total_data *data, int count, int *ants_finall)
{
	int i;
	
	i = -1;
	while (++i < count)
	{
		if (ants_finall[i] != -1)
			ft_printf("L%d-%s ", i + 1, search_room_index(data, data->matrix_path[i % data->numb_path][ants_finall[i]]));
		if (data->matrix_path[i % data->numb_path][ants_finall[i]] == data->end)
		{
			ants_finall[i] = -1;
			data->numb_ants--;
		}
	}
	ft_printf("\n");
}

void	run_ants(t_total_data *data)
{
	int count;
	int i;
	int ants_finall[data->numb_ants];
	int num_ants;

	num_ants = data->numb_ants;
	i = -1;
	while (++i < data->numb_ants)
		ants_finall[i] = 0;
	count = data->numb_path;
	while (data->numb_ants > 0)
	{
		i = -1;
		while (++i < count)
		{
			if (ants_finall[i] != -1)
				ants_finall[i]++;
		}
		print_one_step(data, count, ants_finall);
		count += data->numb_path;
		if (count > num_ants)
			count = num_ants;
	}
}