#if defined(__APPLE__)
	#include <OpenGL/OpenGL.h>
	#include <GLUT/GLUT.h>
#else
	#include <GL/gl.h>
	#include <GL/freeglut.h>
#endif

#include <algorithm>
#include <iostream>
#include <cmath>
#include "model.h"
#include <time.h>       /* time */

#define MI_PI 3.1415926535

using namespace std;

int angleX_current = 0;
int angleY_current = 0;

bool rotation = true;
int scale_x = 0;
int change = 1;
double edge_x, edge_y, edge_z;
float zoom = 1;
double maxEdge;
bool zoom_state = false;
double sizeWanna;
float x_actual, y_actual;
float scaleXYZ = 1.0f;
float scaleLegoman_x, scaleLegoman_y, scaleLegoman_z;
float scaleLegoman_y_;
float speed = 1;
float angle = -speed*2*M_PI*angleX_current/360;
float ratio;
float dist;
double FOV;
float zNear;
float zFar;
float edgeSize = 10;
float pToP = sqrt((edgeSize*edgeSize) + (edgeSize*edgeSize));
float SPHERE_RADIUS = (sqrt(pToP*pToP + 1.5*1.5))/2;
int pos = 0;

vector<double> VRP(3, 0.0);
float light0_position[4] = {5.0, 1.5, 5.0, 0.5};
float light0_position1[4] = {5.0, 1.5, -5.0, 1.0};
float light0_position2[4] = {-5.0, 1.5, 5.0, 1.0};
float light0_position3[4] = {-5.0, 1.5, -5.0, 1.0};
float light2_position[4];

float luz0[4] = {1.0, 1.0, 0.0, 1.0};
float luz1[4] = {1.0, 1.0, 1.0, 1.0};
float luz2[4] = {1.0, 1.0, 1.0, 1.0};

int ori_x = 0;
struct Position
{
    Position() : x(0), y(0), z(0){}
    float x, y, z;
};

struct  Patricio
{
	double Rotation;
	vector<double> OBS;
	double speed;
	/* data */
};

Material mat;
Patricio Patricio;
Model m;

Position start, finish;

double max_x, max_y, max_z, min_x, min_y, min_z, center_x, center_y, center_z;

float width_current, height_current;


float size;

bool first = true;
bool segon = true;
bool visible = true;
bool primer = true;
bool FIRST_PERSONA_VISION = false;
bool light = true;
bool normal = true;
bool ilumine = true;
bool light1 = true;
bool light0 = false;
bool light2 = false;
bool cull_face = false;

void cameraProperties()
{
	//cout << "SPHERE_RADIUS es " << SPHERE_RADIUS << endl; 
	dist = 3*SPHERE_RADIUS;
	FOV = 2*(asin(SPHERE_RADIUS/dist))*180/3.14;
	zNear = 2*SPHERE_RADIUS;
	zFar = 4*SPHERE_RADIUS;

}

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


void standardizeModel(double sizeWanna)
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

	//SPHERE_RADIUS = (sqrt((edge_x*edge_x) + (edge_y*edge_y) + (edge_z*edge_z)))/2;
	
	maxEdge = std::max(edge_x, edge_y);
	maxEdge = std::max(edge_z, maxEdge);

	center_x = (max_x + min_x)/2;
	center_y = (max_y + min_y)/2;
	center_z = (max_z + min_z)/2;	


	if(sizeWanna == 1.0) scaleLegoman_y = sizeWanna/maxEdge;
	
	else if(sizeWanna == 1.5) scaleLegoman_y_ = sizeWanna/maxEdge;
	
}

void posCamera()
{
	//glLoadIdentity();

	if(FIRST_PERSONA_VISION)
	{

		VRP[0] = Patricio.OBS[0] + sin(Patricio.Rotation*MI_PI/180.0);
		VRP[2] = Patricio.OBS[2] + cos(Patricio.Rotation*MI_PI/180.0);
		 
		gluLookAt(Patricio.OBS[0], 1, Patricio.OBS[2], VRP[0], 1, VRP[2], 0, 1, 0); 
	}

	else
	{

		glTranslatef(0.0, 0.0, -dist);
		glRotatef(0.0, 0.0, 0.0, 1.0);
		glRotatef((float)angleY_current, 1.0, 0.0, 0.0);
		glRotatef((float)angleX_current, 0.0, 1.0, 0.0);
		glTranslatef(0.0, 0.0, 0.0);
	}
}

