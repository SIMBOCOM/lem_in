/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers_printf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthai <rthai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 16:02:37 by flogan            #+#    #+#             */
/*   Updated: 2019/11/19 16:38:05 by rthai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

void	flags(char **format, t_arg *arg, int *j)
{
	while ((*format)[*j] && ft_strchr("-+ #0", (*format)[*j]))
	{
		((*format)[*j] == '+') ? arg->plus = 1 : 0;
		((*format)[*j] == ' ') ? arg->space = 1 : 0;
		((*format)[*j] == '-') ? arg->minus = 1 : 0;
		((*format)[*j] == '#') ? arg->hash = 1 : 0;
		((*format)[*j] == '0') ? arg->zero = 1 : 0;
		(*j)++;
	}
}

void	parser_type(char **format, t_arg *arg, va_list args, int *j)
{
	if ((*format)[*j] && ft_strchr("diouxXaAeEfFgGncpsSnDIOU", (*format)[*j]))
	{
		if (ft_strchr("DIOU", (*format)[*j]) && (arg->spec = 27756))
			arg->type ^= ft_tolower((*format)[*j]);
		else
			arg->type ^= (*format)[*j];
		(*j)++;
		if (ft_strchr("di", arg->type))
			arg->s = ft_itoa_bases(0, DI(arg->spec, va_arg(args, long long)),
					arg);
		else if (ft_strchr("ouxX", arg->type))
			arg->s = ft_itoa_bases(OUX(arg->spec, va_arg(args,
							unsigned long long)), 0, arg);
		else if (ft_strchr("c", arg->type))
			print_char(arg, args);
		else if (ft_strchr("s", arg->type))
			(arg->s) = va_arg(args, char*);
		else if (ft_strchr("p", arg->type) && (arg->hash = 1))
			arg->s = ft_itoa_bases(va_arg(args, unsigned long long), 0, arg);
		else if (ft_strchr("f", arg->type))
			arg->s = print_fd(arg, args);
		else
			arg->s = ft_itoa_bases(0, va_arg(args, int), arg);
	}
}

void	parser_spec(char **format, t_arg *arg, va_list args, int *j)
{
	if ((*format)[*j] && ft_strchr("lhjztL", (*format)[*j]))
	{
		arg->spec ^= (*format)[*j];
		if (!(arg->spec ^ (*format)[*j + 1]))
		{
			if (!ft_strchr("lhjztL", (*format)[*j + 2]))
			{
				arg->spec <<= 8;
				arg->spec ^= (*format)[*j + 1];
			}
			(*j)++;
		}
		(*j)++;
	}
	while ((*format)[*j] && ft_strchr("lhjztL", (*format)[*j]))
		(*j)++;
	flags(format, arg, j);
	parser_type(format, arg, args, j);
}

void	parser_accuracy(char **format, t_arg *arg, va_list args, int *j)
{
	int i;

	if ((*format)[*j] && ft_strchr(".", (*format)[*j]))
	{
		arg->acc_flag = 1;
		(*j)++;
		if ((*format)[*j] && (*format)[*j] == '*')
		{
			i = va_arg(args, int);
			if (i < 0 && (arg->acminus = 1))
				i *= -1;
			arg->accuracy = i;
			(*j)++;
		}
		while ((*format)[*j] && ft_strchr("0123456789", (*format)[*j]))
			arg->accuracy = arg->accuracy * 10 + (*format)[(*j)++] - '0';
	}
	while ((*format)[*j] && ft_strchr(".0123456789", (*format)[*j]))
		(*j)++;
	flags(format, arg, j);
	parser_spec(format, arg, args, j);
}

void	parser_width(char **format, t_arg *arg, va_list args, int *j)
{
	int i;

	(*j)++;
	flags(format, arg, j);
	if ((*format)[*j] && (*format)[*j] == '*')
	{
		i = va_arg(args, int);
		if (i < 0 && (arg->minus = 1))
			i *= -1;
		arg->width = i;
		(*j)++;
	}
	if ((*format)[*j] && ft_strchr("0123456789", (*format)[*j]))
		arg->width = 0;
	while ((*format)[*j] && ft_strchr("0123456789", (*format)[*j]))
		arg->width = arg->width * 10 + (*format)[(*j)++] - '0';
	flags(format, arg, j);
	parser_accuracy(format, arg, args, j);
}
