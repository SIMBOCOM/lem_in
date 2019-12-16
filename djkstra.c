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
	int i;
	int it;

	
	it = -1;
	n = data->size_matrix;
	start_djkstra(data, used);
	data->dist[data->start].distance = 0;
	while (++it < n)
	{
		int u = -1;
		i = -1;
		while (++i < n)
			if (!used[i] && (u == -1 || data->dist[i].distance < data->dist[u].distance))
				u = i;
		if (data->dist[u].distance == INT_MAX)
			break;
		used[u] = 1;
		i = -1;
		while (++i < n)
			if(data->matrix[u][i] != 0 && data->matrix[u][i] != -1 && data->dist[u].distance + data->matrix[u][i] < data->dist[i].distance)
			{
				data->dist[i].distance = data->dist[u].distance + data->matrix[u][i];
				data->dist[i].index_parent = u;
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

void	reverse_matrix(t_total_data *data, int size, int u, t_path *path)
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

void	push_matrix_path(t_total_data *data, t_path *path)
{
	int temp[data->size_matrix];
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
			reverse_matrix(data, i + 1, path->numb_path, path);
			break ;
		}
	}
}

void	delete_node(t_total_data *data, t_path *path)
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

void	search_path_first(t_total_data *data)
{
	int size;
	int i;

	size = get_num_path(data);
	data->path_first.matrix_path = (int**)malloc(sizeof(int*) * size);
	i = -1;
	while (++i < size)
		data->path_first.matrix_path[i] = (int*)malloc(sizeof(int) * data->size_matrix);
	data->path_first.numb_path = 0;
	while (djkstra(data))
	{
		push_matrix_path(data, &(data->path_first));
		delete_node(data, &(data->path_first));
		push_null_matrix(data);
		data->path_first.numb_path++;
	}
}

void search_path_second(t_total_data *data)
{
	int size;
	int i;

	size = get_num_path(data);
	data->path_second.matrix_path = (int**)malloc(sizeof(int*) * size);
	i = -1;
	while (++i < size)
		data->path_second.matrix_path[i] = (int*)malloc(sizeof(int) * data->size_matrix);
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

void	copy_matrix(int **first, int **second, int size)
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

int		**copy_create_matrix(int n, int **matrix)
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

void		length_roads(t_total_data *data, t_path *path)
{
	int i;
	int j;
	int length;

	i = -1;
	path->tarakan = malloc(sizeof(t_path_tarakan) * path->numb_path);
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

void	tarakan_create(t_total_data *data, t_path *path)
{
	int i;
	int j;
	int ants_count;

	ants_count = data->numb_ants;
	length_roads(data, path);
	i = 1;
	while (i++)
	{
		j = -1;
		if (ants_count <= 0)
		{
			path->size_of_step = i - 1;
			return ;
		}
		while (++j < path->numb_path)
			if (!(i % path->tarakan[j].size_of_road) || path->tarakan[j].size_of_tarakan)
			{
				path->tarakan[j].size_of_tarakan++;
				ants_count--;
			}
	}
}

void	algorithm(t_total_data *data)
{
	int **matrix_save;
	
	matrix_save = copy_create_matrix(data->size_matrix, data->matrix);
	data->dist = malloc(sizeof(t_top_djks) * data->size_matrix);
	search_path_first(data);
	if (!data->path_first.numb_path)
		return (print_error(E_PATH));
	copy_matrix(data->matrix, matrix_save, data->size_matrix);
	search_path_second(data);
	tarakan_create(data, &(data->path_second));
	tarakan_create(data, &(data->path_first));
	if (data->path_first.size_of_step >= data->path_second.size_of_step)
		run_ants_new(data, &(data->path_second));
	else
		run_ants_new(data, &(data->path_first));
}

void	print_one_step_new(t_total_data *data, int count,
				t_path *path, t_pos_index_tarakan	*ants_finall)
{
	int i;

	i = -1;
	while (++i < count)
	{
		if (!ants_finall[i].num_road)
		{
			if (path->tarakan[i % path->numb_path].size_of_tarakan)
			{
				ants_finall[i].num_road = i % path->numb_path;
				path->tarakan[i % path->numb_path].size_of_tarakan--;
				if (path->numb_path != 1 && !path->tarakan[i % path->numb_path].size_of_tarakan)
					path->numb_path--;
			}
		}
		if (ants_finall[i].index != -1)
			ft_printf("L%d-%s ", i + 1,
			search_room_index(data, path->matrix_path[ants_finall[i].num_road][ants_finall[i].index]));
		if (path->matrix_path[ants_finall[i].num_road][ants_finall[i].index] == data->end)
		{
			ants_finall[i].index = -1;
			// ft_printf("i = %d\n", i);
		}
	}
	ft_printf("\n");
}

void	run_ants_new(t_total_data *data, t_path *path)
{
	int					i;
	int					j;
	int					count;
	t_pos_index_tarakan	ants_finall[data->numb_ants];

	i = -1;
	int numb_path_new = path->numb_path;
	for (int z = 0; z < path->numb_path; z++)
		if (!path->tarakan[z].size_of_tarakan)
			numb_path_new--;
	path->numb_path = numb_path_new;
	while (++i < data->numb_ants)
	{
		ants_finall[i].index = 0;
		ants_finall[i].num_road = 0;
	}
	count = path->numb_path;
	if (count > data->numb_ants)
		count = data->numb_ants;
	i = -1;
	while (++i < path->size_of_step)
	{
		
		j = -1;
		while (++j < count)
			if (ants_finall[j].index != -1)
				ants_finall[j].index++;
		print_one_step_new(data, count, path, ants_finall);
		// for (int k = 0; k < count; k++)
			// ft_printf("i = %d ants_finall[i].index = %d road = %d\n", k, ants_finall[k].index, ants_finall[k].num_road);
		count += path->numb_path;
		if (count > data->numb_ants)
			count = data->numb_ants;
	}
}



void	print_one_step(t_total_data *data, int count, int *ants_finall, t_path *path)
{
	int i;
	
	i = -1;
	while (++i < count)
	{
		if (ants_finall[i] != -1)
			ft_printf("L%d-%s ", i + 1, search_room_index(data, path->matrix_path[i % path->numb_path][ants_finall[i]]));
		if (path->matrix_path[i % path->numb_path][ants_finall[i]] == data->end)
		{
			
			ants_finall[i] = -1;
			data->numb_ants--;
		}
	}
	ft_printf("\n");
}

void	run_ants(t_total_data *data, t_path *path)
{
	int count;
	int i;
	int ants_finall[data->numb_ants];
	int num_ants;

	num_ants = data->numb_ants;
	i = -1;
	while (++i < data->numb_ants)
		ants_finall[i] = 0;
	count = path->numb_path;
	while (data->numb_ants > 0)
	{
		i = -1;
		while (++i < count)
		{
			if (ants_finall[i] != -1)
				ants_finall[i]++;
		}
		print_one_step(data, count, ants_finall, path);
		count += path->numb_path;
		if (count > num_ants)
			count = num_ants;
	}
}