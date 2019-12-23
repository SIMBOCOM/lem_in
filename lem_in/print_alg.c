/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_alg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flogan <flogan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 14:30:24 by flogan            #+#    #+#             */
/*   Updated: 2019/12/23 14:45:12 by flogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		init_road(int i, t_path *path,
		t_pos_index_tarakan *ants_finall, int *k)
{
	if (ants_finall[i].num_road == -1)
	{
		if (path->tarakan[*k].size_of_tarakan)
		{
			ants_finall[i].num_road = *k;
			path->tarakan[*k].size_of_tarakan--;
			if (path->numb_path != 1
				&& !path->tarakan[*k].size_of_tarakan)
				path->numb_path--;
			(*k)++;
		}
	}
}

void		tarakan_create(t_total_data *data, t_path *path)
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
		while (ants_count && ++j < path->numb_path)
			if (!(i % path->tarakan[j].size_of_road)
				|| path->tarakan[j].size_of_tarakan)
			{
				path->tarakan[j].size_of_tarakan++;
				ants_count--;
			}
	}
}

void		print_one_step(t_total_data *data, int count,
					t_path *path, t_pos_index_tarakan *ants_finall)
{
	int i;
	int flag;
	int k;

	i = -1;
	flag = 0;
	k = 0;
	while (++i < count)
	{
		init_road(i, path, ants_finall, &k);
		if (ants_finall[i].index != -1 && ants_finall[i].num_road != -1)
		{
			if (flag)
				write(1, " ", 1);
			ft_printf("L%d-%s ", i + 1, search_room_index(data,
			path->matrix_path[ants_finall[i].num_road][ants_finall[i].index]));
			flag++;
		}
		if (ants_finall[i].index != -1 && ants_finall[i].num_road != -1 &&
			path->matrix_path[ants_finall[i].num_road][ants_finall[i].index]
			== data->end)
			ants_finall[i].index = -1;
	}
}

void		start_run_ants(t_pos_index_tarakan *ants_finall,
							t_path *path, t_total_data *data)
{
	int i;
	int numb_path_new;

	i = -1;
	numb_path_new = path->numb_path;
	while (++i < path->numb_path)
		if (!path->tarakan[i].size_of_tarakan)
			numb_path_new--;
	path->numb_path = numb_path_new;
	i = -1;
	while (++i < data->numb_ants)
	{
		ants_finall[i].index = 0;
		ants_finall[i].num_road = -1;
	}
}

void		run_ants(t_total_data *data, t_path *path)
{
	int					i;
	int					j;
	int					count;
	t_pos_index_tarakan	ants_finall[data->numb_ants];

	start_run_ants(ants_finall, path, data);
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
		print_one_step(data, count, path, ants_finall);
		count += path->numb_path;
		if (count > data->numb_ants)
			count = data->numb_ants;
		if (i + 1 < path->size_of_step)
			ft_printf("\n");
	}
}
