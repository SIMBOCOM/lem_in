#include "visual_header.h"

t_room		*search_room_name_elem(t_total_data *data, char *str)
{
	t_lem_list *shift;

	shift = data->rooms;
	while (shift && ft_strcmp(shift->room.name, str))
		shift = shift->next;
	if (shift)
		return (&shift->room);
	else
		return (NULL);
}

t_lem_list *search_room_index_list(t_total_data *data, int index)
{
	t_lem_list *shift;

	shift = data->rooms;
	while (shift && shift->index != index)
		shift = shift->next;
	return (shift);
}
