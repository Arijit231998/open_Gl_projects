#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

const int width = 1800;
const int height = 1040;

GLfloat eyeX = 0;
GLfloat eyeY = 5;
GLfloat eyeZ = 40;
float rot = 0;
GLfloat bedWidth = 4;         // Adjusted bed dimensions
GLfloat bedLength = 6;
GLfloat bedHeight = 3.5;
GLfloat mattressHeight = 0.7;
GLfloat headboardHeight = 3;


static GLfloat v_cube[8][3] =
{
    {0.0, 0.0, 0.0}, //point index 0
    {0.0, 0.0, 1.0}, //point index 1
    {1.0, 0.0, 1.0}, //point index 2
    {1.0, 0.0, 0.0}, //point index 3
    {0.0, 1.0, 0.0}, //point index 4
    {0.0, 1.0, 1.0}, //point index 5
    {1.0, 1.0, 1.0}, //point index 6
    {1.0, 1.0, 0.0}  //point index 7
};

GLubyte c_Indices[6][4] =
{
    {0, 1, 2, 3},
    {1, 5, 6, 2},
    {2, 6, 7, 3},
    {5, 4, 7, 6},
    {1, 5, 4, 0},
    {0, 4, 7, 3}
};

void unitcube()
{
    glBegin(GL_QUADS);
    for (GLint i = 0; i < 6; i++)
    {
        for (GLint j = 0; j < 4; j++)
        {
            glVertex3fv(&v_cube[c_Indices[i][j]][0]);
        }
    }
    glEnd();
}
void drawBed(GLfloat width, GLfloat length, GLfloat height, GLfloat mattressHeight, GLfloat headboardHeight)
{
    // Draw the main frame
    glColor3f(0.5, 0.3, 0.1);
    glPushMatrix();
    glTranslatef(0, height / 10, 0);
    glScalef(width, height, length);
    unitcube();
    glPopMatrix();

    // Draw the mattress
    glColor3f(0.9,0.2,0.1 );
    glPushMatrix();
    glTranslatef(0, height + mattressHeight / 15, 0);
    glScalef(width, mattressHeight, length);
    unitcube();
    glPopMatrix();

    // Draw the headboard
    glColor3f(0.5, 0.3, 0.1);
    glPushMatrix();
    glTranslatef(0, height / 8 + headboardHeight / 5, -length / 8);
    glScalef(width, headboardHeight, 0.9);
    unitcube();
    glPopMatrix();
}
void bedroom()
{
    glColor3f(0.9, 1, 0.8);
    glPushMatrix();
    glTranslatef(-30,-5,-15);
    glScalef(1, 18, 55);
    unitcube();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(26,-5,-15);
    glScalef(1, 18, 55);
    unitcube();
    glPopMatrix();

    glColor3f(0.8, 1, 1);
    glPushMatrix();
    glTranslatef(-30,-5,-15);
    glScalef(56, 18, 1);
    unitcube();
    glPopMatrix();

    glColor3f(1, 1, 0.918);
    glPushMatrix();
    glTranslatef(-30,12,-15);
    glScalef(56, 1, 55);
    unitcube();
    glPopMatrix();

    glColor3f(0.9, 0.5, 0);
    glPushMatrix();
    glTranslatef(-30,-5,-15);
    glScalef(56, 1, 55);
    unitcube();
    glPopMatrix();
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-5, 5, -5, 5, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyeX, eyeY, eyeZ, 0, 0, 0, 0, 1, 0);
    glViewport(0, 0, width, height);
    glRotatef(rot, 0, 0, 1);
    glRotatef(rot, 1, 0, 0);
    glRotatef(rot, 0, 1, 0);

    glPushMatrix();
    glScalef(3, 1, 3);
    glRotatef(rot, 0, 0, 1);
    bedroom();
    drawBed(bedWidth, bedLength, bedHeight, mattressHeight, headboardHeight);
    glPopMatrix();


    glutSwapBuffers();
}

static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
    case 'q':
        exit(0);
        break;

    case ',':
        rot++;
        break;
    case '.':
        rot--;
        break;
    case 's':
        eyeZ++;
        break;
    case 'w':
        eyeZ--;
        break;

    case 'd':
        eyeX++;
        break;
    case 'a':
        eyeX--;
        break;
    }

    glutPostRedisplay();
}

static void idle(void)
{
    //rot -= 0.01;
    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(10, 10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Bedroom Scene");

    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);

    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);
    glEnable(GL_BLEND);

    glutMainLoop();

    return EXIT_SUCCESS;
}