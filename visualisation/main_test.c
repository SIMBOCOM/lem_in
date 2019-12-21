#include <SDL.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <SDL_image.h>
#include "../lem_in.h"

typedef struct s_texture
{
	GLuint tex;
	int w; // Lower
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

void loadTexture(t_texture* inputTexture, const char* pathToTexture, GLint textureFiltration)
{
	SDL_Surface* surface = IMG_Load(pathToTexture);
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

void initGLandSDL(SDL_Window **win)
{
	if ( SDL_Init(SDL_INIT_EVERYTHING) < 0 )
	{
		printf("Unable to init SDL, error: ");
		exit(1);
	}
	*win = SDL_CreateWindow("Some cool visualization.",
							SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
							WIDTH, HEIGHT,
							SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	SDL_GLContext glcontext = SDL_GL_CreateContext(*win); // создаем контекст OpenGL
	if(*win == NULL)
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

t_lem_list *search_room_index_list(t_total_data *data, int index)
{
	t_lem_list *shift;

	shift = data->rooms;
	while (shift && shift->index != index)
		shift = shift->next;
	return (shift);
}

t_min_max	min_max(t_total_data *data)
{
	t_lem_list *shift;
	t_min_max	mm;
	int min_x;
	int min_y;

	shift = data->rooms;
	min_x = shift->room.x;
	min_y = shift->room.y;
	mm.midl_x = 0;
	mm.midl_y = 0;
	while (shift)
	{
//		if (mm.midl_x < shift->room.x)
//			mm.midl_x = shift->room.x;
//		if (mm.midl_y < shift->room.y)
//			mm.midl_y = shift->room.y;
//		if (min_x > shift->room.x)
//			min_x = shift->room.x;
//		if (min_y > shift->room.y)
//			min_y = shift->room.y;
		mm.midl_x += shift->room.x;
		mm.midl_y += shift->room.y;
		shift = shift->next;
	}
	mm.midl_x /= data->size_matrix;
	mm.midl_y /= data->size_matrix;
	return (mm);
}

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
	ft_printf("shift = %lf\n", ang_shift);
	while (shift)
	{
		shift->room.x = (50 / 2) * cos(angle*M_PI/180);
		shift->room.y = (50 / 2) * sin(angle*M_PI/180);
		ft_printf("x = %lf\n", angle);
		ft_printf("y = %lf\n\n", M_PI);
		angle += ang_shift;
		shift = shift->next;
	}
}

void draw_graph(t_total_data *data, t_texture tex)
{
	int i;
	int j;

	t_lem_list *shift = data->rooms;

	i = -1;
	glPointSize(7);

	i = -1;
	glClear(GL_COLOR_BUFFER_BIT);
	glBindTexture(GL_TEXTURE_2D, 0);
	glColor4f(1.0f, 1.0f,1.0f, 1.0f);
	glBegin(GL_LINES);

	t_lem_list *temp_i;
	t_lem_list *temp_j;

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

	glBindTexture(GL_TEXTURE_2D, tex.tex);

	while (shift)
	{
		if (search_room_index(data, data->start) == shift->room.name)
		{
			t_texture tex_start;
			loadTexture(&tex_start, "starter.png", GL_NEAREST);
			glBindTexture(GL_TEXTURE_2D, tex_start.tex);
		}
		if (search_room_index(data, data->end) == shift->room.name)
		{
			t_texture tex_end;
			loadTexture(&tex_end, "exiter.png", GL_NEAREST);
			glBindTexture(GL_TEXTURE_2D, tex_end.tex);
		}
		glPushMatrix();
		glTranslatef(shift->room.x, shift->room.y, 0.0f);
		glBegin(GL_POLYGON);
		glTexCoord2f(0.0f, 0.0f);
		glVertex2f(-2.5, 2);    // Низ лево
		glTexCoord2f(1.0f, 0.0f);
		glVertex2f( 2.5,  2);    // Низ право
		glTexCoord2f(1.0f, 1.0f);
		glVertex2f(2.5, -2);    // Верх право
		glTexCoord2f(0.0f, 1.0f);
		glVertex2f( -2.5, -2);    // Верх лево
		glEnd();
		glPopMatrix();
		shift = shift->next;
		glBindTexture(GL_TEXTURE_2D, tex.tex);
	}

}

t_vec2  lerpvec2(t_vec2 source, t_vec2 target, float t)
{
	return ((t_vec2){(1.0f - t) * source.x + t * target.x, (1.0f - t) * source.y + t * target.y});
}

char 	*search_room_vector(char *str, char **arr2, t_total_data *data)
{
	int i;
	char *tmp;

	i = -1;
	while (arr2 && arr2[++i])
	{
		tmp = ft_strchr(arr2[i], '-');
		*(tmp++) = 0;
//		ft_printf("str =   %s       %s\n", str, arr2[i] + 1);
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

int		create_rooms_vector(t_vec **rooms, char *str, char *prev, t_total_data *data)
{
	char **arr;
	char **arr2;
	char *tmp;
	t_vec *tmp_rooms;
	int i;

	i = -1;
	if (!(*rooms = malloc(sizeof(t_vec))))
		print_error(E_MALLOC);
	tmp_rooms = *rooms;
	arr = ft_strsplit(str, ' ');
	arr2 = ft_strsplit(prev, ' ');
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
	tmp_rooms = *rooms;
	while (tmp_rooms)
	{
		tmp_rooms->a = search_room_vector(tmp_rooms->ant, arr2, data);
		tmp_rooms = tmp_rooms->next;
	}
	return (1);
}

void	ants_start(t_total_data *data, char *str, char **prev, SDL_Window *win, t_texture tex1)
{
	char *new = ft_strdup(str);
	t_vec *rooms;
	t_vec *tmp_rooms;

	rooms = NULL;
	create_rooms_vector(&rooms, str, *prev, data);

	t_texture tex;
	loadTexture(&tex, "packman1.png", GL_NEAREST);

	float t = 0.0f;
	while (1) {
		glClear(GL_COLOR_BUFFER_BIT);
		draw_graph(data, tex1);
		glBindTexture(GL_TEXTURE_2D, tex.tex);
		t+= 0.02f;
		if (t > 1.0f)
			break;
		tmp_rooms = rooms;
		while (tmp_rooms)
		{
			t_room *start_vector = search_room_name_elem(data, tmp_rooms->a);
			t_room *end_vector = search_room_name_elem(data, tmp_rooms->b);
			t_vec2 a = (t_vec2){(float)start_vector->x, (float)start_vector->y};
			t_vec2 b = (t_vec2){(float)end_vector->x, (float)end_vector->y};
			t_vec2 c = lerpvec2(a, b, t);
			float angle = atan2f(end_vector->x - start_vector->x, end_vector->y - start_vector->y);
			printf("%f\n", angle);
			glPushMatrix();
			glTranslatef(c.x, c.y, 0.0f);
			glRotatef(angle*180/M_PI, 0.0f, 0.0f, -1.0f);
			glBegin(GL_POLYGON);
			glTexCoord2f(0.0f, 0.0f);
			glVertex2f(- 1, 1);    // Низ лево
			glTexCoord2f(1.0f, 0.0f);
			glVertex2f( 1,  1);    // Низ право
			glTexCoord2f(1.0f, 1.0f);
			glVertex2f(1, -1);    // Верх право
			glTexCoord2f(0.0f, 1.0f);
			glVertex2f( - 1, -1);    // Верх лево
			glEnd();
//				SDL_GL_SwapWindow(win);
			glPopMatrix();
			tmp_rooms = tmp_rooms->next;
		}
		SDL_GL_SwapWindow(win);

	}

	tmp_rooms = rooms;
	while (tmp_rooms)
	{
		t_room *end_vector = search_room_name_elem(data, tmp_rooms->b);
		glPushMatrix();
		glTranslatef(end_vector->x, end_vector->y, 0.0f);
		glBegin(GL_POLYGON);
		glTexCoord2f(0.0f, 0.0f);
		glVertex2f(- 1.5, 1);    // Низ лево
		glTexCoord2f(1.0f, 0.0f);
		glVertex2f( 1.5,  1);    // Низ право
		glTexCoord2f(1.0f, 1.0f);
		glVertex2f(1.5, -1);    // Верх право
		glTexCoord2f(0.0f, 1.0f);
		glVertex2f( -1.5, -1);    // Верх лево
		glEnd();
		glPopMatrix();
		tmp_rooms = tmp_rooms->next;
	}
	if (*prev)
		free(*prev);
	*prev = ft_strdup(new);
	free(new);
}

void	parser_vis(t_total_data *data)
{
	char	*str;
	int		i;
	int		flag[2];
	char *tmp;

	ft_printf("midl");
	flag[0] = 0;
	flag[1] = 0;
	tmp = NULL;
	str = 0;
	i = 0;
	get_next_line(0, &str);
	data->numb_ants = ft_atoi(str);
	free(str);
	while (get_next_line(0, &str))
	{
		ft_printf("%s$\n", str);
		if (!ft_strcmp(str, ""))
			break;
		else
			valid(str, flag, data, &i);
	}

//	data->mm = min_max(data);
//	t_lem_list *shift;
//	shift = data->rooms;
//
//	while (shift)
//	{
//		shift->room.x += data->mm.midl_x;
//		shift->room.y += data->mm.midl_y;
//
//		shift = shift->next;
//	}
	create_coord(data);
	SDL_Window *win = NULL;
	initGLandSDL(&win);

	int running = 1;
	SDL_Event event;

	gluOrtho2D(-WIDTH / 2, WIDTH / 2, -HEIGHT / 2, HEIGHT / 2);
	glScalef(20.0f, 20.0f, 10.0f);

	int antran = 0;
	int update = 0;
	t_texture tex;
	loadTexture(&tex, "ranger2.png", GL_NEAREST);
	float t = 0.0f;
	while (running == 1)
	{
//		glClear(GL_COLOR_BUFFER_BIT);
		draw_graph(data, tex);
		if (antran)
		{
			get_next_line(0, &str);
			if (str[0] == 'L')
			{
				ants_start(data, str, &tmp, win, tex);
				update = 0;
			}
		}
		if (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					running = 0;
					break;
				case SDL_MOUSEBUTTONDOWN:
					antran = 1;
					break;
			}
		}
		if (!update)
		{
			SDL_GL_SwapWindow(win);
			update = 1;
			usleep(1000000);
		}
	}
}

int main()
{

	t_total_data data;
	data.end = 0;
	data.start = 0;
	data.size_matrix = 0;
	data.numb_ants = 0;
	data.matrix = NULL;
	data.rooms = NULL;
	parser_vis(&data);

	return (0);
}