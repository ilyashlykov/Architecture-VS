#include	<stdio.h>
#include	<stdlib.h>
#include	<math.h>
#include <cmath>
#include <time.h>
#include <iostream>
#include <glut.h>

using namespace std;

void display();
void drawSideType1();
void drawSideType2();
void drawCubeType1();
void drawCubeType2();
void keyboard(unsigned char key, int x, int y);
void mouseButton(int button, int state, int x, int y);
void mouseMove(int x, int y);
float module(float a[3]);
float* new_vector(float va[3], float vb[3], float vc[3], float vd[3], float y, float z);
void init();

GLdouble eye_x = -4, eye_y = 1.8, eye_z = -4;

float angle = 0;
float deltaAngle = 0.0f;
int xOrigin = -1;
bool flagLocal = false;


int main(int argc, char* argv[])
{
    srand(time(0));

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 500);

    int    glWin = glutCreateWindow("CUBOIDS");

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMove);

    init();


    glutMainLoop();

    return 0;
}


void init() {
    glClearColor(0.0, 0.0, 0.0, -1.0);
    glEnable(GL_DEPTH_TEST);

    glViewport(0, 0, 2560.0, 1440.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 1000.0 / 500.0, 1.0, 200.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
        eye_x * cos(angle + deltaAngle), eye_y, eye_z * sin(angle + deltaAngle),
        0.0, 0.0, 0.0,
        0.0, 1.0, 0.0
    );
}


void drawSideType1()
{

    glBegin(GL_QUADS);
    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(0.0, 1.0, 1.0);
    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 1.0);
    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(0.0, 1.0, 0.0);
    glEnd();
    glEnable(GL_NORMALIZE);
}

float module(float a[3])
{
    float mod = 0;
    for (int i = 0; i < 2; i++)
    {
        mod += pow(a[i], 2);
    }
    mod = sqrt(mod);
    return mod;
}

float* new_vector(float va[3], float vb[3], float vc[3], float vd[3], float y, float z)
{
    float new_vect[3];
    float sum[3];
    float a = (1.0 - y) * (1.0 - z);
    float b = (1.0 - y) * z;
    float c = y * z;
    float d = y * (1.0 - z);

    for (int i = 0; i < 3; i++)
    {
        sum[i] = a * va[i] + b * vb[i] + c * vc[i] + d * vd[i];
    }

    for (int i = 0; i < 3; i++)
    {
        new_vect[i] = (a * va[i] + b * vb[i] + c * vc[i] + d * vd[i]) / module(sum);
    }

    return new_vect;
}

void drawSideType2()
{
    float va[3] = { -0.5, 0.5, 0.5 };
    float vb[3] = { -0.5, -0.5, 0.5 };
    float vc[3] = { -0.5, -0.5, -0.5 };
    float vd[3] = { -0.5, 0.5, -0.5 };
    float* new_a;
    float* new_b;
    float* new_c;
    float* new_d;

    glBegin(GL_QUADS);
    new_a = new_vector(va, vb, vc, vd, 1.0, 1.0);
    glNormal3f(new_a[0], new_a[1], new_a[2]);
    glVertex3f(0.0, 1.0, 1.0);
    new_b = new_vector(va, vb, vc, vd, 0.0, 1.0);
    glNormal3f(new_b[0], new_b[1], new_b[2]);
    glVertex3f(0.0, 0.0, 1.0);
    new_c = new_vector(va, vb, vc, vd, 0.0, 0.0);
    glNormal3f(new_c[0], new_c[1], new_c[2]);
    glVertex3f(0.0, 0.0, 0.0);
    new_d = new_vector(va, vb, vc, vd, 1.0, 0.0);
    glNormal3f(new_d[0], new_d[1], new_d[2]);
    glVertex3f(0.0, 1.0, 0.0);
    glEnd();

    glEnable(GL_NORMALIZE);
}

void drawCubeType1()
{
    glPushMatrix();
    drawSideType1();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(1.0, 0.0, 0.0);
    glRotatef(180.0f, 0.0, 1.0, 0.0);
    glTranslatef(0.0, 0.0, -1.0);
    drawSideType1();
    glPopMatrix();
    glPushMatrix();
    glRotatef(-90.0f, 0.0, 0.0, 1.0);
    glRotatef(180.0f, 0.0, 1.0, 0.0);
    glTranslatef(0.0, 0.0, -1.0);
    drawSideType1();
    glTranslatef(1.0, 0.0, 0.0);
    glRotatef(180.0f, 0.0, 1.0, 0.0);
    glTranslatef(0.0, 0.0, -1.0);
    drawSideType1();
    glPopMatrix();
    glPushMatrix();
    glRotatef(90.0f, 0.0, 1.0, 0.0);
    glRotatef(180.0f, 0.0, 1.0, 0.0);
    glTranslatef(0.0, 0.0, -1.0);
    drawSideType1();
    glTranslatef(1.0, 0.0, 0.0);
    glRotatef(180.0f, 0.0, 1.0, 0.0);
    glTranslatef(0.0, 0.0, -1.0);
    drawSideType1();
    glPopMatrix();
}

