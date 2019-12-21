//
// Created by Rookwood Thai on 21/12/2019.
//

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
}				t_vec2;

typedef struct	s_vec
{
	char *ant;
	char *a;
	char *b;
	struct s_vec *next;
}				t_vec;

#endif
