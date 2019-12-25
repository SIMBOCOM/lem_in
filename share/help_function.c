/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flogan <flogan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 14:30:46 by flogan            #+#    #+#             */
/*   Updated: 2019/12/23 15:07:41 by flogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_error(int id)
{
	write(2, "ERROR\n", 6);
	exit(id);
}

int		ft_atoi_mod(const char *str)
{
	__int128	res;
	int			negative;

	negative = 1;
	res = 0;
	if (*str == '-')
		negative = -1;
	if (*str == '-' || *str == '+')
		++str;
	if (!*str)
		print_error(E_INT);
	while (*str && *str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - 48);
		++str;
	}
	if (*str || !((res *= negative) >= INT_MIN && res <= INT_MAX))
		print_error(E_INT);
	return ((int)res);
}

void	print_str(char **str)
{
	if (*str)
	{
		ft_printf("%s\n", *str);
		ft_strdel(str);
	}
	*str = NULL;
}