void toggleCamera()
{
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	width_current = glutGet( GLUT_WINDOW_WIDTH );
    height_current = glutGet( GLUT_WINDOW_HEIGHT );
	ratio = (float) width_current/height_current;

	float quo = 1.0;
	float vw = ratio;
	if (ratio < 1) {
		quo /= ratio;
		vw = 1.0;
	}

	cameraProperties();

 	if(not change) glOrtho(-SPHERE_RADIUS*vw*zoom, SPHERE_RADIUS*vw*zoom, -SPHERE_RADIUS*quo*zoom, SPHERE_RADIUS*quo*zoom, zNear, zFar);
 	//glOrtho(left, right, bottom, top, zN, zF);
	else 
	{

		if(not FIRST_PERSONA_VISION)
		{

			if(ratio >= 1) gluPerspective(FOV*zoom, ratio, zNear, zFar);
			else if(ratio < 1)
			{	
				gluPerspective((SPHERE_RADIUS*quo/(dist - SPHERE_RADIUS*quo))*(180/M_PI)*zoom, ratio,  zNear, zFar);
			}
		}
		else 
		{

			gluPerspective(90, ratio, 0.1, 1000);
		}
			//
	}

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	posCamera();


}

void make_ninot()
{

	float v[4] = {0.8, 0.8, 0.8, 1.0};
	float vd[4] = {0.7, 0.7, 0.7, 1.0};
	float vs[4] = {1.0, 1.0, 1.0, 1.0};
	glPushMatrix();
		glPushMatrix();
			// sphere 1
			if(! ilumine) glColor4fv(v);
			else
			{
				glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, v);
				glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, vd);
				glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, vs);
				glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 108.0);
			}
			glTranslatef(0., 0., 0.);
			glutSolidSphere(0.4,20,20);
		glPopMatrix();
		
		// sphere 2
		glPushMatrix();
			if(! ilumine) glColor4fv(v);
			else
			{
				glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, v);
				glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, vd);
				glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, vs);
				glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 108.0);
			}//
			glTranslatef (0.,0.6,0.);
			glutSolidSphere(0.2,20,20);
		glPopMatrix();

		// cone
		
		glPushMatrix();

			float v1[4] = {0.7, 0.3, 0.0, 1.0};
			float v2d[4] = {0.7, 0.3, 0.0, 1.0};
			float v2s[4] = {1.0, 1.0, 1.0, 1.0};
			if(! ilumine) glColor4fv(v1);
			else 
			{
				glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, v1);
				glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, v2d);
				glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, v2s);
				glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 108.0);	
			}
			//
			glTranslatef(0.1,0.6,0.0);
			glRotatef(90.,0.,1.,0.);
			glutSolidCone(0.1,0.2,20,20);
		glPopMatrix();	
	glPopMatrix();	
}



void renderModel() 
{
	glPushMatrix();

	const int &n = m.faces().size();
	for (int i = 0; i < n; ++i) {
		const Face &f = m.faces()[i];
		if(!ilumine) glColor4fv(Materials[f.mat].diffuse);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, Materials[f.mat].ambient);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Materials[f.mat].diffuse);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Materials[f.mat].specular);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, Materials[f.mat].shininess);
		glBegin(GL_TRIANGLES);	
			if(! normal) glNormal3dv(f.normalC);  // normal face	
			for (int j = 0; j < 3; ++j) {
				if(normal) glNormal3dv(&m.normals()[f.n[j]]); // normal vertex
				glVertex3dv(&m.vertices()[f.v[j]]);	
			}
		glEnd();
	}

	glPopMatrix();
}

