#if defined(__APPLE__)
	#include <OpenGL/OpenGL.h>
	#include <GLUT/GLUT.h>
#else
	#include <GL/gl.h>
	#include <GL/freeglut.h>
#endif

#include <stdio.h>

struct Position
{
    Position() : x(0), y(0) {}
    float x, y;
};

Position vec[3];

float old_width = 600.0;
float old_height = 600.0;

float x_actual, y_actual;
int num_click;
int key_f = 0;
int new_triangle = 0;
int paint;
float red,green,blue;

void help(void)
{
	fprintf(stdout, "Help instructions\n");
	fprintf(stdout, "-------------------\n");
	fprintf(stdout, "key 't': using the mouse you can introduce new axes to three vertex of the triangle\n");
	fprintf(stdout, "key 'f': activate/desactivate the feature that allows you modify the backgound by moving the mouse\n");
	fprintf(stdout, "esc: exit the application\n");
	fprintf(stdout, "\n");
}

void change_color(int x, int y)
{
	if (x < 0)
		red = 0.0;
	else if (x > old_width)
		red = 1.0;
	else
		red = ((float) x)/ old_height;
		// setting green to be relative to the mouse 
		// position inside the window
	if (y < 0)
		green = 0.0;
	else if (y > old_width)
		green = 1.0;
	else
		green = ((float) y)/old_height;
		// removing the blue component.
		blue = 0.0;
}

void refresh (void)
{ 

	

	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(red, green, blue);
	
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_TRIANGLES);
		glVertex3f(-1.0,-1.0,0.0f);
		glVertex3f(1.0, -1.0, 0.0f);
		glVertex3f(0.0, 1.0,0.0f);
	glEnd();

	if(num_click >= 0 && new_triangle)
	{ 
		vec[num_click].x = x_actual;
		vec[num_click].y = y_actual;
		glColor3f(1.0f, 1.0f, 1.0f); 
		glBegin(GL_POINTS);
  			glVertex3f(x_actual, y_actual, 0.0f);
		glEnd();

		if(num_click == 0) paint = 1;
	}

	if(paint)
	{ 

		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_TRIANGLES);
			glVertex3f(vec[0].x, vec[0].y, 0.0f);
			glVertex3f(vec[1].x, vec[1].y, 0.0f);
			glVertex3f(vec[2].x, vec[2].y, 0.0f);
		glEnd();
	}

	glFlush();
	glutSwapBuffers();
}

void resize(int ample, int alt)
{

	int min;

	int aux_x = 0;
	int aux_y = 0;

	if(ample > alt)
	{
		min = alt;
		aux_x = (ample-min)/2;
		
		
	}
	else 
	{
		min = ample;
		aux_y = (alt-min)/2;
		
	}

	glViewport(aux_x, aux_y, min, min);
		
}

void background(int x, int y)
{
	
	if(key_f == 1)
	{
		glClearColor(red,green,blue,1.0f);
		
		change_color(x, y);

		glutPostRedisplay();
	}
	
}

void processMouse(int button, int state, int x, int y)
{
	

	if(new_triangle == 1)
	{	
		if(state == GLUT_DOWN)
		{
			
			old_width = glutGet( GLUT_WINDOW_WIDTH );
        	old_height = glutGet( GLUT_WINDOW_HEIGHT );

			x_actual = ((float)x/(float)old_width)*2.0 - 1.0;
			y_actual = (1-(float)y/(float)old_height)*2.0 - 1.0;
			--num_click;
			glutPostRedisplay();
		}
	}
}



void keyBordFunc(unsigned char c, int x, int y)
{
	switch(c)
	{
		case 'h':
			help();
		break;

		case 27:
			exit(0);
		break;

		case 't':

			new_triangle = 1;
			num_click = 3;
			paint = 0;
		break;

		case 'f':
			if(key_f == 0) key_f = 1;
			else key_f = 0;
		break;

	}

	glutPostRedisplay();
}

//Ejecución principal
int main(int argc, char **argv)
{
  	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(old_width,old_height);
	glutInitWindowPosition(0, 0);

	glutCreateWindow("IDI: Practiques OpenGL");
	
	glutDisplayFunc (refresh);
	glutReshapeFunc (resize);
	glutKeyboardFunc(keyBordFunc);
	
	glutMouseFunc(processMouse);
	glutMotionFunc(background);
  	glutMainLoop();
  	return 0;

}
