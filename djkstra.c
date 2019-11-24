/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   djkstra.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthai <rthai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 16:26:46 by rthai             #+#    #+#             */
/*   Updated: 2019/11/24 16:38:44 by rthai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	initial_matrix(t_top_djks **matrix, int n)
{
	int i;
	int j;

	i = -1;
	while (++i < n)
	{
		j = -1;
		while (++j < n)
			matrix[i][j].distance = INT_MAX;
	}
}

void	dijkstra(t_total_data *data)
{
	int i;
	int j;
	
	i = -1;
	t_top_djks matrix_djks[data->size_matrix][data->size_matrix];
	initial_matrix(matrix_djks, data->size_matrix)
	while (++i < data->size_matrix)
	{
		
	}
	
}