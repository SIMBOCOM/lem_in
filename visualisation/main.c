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

void initGLandSDL(SDL_Window **win)
{
    // Инициализация SDL

    if ( SDL_Init(SDL_INIT_EVERYTHING) < 0 )
    {
        // std::cout << "Unable to init SDL, error: " << SDL_GetError() << std::endl;
        printf("Unable to init SDL, error: ");
        exit(1);
    }

    *win = SDL_CreateWindow("Some cool visualization.",
                           SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                           800, 600,
                           SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    SDL_GLContext glcontext = SDL_GL_CreateContext(*win); // создаем контекст OpenGL
    if(*win == NULL)
    {
        printf("Unable to create window: ");
        exit(1);
    }

    // Инициализация OpenGL
    glClearColor(100.0f, 0.0f, 0.0f, 0.0f); // устанавливаем фоновый цвет на черный
    glEnable(GL_TEXTURE_2D);
    glMatrixMode(GL_PROJECTION);
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glLoadIdentity();
}

void loadTexture(t_texture* inputTexture, const char* pathToTexture, GLint textureFiltration)
{
	SDL_Surface* surface = IMG_Load(pathToTexture);
	if (surface==NULL)
	{
//		std::cout << "Error: " << SDL_GetError() << std::endl;
		printf("Texture load error %d\n", SDL_GetError());
		return;
	}

	Uint32 colorkey = SDL_MapRGB( surface->format, 255, 0, 255);

	SDL_SetColorKey( surface, SDL_TRUE | SDL_RLEACCEL, colorkey);

	glGenTextures(1,&inputTexture->tex);
	glBindTexture(GL_TEXTURE_2D, inputTexture->tex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, surface->w, surface->h, 0, GL_BGR, GL_UNSIGNED_BYTE, surface->pixels);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, textureFiltration);
	inputTexture->w = surface->w;
	inputTexture->h = surface->h;
	SDL_FreeSurface(surface);
}

t_lem_list *search_room_index_list(t_total_data *data, int index)
{
	t_lem_list *shift;

	shift = data->rooms;
	while (shift && shift->index != index)
		shift = shift->next;
	return (shift);
}

void draw_graph(t_total_data *data)
{
	int i;
	int j;

	t_lem_list *shift = data->rooms;

	i = -1;
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(7);

	i = -1;
	glBegin(GL_LINES);
	glColor3d(30,30,255);
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
				ft_printf("i = %d j = %d\n", temp_i->room.x, temp_i->room.y);
				glVertex2f(temp_i->room.x, temp_i->room.y);
				glVertex2f(temp_j->room.x, temp_j->room.y);
			}
		}
	}
	glEnd();

//	glBegin(GL_POINTS);
//	glColor3d(255,0,255);
//	while (shift)
//	{
//		ft_printf("x = %f y = %f\n", norm(shift->room.x, mm, 1), norm(shift->room.y, mm, 0));
//		glVertex2f(norm(shift->room.x, mm, 1), norm(shift->room.y, mm, 0));
//		shift = shift->next;
//	}
//	glEnd();

}

void	parser_vis(t_total_data *data)
{
	char	*str;
	int		i;
	int		flag[2];


	flag[0] = 0;
	flag[1] = 0;
	str = 0;
	i = 0;
	get_next_line(0, &str);
	data->numb_ants = ft_atoi(str);
	free(str);
	while (get_next_line(0, &str))
		valid_visual(str, flag, data, &i);
}

// gcc ./main.c -framework OpenGL -L/Users/flogan/.brew/lib -lSDL2 -I/Users/flogan/.brew/include/SDL2 -D_THREAD_SAFE
//gcc visualisation/main_test.c  parser.c valid.c list_methods.c djkstra.c ft_printf/libftprintf.a   -framework OpenGL -L/Users/flogan/.brew/lib -lSDL2 -I/Users/flogan/.brew/include/SDL2 -D_THREAD_SAFE -lSDL2_image
int main()
{
	t_total_data data;
	data.end = 0;
	data.start = 0;
	data.size_matrix = 0;
	data.numb_ants = 0;
	data.matrix = NULL;
	data.rooms = NULL;

    SDL_Window *win = NULL;
    initGLandSDL(&win);

    int running = 1;
    SDL_Event event;
    t_texture tex;

    parser_vis(&data);
    loadTexture(&tex, "./tarakan.bmp", GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, tex.tex);

	gluOrtho2D(-80, 80, -60, 60);
	glScalef(10.0f, 40.0f, 10.0f);

    while (running == 1)
    {
    	glClear(GL_COLOR_BUFFER_BIT);
//    	draw_graph(&data);
        while (SDL_PollEvent(&event))
        {
             switch(event.type)
             {
                 case SDL_QUIT:
                     running = 0;
                     break;
             }
        }
		glClearColor(100.0f, 0.0f, 0.0f, 0.0f);
        SDL_GL_SwapWindow(win);
    }
    return (0);
}






























t_texture tex;
loadTexture(&tex, "stas.png", GL_NEAREST);

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
glPushMatrix();
glTranslatef(c.x, c.y, 0.0f);
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

glBegin(GL_POLYGON);
glTexCoord2f(0.0f, 0.0f);
glVertex2f(room->x - 1, room->y + 0.5);    // Низ лево
glTexCoord2f(1.0f, 0.0f);
glVertex2f(room->x + 1, room->y + 0.5);    // Низ право
glTexCoord2f(1.0f, 1.0f);
glVertex2f(room->x + 1, room->y - 0.5);    // Верх право
glTexCoord2f(0.0f, 1.0f);
glVertex2f(room->x - 1, room->y - 0.5);    // Верх лево
glEnd();
if (tmp)
{
str = tmp;
str1 = tmp++;
}









//	tmp_rooms = rooms;
//	while (tmp_rooms)
//	{
//		t_room *end_vector = search_room_name_elem(data, tmp_rooms->b);
//		glBegin(GL_POLYGON);
//		glTexCoord2f(0.0f, 0.0f);
//		glVertex2f(end_vector->x - 1, end_vector->y + 0.5);    // Низ лево
//		glTexCoord2f(1.0f, 0.0f);
//		glVertex2f(end_vector->x + 1, end_vector->y + 0.5);    // Низ право
//		glTexCoord2f(1.0f, 1.0f);
//		glVertex2f(end_vector->x + 1, end_vector->y - 0.5);    // Верх право
//		glTexCoord2f(0.0f, 1.0f);
//		glVertex2f(end_vector->x - 1, end_vector->y - 0.5);    // Верх лево
//		glEnd();
//		tmp_rooms = tmp_rooms->next;
//	}