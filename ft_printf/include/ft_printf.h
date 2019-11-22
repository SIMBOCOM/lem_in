/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthai <rthai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 12:55:03 by flogan            #+#    #+#             */
/*   Updated: 2019/11/20 18:49:39 by rthai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft/libft.h"
# include <stddef.h>
# include <stdarg.h>
# include <stdlib.h>
# include <limits.h>
# define DI(x, y) (!x) ? (int)y : LM(x, y)
# define OUX(x, y) (!x) ? (unsigned int)y : ULM(x, y)
# define LM(x, y) (x == 'l') ? (long)y : HH(x,y)
# define HH(x, y) (x == *(short*)"hh") ? (char)y : H(x,y)
# define H(x, y) (x == 'h') ? (short)y : LL(x,y)
# define LL(x, y) (x == *(short*)"ll") ? (long long)y : J(x,y)
# define J(x, y) (x == 'j') ? (intmax_t)y : Z(x, y)
# define Z(x, y) (x == 'z') ? (size_t)y : L(x, y)
# define L(x, y) (x == 'L') ? (__int32_t)y : T(x,y)
# define ULM(x, y) (x == 'l') ? (unsigned long)y : UHH(x,y)
# define UHH(x, y) (x == *(short*)"hh") ? (unsigned char)y : UH(x,y)
# define UH(x, y) (x == 'h') ? (unsigned short)y : ULL(x,y)
# define ULL(x, y) (x == *(short*)"ll") ? (unsigned long long)y : UJ(x,y)
# define UJ(x, y) (x == 'j') ? (intmax_t)y : UL(x, y)
# define UL(x, y) (x == 'L') ? (uint32_t)y : T(x,y)
# define MAX(a,b) (a > b ? a : b)
# define SIGN(a) a >= 0 ? 0 : -a
# define MAX_ZERO 1000
# define T(x, y) (x == 't') ? (ptrdiff_t)y : y
# define MAX_SIZE_ARRAY 500
# define BASE 1000000000

typedef struct		s_arg
{
	unsigned			plus: 1;
	unsigned			space: 1;
	unsigned			minus: 1;
	unsigned			hash: 1;
	unsigned			zero: 1;
	unsigned			acc_flag: 1;
	char				*s;
	unsigned int		width;
	unsigned int		accuracy;
	unsigned long long	counter;
	unsigned			spec: 16;
	unsigned			type: 8;
	unsigned			sign: 1;
	unsigned			malloc: 1;
	unsigned			acminus: 1;
}					t_arg;
typedef struct		s_vector
{
	int		array[MAX_SIZE_ARRAY];
	int		size;
}					t_vector;
typedef struct		s_doub_float
{
	t_vector		whole_part;
	t_vector		fraction_part;
	long long		number_zero;
	int				power;
	int				sign;
}					t_doub_float;
char				*ft_itoa_bases(unsigned long long uvalue,
		long long value, t_arg *arg);
void				parser(char **format, t_arg *arg, va_list args, int *j);
void				parse_string(char **str, int *j, t_arg *arg);
void				print_numbers(t_arg *arg);
void				print_string(t_arg *arg);
void				print_char(t_arg *arg, va_list args);
void				parser_width(char **format, t_arg *arg, va_list args,
		int *j);
int					ft_printf(char *str, ...);
int					vector_append(t_vector *a, int i);
void				mult_long_to_short(t_vector *a, int b);
char				*print_double(double a, t_arg *arg);
void				sum_long_to_short(t_vector *a, int b);
void				sum_long_to_long(t_vector *a, t_vector b);
char				*print_long_double(long double a, t_arg *arg);
void				initialization(t_doub_float *number);
void				push_fraction_part(t_doub_float *number, __uint128_t *b,
	int start_mant);
void				push_whole_part(t_doub_float *number,
	__uint128_t *b, int start_matisa);
int					none(t_arg *arg);
unsigned long long	my_pow(int base, int power);
int					size_number(int number);
int					size_vector(t_vector *number);
void				number_zero(t_doub_float *number, int z);
t_vector			my_big_pow(int a, int base);
void				padding_zero(t_doub_float *number, char **ptr, t_arg *arg);
void				round_str(char *str);
void				convert_vector(t_vector *number, char **str, int *accuracy);
char				*convert_to_str(t_doub_float *number, t_arg *arg);
void				add_discharge(int *index, char *str);
char				*print_fd(t_arg *arg, va_list args);
void				print_nmbr(t_arg *arg);
void				pre(unsigned long long *uvalue, long long value,
t_arg *arg, int *base);
void				parse_string(char **str, int *j, t_arg *arg);

#endif