void renderSnowmen()
{
	glPushMatrix();
		glTranslated(2.5, 0.4, -2.5);
		make_ninot();
	glPopMatrix();

	glPushMatrix();
		glTranslated(-2.5, 0.4, 2.5);
		make_ninot();
	glPopMatrix();

	glPushMatrix();
		glTranslated(-2.5, 0.4, -2.5);
		make_ninot();
	glPopMatrix();
}


void renderWalls()
{
	if(not visible) return;

	float v2[4] = {0.0, 0.3, 0.0, 1.0};
	float v3[4] = {0.0, 0.7, 0.0, 0.2};
	float vdw[4] = {0.0, 0.0, 0.0, 0.0};
	glPushMatrix();
		glTranslatef(0.0, 0.0+0.75, -4.9);
		glScalef(10, 1.5, 0.2);
		if(! ilumine) glColor3f(0.0, 0.3, 0.0);
		else
		{
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, v2);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, v3);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, vdw);
			glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 1.0);
		}
		
		//
		glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(1.5, 0.0+0.75, 2.5);
		glScalef(0.2, 1.5, 4.0);

		if(! ilumine) glColor3f(0.0, 0.3, 0.0);
		else
		{
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, v2);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, v3);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, vdw);
			glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 1.0);
		}
		
		//glColor3f(0.0, 0.5, 0.0);
		glutSolidCube(1.0);
	glPopMatrix();

}


void renderScene()
{
	
	glPushMatrix();
		float v4[4] = {0.0, 0.0, 0.8, 0.2};
		float v5[4] = {0.0, 0.0, 0.8, 0.8};
		if(! ilumine) glColor3f(0.0, 0.8, 0.8);
		else 
		{
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, v5);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, v4);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, v5);
			glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 120.0);
		}
		glNormal3f(0.0, 1.0, 0.0);
		glBegin(GL_QUADS);
			
			glVertex3f(-10/2, -0.0, -10/2);
			glVertex3f(-10/2, -0.0, 10/2);
			glVertex3f(10/2, -0.0, 10/2);
			glVertex3f(10/2, -0.0, -10/2);
		glEnd();
	glPopMatrix();
	
	renderWalls();

	renderSnowmen();
		
}

// yellow light
void renderLight0()
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	    glLightfv(GL_LIGHT0, GL_DIFFUSE, luz0);
	    glLightfv(GL_LIGHT0, GL_SPECULAR, luz0);
	    if(pos == 0) glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
		else if(pos == 1) glLightfv(GL_LIGHT0, GL_POSITION, light0_position1);
		else if(pos == 2) glLightfv(GL_LIGHT0, GL_POSITION, light0_position2);
		else if(pos == 3) glLightfv(GL_LIGHT0, GL_POSITION, light0_position3);
	glPopMatrix();  
}

//white light
void renderLight1()
{
	float camera1[4] = {0.0, 0.0, 0.0, 1.0};
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		glLoadIdentity();
        glLightfv(GL_LIGHT1, GL_DIFFUSE, luz1);
        glLightfv(GL_LIGHT1, GL_SPECULAR, luz1);
        glLightfv(GL_LIGHT1, GL_POSITION, camera1);  
	glPopMatrix(); 
}

void renderLight2()
{
	light2_position[3] = 1.0;
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		glLightfv(GL_LIGHT2, GL_DIFFUSE, luz2);
	    glLightfv(GL_LIGHT2, GL_SPECULAR, luz2);
	    glLightfv(GL_LIGHT2, GL_POSITION, light2_position);  
	glPopMatrix(); 
}


void refresh(void)
{ 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	renderLight0();
	renderLight1();
	renderLight2();

	renderAxis(SPHERE_RADIUS);
	renderScene();
	glPushMatrix();
		glTranslatef(Patricio.OBS[0], 0.0, Patricio.OBS[2]);
		glRotated(Patricio.Rotation, 0, 1, 0);
		
		glScalef(scaleLegoman_y, scaleLegoman_y, scaleLegoman_y);
		glTranslatef(-center_x, -min_y, -center_z);
		renderModel();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(2.5, 0.0, 2.5);
		renderAxis(2);
		glScalef(scaleLegoman_y_, scaleLegoman_y_, scaleLegoman_y_);
		glTranslatef(-center_x, -min_y, -center_z);
		renderModel();
	glPopMatrix();

	glutSwapBuffers();
}



