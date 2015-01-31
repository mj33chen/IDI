#if defined(__APPLE__)
	#include <OpenGL/OpenGL.h>
	#include <GLUT/GLUT.h>
#else
	#include <GL/gl.h>
	#include <GL/freeglut.h>
#endif

#include <algorithm>
#include <iostream>
#include <vector>
#include "model.h"

using namespace std;


int rotation = 0;
int translate = 0;
int scale_x = 0;

float x_actual, y_actual;
float scaleXYZ = 1.0f;

int ori_x = 0;
struct Position
{
    Position() : x(0), y(0) {}
    float x, y;
};

Position start, finish;

float width_current, height_current;

int angleX_current = 0;
int angleY_current = 0;

float size;
Model m;

void renderAxis(float size)
{
	glPushMatrix();

	glBegin(GL_LINES);

	glColor4f(0.0, 1.0, 1.0, 1.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(size, 0.0, 0.0);

	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, size, 0.0);

	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, size);

	glEnd();

	glPopMatrix();
}

void make_landscape()
{
	glPushMatrix();

	glColor3f(1.0, 0.0, 1.0);
	glBegin(GL_QUADS);
		glVertex3f(-1.5/2, -0.4, -1.5/2);
		glVertex3f(-1.5/2, -0.4, 1.5/2);
		glVertex3f(1.5/2, -0.4, 1.5/2);
		glVertex3f(1.5/2, -0.4, -1.5/2);
	glEnd();
	glPopMatrix();	
}

void make_ninot()
{
	// esfera 1
	glPushMatrix();
	glColor3f(1.0, 1.0, 0.0);
	glutWireSphere(0.4,20,20);
	glPopMatrix();
	//esfera 2
	glPushMatrix();
	glColor3f(1.0, 0.0, 1.0);
	glTranslatef (0.,0.6,0.);
	glutWireSphere(0.2,20,20);
	glPopMatrix();
	//con
	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	glTranslatef(0.1,0.6,0.0);
	glRotatef(90.,0.,1.,0.);
	glutWireCone(0.1,0.2,20,20);
	glPopMatrix();	
}

void renderModel(Model &model) 
{
	glPushMatrix();

	vector<Face> faces = model.faces();

	for(int i = 0; i < faces.size(); ++i)
	{
		const Face &f = faces[i];
		glColor4fv(Materials[f.mat].diffuse);
		glBegin(GL_TRIANGLES);
		for(int j = 0; j < f.v.size(); j+=3)
		{
			glVertex3dv(&model.vertices()[f.v[j]]);
		}
		glEnd();
	}

	glPopMatrix();	

}

void refresh(void)
{ 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	renderAxis(3.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(x_actual, 0.0f, 0.0f);
	glTranslatef(0.0f, y_actual, 0.0f);

	glRotatef((float)angleY_current, 1.0f, 0.0f, 0.0f);
	glRotatef((float)angleX_current, 0.0f, 1.0f, 0.0f);

	glScalef(scaleXYZ, scaleXYZ, scaleXYZ);
	
	/* render a solid teapot */
	//glColor3f(1.0f, 1.0f, 0.0f);
	//glutWireTeapot(0.5f);
	
	make_ninot();

	make_landscape();
	renderModel(m);

	glutSwapBuffers();
}

void resize(int ample, int alt)
{
	
	width_current = ample;
	height_current = alt;
	
	int min = std::min(ample, alt);

	int aux_x = 0;
	int aux_y = 0;

	aux_x = (ample-min)/2;

	aux_y = (alt-min)/2;

	glViewport(aux_x, aux_y, min, min);
		
}

void mouseMoved(int x, int y)
{
	
	width_current = glutGet( GLUT_WINDOW_WIDTH );
    height_current = glutGet( GLUT_WINDOW_HEIGHT );
		
	if(rotation)
	{	
		finish.x = x;
		finish.y = y;
		
		angleX_current += x - start.x;
		angleY_current += y - start.y;

		//cout << "angle X current = " << angleX_current << endl;
    	//cout << "angle Y current = " << angleY_current << endl;

	}
	
	if(translate)
	{
		x_actual = ((float)x/(float)width_current)*2.0 - 1.0;
		y_actual = (1-(float)y/(float)height_current)*2.0 - 1.0;
		//x_actual = x;
		//y_actual = y;
	}
	
	if(scale_x)
	{
		if(x > ori_x) scaleXYZ += 0.01;
		else if(x <= ori_x) scaleXYZ -= 0.01;
		ori_x = x;

	}

	start.x = x;
	start.y = y;

	
    glutPostRedisplay();
}


void processMouse(int button, int state, int x, int y)
{

	if( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN )
    {
        start.x = finish.x = x;
        start.y = finish.y = y;
        
    }
    if( button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        finish.x=x;
        finish.y=y;

    }
    glutPostRedisplay();
}

void keyBordFunc(unsigned char c, int x, int y)
{
	switch(c)
	{

		
		case 'r':
			if(rotation == 0) rotation = 1;
			else rotation = 0;
		break;
		
		case 't':
			if(translate == 0) translate = 1;
			else translate = 0;
		break;
		
		case 'e':
			if(scale_x == 0) scale_x = 1;
			else scale_x = 0;
		break;
		
		case 27:
			exit(0);
		break;
	}
	glutPostRedisplay();
}

void init()
{
	width_current = 600;
	height_current = 600;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1, 1, -1, 1, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_DEPTH_TEST);
}

int main(int argc, char **argv)
{
  	glutInit(&argc,argv);
 
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(600,600);
	glutInitWindowPosition(0, 0);
	init();
	glutCreateWindow("IDI: Practiques OpenGL");
	m.load("HomerProves.obj");
	glutDisplayFunc (refresh);
	glutReshapeFunc (resize);
	glutKeyboardFunc(keyBordFunc);
	
	glutMouseFunc(processMouse);
	glutMotionFunc(mouseMoved);
  	glutMainLoop();
  	return 0;

}