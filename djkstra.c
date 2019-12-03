/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   djkstra.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthai <rthai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 16:26:46 by rthai             #+#    #+#             */
/*   Updated: 2019/12/03 19:18:30 by rthai            ###   ########.fr       */
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
	// print_matrix(data);
	// ft_printf("\n");
	// int i = data->dist[data->end].index_parent;
	// ft_printf("%d", data->end + 1);
	// while (i != data->start)
	// {
	// 	ft_printf("%d", i + 1);
	// 	i = data->dist[i].index_parent;
	// }
	// ft_printf("%d", i + 1);
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

void	reverse_matrix(t_total_data *data, int matrix_path[get_num_path(data)][data->size_matrix], int size, int u)
{
	int i;
	int temp;

	i = 0;
	size--;
	while (i < size)
	{
		temp = matrix_path[u][i];
		matrix_path[u][i] = matrix_path[u][size];
		matrix_path[u][size] = temp;
		i++;
		size--;
	}
}

void	push_matrix_path(t_total_data *data, int matrix_path[get_num_path(data)][data->size_matrix])
{
	int temp[data->size_matrix];
	int i;
	int shift;

	i = 0;
	shift = data->start;
	ft_printf("data = %d", matrix_path[0][0]);
	while (1)
	{
		matrix_path[data->numb_path][i++] = shift;
		shift = data->dist[shift].index_parent;
		if (shift == data->start)
		{
			matrix_path[data->numb_path][i] = shift;
			reverse_matrix(data, matrix_path, i + 1, data->numb_path);
			break ;
		}
	}
}

void	delete_node(t_total_data *data, int matrix_path[get_num_path(data)][data->size_matrix])
{
	int i;
	int j;

	i = 0;
	while (matrix_path[data->numb_path][++i] != data->end)
	{
		j = -1;
		while (++j < data->size_matrix)
		{
			data->matrix[i][j] = 0;
			data->matrix[j][i] = 0;
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
	int matrix_path[get_num_path(data)][data->size_matrix];

	matrix_path[0][0] = 1;
	data->dist = malloc(sizeof(t_top_djks) * data->size_matrix);
	data->numb_path = 0;
	while (djkstra(data))
		push_null_matrix(data);
	get_cross(data);
	reverse_ones(data);
	while (djkstra(data))
	{
		push_matrix_path(data, matrix_path);
		delete_node(data, matrix_path);
		push_null_matrix(data);
		data->numb_path++;
	}
	// print_matrix(data);
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


