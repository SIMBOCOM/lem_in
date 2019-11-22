/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_function_float.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthai <rthai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 17:08:05 by rthai             #+#    #+#             */
/*   Updated: 2019/11/19 16:37:56 by rthai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

unsigned long long		my_pow(int base, int power)
{
	unsigned long long result;

	power++;
	result = 1;
	if (!base)
		return (0);
	while (--power > 0)
		result *= base;
	return (result);
}

int						size_number(int number)
{
	long long	temp;
	int			size;

	size = 0;
	temp = 1;
	while ((number / temp))
	{
		size++;
		temp *= 10;
	}
	return (size);
}

int						size_vector(t_vector *number)
{
	return (size_number(number->array[number->size - 1])
	+ (number->size - 1) * 9);
}

void					number_zero(t_doub_float *number, int z)
{
	int num_zero;
	int size;

	size = size_vector(&(number->fraction_part));
	num_zero = z - size;
	number->number_zero = num_zero;
}

t_vector				my_big_pow(int a, int base)
{
	t_vector	result;
	int			five_in_13;

	five_in_13 = 1220703125;
	result.size = 1;
	result.array[0] = 1;
	if (a == 0)
	{
		result.array[0] = 0;
		return (result);
	}
	while (base > 0)
	{
		if (base >= 13)
		{
			mult_long_to_short(&result, five_in_13);
			base -= 13;
		}
		else
		{
			mult_long_to_short(&result, my_pow(a, base));
			base = 0;
		}
	}
	return (result);
}
