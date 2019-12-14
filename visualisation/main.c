#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <stdio.h>
#include <unistd.h>
#include "../lem_in.h"

t_total_data *data;

float norm(int n)
{
	if (n == 0)
		return (0);
	else
	{
		ft_printf("%f\n", (float)(n / 13.0));
		if (n < 7)
			return ((float)((n / 14.0 - 7.0 / 14)));
		else
			return ((float)(n / 14.0 - 7.0 / 14));
	}
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
	t_lem_list *shift = data->rooms;

	i = -1;
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(7);
	glBegin(GL_POINTS);
	glColor3d(255,0,255);
	
	while (shift)
	{
		
		glVertex2f(norm(shift->room.x), norm(shift->room.y));
		shift = shift->next;
	}
	
	glEnd();
	glFlush();

	// i = -1;
	// glBegin(GL_LINES);
	// glColor3d(30,30,255);
	// while (++i < 3)
	// {
	// 	glVertex3f(norm(arr[link[i][0]][1]), norm(arr[link[i][0]][2]), 0.0);
	// 	glVertex3f(norm(arr[link[i][1]][1]), norm(arr[link[i][1]][2]), 0.0);
	// }
	// glEnd();
	// glFlush();
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

	int arr[5][3]= {0, 2, 0, 1, 0, 2, 2, 4, 2, 3, 4, 4, 4, 2, 6};
	int link[5][2]= {0,1,0,2,2,3,3,4,4,1};
	draw_graph(data);
	// draw_graph(arr, link);
	// i = -1;
	// usleep(5000000);
	// j = -1;
	// while (++j < 3)
	// {
	// 	draw_ants(norm(arr[link[j][1]][1]), norm(arr[link[j][1]][2]));
	// }
}
int run(int argc, char **argv, t_total_data *temp)
{
	data = temp;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(400, 300);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Hello world!");
	glutDisplayFunc(displayMe);
	
	glutMainLoop();
	return 0;
}
