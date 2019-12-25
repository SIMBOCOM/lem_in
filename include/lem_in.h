/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flogan <flogan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 19:41:01 by rthai             #+#    #+#             */
/*   Updated: 2019/12/23 14:35:26 by flogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include <stdlib.h>
# include "ft_printf.h"
# define HASH 128
# define E_MALLOC 1
# define E_NO_VALID 2
# define E_START 3
# define E_END 4
# define E_VAL_LINK 5
# define E_INT 6
# define E_NO_LINK 7
# define E_PATH 8
# define E_ANT 9
# define E_ROOM 10
# define WIDTH 1600
# define HEIGHT 1200

typedef struct	s_room
{
	char	*name;
	int		x;
	int		y;
}				t_room;

typedef struct	s_lem_list
{
	t_room				room;
	int					index;
	struct s_lem_list	*next;
}				t_lem_list;

typedef struct	s_path_tarakan
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
	t_lem_list			*rooms;
	int					**matrix;
	int					size_matrix;
	struct s_top_djks	*dist;
	int					numb_ants;
	int					start;
	int					end;
	t_path				path_first;
	t_path				path_second;
}				t_total_data;

typedef struct	s_top_djks
{
	int		distance;
	int		index_parent;
}				t_top_djks;

typedef	struct	s_pos_index_tarakan
{
	int index;
	int num_road;
}				t_pos_index_tarakan;

void			push_front(t_total_data *data, int index, t_room *room);
int				ft_atoi_mod(const char *str);
int				search_room_name(t_total_data *data, char *str);
char			*search_room_index(t_total_data *data, int index);
t_lem_list		*lst_create(int index, t_room *room);
void			my_copy(t_room *in, t_room *out);
void			print_error(int id);
void			create_matrix(int ***matrix, int n, int m);
void			parser_room(t_total_data *data, char *str, int index);
void			valid(char *str, t_total_data *data, int *i);
int				get_num_path(t_total_data *data);
void			parser_lem(t_total_data *data);
int				djkstra(t_total_data *data);
void			algorithm(t_total_data *data);
void			run_ants(t_total_data *data, t_path *path);
void			freez(t_total_data *data);
void			free_matrix(int ***matrix, int size);
void			print_str(char **str);
void			search_path_second(t_total_data *data);
void			search_path_first(t_total_data *data);
void			get_cross(t_total_data *data);
int				get_num_path(t_total_data *data);
void			start_djkstra(t_total_data *data, int *used);
void			djkstra_push_node(t_total_data *dat, int u);
void			push_null_matrix(t_total_data *data);
void			delete_node(t_total_data *data, t_path *path);
void			length_roads(t_total_data *data, t_path *path);
void			init_road(int i, t_path *path,
						t_pos_index_tarakan *ants_finall, int *k);
void			tarakan_create(t_total_data *data, t_path *path);
void			print_one_step(t_total_data *data, int count,
						t_path *path, t_pos_index_tarakan *ants_finall);
void			start_run_ants(t_pos_index_tarakan *ants_finall,
						t_path *path, t_total_data *data);
void			run_ants(t_total_data *data, t_path *path);
void			reverse_ones(t_total_data *data);
void			reverse_matrix(int size, int u, t_path *path);
void			push_matrix_path(t_total_data *data, t_path *path);
void			copy_matrix(int **first, int **second, int size);
int				**copy_create_matrix(int n, int **matrix);

#endif
