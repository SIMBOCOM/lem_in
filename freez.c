#include "lem_in.h"

void	freez(t_total_data *data)
{
	t_lem_list	*tmp;
	t_lem_list	*tmp1;
	int i;
	int j;

	i = -1;
	tmp = data->rooms;
	while (tmp)
	{
		tmp1 = tmp;
		tmp = tmp->next;
		free(tmp1->room.name);
		free(tmp1);
	}
	if (data->path_first.tarakan)
		free(data->path_first.tarakan);
	if (data->path_second.tarakan)
		free(data->path_second.tarakan);


	while (++i < data->path_first.numb_path)
		free(data->path_first.matrix_path[i]);
	i = -1;
	free(data->path_first.matrix_path);
	while (++i < data->path_first.numb_path)
		free(data->path_second.matrix_path[i]);
	free(data->path_second.matrix_path);

//	ft_memdel((void**)data->matrix);
}