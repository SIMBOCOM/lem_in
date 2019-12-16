#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <unistd.h>
#include "../lem_in.h"
#include "mlx.h"


t_total_data *data;

t_lem_list *search_room_index_list(t_total_data *data, int index)
{
	t_lem_list *shift;

	shift = data->rooms;
	while (shift && shift->index != index)
		shift = shift->next;
	return (shift);
}

t_min_max	min_max()
{
	t_lem_list *shift;
	t_min_max	mm;

	shift = data->rooms;
	mm.max_x = shift->room.x;
	mm.max_y = shift->room.y;

	mm.min_x = shift->room.x;
	mm.min_y = shift->room.y;
	mm.midl_x = 0;
	mm.midl_y = 0;
	while (shift)
	{
		if (mm.min_x > shift->room.x)
			mm.min_x = shift->room.x;
		if (mm.min_y > shift->room.y)
			mm.min_y = shift->room.y;
		if (mm.max_x < shift->room.x)
			mm.max_x = shift->room.x;
		if (mm.max_y < shift->room.y)
			mm.max_y = shift->room.y;
		mm.midl_x += shift->room.x;
		mm.midl_y += shift->room.y;
		shift = shift->next;
	}
	mm.midl_x /= data->size_matrix;
	mm.midl_y /= data->size_matrix;
	return (mm);
}

float norm(int n, t_min_max mm, int x_y)
{
	if (x_y && !(mm.max_x || mm.min_x))
		return (0);
	if (!x_y && !(mm.max_y || mm.min_y))
		return (0);
	
	if (x_y)
		return ((float)((float)n / (mm.max_x + mm.min_x) - (float)mm.midl_x / (mm.max_x + mm.min_x)));
	else
		return ((float)((float)n / (mm.max_y + mm.min_y) - (float)mm.midl_y / (mm.max_y + mm.min_y)));
}

void	parser_vis()
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
		valid(str, flag, data, &i);
}

void draw_ants(float x, float y)
{
	glPointSize(7);
	glBegin(GL_POINTS);
	glColor3d(10,10,10);
	glVertex2f(x, y);
	glEnd();
	glFlush();
	usleep(700000);
	glPointSize(7);
	glBegin(GL_POINTS);
	glColor3d(255,0,255);
	glVertex2f(x, y);
	glEnd();
	glFlush();
}

void draw_graph()
{
	int i;
	int j;
	t_min_max mm;

	mm = min_max();
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
				glVertex2f(norm(temp_i->room.x, mm, 1), norm(temp_i->room.y, mm, 0));
				glVertex2f(norm(temp_j->room.x, mm, 1), norm(temp_j->room.y, mm, 0));
			}
		}
	}
	glEnd();

	glBegin(GL_POINTS);
	glColor3d(255,0,255);
	while (shift)
	{
		ft_printf("x = %f y = %f\n", norm(shift->room.x, mm, 1), norm(shift->room.y, mm, 0));
		glVertex2f(norm(shift->room.x, mm, 1), norm(shift->room.y, mm, 0));
		shift = shift->next;
	}
	glEnd();
	glFlush();


	glFlush();
}


// void draw_graph(int arr[5][3], int link[5][2])
// {
// 	int i;

// 	i = -1;
// 	glClear(GL_COLOR_BUFFER_BIT);
// 	glPointSize(7);
// 	glBegin(GL_POINTS);
// 	glColor3d(255,0,255);
// 	while (++i < 4)
// 		glVertex2f(norm(arr[i][1]), norm(arr[i][2]));
// 	glEnd();
// 	glFlush();

// 	i = -1;
// 	glBegin(GL_LINES);
// 	glColor3d(30,30,255);
// 	while (++i < 3)
// 	{
// 		glVertex3f(norm(arr[link[i][0]][1]), norm(arr[link[i][0]][2]), 0.0);
// 		glVertex3f(norm(arr[link[i][1]][1]), norm(arr[link[i][1]][2]), 0.0);
// 	}
// 	glEnd();
// 	glFlush();
// }

void displayMe()
{
	int i;
	int j;

	draw_graph();
	// draw_graph(arr, link);
	// i = -1;

	// usleep(5000000);
	// j = -1;
	// while (++j < 3)
	// {
	// 	draw_ants(norm(arr[link[j][1]][1]), norm(arr[link[j][1]][2]));
	// }
}

int main(int argc, char **argv)
{
	//gcc visualisation/main.c parser.c valid.c djkstra.c list_methods.c ft_printf/libftprintf.a -framework OpenGL -framework GLut -Wno-deprecated-declarations
	// char *str = "-34--25";
	// if (ft_strcmp(str, ft_strchr(str, '-')) && ft_strchr(str, '-')[-1] != ' ')
	// {
	// 	ft_printf("1");
	// 	return (0);	
	// }
	// 	while (!ft_strcmp(str, ft_strchr(str, '-')))
	// 	{
	// 		if (!(str = ft_strchr(str, '-') + 1))
	// 		{
	// 			ft_printf("2");
	// 			return (0);	
	// 		}
	// 		if (ft_strchr(str, '-') && ft_strcmp(str, ft_strchr(str, '-')) && ft_strchr(str, '-')[-1] != ' ')
	// 		{
	// 			ft_printf("2");
	// 			return (0);	
	// 		}
	// 		exit(1);
	// 	}
	// exit(1);
	

	t_total_data temp;
	temp.end = 0;
	temp.start = 0;
	temp.size_matrix = 0;
	temp.numb_ants = 0;
	temp.matrix = NULL;
	temp.rooms = NULL;
	data = &temp;
	parser_vis();


	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(400, 300);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Hello world!");
	glutDisplayFunc(displayMe);
	
	glutMainLoop();
	return 0;
}
