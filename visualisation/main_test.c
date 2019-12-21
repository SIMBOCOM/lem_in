/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthai <rthai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 17:51:29 by rthai             #+#    #+#             */
/*   Updated: 2019/12/21 17:52:51 by rthai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual_header.h"

SDL_Window *win;

void	create_coord(t_total_data *data)
{
	double	angle;
	double	ang_shift;
	t_lem_list *shift;
	int step;

	step = 0;
	shift = data->rooms;
	angle = 0;
	ang_shift = (double)360 / (double)data->size_matrix;
	while (shift)
	{
		shift->room.x = (50 / 2) * cos(angle*M_PI/180);
		shift->room.y = (50 / 2) * sin(angle*M_PI/180);
		angle += ang_shift;
		shift = shift->next;
	}
}

void	loadTexture(t_texture* inputTexture, const char* pathToTexture, GLint textureFiltration)
{
	SDL_Surface* surface;
	surface = IMG_Load(pathToTexture);

	if (surface==NULL)
	{
		printf("Texture load error %d\n", SDL_GetError());
		return;
	}
	Uint32 colorkey = SDL_MapRGB( surface->format, 255, 30, 255);
	SDL_SetColorKey( surface, SDL_TRUE | SDL_RLEACCEL, colorkey);
	glGenTextures(1,&inputTexture->tex);
	glBindTexture(GL_TEXTURE_2D, inputTexture->tex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, textureFiltration);
	inputTexture->w = surface->w;
	inputTexture->h = surface->h;
	SDL_FreeSurface(surface);
}

void	initGLandSDL()
{
	if ( SDL_Init(SDL_INIT_EVERYTHING) < 0 )
	{
		printf("Unable to init SDL, error: ");
		exit(1);
	}
	win = SDL_CreateWindow("Some cool visualization.",
							SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
							WIDTH, HEIGHT,
							SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	SDL_GLContext glcontext = SDL_GL_CreateContext(win); // создаем контекст OpenGL
	if(win == NULL)
	{
		printf("Unable to create window: ");
		exit(1);
	}
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // устанавливаем фоновый цвет на черный
	glEnable(GL_TEXTURE_2D);
	glMatrixMode(GL_PROJECTION);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glLoadIdentity();
}

void	draw_polygon(int x, int y)
{
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f);
	glVertex2f(-x, y);    // Низ лево
	glTexCoord2f(1.0f, 0.0f);
	glVertex2f( x,  y);    // Низ право
	glTexCoord2f(1.0f, 1.0f);
	glVertex2f(x, -y);    // Верх право
	glTexCoord2f(0.0f, 1.0f);
	glVertex2f( -x, -y);    // Верх лево
	glEnd();
}

void	draw_graph_line(t_total_data *data)
{
	int i;
	int j;
	t_lem_list *temp_i;
	t_lem_list *temp_j;

	i = -1;
	glColor4f(1.0f, 1.0f,1.0f, 1.0f);
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
	t_lem_list *shift = data->rooms;

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
	t_room *start_vector;
	t_room *end_vector;
	t_vec2 a;
	t_vec2 b;
	float angle;

	start_vector = search_room_name_elem(data, tmp_rooms->a);
	end_vector = search_room_name_elem(data, tmp_rooms->b);
	a = (t_vec2){(float)start_vector->x, (float)start_vector->y, 0};
	b = (t_vec2){(float)end_vector->x, (float)end_vector->y, 0};
	angle = atan2f(end_vector->x - start_vector->x, end_vector->y - start_vector->y);
	return ((t_vec2){(1.0f - t) * a.x + t * b.x, (1.0f - t) * a.y + t * b.y, angle});
}

char	*search_room_vector(char *str, char **arr2, t_total_data *data)
{
	int i;
	char *tmp;

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
	ft_printf("\n");
	return (search_room_index(data, data->start));
}

void	push_coord_ants(t_vec **rooms, char *str)
{
	char **arr;
	char *tmp;
	int i;
	t_vec *tmp_rooms;

	tmp_rooms = *rooms;
	i = -1;
	arr = ft_strsplit(str, ' ');
	while (arr[++i])
	{
		tmp = ft_strchr(arr[i], '-');
		*(tmp++) = 0;
		tmp_rooms->ant = arr[i] + 1;
		tmp_rooms->b = tmp;
		tmp_rooms->a = NULL;
		if (arr[i + 1])
		{
			if (!(tmp_rooms->next = malloc(sizeof(t_vec))))
				print_error(E_MALLOC);
		}
		else
			tmp_rooms->next = NULL;
		tmp_rooms = tmp_rooms->next;
	}
}

void	create_rooms_vector(t_vec **rooms, char *str, char *prev, t_total_data *data)
{
	char **arr2;
	t_vec *tmp_rooms;

	if (!(*rooms = malloc(sizeof(t_vec))))
		print_error(E_MALLOC);
	tmp_rooms = *rooms;
	push_coord_ants(rooms, str);
	arr2 = ft_strsplit(prev, ' ');
	while (tmp_rooms)
	{
		tmp_rooms->a = search_room_vector(tmp_rooms->ant, arr2, data);
		tmp_rooms = tmp_rooms->next;
	}
}

void	vis_ants_run(t_total_data *data, t_texture *texture, t_vec *rooms)
{
	float t;
	t_vec2 c;
	t_vec *tmp_rooms;

	t = 0.0f;
	while (1)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		draw_graph(data, texture);
		glBindTexture(GL_TEXTURE_2D, texture[3].tex);
		t += 0.02f;
		if (t > 1.0f)
			break;
		tmp_rooms = rooms;
		while (tmp_rooms)
		{
			c = lerpvec2(data, t, tmp_rooms);
			glPushMatrix();
			glTranslatef(c.x, c.y, 0.0f);
			glRotatef(c.angle*180/M_PI, 0.0f, 0.0f, -1.0f);
			draw_polygon((double)1, (double)1);
			glPopMatrix();
			tmp_rooms = tmp_rooms->next;
		}
		SDL_GL_SwapWindow(win);
	}
}

void	ants_start(t_total_data *data, char *str, char **prev, t_texture *texture)
{
	char *new = ft_strdup(str);
	t_vec *rooms;
	t_vec *tmp_rooms;

	ft_printf("%s\n", *prev);
	rooms = NULL;
	create_rooms_vector(&rooms, str, *prev, data);
	vis_ants_run(data, texture, rooms);
	tmp_rooms = rooms;
	while (tmp_rooms)
	{
		t_room *end_vector = search_room_name_elem(data, tmp_rooms->b);
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

void	parser_vis(t_total_data *data, t_texture *texture)
{
	char	*str;
	int		i;
	char *tmp;

	tmp = NULL;
	str = 0;
	i = 0;
	while (get_next_line(0, &str) && str[0] == '#')
		print_str(str);
	data->numb_ants = ft_atoi(str);
	print_str(str);
	while (get_next_line(0, &str))
	{
		ft_printf("%s$\n", str);
		if (!ft_strcmp(str, ""))
			break;
		else
			valid(str, data, &i);
	}
	create_coord(data);
}

void	parser_ants_run(t_total_data *data, t_texture *texture, char **tmp)
{
	char *str;

	str = NULL;
	draw_graph(data, texture);
	if (!(get_next_line(0, &str)))
		return ;
	if (str[0] == 'L')
	{
		ants_start(data, str, tmp, texture);
		SDL_GL_SwapWindow(win);
		usleep(100000);
	}
	if (str)
		free(str);
}

void	work_window(t_total_data *data, t_texture *texture)
{
	char *tmp;
	int antrun;
	SDL_Event event;

	antrun = 0;
	tmp = NULL;
	parser_vis(data, texture);
	draw_graph(data, texture);
	SDL_GL_SwapWindow(win);
	while (1)
	{
		if (antrun)
			parser_ants_run(data, texture, &tmp);
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
					break;
			if (event.type == SDL_MOUSEBUTTONDOWN)
				antrun = !antrun;
		}
	}
}

void	vis_load_texture(t_texture *texture)
{
	loadTexture(texture, "pictures/starter.png", GL_NEAREST);
	loadTexture(texture + 1, "pictures/exiter.png", GL_NEAREST);
	loadTexture(texture + 2, "pictures/ranger2.png", GL_NEAREST);
	loadTexture(texture + 3, "pictures/packman1.png", GL_NEAREST);
}

int main()
{
	t_texture texture[4];

	win = NULL;
	initGLandSDL(&win);
	gluOrtho2D(-WIDTH / 2, WIDTH / 2, -HEIGHT / 2, HEIGHT / 2);
	glScalef(20.0f, 20.0f, 10.0f);


	t_total_data data;
	data.end = -1;
	data.start = -1;
	data.size_matrix = 0;
	data.numb_ants = 0;
	data.matrix = NULL;
	data.rooms = NULL;
	vis_load_texture(texture);
	work_window(&data, texture);

	return (0);
}