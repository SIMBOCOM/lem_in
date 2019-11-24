/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flogan <flogan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 14:49:15 by rthai             #+#    #+#             */
/*   Updated: 2019/11/24 14:15:51 by flogan           ###   ########.fr       */
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

typedef struct	s_total_data
{
	t_lem_list	*hash_tab[HASH];
	int			**matrix;
	int			size_matrix;
	int			numb_ants;
	int			start;
	int			end;
}				t_total_data;

void		parser_lem(t_total_data *data);
void		parser_links(t_total_data *data, char *str);
void		push_front(t_lem_list **list, int index, t_room *room);
int			search_room(t_lem_list **list, char *str);
void		push_front(t_lem_list **list, int index, t_room *room);
t_lem_list	*lst_create(int index, t_room *room);
void		my_copy(t_room *in, t_room *out);
int			hash_sum(char *str);
void		print_error(int id);
void		create_matrix(int ***matrix, int n);
void		parser_room(t_total_data *data, char *str, int index);
void		valid(char *str, int flag[2], t_total_data *data, int *i);

#endif