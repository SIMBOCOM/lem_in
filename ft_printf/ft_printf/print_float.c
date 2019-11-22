/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_float.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthai <rthai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 20:58:13 by rthai             #+#    #+#             */
/*   Updated: 2019/11/19 16:38:28 by rthai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

void	initialization(t_doub_float *number)
{
	number->whole_part.size = 1;
	number->number_zero = MAX_ZERO;
	if (number->power < 0)
	{
		number->whole_part.array[0] = 0;
		number->fraction_part.size = 1;
		number->fraction_part = my_big_pow(5, -number->power);
		number_zero(number, -number->power);
		return ;
	}
	number->whole_part.array[0] = 1;
	number->fraction_part.size = 1;
	number->fraction_part.array[0] = 0;
}

void	push_fraction_part(t_doub_float *number, __uint128_t *b, int start_mant)
{
	int i;
	int shift;

	i = 0;
	if (number->power > 0)
		shift = start_mant - number->power;
	else
		shift = start_mant;
	while (--shift >= 0)
	{
		mult_long_to_short(&(number->fraction_part), 10);
		sum_long_to_long(&(number->fraction_part),
		my_big_pow((int)((*b >> shift) & 1) * 5,
		i + 1 + (SIGN(number->power))));
		i++;
	}
	number_zero(number, i + (SIGN(number->power)));
}

void	push_whole_part(t_doub_float *number, __uint128_t *b, int start_matisa)
{
	int i;

	i = 0;
	while (i < number->power)
	{
		mult_long_to_short(&(number->whole_part), 2);
		if (start_matisa - i >= 0)
			sum_long_to_short(&(number->whole_part),
			(*b >> (start_matisa - i)) & 1);
		i++;
	}
}

char	*print_double(double a, t_arg *arg)
{
	t_doub_float	number;
	__uint128_t		*b;
	int				i;

	i = 0;
	b = (__uint128_t*)&a;
	arg->sign = (*b >> 63) & 1;
	number.power = ((*b & 0x7FF0000000000000) >> 52) - 1023;
	initialization(&number);
	*b = *b & 0x000FFFFFFFFFFFFF;
	push_whole_part(&number, b, 51);
	push_fraction_part(&number, b, 52);
	return (convert_to_str(&number, arg));
}

char	*print_long_double(long double a, t_arg *arg)
{
	t_doub_float	number;
	__uint128_t		*b;
	int				i;

	i = 0;
	b = (__uint128_t*)&a;
	arg->sign = (*b >> 79) & 1;
	i = 79;
	number.power = 0;
	while (--i >= 64)
		number.power = number.power * 2 + ((*b >> i) & 1);
	number.power = number.power - 16383;
	initialization(&number);
	push_whole_part(&number, b, 62);
	push_fraction_part(&number, b, 63);
	return (convert_to_str(&number, arg));
}
