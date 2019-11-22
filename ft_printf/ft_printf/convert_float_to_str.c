/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_float_to_str.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthai <rthai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 17:10:53 by rthai             #+#    #+#             */
/*   Updated: 2019/11/19 16:37:38 by rthai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

void	padding_zero(t_doub_float *number, char **ptr, t_arg *arg)
{
	while (number->number_zero && arg->accuracy)
	{
		*(*ptr)++ = '0';
		number->number_zero--;
		arg->accuracy--;
	}
}

void	round_str(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	if (i && str[--i] >= '5')
	{
		while (i && (str[i - 1] == '9' || str[i - 1] == '.'))
		{
			if (str[i - 1] != '.')
				str[i - 1] = '0';
			i--;
		}
		add_discharge(&i, str);
	}
}

void	convert_vector(t_vector *number, char **str, int *accuracy)
{
	int base;
	int b;
	int i;

	i = number->size;
	while (--i >= 0 && *accuracy)
	{
		b = number->array[i];
		if (i == number->size - 1)
			base = my_pow(10, size_number(b) - 1);
		else
			base = 100000000;
		while (base > 0 && *accuracy)
		{
			*(*str)++ = b / base + '0';
			b %= base;
			base /= 10;
			(*accuracy)--;
		}
	}
}

char	*convert_to_str(t_doub_float *number, t_arg *arg)
{
	int		size_whole;
	char	*result;
	char	*ptr;

	arg->accuracy++;
	if (!(size_whole = size_vector(&(number->whole_part))))
		size_whole++;
	result = (char*)malloc(sizeof(char) * (size_whole + arg->accuracy + 2));
	ptr = result;
	convert_vector(&(number->whole_part), &ptr, &size_whole);
	if (arg->hash || arg->accuracy != 1)
		*ptr++ = '.';
	padding_zero(number, &ptr, arg);
	convert_vector(&(number->fraction_part), &ptr, (int*)&arg->accuracy);
	arg->accuracy++;
	while (--arg->accuracy)
		*ptr++ = '0';
	*ptr = 0;
	round_str(result);
	*(--ptr) = 0;
	return (result);
}

void	add_discharge(int *index, char *str)
{
	char	c;
	char	d;
	int		i;

	i = *index;
	if (!i && str[i] == '0')
	{
		c = str[i];
		str[i] = '1';
		i++;
		while (str[i])
		{
			d = str[i];
			str[i] = c;
			c = d;
			i++;
		}
	}
	else
		str[i - 1] = str[i - 1] + 1;
	*index = i;
}
