/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flogan <flogan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 20:31:14 by rthai             #+#    #+#             */
/*   Updated: 2019/12/23 14:40:24 by flogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		main(void)
{
	t_total_data data;

	data.end = -1;
	data.start = -1;
	data.size_matrix = 0;
	data.numb_ants = 0;
	data.matrix = NULL;
	data.rooms = NULL;
	parser_lem(&data);
	algorithm(&data);
}