void drawCubeType2()
{
    glPushMatrix();
    drawSideType2();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(1.0, 0.0, 0.0);
    glRotatef(180.0f, 0.0, 1.0, 0.0);
    glTranslatef(0.0, 0.0, -1.0);
    drawSideType2();
    glPopMatrix();
    glPushMatrix();
    glRotatef(-90.0f, 0.0, 0.0, 1.0);
    glRotatef(180.0f, 0.0, 1.0, 0.0);
    glTranslatef(0.0, 0.0, -1.0);
    drawSideType2();
    glTranslatef(1.0, 0.0, 0.0);
    glRotatef(180.0f, 0.0, 1.0, 0.0);
    glTranslatef(0.0, 0.0, -1.0);
    drawSideType2();
    glPopMatrix();
    glPushMatrix();
    glRotatef(90.0f, 0.0, 1.0, 0.0);
    glRotatef(180.0f, 0.0, 1.0, 0.0);
    glTranslatef(0.0, 0.0, -1.0);
    drawSideType2();
    glTranslatef(1.0, 0.0, 0.0);
    glRotatef(180.0f, 0.0, 1.0, 0.0);
    glTranslatef(0.0, 0.0, -1.0);
    drawSideType2();
    glPopMatrix();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glScalef(1, 1, 1);
    glTranslatef(-0.002f, 0.0f, -2.0f);
    drawCubeType1();
    glTranslatef(0.0f, 0.0f, 3.0f);
    drawCubeType2();
    glPopMatrix();
    glPopMatrix();
    glutSwapBuffers();
}


void keyboard(unsigned char key, int x, int y)
{
    float mAmb[] = { 0.2f, 0.2f, 0.2f };
    float mDif[] = { 0.8f, 0.8f, 0.8f };
    float mSpec[] = { 0.9f, 0.9f, 0.9f };
    float mEm[] = { 0.0f, 0.5f, 0.5f };
    float zeroDif[] = { 0.0f, 0.0f, 0.0f };
    float lPos[] = { static_cast<float>(eye_x * 5.0), static_cast<float>(eye_y * 5.0), static_cast<float>(eye_z * 5.0) };
    float lPos1[] = { static_cast<float>(eye_x * 0.3), static_cast<float>(eye_y * 0.3), static_cast<float>(eye_z * 0.4) };
    GLfloat lSpec[] = { 1.0f, 1.0f, 1.0f };
    GLfloat lSpec1[] = { 0.5f, 0.5f, 0.5f };
    GLfloat lDif[] = { 1.0f, 1.0f, 1.0f };
    GLfloat lZero[] = { 0.0f, 0.0f, 0.0f };
    GLfloat lAmb[] = { 0.0, 0.0, 0.0, 1.0 };
    float amb[4] = { 2.0, 7.0, 2.0, 1 };

    switch (key)
    {
    case '1':
        glClearColor(0.0, 1.0, 1.0, -1.0);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mSpec);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, zeroDif);
        glLightfv(GL_LIGHT0, GL_SPECULAR, lSpec);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, lZero);
        glLightfv(GL_LIGHT0, GL_POSITION, lPos);
        glEnable(GL_LIGHT0);
        glEnable(GL_LIGHTING);
        glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);

        glutPostRedisplay();
        break;
    case '2':
        glClearColor(0.0, 1.0, 1.0, -1.0);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mSpec);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, zeroDif);
        glLightfv(GL_LIGHT0, GL_SPECULAR, lZero);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, lSpec);
        glLightfv(GL_LIGHT0, GL_POSITION, lPos);
        glEnable(GL_LIGHT0);
        glEnable(GL_LIGHTING);
        glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);

        glutPostRedisplay();
        break;
    case '3':
        glClearColor(0.0, 1.0, 1.0, -1.0);
        glMaterialfv(GL_FRONT, GL_SPECULAR, zeroDif);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mDif);
        glLightfv(GL_LIGHT0, GL_SPECULAR, lSpec);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, lZero);
        glLightfv(GL_LIGHT0, GL_POSITION, lPos);
        glEnable(GL_LIGHT0);
        glEnable(GL_LIGHTING);
        glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);

        glutPostRedisplay();
        break;
    case '4':
        glClearColor(0.0, 1.0, 1.0, -1.0);
        glMaterialfv(GL_FRONT, GL_SPECULAR, zeroDif);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mDif);
        glLightfv(GL_LIGHT0, GL_SPECULAR, lZero);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, lDif);
        glLightfv(GL_LIGHT0, GL_POSITION, lPos);
        glEnable(GL_LIGHT0);
        glEnable(GL_LIGHTING);
        glEnable(GL_DEPTH_TEST);
        glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);
        glutPostRedisplay();
        break;

    case 'a':
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);
        glEnable(GL_LIGHTING);
        glEnable(GL_DEPTH_TEST);
        glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);

        glutPostRedisplay();
        break;
    case 'l':

        glLightfv(GL_LIGHT0, GL_POSITION, lPos1);
        glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.0);
        glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 1.0);
        glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 5.0);
        glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
        glutPostRedisplay();

        break;

    case 'e':
        glMaterialfv(GL_FRONT, GL_EMISSION, mEm);
        glEnable(GL_LIGHTING);

        glutPostRedisplay();
        break;
    case 's':
        glShadeModel(GL_FLAT);
        glEnable(GL_LIGHTING);

        glutPostRedisplay();
        break;
    }
}


void mouseButton(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_UP)
        {
            angle += deltaAngle;
            xOrigin = -1;
        }
        else
        {
            xOrigin = x;
        }
    }
}

void mouseMove(int x, int y)
{
    if (xOrigin >= 0)
    {
        deltaAngle = (x - xOrigin) * 0.005f;

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(
            eye_x * cos(angle + deltaAngle), eye_y, eye_z * sin(angle + deltaAngle),
            0.0, 0.0, 0.0,
            0.0, 1.0, 0.0
        );
        glutPostRedisplay();
    }
}


