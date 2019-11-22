/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_function_parsers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthai <rthai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 19:48:11 by rthai             #+#    #+#             */
/*   Updated: 2019/11/19 16:37:58 by rthai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

char	*print_fd(t_arg *arg, va_list args)
{
	if (!arg->accuracy && !arg->acc_flag)
		arg->accuracy = 6;
	if (arg->spec == 'L')
		return (print_long_double((long double)va_arg(args, long double), arg));
	if (arg->spec == 'l')
		return (print_double((double)va_arg(args, double), arg));
	return (print_double((double)va_arg(args, double), arg));
}

void	parse_string(char **str, int *j, t_arg *arg)
{
	if (*(*str + *j) == '%' && *(*str + 1 + *j) == '%'
			&& (*j += 2) && (++(arg->counter)))
		ft_putchar(*((*str += *j) - 1));
	else if (*(*str + *j) == '%' && *(*str + 1 + *j) == '\0' && (*j += 1))
		*str += *j;
	else
	{
		ft_putchar(*(*str)++);
		arg->counter++;
	}
	*j = 0;
}

void	pre(unsigned long long *uvalue, long long value, t_arg *arg, int *base)
{
	if (value != 0)
	{
		if (value < 0 && *base == 10 && (*uvalue = -value))
			arg->sign = 1;
		else
			*uvalue = value;
	}
}

int		none(t_arg *arg)
{
	if (arg->plus || arg->space || arg->minus ||
	arg->hash || arg->zero || arg->acc_flag ||
	arg->width || arg->accuracy || arg->sign)
		return (0);
	return (1);
}

void	print_nmbr(t_arg *arg)
{
	if (arg->plus)
		ft_putchar('+');
	else if (arg->type == 'o' && arg->hash)
		ft_putchar('0');
	else if (arg->width)
		ft_putchar(' ');
	else
		--(arg->counter);
}
