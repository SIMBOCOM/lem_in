#ifndef VISUAL_HEADER_H
#define VISUAL_HEADER_H
#include <SDL.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <SDL_image.h>
#include "../lem_in.h"

typedef struct s_texture
{
	GLuint tex;
	int w;
	int h;
} t_texture;

typedef struct	s_vec2
{
	float x;
	float y;
	float angle;
}				t_vec2;

typedef struct	s_vec
{
	char *ant;
	char *a;
	char *b;
	struct s_vec *next;
}				t_vec;

t_lem_list *search_room_index_list(t_total_data *data, int index);
t_room		*search_room_name_elem(t_total_data *data, char *str);

#endif
