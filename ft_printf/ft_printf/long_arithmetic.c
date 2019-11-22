/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_arithmetic.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthai <rthai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 16:53:45 by rthai             #+#    #+#             */
/*   Updated: 2019/11/22 18:37:27 by rthai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int		vector_append(t_vector *a, int i)
{
	if (a->size >= MAX_SIZE_ARRAY)
		return (0);
	a->size++;
	a->array[i] = 0;
	return (1);
}

void	sum_long_to_long(t_vector *a, t_vector b)
{
	int i;
	int carry;
	int base;

	carry = 0;
	if (!a->size)
	{
		a->size = 1;
		a->array[0] = 0;
	}
	base = BASE;
	i = -1;
	while (++i < (MAX(a->size, b.size)) || carry)
	{
		if (i == a->size)
			if (!vector_append(a, i))
				return ;
		a->array[i] += (b.size > i ? b.array[i] : 0) + carry;
		carry = a->array[i] >= base;
		if (carry)
			a->array[i] -= base;
	}
}

void	sum_long_to_short(t_vector *a, int b)
{
	int i;
	int carry;
	int base;

	if ((i = 1) && !a->size)
	{
		a->size = 1;
		a->array[0] = 0;
	}
	base = BASE;
	a->array[0] += b;
	carry = a->array[0] >= base;
	if (carry)
		a->array[i] -= base;
	while (carry)
	{
		if (i == a->size)
			if (!vector_append(a, i))
				return ;
		a->array[i] += carry;
		carry = a->array[i] >= base;
		if (carry)
			a->array[i] -= base;
		i++;
	}
}

void	mult_long_to_short(t_vector *a, int b)
{
	int			carry;
	int			i;
	long long	cur;
	long long	base;

	base = BASE;
	carry = 0;
	i = 0;
	if (!a->size)
	{
		a->size = 1;
		a->array[0] = 0;
	}
	while (i < a->size || carry)
	{
		if (i == a->size)
			if (!vector_append(a, i))
				return ;
		cur = carry + (long long)a->array[i] * (long long)b;
		a->array[i] = (int)(cur % base);
		carry = (int)(cur / base);
		i++;
	}
	while (a->size > 1 && a->array[a->size - 1] == 0)
		a->size--;
}
