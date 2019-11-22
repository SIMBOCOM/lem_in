/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthai <rthai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 20:31:14 by rthai             #+#    #+#             */
/*   Updated: 2019/11/22 20:34:56 by rthai            ###   ########.fr       */
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
	for (int i = 0; i < HASH; i++)
		data.hash_tab[i] = NULL;
	parser_lem(&data);
}