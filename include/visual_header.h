/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_header.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flogan <flogan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 14:30:03 by flogan            #+#    #+#             */
/*   Updated: 2019/12/23 14:38:51 by flogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUAL_HEADER_H
# define VISUAL_HEADER_H
# include "lem_in.h"
# include <OpenGL/gl.h>
# include <OpenGL/glu.h>
# include </Users/flogan/.brew/include/SDL2/SDL.h>
# include </Users/flogan/.brew/include/SDL2/SDL_image.h>

typedef struct	s_texture
{
	SDL_Window	*win;
	GLuint		tex;
	int			w;
	int			h;
}				t_texture;

typedef struct	s_vec2
{
	float x;
	float y;
	float angle;
}				t_vec2;

typedef struct	s_vec
{
	char			*ant;
	char			*a;
	char			*b;
	struct s_vec	*next;
}				t_vec;

t_lem_list		*search_room_index_list(t_total_data *data, int index);
t_room			*search_room_name_elem(t_total_data *data, char *str);
void			init_vis(t_total_data *data, t_texture *texture);
void			vis_load_texture(t_texture *texture);
void			initglandsdl(SDL_Window **win);
void			loadtexture(t_texture *inputtexture,
					const char *path_to_texture, GLint texturefiltration);
void			draw_polygon(int x, int y);
void			draw_graph_line(t_total_data *data);
void			draw_graph_room(t_total_data *data, t_texture *texture);
void			draw_graph(t_total_data *data, t_texture *texture);
t_vec2			lerpvec2(t_total_data *data, float t, t_vec *tmp_rooms);
void			work_window(t_total_data *data, t_texture *texture);
char			*search_room_vector(char *str, char **arr2, t_total_data *data);
void			vis_ants_run(t_total_data *data,
					t_texture *texture, t_vec *rooms);
void			ants_start(t_total_data *data, char *str, char **prev,
					t_texture *texture);
void			push_coord_ants(t_vec **rooms, char *str);
void			create_rooms_vector(t_vec **rooms, char *str, char *prev,
					t_total_data *data);
void			create_coord(t_total_data *data);
void			parser_ants_run(t_total_data *data,
					t_texture *texture, char **tmp);
void			parser_vis(t_total_data *data);

#endif
