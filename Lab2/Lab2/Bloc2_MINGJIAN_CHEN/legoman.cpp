#if defined(__APPLE__)
	#include <OpenGL/OpenGL.h>
	#include <GLUT/GLUT.h>
#else
	#include <GL/gl.h>
	#include <GL/freeglut.h>
#endif

#include <algorithm>
#include <iostream>
#include "model.h"

using namespace std;

int rotation = 0;
int translate = 0;
int scale_x = 0;
int change = 0;
double edge_x, edge_y, edge_z;

double maxEdge;

float x_actual, y_actual;
float scaleXYZ = 1.0f;
float scaleLegoman_x, scaleLegoman_y, scaleLegoman_z;
float legoman_X = -0.75f; 
float legoman_Y = 0.4f;

int ori_x = 0;
struct Position
{
    Position() : x(0), y(0), z(0){}
    float x, y, z;
};

Model m;

Position start, finish;

double max_x, max_y, max_z, min_x, min_y, min_z, center_x, center_y, center_z;

float width_current, height_current;

int angleX_current = 0;
int angleY_current = 30;

float size;

bool first = true;

void renderAxis(int size)
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

void standardizeModel()
{
	const int &tam = m.vertices().size();  //tam @
	const Face &f = m.faces()[0];          // it begins to compare from the first face 
	const Vertex *v;
	v = &m.vertices()[f.v[0]];
	min_x = max_x = (*v);   //first vertex of the face
	min_y = max_y = *(v+1); // segon
	min_z = max_z = *(v+2); // third

	for(int i = 0; i < tam; i+=3)
	{
		if(m.vertices()[i] > max_x) max_x = m.vertices()[i];
		if(m.vertices()[i] < min_x) min_x = m.vertices()[i];

		if(m.vertices()[(i)+1] > max_y) max_y = m.vertices()[(i)+1];
		if(m.vertices()[(i)+1] < min_y) min_y = m.vertices()[(i)+1];

		if(m.vertices()[(i)+2] > max_z) max_z = m.vertices()[(i)+2];
		if(m.vertices()[(i)+2] < min_z) min_z = m.vertices()[(i)+2];
	}

	edge_x = (max_x-min_x);
	edge_y = (max_y-min_y);
	edge_z = (max_z-min_z);

	maxEdge = std::max(edge_x, edge_y);
	maxEdge = std::max(edge_z, maxEdge);
	/*cout << "maxEdge es " << maxEdge << endl;
	cout << "x edge es " << edge_x << endl;
	cout << "y edge es " << edge_y << endl;
	cout << "z edge es " << edge_z << endl;*/
	center_x = (max_x + min_x)/2;
	center_y = (max_y + min_y)/2;
	center_z = (max_z + min_z)/2;	
	/*cout << "center_x es " << center_x << endl;
	cout << "center_y es " << center_y << endl;
	cout << "center_z es " << center_z << endl;*/

	//scaleLegoman_x = 0.5/(max_x - min_x);
	scaleLegoman_y = 0.5/maxEdge;
	//cout << "scaleLegoman_y es " << scaleLegoman_y << endl;
	//scaleLegoman_z = 0.5/(max_z - min_z);

}

void make_ninot()
{
	glPushMatrix();
		glTranslatef(0., 0., 0.);
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
	glPopMatrix();	
}


void renderModel() 
{
	glPushMatrix();
	//glTranslatef(legoman_X, 0.0, 0.0);
	//glTranslatef(0.0, -legoman_Y, 0.0);
	//if(change) glTranslatef(legoman_X, -legoman_Y, 0.75f;
	//else glTranslatef(-0.75f, -0.4f, 0.75);
	glTranslatef(legoman_X, 0.25f-legoman_Y, 0.75f);
	renderAxis(2);

	glScalef(scaleLegoman_y, scaleLegoman_y, scaleLegoman_y);
	glTranslatef(-center_x, -center_y, -center_z);
	
// 	cout << "scaleLegoman x es " << scaleLegoman_x << endl;
// 	cout << "scaleLegoman y es " << scaleLegoman_y << endl;
// 	cout << "scaleLegoman z es " << scaleLegoman_z << endl;
	
	
	const int &n = m.faces().size();
	for (int i = 0; i < n; ++i) {
		const Face &f = m.faces()[i];
		glColor4fv(Materials[f.mat].diffuse);
		glBegin(GL_TRIANGLES);		
		for (int j = 0; j < 3; ++j) {
			glVertex3dv(&m.vertices()[f.v[j]]);	
		}
		glEnd();
	}
	//cout << "he dibujado el legoman" << endl;
	
	

	glPopMatrix();
}


