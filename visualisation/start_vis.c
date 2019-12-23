/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_vis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flogan <flogan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 14:28:38 by flogan            #+#    #+#             */
/*   Updated: 2019/12/23 14:45:27 by flogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual_header.h"

void	loadtexture(t_texture *inputtexture, const char *path_to_texture,
					GLint texturefiltration)
{
	SDL_Surface		*surface;
	Uint32			colorkey;

	surface = IMG_Load(path_to_texture);
	if (surface == NULL)
	{
		printf("Texture load error %s\n", SDL_GetError());
		return ;
	}
	colorkey = SDL_MapRGB(surface->format, 255, 30, 255);
	SDL_SetColorKey(surface, SDL_TRUE | SDL_RLEACCEL, colorkey);
	glGenTextures(1, &inputtexture->tex);
	glBindTexture(GL_TEXTURE_2D, inputtexture->tex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0,
				GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texturefiltration);
	inputtexture->w = surface->w;
	inputtexture->h = surface->h;
	SDL_FreeSurface(surface);
}

void	initglandsdl(SDL_Window **win)
{
	SDL_GLContext glcontext;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("Unable to init SDL, error: ");
		exit(1);
	}
	*win = SDL_CreateWindow("Some cool visualization.",
							SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
							WIDTH, HEIGHT,
							SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	glcontext = SDL_GL_CreateContext(*win);
	if (*win == NULL)
	{
		printf("Unable to create window: ");
		exit(1);
	}
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_TEXTURE_2D);
	glMatrixMode(GL_PROJECTION);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glLoadIdentity();
}

void	init_vis(t_total_data *data, t_texture *texture)
{
	texture->win = NULL;
	initglandsdl(&(texture->win));
	gluOrtho2D(-WIDTH / 2, WIDTH / 2, -HEIGHT / 2, HEIGHT / 2);
	glScalef(20.0f, 20.0f, 10.0f);
	data->end = -1;
	data->start = -1;
	data->size_matrix = 0;
	data->numb_ants = 0;
	data->matrix = NULL;
	data->rooms = NULL;
}

void	vis_load_texture(t_texture *texture)
{
	loadtexture(texture, "visualisation/pictures/starter.png", GL_NEAREST);
	loadtexture(texture + 1, "visualisation/pictures/exiter.png", GL_NEAREST);
	loadtexture(texture + 2, "visualisation/pictures/but1.png", GL_NEAREST);
	loadtexture(texture + 3, "visualisation/pictures/packman1.png", GL_NEAREST);
}

void	work_window(t_total_data *data, t_texture *texture)
{
	char		*tmp;
	int			antrun;
	SDL_Event	event;

	antrun = 0;
	tmp = NULL;
	parser_vis(data);
	draw_graph(data, texture);
	SDL_GL_SwapWindow(texture->win);
	while (1)
	{
		if (antrun)
			parser_ants_run(data, texture, &tmp);
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				exit(1);
			if (event.type == SDL_MOUSEBUTTONDOWN)
				antrun = !antrun;
		}
	}
}
