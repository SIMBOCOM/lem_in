/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthai <rthai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 19:41:01 by rthai             #+#    #+#             */
/*   Updated: 2019/12/14 15:24:03 by rthai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
#include <stdlib.h>
#include "ft_printf/include/ft_printf.h"
# define HASH 128
# define E_MALLOC 1
# define E_NO_VALID 2
# define E_START 3
# define E_END 4
# define E_VAL_LINK 5


typedef struct	s_room
{
	char	*name;
	int		x;
	int		y;
}				t_room;

typedef struct	s_lem_list
{
	t_room			room;
	int				index;
	struct s_lem_list	*next;
}				t_lem_list;

typedef struct s_path_tarakan
{
	int		size_of_road;
	int		size_of_tarakan;
}				t_path_tarakan;

typedef struct	s_path
{
	int				numb_path;
	int				**matrix_path;
	int				size_of_step;
	t_path_tarakan	*tarakan;
}				t_path;

typedef struct	s_total_data
{
	t_lem_list	*rooms;
	int			**matrix;
	int			size_matrix;
	struct s_top_djks *dist;
	int			numb_ants;
	int			start;
	int			end;
	t_path		path_first;
	t_path		path_second;
}				t_total_data;

typedef struct	s_top_djks
{
	int		distance;
	int		index_parent;
}				t_top_djks;

typedef	struct	t_pos_index_tarakan
{
	int index;
	int num_road;
}				t_pos_index_tarakan;


void		parser_lem(t_total_data *data);
void		parser_links(t_total_data *data, char *str);
void		push_front(t_total_data *data, int index, t_room *room);
int			search_room_name(t_total_data *data, char *str);
char		*search_room_index(t_total_data *data, int index);
t_lem_list	*lst_create(int index, t_room *room);
void		my_copy(t_room *in, t_room *out);
void		print_error(int id);
void		create_matrix(int ***matrix, int n);
void		parser_room(t_total_data *data, char *str, int index);
void		valid(char *str, int flag[2], t_total_data *data, int *i);
t_lem_list	*get_array_room(t_total_data *data, t_lem_list arr[data->size_matrix]);
int 		get_num_path(t_total_data *data);

int		djkstra(t_total_data *data);
void	print_matrix(t_total_data *data);
void	algorithm(t_total_data *data);
void	run_ants_new(t_total_data *data, t_path *path);
int		run(int, char**, t_total_data *data);

#endif