/*void make_landscape()
{
	glPushMatrix();
	
	glPopMatrix();
}*/


void refresh(void)
{ 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();

	glTranslatef(x_actual, 0.0f, 0.0f);
	glTranslatef(0.0f, y_actual, 0.0f);

	glRotatef((float)angleY_current, 1.0f, 0.0f, 0.0f);
	glRotatef((float)angleX_current, 0.0f, 1.0f, 0.0f);
	glScalef(scaleXYZ, scaleXYZ, scaleXYZ);
	
	/* render a solid teapot */
	//glColor3f(1.0f, 1.0f, 0.0f);
	//glutWireTeapot(0.5f);
	//glTranslatef(center_x, center_y, center_z);


	renderAxis(3);

	
	//make_landscape();
	glColor4f((float)0x7C/0xFF, (float)0xD2/0xFF, (float)0x79/0xFF, 1);
	glBegin(GL_QUADS);
		glVertex3f(-1.5/2, -0.4, -1.5/2);
		glVertex3f(-1.5/2, -0.4, 1.5/2);
		glVertex3f(1.5/2, -0.4, 1.5/2);
		glVertex3f(1.5/2, -0.4, -1.5/2);
	glEnd();
	

	glBegin(GL_LINES);
		//Visual guide for -0.75,x,-0.75
		glColor4f(0,1,0,1);
		glVertex3f(-0.75,-0.4,0.75);
		glVertex3f(-0.75,0.4,0.75);
	glEnd();
	renderModel();
	make_ninot();

	glPopMatrix();


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
	if(not change)
	{
		if(rotation)
		{	
			finish.x = x;
			finish.y = y;
			
			angleX_current += x - start.x;
			angleY_current += y - start.y;

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
	}

	if(change)
	{
		legoman_X += (x-start.x)/100.0;
		legoman_Y += (y-start.y)/100.0;
	}

	start.x = x;
	start.y = y;

	
    glutPostRedisplay();
}


void processMouse(int button, int state, int x, int y)
{


        start.x = finish.x = x;
        start.y = finish.y = y;
        
    

    glutPostRedisplay();
}

void keyBordFunc(unsigned char c, int x, int y)
{
	switch(c)
	{
		//case 't':
		case 'a':
			angleX_current += 1;
		break;
		
		case 'd':
			angleX_current -= 1;
		break;
		
		case 'w':
			angleY_current += 1;
		break;
		
		case 's':
			angleY_current -= 1;
		break;
		
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
		
		case 'c':
			if(change == 0) change = 1;
			else change = 0;
		break;

		case 'h':
			cout << "Snowman manual instruction" << endl;
			cout << "h-------------------help" << endl;
			cout << "w-------------------turn up" << endl;
			cout << "s-------------------turn down" << endl;
			cout << "a-------------------turn left" << endl;
			cout << "d-------------------turn right" << endl;
			cout << "e-------------------scalar" << endl;
			cout << "t-------------------translate" << endl;
			cout << "r-------------------rotate" << endl;
			cout << "ESC-----------------exit" << endl;
		break;

		case 27:
			exit(0);
		break;
	}
	glutPostRedisplay();
}


int main(int argc, const char *argv[])
{
  	glutInit(&argc,(char**) argv);
 	width_current = 600;
	height_current = 600;

	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(width_current,height_current);
	glutCreateWindow("IDI: Practiques OpenGL");

	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	int size = 1;
	glOrtho(-size, size, -size, size, -size, size);
	glMatrixMode(GL_MODELVIEW);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glClearColor((float)0xFA/0xF2, (float)0xD2/0xAF, (float)0xB1/0xA1, 1);
	
	glutDisplayFunc (refresh);
	glutReshapeFunc (resize);
	glutKeyboardFunc(keyBordFunc);
	
	glutMouseFunc(processMouse);
	glutMotionFunc(mouseMoved);
	m.load(argv[1]);
	if(first) 
	{
		standardizeModel();
		//cout << "he estandarizado el legoman" << endl;
		first = false;
	}
	
	//cout << "he cargado el legoman" << endl;
  	glutMainLoop();
  	return 0;

}