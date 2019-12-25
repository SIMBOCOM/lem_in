/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flogan <flogan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 14:27:16 by flogan            #+#    #+#             */
/*   Updated: 2019/12/23 14:44:16 by flogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual_header.h"

void	parser_vis(t_total_data *data)
{
	char	*str;
	int		i;

	str = 0;
	i = 0;
	while (get_next_line(0, &str) && str[0] == '#')
		print_str(&str);
	data->numb_ants = ft_atoi(str);
	print_str(&str);
	while (get_next_line(0, &str))
	{
		ft_printf("%s\n", str);
		if (!ft_strcmp(str, ""))
			break ;
		else
			valid(str, data, &i);
	}
	create_coord(data);
}

void	parser_ants_run(t_total_data *data, t_texture *texture, char **tmp)
{
	char *str;

	str = NULL;
	draw_graph(data, texture);
	if (!(get_next_line(0, &str)))
		return ;
	if (str[0] == 'L')
	{
		ants_start(data, str, tmp, texture);
		SDL_GL_SwapWindow(texture->win);
		usleep(100000);
	}
	if (str)
		free(str);
}

void	create_coord(t_total_data *data)
{
	double		angle;
	double		ang_shift;
	t_lem_list	*shift;
	int			step;

	step = 0;
	shift = data->rooms;
	angle = 0;
	ang_shift = (double)360 / (double)data->size_matrix;
	while (shift)
	{
		shift->room.x = (50 / 2) * cos(angle * M_PI / 180);
		shift->room.y = (50 / 2) * sin(angle * M_PI / 180);
		angle += ang_shift;
		shift = shift->next;
	}
}

void	create_rooms_vector(t_vec **rooms, char *str, char *prev,
							t_total_data *data)
{
	char	**arr2;
	t_vec	*tmp_rooms;

	if (!(*rooms = malloc(sizeof(t_vec))))
		print_error(E_MALLOC);
	tmp_rooms = *rooms;
	push_coord_ants(rooms, str);
	arr2 = ft_strsplit(prev, ' ');
	while (tmp_rooms)
	{
		tmp_rooms->a = search_room_vector(tmp_rooms->ant, arr2, data);
		tmp_rooms = tmp_rooms->next;
	}
}

void	push_coord_ants(t_vec **rooms, char *str)
{
	char	**arr;
	char	*tmp;
	int		i;
	t_vec	*tmp_rooms;

	tmp_rooms = *rooms;
	i = -1;
	arr = ft_strsplit(str, ' ');
	while (arr[++i])
	{
		tmp = ft_strchr(arr[i], '-');
		*(tmp++) = 0;
		tmp_rooms->ant = arr[i] + 1;
		tmp_rooms->b = tmp;
		tmp_rooms->a = NULL;
		if (arr[i + 1])
		{
			if (!(tmp_rooms->next = malloc(sizeof(t_vec))))
				print_error(E_MALLOC);
		}
		else
			tmp_rooms->next = NULL;
		tmp_rooms = tmp_rooms->next;
	}
}
