#if defined(__APPLE__)
    #include <OpenGL/OpenGL.h>
    #include <GLUT/GLUT.h>
#else
    #include <GL/gl.h>
    #include <GL/freeglut.h>
#endif
#include <stdio.h>

int noutriangle = 0;
float g = 1.0;
float b = 1.0;
float r = 1.0;
float posx, posy;
int apintar = 0;
int cont = 0;
int orix, oriy;
int amp, hi;
int x1, y1, x2, y2, x3, y3;
float xx1, yy1, xx2, yy2, xx3, yy3;
int fpretat = 0;

void refresh(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    if (noutriangle == 0)  {
        glBegin(GL_TRIANGLES);
            glVertex3f(-(1.0/2.0), -(1.0/3.0), 0);
            glVertex3f(1.0/2.0, -(1.0/3.0), 0);
            glVertex3f(0, 2.0/3.0, 0);
        glEnd();
    }
    else {
        glBegin(GL_TRIANGLES);
            glVertex3f(xx1, yy1, 0);
            glVertex3f(xx2, yy2, 0);
            glVertex3f(xx3, yy3, 0);
        glEnd();
    }
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

void convertir() {
    float sizeamp =  glutGet( GLUT_WINDOW_WIDTH );
    float sizehi  = glutGet( GLUT_WINDOW_HEIGHT );
    xx1 = (float(x1))*1.0/(amp/2.0) - 1.0;
    xx2 = (float(x2))*1.0/(amp/2.0) - 1.0;
    xx3 = (float(x3))*1.0/(amp/2.0) - 1.0;
    yy1 = -(float(y1))*1.0/(hi/2.0) + 1.0;
    yy2 = -(float(y2))*1.0/(hi/2.0) + 1.0;
    yy3 = -(float(y3))*1.0/(hi/2.0) + 1.0;
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
        if (apintar == 1) {
            ++cont;
            if (cont == 1) {
                x1 = xclick;
                y1 = yclick;

            }
            else if (cont == 2) {
                x2 = xclick;
                y2 = yclick;
            }
            else if (cont == 3) {
                x3 = xclick;
                y3 = yclick;
                convertir();
                cont = 0;
                apintar = 0;
            }
        }
    }
    glutPostRedisplay();
}

void motion (int x, int y) {
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
        posx = x;
        posy = y;
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0, g, b, 0);
    }
    glutPostRedisplay();
}

void ayuda() {
    printf("Usage:\n");
    printf("Este programa pinta un triangulo centralizado en el centro de la pantalla y sin deformacion\nSi quieres salir del programa apreta ESC \n\n");
    printf("Si deseas una ayuda sobre las funcionalidades apreta 'h'\n\n");
    printf("Apreta 'f'' para activar/desactivar la funcionalidad que permite cambiar color de fondo en mover el raton\n\n");
    printf("Apreta 't' permite pinta un nuevo triangulo con 3 clics siguientes\n\n");
}

void keyboard(unsigned char c, int x, int y) {
    if (c == 'f') {
        if (fpretat == 0) fpretat = 1;
        else fpretat = 0;
    }
    else if (c == 't') {
        apintar = 1;
        cont = 0;
        noutriangle = 1;
    }
    else if (c ==  'h') {
        ayuda();
    }
    else if (c == 27) exit(0);
    glutPostRedisplay();
}

void initGL() {
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (600, 600);
    glutCreateWindow("IDI: Practiques OpenGL");
    glutDisplayFunc (refresh);
    glutReshapeFunc(myfunc);
    glutKeyboardFunc (keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
}

int main(int argc, const char *argv[]) {
    glutInit(&argc, (char **)argv);
    initGL();
    glutMainLoop();
    return 0;
}

