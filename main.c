/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthai <rthai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 20:31:14 by rthai             #+#    #+#             */
/*   Updated: 2019/12/05 19:30:05 by rthai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int main()
{
	t_total_data data;

	data.end = 0;
	data.start = 0;
	data.size_matrix = 0;
	data.numb_ants = 0;
	data.matrix = NULL;
	data.rooms = NULL;
	parser_lem(&data);
}