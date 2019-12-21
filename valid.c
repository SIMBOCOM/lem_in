#include "lem_in.h"

int		parse_links(t_total_data *data, char *str, char *tmp)
{
	if (data->matrix == NULL)
		create_matrix(&(data->matrix), data->size_matrix, data->size_matrix);
	*(tmp++) = 0;
	if (search_room_name(data, tmp) == -1 || search_room_name(data, str) == -1)
	  print_error(E_VAL_LINK);
	if (!strcmp(str, tmp))
	  print_error(E_VAL_LINK);
	data->matrix[search_room_name(data, tmp)][search_room_name(data, str)] = 1;
	data->matrix[search_room_name(data, str)][search_room_name(data, tmp)] = 1;
	return (1);
}

char	*valid_linker(char *str)
{
	if (ft_strchr(str, '-'))
	{
		if (ft_strcmp(str, ft_strchr(str, '-')) && ft_strchr(str, '-')[-1] != ' ')
			return (ft_strchr(str, '-'));
		while (!ft_strcmp(str, ft_strchr(str, '-')))
		{
			str = ft_strchr(str, '-') + 1;
			if (!ft_strchr(str, '-'))
				return (NULL);
			if (ft_strchr(str, '-') &&  ft_strcmp(str, ft_strchr(str, '-')) && ft_strchr(str, '-')[-1] != ' ')
				return (ft_strchr(str, '-'));
		}
	}
	return (0);
}

void	valid(char *str, t_total_data *data, int *i)
{
	char *tmp;

	if (!ft_strlen(str))
		print_error(E_NO_VALID);
	if (!ft_strcmp(str, "##start"))
	{
		if (data->start != -1)
			print_error(E_START);
		data->start = *i;
	}
	if (!ft_strcmp(str,"##end"))
	{
		if (data->end != -1)
			print_error(E_END);
		data->end = *i;
	}
	if ((tmp = valid_linker(str)))
	{
		if (!data->matrix)
			data->size_matrix = *i;
		parse_links(data, str, tmp);
	}
	else if (!ft_strchr(str, '#'))
	{
		parser_room(data, str, *i);
		(*i)++;
	}
}