/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_ants.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flogan <flogan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 14:28:22 by flogan            #+#    #+#             */
/*   Updated: 2019/12/23 14:44:03 by flogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual_header.h"

char	*search_room_vector(char *str, char **arr2, t_total_data *data)
{
	int		i;
	char	*tmp;

	i = -1;
	while (arr2 && arr2[++i])
	{
		tmp = ft_strchr(arr2[i], '-');
		*(tmp++) = 0;
		if (!ft_strcmp(str, arr2[i] + 1))
		{
			*(--tmp) = '-';
			return (tmp + 1);
		}
		*(--tmp) = '-';
	}
	return (search_room_index(data, data->start));
}

void	vis_ants_run(t_total_data *data, t_texture *texture, t_vec *rooms)
{
	float	t;
	t_vec2	c;
	t_vec	*tmp_rooms;

	t = 0.0f;
	while (1)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		draw_graph(data, texture);
		glBindTexture(GL_TEXTURE_2D, texture[3].tex);
		if ((t += 0.02f) > 1.0f)
			break ;
		tmp_rooms = rooms;
		while (tmp_rooms)
		{
			c = lerpvec2(data, t, tmp_rooms);
			glPushMatrix();
			glTranslatef(c.x, c.y, 0.0f);
			glRotatef(c.angle * 180 / M_PI, 0.0f, 0.0f, -1.0f);
			draw_polygon((double)1, (double)1);
			glPopMatrix();
			tmp_rooms = tmp_rooms->next;
		}
		SDL_GL_SwapWindow(texture->win);
	}
}

void	ants_start(t_total_data *data, char *str, char **prev,
					t_texture *texture)
{
	char	*new;
	t_vec	*rooms;
	t_vec	*tmp_rooms;
	t_room	*end_vector;

	new = ft_strdup(str);
	rooms = NULL;
	create_rooms_vector(&rooms, str, *prev, data);
	vis_ants_run(data, texture, rooms);
	tmp_rooms = rooms;
	while (tmp_rooms)
	{
		end_vector = search_room_name_elem(data, tmp_rooms->b);
		glPushMatrix();
		glTranslatef(end_vector->x, end_vector->y, 0.0f);
		draw_polygon((double)1.5, (double)1);
		glPopMatrix();
		tmp_rooms = tmp_rooms->next;
	}
	if (*prev)
		free(*prev);
	*prev = ft_strdup(new);
	ft_printf("%s\n", *prev);
	free(new);
}
