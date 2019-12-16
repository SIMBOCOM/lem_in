/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flogan <flogan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 19:42:31 by rthai             #+#    #+#             */
/*   Updated: 2019/12/16 12:43:11 by flogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_error(int id)
{
	ft_printf("%d", id);
	exit(id);
}

int		ft_atoi_mod(const char *str)
{
	long	n;
	int		flag;

	n = 0;
	flag = 1;
	while (*str >= '\0' && ((*str >= 9 && *str <= 13) || *str == ' '))
		str++;
	if (*str == '-' && (flag = -1))
		str++;
	if (*str == '+' && flag == 1)
		str++;
	while (*str >= '0' && *str <= '9')
	{
		if (n > (n * 10 + *str - '0'))
		{
			if (flag == -1)
				return (0);
			else
				return (-1);
		}
		n = n * 10 + *str - '0';
		str++;
	}
	if ((n * flag) > INT_MAX || (n * flag) < INT_MIN)
		print_error(E_INT);
	return ((int)(n * flag));
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

int valid_link(t_total_data *data)
{
	int i;
	int j;

	i = -1;
	while (++i < data->size_matrix)
	{
		j = -1;
		while (++j < data->size_matrix)
			if(data->matrix[i][j])
				return (1);
	}
	return (0);
}

void	parser_room(t_total_data *data, char *str, int index)
{
	t_room		new_room;
	char		*temp;

	// ft_printf("%d\n", 1111);
	if (!(temp = ft_strchr(str, ' ')))
		print_error(E_ROOM);
	*temp++ = 0;
	new_room.name = ft_strdup(str);
	new_room.x = ft_atoi_mod(temp);
	temp = ft_strchr(temp, ' ');
	new_room.y = ft_atoi_mod(temp);
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
	if ((data->numb_ants = ft_atoi_mod(str)) <= 0)
		print_error(E_ANT);
	free(str);
	while (get_next_line(0, &str))
	{
		ft_printf("%s\n", str);
		valid(str, flag, data, &i);
	}
	if (!valid_link(data))
		return (print_error(E_NO_LINK));
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