void resize(int ample, int alt)
{
	
	width_current = ample;
	height_current = alt;
	
	glViewport(0, 0, width_current, height_current);
	toggleCamera();
	glutPostRedisplay();
		
}

void mouseMoved(int x, int y)
{
	
	if(zoom_state and (not FIRST_PERSONA_VISION))
	{

		zoom *= (y-start.y)/100+1;

		toggleCamera();
	}	

	width_current = glutGet( GLUT_WINDOW_WIDTH );
    height_current = glutGet( GLUT_WINDOW_HEIGHT );
	if(rotation || FIRST_PERSONA_VISION)
	{	
		finish.x = x;
		finish.y = y;
		
		angleX_current += x - start.x;
		angleY_current += y - start.y;
		toggleCamera();
	}


	start.x = x;
	start.y = y;
	
    glutPostRedisplay();
}


void processMouse(int button, int state, int x, int y)
{
	if(button == GLUT_RIGHT_BUTTON and state == GLUT_DOWN and (not FIRST_PERSONA_VISION))
	{
		zoom_state = true;
		rotation = false;
	}

	if (button == GLUT_RIGHT_BUTTON and state == GLUT_UP)
	{
		zoom_state = false;
	}

    start.x = finish.x = x;
    start.y = finish.y = y;
    glutPostRedisplay();
}


