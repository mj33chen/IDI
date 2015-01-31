#if defined(__APPLE__)
    #include <OpenGL/OpenGL.h>
    #include <GLUT/GLUT.h>
#else
    #include <GL/gl.h>
    #include <GL/freeglut.h>
#endif
#include <stdio.h>
#include "model.h"
#include <iostream>
using namespace std;

Model m;
int enable = 1;
int line = 0;
float g = 1.0;
float b = 1.0;
float r = 1.0;
float posx, posy;
int cont = 0;
int orix, oriy;
int amp, hi;
int fpretat = 0;
int gir = 0;
int trans = 0;
int ejex = 0;
int ejey = 0;
int ejez = 0;
int alfaz = 0;
int alfay = 0;
int alfax = 0;
float tx = 0.0;
float ty = 0.0;
int ordre = 0;
int e = 0;
double minx, maxx, miny, maxy, minz, maxz;

void minimcontenedora() {
    minx = maxx = miny = maxy = minz = maxz = 0;
    for (int i = 1; i < m.vertices().size(); ++i) {
        const double *v = &m.vertices()[i];  //obtenemos la direccion del vertice i guardado en puntero v
        if (*(v) < minx) minx = *(v);
        if (*(v) > maxx) maxx = *(v);
        if (*(v+1) < miny) miny = *(v+1);
        if (*(v+1) > maxy) maxy = *(v+1);
        if (*(v+2) < minz) minz = *(v+2);
        if (*(v+2) > maxz) maxz = *(v+2);
    }
}

void pintaterra() {
    glPushMatrix();
    glColor4f(1, 0.8, 1, 1);
    glBegin(GL_QUADS);
        glVertex3f(-0.75, -0.4, -0.75);
        glVertex3f(-0.75, -0.4, 0.75);
        glVertex3f(0.75, -0.4, 0.75);
        glVertex3f(0.75, -0.4, -0.75);
    glEnd();
    glPopMatrix();
}

void pintamodel () {
    for (int i = 0; i < m.faces().size(); ++i) {
        const Face &f = m.faces()[i];  //obtenemos la cara i
        glPushMatrix();
        glTranslated(-1, -0.15, 0.5);
        glScaled(1/((maxx-minx)*2.0), 1/((maxy-miny)*2.0), 1/((maxz-minz)*2.0));
        glTranslated(-(maxx-minx)/2.0, -(maxy-miny)/2.0, -(maxz-minz)/2.0);
        glBegin(GL_TRIANGLES);
            glColor4fv(Materials[f.mat].diffuse);
            glVertex3dv(&m.vertices()[f.v[0]]);
            glVertex3dv(&m.vertices()[f.v[1]]);
            glVertex3dv(&m.vertices()[f.v[2]]);;
        glEnd();
        glPopMatrix();

    // O una altra alternativa d’ús
    // const double *v = &m.vertices()[i];
    // glVertex3dv (v)
    }
}

void refresh(void) {
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    if (e == 1) glScaled(0.5,0.5,0.5);

        glRotated(alfax, ejex, 0, 0);
        glRotated(alfay, 0, ejey, 0);
        glRotated(alfaz, 0, 0, ejez);

        glTranslated(tx, ty, 0.0);

    //esfera1
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glutWireSphere(0.4, 500, 500);
    glPopMatrix();
    //esfera2
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(0, 0.6, 0);
    glutWireSphere(0.2, 500, 500);
    glPopMatrix();
    //cono
    glPushMatrix();
    glColor3f(1.0, 0.2, 0.6);
    glTranslatef(0.2, 0.6, 0);
    glRotatef(90, 0, 1, 0);
    glutWireCone(0.1, 0.2, 500, 500);
    glPopMatrix();
    pintamodel();
    pintaterra();
    glutSwapBuffers();
}


void myfunc(int x, int y) {
    amp = x;
    hi = y;
    orix = oriy = 0;
    if (x < y) {
        oriy = (y - x)/2;
        y = x;
    }
    else {
        orix = (x - y)/2;
        x = y;
    }
    glViewport(orix, oriy, x, y);
}

void mouse(int boton,  int stat, int xclick, int yclick) {
    if (stat == GLUT_DOWN) {
        if (fpretat == 1) {
            g = 1.0;
            b = 1.0;
            posx = xclick;
            posy = yclick;
            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(0, g, b, 0);
        }
    }
    glutPostRedisplay();
}

void motion (int x, int y) {
    if (x < posx) {
        if (gir == 1) {
            ejey = 1;
            alfay -= 5;
        }
        else if (trans == 1) {
            tx -= 0.05;
        }
    }
    else if (x > posx) {
        if (gir == 1) {
            ejey = 1;
            alfay += 5;
        }
        else if (trans == 1) {
            tx += 0.05;
        }
    }
    if (y < posy) {
        if (gir == 1) {
            ejex = 1;
            alfax -= 5;
        }
        else if (trans == 1) {
            ty += 0.05;
        }
    }
    else if (y > posy) {
        if (gir == 1) {
            ejex = 1;
            alfax += 5;
        }
        else if (trans == 1) {
            ty -= 0.05;
        }
    }
    if (fpretat == 1) {
        if (x < posx) {
            if (g >= 0.1) g -= 0.1;
            else g = 0.0;
            r += 0.1;
        }
        else {
            if (g <= 0.9) g+= 0.1;
            else g = 1.0;
            r -= 0.1;
        }
        if (y < posy) {
            if (b >= 0.1) b -= 0.1;
            else b = 0.0;
        }
        else {
            if (b <= 0.9) b+= 0.1;
            else b = 1.0;
        }
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0, g, b, 0);
    }
    posx = x;
    posy = y;
    glutPostRedisplay();
}

void ayuda() {

}

void keyboard(unsigned char c, int x, int y) {
    if (c == 'f') {
        if (fpretat == 0) fpretat = 1;
        else fpretat = 0;
    }
    else if (c == 't') {  //translacion
        trans = 1;
        gir = 0;

    }
    else if (c == 'g') { //gir
        trans = 0;
        gir = 1;

    }
    else if (c ==  'h') {
        ayuda();
    }
    else if (c == 'a') {
        alfaz +=15;
        ejez = 1;
    }
    else if (c == 'd') {
        alfaz -= 15;
        ejez = 1;
    }
    else if (c == 'e') {
        if (e == 1) e = 0;
        else e = 1;
    }
    else if (c == 'l') {
        if (line == 1) {
            line = 0;
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
        else {
            line = 1;
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
    }
    else if (c == 'o') {
        if (enable == 1) {
            enable = 0;
            glDisable(GL_DEPTH_TEST);
        }
        else {
            enable = 1;
            glEnable(GL_DEPTH_TEST);
        }
    }
    else if (c == 27) exit(0);
    glutPostRedisplay();
}

void initGL() {
    glutCreateWindow("IDI: Practiques OpenGL");
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);

    glutDisplayFunc (refresh);
    glutReshapeFunc(myfunc);
    glutKeyboardFunc (keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
}

int main(int argc, const char *argv[]) {
    glutInit(&argc, (char **)argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (600, 600);
    initGL();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_DEPTH_TEST);
    m.load("legoman.obj");
    minimcontenedora();
    glutMainLoop();
    return 0;
}
