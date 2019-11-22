/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthai <rthai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 13:38:01 by flogan            #+#    #+#             */
/*   Updated: 2019/11/19 16:37:53 by rthai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

void	apendix_parser(char **format, t_arg *arg, int *j, int i)
{
	while ((*format)[*j + i] && (*format)[*j + i] != '%')
		i++;
	if (i)
		arg->s = ft_strsub(*format, *j, i);
	else if ((*format)[*j] == '%' && (++(*format)))
		arg->s = ft_strdup("%");
	print_numbers(arg);
	(*format) += i;
}

void	parser(char **format, t_arg *arg, va_list args, int *j)
{
	int i;

	i = 0;
	parser_width(format, arg, args, j);
	if (arg->type && !ft_strchr("csS", arg->type)
	&& none(arg) && (write(1, arg->s, ft_strlen(arg->s))))
		arg->counter = ft_strlen(arg->s);
	else if (arg->type)
	{
		if (arg->type != 's' && arg->acminus == 1 && (arg->acc_flag--))
			arg->accuracy = 0;
		if (ft_strchr("diouxXfp", arg->type))
			print_numbers(arg);
		if (ft_strchr("s", arg->type))
			print_string(arg);
	}
	else if (!arg->s && (*format)[*j] && (arg->malloc = 1))
		apendix_parser(format, arg, j, i);
	(*format) += *j;
	*j = 0;
}

void	print_char(t_arg *arg, va_list args)
{
	int c;

	c = va_arg(args, unsigned int);
	if (none(arg) && (arg->counter += 1) && (write(1, &c, 1)))
		return ;
	while (!arg->minus && arg->zero && (!arg->acc_flag && !arg->accuracy)
			&& arg->width > 1 && (--(arg->width)) && (++(arg->counter)))
		ft_putchar('0');
	while (!arg->minus && arg->width > 1 &&
			arg->width-- && (++(arg->counter)))
		ft_putchar(' ');
	ft_putchar(c);
	++(arg->counter);
	while (arg->minus && arg->width > 1 &&
			arg->width-- && (++(arg->counter)))
		ft_putchar(' ');
}

void	print_string(t_arg *arg)
{
	unsigned int size;

	if (arg->s == NULL && (arg->malloc = 1))
		arg->s = ft_strdup("(null)");
	if (none(arg) && (arg->counter = ft_strlen(arg->s))
	&& (write(1, arg->s, ft_strlen(arg->s))))
		return ;
	size = (arg->acc_flag && arg->accuracy < ft_strlen(arg->s)) ?
		arg->accuracy : ft_strlen(arg->s);
	while (!arg->minus && arg->zero && (!arg->acc_flag && !arg->accuracy)
			&& arg->width > size && (--(arg->width)) && (++(arg->counter)))
		ft_putchar('0');
	while (!arg->minus && arg->width > size &&
			arg->width-- && (++(arg->counter)))
		ft_putchar(' ');
	write(1, arg->s, size);
	arg->counter += size;
	while (arg->minus && arg->width > size &&
			arg->width-- && (++(arg->counter)))
		ft_putchar(' ');
}

int		ft_printf(char *str, ...)
{
	int			j;
	long long	counter;
	va_list		args;
	t_arg		array;

	if (!ft_strcmp(str, "%"))
		return (0);
	j = 0;
	counter = 0;
	ft_bzero((void*)&array, sizeof(array));
	va_start(args, str);
	while (str[j])
	{
		ft_bzero((void*)&array, sizeof(array));
		(str[j] && str[j] == '%' && str[j + 1] != '%' && str[j + 1] != '\0') ?
			parser(&str, &array, args, &j) : parse_string(&str, &j, &array);
		counter += array.counter;
		if (array.malloc)
			ft_strdel(&array.s);
	}
	va_end(args);
	return (counter);
}