void keyBordFunc(unsigned char c, int x, int y)
{

	if(c == 'a')
	{
		Patricio.Rotation += 2.5;
		toggleCamera();
	}
	
	else if(c == 'd')
	{

		Patricio.Rotation -= 2.5;
		toggleCamera();
	}
			
	else if(c == 'w')
	{
		Patricio.OBS[0] += sin(Patricio.Rotation*MI_PI/180) * Patricio.speed;
		Patricio.OBS[2] += cos(Patricio.Rotation*MI_PI/180) * Patricio.speed;
		light2_position[0] = Patricio.OBS[0];
		light2_position[1] = 1;
		light2_position[2] = Patricio.OBS[2];
		toggleCamera();
	}

	else if(c == 's')
	{
		Patricio.OBS[0] -= sin(Patricio.Rotation*MI_PI/180) * Patricio.speed;
		Patricio.OBS[2] -= cos(Patricio.Rotation*MI_PI/180) * Patricio.speed;
		light2_position[0] = Patricio.OBS[0];
		light2_position[1] = 1;
		light2_position[2] = Patricio.OBS[2];
		toggleCamera();

	}
	
	else if(c == 'r')
	{
		zoom = 1;
		change = 1;
		angleY_current = 0;
		angleX_current = 0;
		Patricio.Rotation = -90.0;
		Patricio.speed = 0.2;
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHT1);
		glDisable(GL_LIGHT2);
		glDisable(GL_LIGHT0);
		glEnable(GL_LIGHTING);
		glEnable(GL_NORMALIZE);

		first = true;
		segon = true;
		visible = true;
		primer = true;
		FIRST_PERSONA_VISION = false;
		light = true;
		normal = true;
		ilumine = true;
		light1 = true;
		light0 = false;
		light2 = false;
		cull_face = false;
		light0_position[0] = 5.0;
		light0_position[1] = 1.5;
		light0_position[2] = 5.0;
		light0_position[4] = 1.0;
		Patricio.OBS = vector<double>(3, 0.0);
		toggleCamera();
	}
	
	else if(c == 'b')
	{
		if(not FIRST_PERSONA_VISION)
		{
			rotation = !rotation;
			zoom_state = false;
		}
	}
	
	else if(c == 'v')
	{
		visible = !visible;
	}

	else if(c == 'n')
	{
		normal = !normal;
	}

	else if(c == 'p')
	{
		if(not FIRST_PERSONA_VISION)
		{	
			change = !change;
		}
		toggleCamera();
	}

	else if(c == 'c' and change)
	{
		if(not FIRST_PERSONA_VISION)
		{
			change = false;
			FIRST_PERSONA_VISION = true;
		}
		else
			FIRST_PERSONA_VISION = false;
		change = true;
		toggleCamera();	
		//glutPostRedisplay();
	}

	else if(c == 'z')
	{
		Patricio.speed += 0.1;
	}

	else if(c == 'x')
	{
		if(Patricio.speed >= 0.2)
			Patricio.speed -= 0.1;
		else Patricio.speed = 0.2;
	}

	else if(c == 'i')
	{
		ilumine = !ilumine;
		if(ilumine) glEnable(GL_LIGHTING);
		else glDisable(GL_LIGHTING);
		
	}

	else if(c == 'f')
	{
		cull_face = !cull_face;
		if(cull_face) glEnable (GL_CULL_FACE);
		else glDisable(GL_CULL_FACE);
	}

	else if(c == 'm')
	{
		++pos;
		pos %= 4;
	}

	else if(c == '0')
	{
		light0 = !light0;
		if(light0)
		{
			glEnable(GL_LIGHT0);
			if(ilumine) cout << "You've turned on the LIGHT0" << endl;;
		}
		else 
		{
			glDisable(GL_LIGHT0);
			if(ilumine) cout << "You've turned off the LIGHT0" << endl;;
		}
	}

	else if(c == '1')
	{	
		light1 = !light1;
		if(light1)
		{
			glEnable(GL_LIGHT1);
			if(ilumine) cout << "You've turned on the LIGHT1" << endl;;
		}
		else 
		{
			glDisable(GL_LIGHT1);
			if(ilumine) cout << "You've turned off the LIGHT1" << endl;;
		}
	}

	else if(c == '2')
	{
		light2 = !light2;
		if(light2)
		{
			glEnable(GL_LIGHT2);
			if(ilumine) cout << "You've turned on the LIGHT2" << endl;;
		}
		else 
		{
			glDisable(GL_LIGHT2);
			if(ilumine) cout << "You've turned off the LIGHT2" << endl;;
		}
	}

	else if(c == 'h')
	{
		cout << "Manual instruction" << endl;
		cout << "h-------------------help" << endl;
		cout << "b-------------------inspect" << endl;
		cout << "v-------------------visible walls" << endl;
		cout << "p-------------------Perspective or Anoxe" << endl;
		cout << "c-------------------FIRST_PERSONA_VISION" << endl;
		cout << "m-------------------change the light0 position" << endl;
		cout << "f-------------------turn on/off back culling" << endl;
			cout << "w-------------------go ahead" << endl;
			cout << "s-------------------go back" << endl;
			cout << "a-------------------turn left" << endl;
			cout << "d-------------------turn right" << endl;
			cout << "z-------------------speed up" << endl;
			cout << "d-------------------speed down" << endl;
		cout << "Drag right click to zoom the stage" << endl;
		cout << "num 1----------------turn on/off the LIGHT1" << endl;
		cout << "num 2----------------turn on/off the LIGHT2" << endl;
		cout << "num 0----------------turn on/off the LIGHT0" << endl;
		cout << "ESC-----------------exit" << endl;
	}


	else if(c == 27)
		exit(0);

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
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);
	//glEnable(GL_CULL_FACE);
	toggleCamera();

	glClearColor((float)0.0, (float)0.0, (float)0.0, 1);
	
	glutDisplayFunc (refresh);
	glutReshapeFunc (resize);
	glutKeyboardFunc(keyBordFunc);
	
	glutMouseFunc(processMouse);
	glutMotionFunc(mouseMoved);

	m.load(argv[1]);

	angleY_current = 0;
	angleX_current = 0;
	Patricio.Rotation = -90.0;
	Patricio.speed = 0.2;
	Patricio.OBS = vector<double>(3, 0.0);

	if(first) 
	{
		sizeWanna = 1.0;
		standardizeModel(sizeWanna);
		first = false;
	}

	if(segon)
	{
		sizeWanna = 1.5;
		standardizeModel(sizeWanna);
		segon = false;
	}

  	glutMainLoop();
  	return 0;

}
