/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthai <rthai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 19:42:31 by rthai             #+#    #+#             */
/*   Updated: 2019/12/08 20:18:26 by rthai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_error(int id)
{
	ft_printf("%d", id);
	exit(id);
}

void	print_matrix(t_total_data *data)
{
	int i;
	int j;

	i = 0;
	while (i < data->size_matrix)
	{
		j = 0;
		while (j < data->size_matrix)
		{
			ft_printf("%2d ", data->matrix[i][j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}

void	parser_room(t_total_data *data, char *str, int index)
{
	t_room		new_room;
	char		*temp;

	// ft_printf("%d\n", 1);
	temp = ft_strchr(str, ' ');
	*temp++ = 0;
	new_room.name = ft_strdup(str);
	new_room.x = ft_atoi(temp);
	temp = ft_strchr(temp, ' ');
	new_room.y = ft_atoi(temp);
	push_front(data, index, &new_room);
	// ft_printf("%d\n", 10);
}

void	parser_lem(t_total_data *data)
{
	char	*str;
	int		i;
	int		flag[2];


	flag[0] = 0;
	flag[1] = 0;
	str = 0;
	i = 0;
	get_next_line(0, &str);
	ft_printf("%s\n", str);
	data->numb_ants = 488;
	free(str);
	while (get_next_line(0, &str))
	{
		ft_printf("%s\n", str);
		valid(str, flag, data, &i);
	}
	write(1, "\n", 1);
	algorithm(data);
	// for (int i = 0; i < data->numb_path; i++)
	// {
	// 	for (int j = 0; data->matrix_path[i][j] != data->end; j++)
	// 	{
	// 		ft_printf("%d ", data->matrix_path[i][j]);
	// 	}
	// 	ft_printf("%d\n", data->end);
	// }
	int jk = data->numb_ants;
	
	// data->numb_ants = jk;
	// run_ants(data, &(data->path_second));
}

void	create_matrix(int ***matrix, int n)
{
	int i;

	i = 0;
	if (!(*matrix = malloc(sizeof(int*) * n)))
		print_error(E_MALLOC);
	while (i < n)
	{
		if (!((*matrix)[i] = malloc(sizeof(int) * n)))
			print_error(E_MALLOC);
		ft_bzero((*matrix)[i], n * sizeof(int));
		i++;
	}
//	ft_printf("%d\n", 2);
}