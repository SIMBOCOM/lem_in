/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   djkstra_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flogan <flogan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 14:30:13 by flogan            #+#    #+#             */
/*   Updated: 2019/12/23 14:39:46 by flogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		start_djkstra(t_total_data *data, int *used)
{
	int i;

	i = -1;
	while (++i < data->size_matrix)
	{
		used[i] = 0;
		data->dist[i].distance = INT_MAX;
	}
}

void		djkstra_push_node(t_total_data *dat, int u)
{
	int i;

	i = -1;
	while (++i < dat->size_matrix)
		if (dat->matrix[u][i] != 0 && dat->matrix[u][i] != -1
		&& dat->dist[u].distance + dat->matrix[u][i] < dat->dist[i].distance)
		{
			dat->dist[i].distance = dat->dist[u].distance + dat->matrix[u][i];
			dat->dist[i].index_parent = u;
		}
}

int			djkstra(t_total_data *data)
{
	int used[data->size_matrix];
	int i;
	int it;
	int u;

	it = -1;
	start_djkstra(data, used);
	data->dist[data->start].distance = 0;
	while (++it < data->size_matrix)
	{
		u = -1;
		i = -1;
		while (++i < data->size_matrix)
			if (!used[i] && (u == -1 ||
			data->dist[i].distance < data->dist[u].distance))
				u = i;
		if (data->dist[u].distance == INT_MAX)
			break ;
		used[u] = 1;
		djkstra_push_node(data, u);
	}
	return (data->dist[data->end].distance == INT_MAX ? 0 : 1);
}
