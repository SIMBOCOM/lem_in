#include "lem_in.h"

int    parse_links(t_total_data *data, char *str)
{
	char *tmp;

	if (str[0] == '-')
		print_error(E_VAL_LINK);
	if (data->matrix == NULL)
		create_matrix(&(data->matrix), data->size_matrix);
	tmp = ft_strchr(str, '-');
	*(tmp++) = 0;
	if (search_room(data->hash_tab + hash_sum(tmp), tmp) == -1 || search_room(data->hash_tab + hash_sum(str), str) == -1)
		print_error(E_VAL_LINK);
	data->matrix[search_room(data->hash_tab + hash_sum(tmp), tmp)][search_room(data->hash_tab + hash_sum(str), str)] = 1;
	data->matrix[search_room(data->hash_tab + hash_sum(str), str)][search_room(data->hash_tab + hash_sum(tmp), tmp)] = 1;
	return (1);   
}

void     valid(char *str, int flag[2], t_total_data *data, int *i)
{
	if (!ft_strlen(str))
		print_error(E_NO_VALID);
	if (!ft_strcmp(str, "##start"))
	{
		//write(1, "FFFF\n", 5);
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
	if (ft_strchr(str, '-'))
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