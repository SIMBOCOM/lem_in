/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flogan <flogan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 19:42:31 by rthai             #+#    #+#             */
/*   Updated: 2019/12/23 14:43:22 by flogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		valid_link(t_total_data *data)
{
	int i;
	int j;

	i = -1;
	while (++i < data->size_matrix)
	{
		j = -1;
		while (++j < data->size_matrix)
			if (data->matrix[i][j])
				return (1);
	}
	return (0);
}

void	parser_room(t_total_data *data, char *str, int index)
{
	t_room		new_room;
	char		*temp;
	char		*hel_null;
	char		*strt;

	strt = ft_strdup(str);
	if (!(temp = ft_strchr(strt, ' ')) || strt[0] == 'L')
		print_error(E_ROOM);
	*temp++ = 0;
	new_room.name = ft_strdup(strt);
	if (!(hel_null = ft_strchr(temp, ' ')))
		print_error(E_NO_VALID);
	*hel_null++ = 0;
	new_room.x = ft_atoi_mod(temp);
	temp = hel_null;
	new_room.y = ft_atoi_mod(temp);
	if (search_room_name(data, strt) != -1)
		print_error(E_ROOM);
	push_front(data, index, &new_room);
	ft_strdel(&strt);
}

void	parser_lem(t_total_data *data)
{
	char	*str;
	int		i;

	str = 0;
	i = 0;
	while (get_next_line(0, &str) && str[0] == '#' &&
	ft_strcmp(str, "##start") && ft_strcmp(str, "##end"))
		print_str(str);
	if ((data->numb_ants = ft_atoi_mod(str)) <= 0)
		print_error(E_ANT);
	print_str(str);
	while (get_next_line(0, &str))
	{
		valid(str, data, &i);
		print_str(str);
	}
	ft_strdel(&str);
	if (!valid_link(data))
		return (print_error(E_NO_LINK));
	write(1, "\n", 1);
	if (data->start == -1 || data->end == -1)
		print_error(E_NO_VALID);
}

void	create_matrix(int ***matrix, int n, int m)
{
	int i;

	i = 0;
	if (!(*matrix = malloc(sizeof(int*) * n)))
		print_error(E_MALLOC);
	while (i < n)
	{
		if (!((*matrix)[i] = malloc(sizeof(int) * m)))
			print_error(E_MALLOC);
		ft_bzero((*matrix)[i], m * sizeof(int));
		i++;
	}
}
