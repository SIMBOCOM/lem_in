/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_graph_ants.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flogan <flogan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 14:27:55 by flogan            #+#    #+#             */
/*   Updated: 2019/12/23 14:44:48 by flogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual_header.h"

void	draw_polygon(int x, int y)
{
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f);
	glVertex2f(-x, y);
	glTexCoord2f(1.0f, 0.0f);
	glVertex2f(x, y);
	glTexCoord2f(1.0f, 1.0f);
	glVertex2f(x, -y);
	glTexCoord2f(0.0f, 1.0f);
	glVertex2f(-x, -y);
	glEnd();
}

void	draw_graph_line(t_total_data *data)
{
	int				i;
	int				j;
	t_lem_list		*temp_i;
	t_lem_list		*temp_j;

	i = -1;
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
	while (++i < data->size_matrix)
	{
		j = -1;
		while (++j != i)
		{
			if (data->matrix[i][j])
			{
				temp_i = search_room_index_list(data, i);
				temp_j = search_room_index_list(data, j);
				glVertex2f(temp_i->room.x, temp_i->room.y);
				glVertex2f(temp_j->room.x, temp_j->room.y);
			}
		}
	}
	glEnd();
}

void	draw_graph_room(t_total_data *data, t_texture *texture)
{
	t_lem_list *shift;

	shift = data->rooms;
	glBindTexture(GL_TEXTURE_2D, texture[2].tex);
	while (shift)
	{
		if (search_room_index(data, data->start) == shift->room.name)
			glBindTexture(GL_TEXTURE_2D, texture[0].tex);
		if (search_room_index(data, data->end) == shift->room.name)
			glBindTexture(GL_TEXTURE_2D, texture[1].tex);
		glPushMatrix();
		glTranslatef(shift->room.x, shift->room.y, 0.0f);
		draw_polygon((double)2.5, (double)2);
		glPopMatrix();
		shift = shift->next;
		glBindTexture(GL_TEXTURE_2D, texture[2].tex);
	}
}

void	draw_graph(t_total_data *data, t_texture *texture)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBindTexture(GL_TEXTURE_2D, 0);
	draw_graph_line(data);
	draw_graph_room(data, texture);
}

t_vec2	lerpvec2(t_total_data *data, float t, t_vec *tmp_rooms)
{
	t_room	*start_vector;
	t_room	*end_vector;
	t_vec2	a;
	t_vec2	b;
	float	angle;

	start_vector = search_room_name_elem(data, tmp_rooms->a);
	end_vector = search_room_name_elem(data, tmp_rooms->b);
	a = (t_vec2){(float)start_vector->x, (float)start_vector->y, 0};
	b = (t_vec2){(float)end_vector->x, (float)end_vector->y, 0};
	angle = atan2f(end_vector->x - start_vector->x,
				end_vector->y - start_vector->y);
	return ((t_vec2){(1.0f - t) * a.x + t * b.x,
				(1.0f - t) * a.y + t * b.y, angle});
}
