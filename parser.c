/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthai <rthai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 19:42:31 by rthai             #+#    #+#             */
/*   Updated: 2019/11/22 21:04:16 by rthai            ###   ########.fr       */
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
			ft_printf("%d ", data->matrix[i][j]);
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
	push_front(data->hash_tab + hash_sum(new_room.name), index, &new_room);
	// ft_printf("%d\n", 10);
}

void	parser_lem(t_total_data *data)
{
	char	*str;
	int		i;

	str = 0;
	i = 0;
	get_next_line(0, &str);
	data->numb_ants = ft_atoi(str);
	// ft_printf("%d", data->numb_ants);
	free(str);
	while (get_next_line(0, &str))
	{
		// ft_printf("%s\n", str);
		if (ft_strstr(str, "##start"))
			data->start = i + 1;
		if (ft_strstr(str, "##end"))
			data->start = i + 1;
		if (ft_strchr(str, '-'))
		{
			if (!data->matrix)
				data->size_matrix = i;
			parser_links(data, str);
		}
		else
			if (!ft_strchr(str, '#'))
				parser_room(data, str, i);
		free(str);
		// ft_printf("%s\n", "lol");
		i++;
	}
	print_matrix(data);
}

void	create_matrix(int ***matrix, int n)
{
	int i;

	i = 0;
	ft_printf("%d\n", n);
	if (!(*matrix = malloc(sizeof(int*) * n)))
		print_error(E_MALLOC);
	while (i < n)
	{
		if (!((*matrix)[i] = malloc(sizeof(int) * n)))
			print_error(E_MALLOC);
		ft_bzero((*matrix)[i], n * sizeof(int));
		// ft_printf("%d", )
		i++;
	}
	ft_printf("%d\n", 2);
}

void	parser_links(t_total_data *data, char *str)
{
	int		i;
	char	*tmp;

	ft_printf("%d\n", 6);
	i = 0;
	if (data->matrix == NULL)
		create_matrix(&(data->matrix), data->size_matrix);
	tmp = ft_strchr(str, '-');
	*tmp = 0;
	tmp++;

	// ft_printf("lol = %d\n", search_room(data->hash_tab + hash_sum(tmp), tmp));
	// ft_printf("lol = %d\n", search_room(data->hash_tab + hash_sum(str), str));
	data->matrix[search_room(data->hash_tab + hash_sum(tmp), tmp)][search_room(data->hash_tab + hash_sum(str), str)] = 1;
	data->matrix[search_room(data->hash_tab + hash_sum(str), str)][search_room(data->hash_tab + hash_sum(tmp), tmp)] = 1;
	ft_printf("%d\n", 5);
}