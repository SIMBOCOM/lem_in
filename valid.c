#include "lem_in.h"

int		parse_links(t_total_data *data, char *str)
{
	char *tmp;

	if (str[0] == '-' || str[0] == 'L')
		print_error(E_VAL_LINK);
	if (data->matrix == NULL)
		create_matrix(&(data->matrix), data->size_matrix);
	tmp = ft_strchr(str, '-');
	*(tmp++) = 0;
	if (search_room_name(data, tmp) == -1 || search_room_name(data, str) == -1)
		print_error(E_VAL_LINK);
	data->matrix[search_room_name(data, tmp)][search_room_name(data, str)] = 1;
	data->matrix[search_room_name(data, str)][search_room_name(data, tmp)] = 1;
	return (1);
}

int valid_linker(char *str)
{
	char *s;

	if (ft_strchr(str, '-'))
	{
		// ft_printf("%s\n", str);
		// ft_printf("%s\n", ft_strchr(str, '-'));
		// ft_printf("%d\n", ft_strcmp(str, ft_strchr(str, '-')) && ft_strchr(str, '-')[-1] != ' ');
		if (ft_strcmp(str, ft_strchr(str, '-')) && ft_strchr(str, '-')[-1] != ' ')
			return (1);
		while (!ft_strcmp(str, ft_strchr(str, '-')))
		{
			str = ft_strchr(str, '-') + 1;
			if (!ft_strchr(str, '-'))
				return (0);
			if (ft_strchr(str, '-') && ft_strcmp(str, ft_strchr(str, '-')) && ft_strchr(str, '-')[-1] != ' ')
				return (1);
		}
	}
	return (0);
}

void	valid(char *str, int flag[2], t_total_data *data, int *i)
{
	if (!ft_strlen(str))
		print_error(E_NO_VALID);
	if (!ft_strcmp(str, "##start"))
	{
		if (flag[0])
			ft_printf("flag  %d\n", flag[0]);
		data->start = *i;
		flag[0] = 1;
	}
	if (!ft_strcmp(str, "##end"))
	{
		if (flag[1])
			print_error(E_END);
		data->end = *i;
		flag[1] = 1;
	}
	if (valid_linker(str))
	{
		if (!data->matrix)
			data->size_matrix = *i;
		parse_links(data, str);
	}
	else if (!ft_strchr(str, '#'))
	{
		parser_room(data, str, *i);
		(*i)++;
	}
	free(str);
}