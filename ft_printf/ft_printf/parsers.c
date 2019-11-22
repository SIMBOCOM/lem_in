/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthai <rthai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 14:03:42 by flogan            #+#    #+#             */
/*   Updated: 2019/11/19 16:38:31 by rthai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

void	print_zero(t_arg *arg, long len, char chr, int flag)
{
	long i;
	char *ptr;

	i = 0;
	ptr = malloc(sizeof(char) * (len + 1));
	while (i < len)
		ptr[i++] = chr;
	write(1, ptr, len);
	free(ptr);
	if (flag)
	{
		arg->counter += len;
		arg->width -= len;
	}
	else
		arg->accuracy -= len;
}

void	apendix_sqrt(t_arg *arg,
unsigned int *size, char *sign, int *hash)
{
	long len;

	len = ft_strlen(arg->s);
	if (!arg->minus && arg->zero && arg->type == 'f'
	&& arg->width > len + arg->sign)
		print_zero(arg, arg->width - (len + arg->sign), '0', 1);
	arg->counter += *size += (arg->acc_flag && arg->accuracy > len)
	? arg->accuracy : len;
	if ((arg->space && arg->type && ft_strchr("dieEgG", arg->type) &&
	*sign == 0 && (!arg->width || arg->width > len ||
	ft_strchr("di", arg->type)) && (++(arg->counter)) && (*size)++))
		ft_putchar(' ');
	if (((arg->type != 'f' && arg->acc_flag) || !arg->zero) &&
	!arg->minus && arg->width > *size)
		print_zero(arg, arg->width - *size, ' ', 1);
	if (*hash && arg->type == 'o' && (!arg->accuracy || arg->accuracy--))
		ft_putchar('0');
	else if (*hash && ((arg->type == 'x' && ft_strcmp(arg->s, "0")) ||
	arg->type == 'p'))
		ft_putstr("0x");
	else if (*hash && arg->type == 'X' && ft_strcmp(arg->s, "0"))
		ft_putstr("0X");
	else if (*hash)
		arg->counter -= (arg->type == 'o') ? 1 : 2;
}

void	apendix_print_numbers(t_arg *arg,
unsigned int *size, char *sign, int *hash)
{
	long len;

	len = ft_strlen(arg->s);
	if (arg->sign && (++(*size)))
		*sign = '-';
	else if (!arg->sign && arg->plus && arg->type && ft_strchr("difFeEgG",
	arg->type) && !(arg->acc_flag && !ft_strcmp(arg->s, "0")
	&& arg->accuracy == 0 && arg->type != 'f') && (++(*size)))
		*sign = '+';
	if (arg->type == 'p')
		*hash = 1;
	*size += *hash += (*hash && arg->hash && ft_strchr("xXp", arg->type));
	if (!*sign && arg->type == 'f' && arg->space)
	{
		ft_putchar(' ');
		arg->width--;
	}
	if (*sign && arg->type == 'f' && arg->zero && (arg->sign = 1))
	{
		ft_putchar(*sign);
		*sign = 0;
	}
	if (arg->type == 'o' && *hash && arg->accuracy > len && !(arg->counter--))
		arg->width++;
	apendix_sqrt(arg, size, sign, hash);
}

void	print_numbers(t_arg *arg)
{
	unsigned int		size;
	char				sign;
	int					hash;
	long				len;

	size = 0;
	sign = 0;
	len = ft_strlen(arg->s);
	hash = (arg->hash && ft_strchr("oxXp", arg->type) &&
	ft_strcmp(arg->s, "0"));
	apendix_print_numbers(arg, &size, &sign, &hash);
	if (sign)
		ft_putchar(sign);
	if (!arg->minus && arg->zero && (!arg->acc_flag && !arg->accuracy)
	&& arg->width > size)
		print_zero(arg, arg->width - size, '0', 1);
	if (arg->accuracy > len)
		print_zero(arg, arg->accuracy - len, '0', 0);
	if (arg->acc_flag && !ft_strcmp(arg->s, "0") && arg->accuracy == 0
	&& arg->type != 'f')
		print_nmbr(arg);
	else
		write(1, arg->s, len);
	if (arg->minus && arg->width > size)
		print_zero(arg, arg->width - size, ' ', 1);
}

char	*ft_itoa_bases(unsigned long long uvalue, long long value, t_arg *arg)
{
	char					*str;
	int						size;
	char					*tab[2];
	int						base;
	unsigned long long		tmp;

	base = (arg->type == 'x' || arg->type == 'X' || arg->type == 'p') ? 16 : 10;
	(arg->type == 'o') ? base = 8 : 0;
	size = 0;
	tab[0] = "0123456789abcdef";
	tab[1] = "0123456789ABCDEF";
	pre(&uvalue, value, arg, &base);
	tmp = uvalue;
	while (tmp /= base)
		size++;
	str = (char*)malloc(sizeof(char) * ++size + 1);
	str[size] = '\0';
	arg->malloc = 1;
	while (size > 0)
	{
		str[--size] = (arg->type == 'x' || arg->type == 'p') ?
			tab[0][uvalue % base] : tab[1][uvalue % base];
		uvalue /= base;
	}
	return (str);
}
