#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <math.h>

const int width = 2000;
const int height = 1060;
GLfloat eyeX = 0;
GLfloat eyeY = 5;
GLfloat eyeZ = 40;

float rot = 0;

static GLfloat v_cube[8][3] =
{
    {0.0, 0.0, 0.0}, //point index 0
    {0.0, 0.0, 1.0}, //point index 1
    {1.0, 0.0, 1.0}, //point index 2
    {1.0, 0.0, 0.0}, //point index 3
    {0.0, 1.0, 0.0}, //point index 4
    {0.0, 1.0, 1.0}, //point index 5
    {1.0, 1.0, 1.0}, //point index 6
    {1.0, 1.0, 0.0}, //point index 7
};
GLubyte v_indices[6][4] =
{
    {0, 1, 2, 3}, 
    {1, 5, 6, 2}, 
    {2, 6, 7, 3},
    {5, 4, 7, 6},
    {1, 5, 4, 0},
    {0, 4, 7, 3},
};
static void getNormal3p
(GLfloat x1, GLfloat y1,GLfloat z1, GLfloat x2, GLfloat y2,GLfloat z2, GLfloat x3, GLfloat y3,GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2-x1;
    Uy = y2-y1;
    Uz = z2-z1;

    Vx = x3-x1;
    Vy = y3-y1;
    Vz = z3-z1;

    Nx = Uy*Vz - Uz*Vy;
    Ny = Uz*Vx - Ux*Vz;
    Nz = Ux*Vy - Uy*Vx;

    glNormal3f(Nx,Ny,Nz);
}
void unitcube(GLfloat R = 1.0, GLfloat G = 0.987, GLfloat B = 0.7)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { R*0.2, G*0.2, B*0.2, 1.0 };
    GLfloat mat_diffuse[] = { R*0.8, G*0.8, B*0.8, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {32.0};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        glVertex3fv(&v_cube[v_indices[i][0]][0]);
        glVertex3fv(&v_cube[v_indices[i][1]][0]);
        glVertex3fv(&v_cube[v_indices[i][2]][0]);
        glVertex3fv(&v_cube[v_indices[i][3]][0]);
    }
    glEnd();
}

void light()
{
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = { 0.5, 0.5, 0.5, 1.0};
    GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 2.0, 5.0, 2.0, 1.0 };

    glEnable( GL_LIGHT0);
    glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv( GL_LIGHT0, GL_POSITION, light_position);

}


void room(){
    //glColor3f(0.941,0.933,0.612);
    glPushMatrix();
    glTranslatef(-28,-5,-15);
    glScalef(1,17,54);
    unitcube();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(26,-5,-15);
    glScalef(1,17,54);
    unitcube();
    glPopMatrix();
    
    //glColor3f(0.929,0.929,0.902);
    glPushMatrix();
    glTranslatef(-28,-5,-15);
    glScalef(53, 18, 1);
    unitcube();
    glPopMatrix();
    
    //glColor3f(1,1,0.918);
    glPushMatrix();
    glTranslatef(-28,12,-15);
    glScalef(55, 1, 55);
    unitcube();
    glPopMatrix();

    //glColor3f(0.388,0.388,0.357);
    glPushMatrix();
    glTranslatef(-28,-5,-15);
    glScalef(55, 1, 55);
    unitcube();
    glPopMatrix();

}

void table(float leg_height = 2, float length = 2, float width = 8)
{
    float height=2;


    float base_height=.5;
    float leg_width=.2;

   
    glPushMatrix();
    glScalef(width,base_height,length);
    glTranslatef(-0.5,0,-0.5);
    unitcube();
    glPopMatrix();

    
    glPushMatrix();
    glTranslatef((width/2-leg_width/2),0,(length/2-leg_width/2));
    glScalef(leg_width,leg_height,leg_width);
    glTranslatef(-0.5,-1,-0.5);
    unitcube();
    glPopMatrix();

    glPushMatrix();
    glTranslatef((width/2-leg_width/2),0,-(length/2-leg_width/2));
    glScalef(leg_width,leg_height,leg_width);
    glTranslatef(-0.5,-1,-0.5);
    unitcube();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-(width/2-leg_width/2),0,(length/2-leg_width/2));
    glScalef(leg_width,leg_height,leg_width);
    glTranslatef(-0.5,-1,-0.5);
    unitcube();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-(width/2-leg_width/2),0,-(length/2-leg_width/2));
    glScalef(leg_width,leg_height,leg_width);
    glTranslatef(-0.5,-1,-0.5);
    unitcube();
    glPopMatrix();


}

void computer()
{
    const float computer_width = 1.5;
    const float computer_height = 0.3;
    const float computer_depth = 1.0;

    //glColor3f(0.3, 0.3, 0.3); // Gray color for the computer
    glPushMatrix();
    glTranslatef(0.0, computer_height / 1.1, 0.2); // Position the computer on the table
    glScalef(computer_width, computer_height, computer_depth); // Scale the computer
    unitcube();
    glPopMatrix();
}

void monitor(){
    GLfloat computer_width1 = 2;
    GLfloat computer_height1 = 0.1;
    GLfloat computer_length1 = 2.4;
    glPushMatrix();
    //glColor3f(0.055, 0.059, 0.055);
    glScalef(computer_width1, computer_length1, computer_height1);
    glTranslatef(-1, 0, -1);
    unitcube();


   

    
   
    glPopMatrix();




}

void chair(float leg_height = 1, float seat_height = 1, float width = 0.5, float depth = 0.5)
{
    float leg_width = 0.1;
    float backrest_height = 1.5;
    
  
    glPushMatrix();
    //glColor3f(0.5, 0.35, 0.05); 
    glTranslatef(0, leg_height + seat_height / 2.0, 0);
    glScalef(width, seat_height, depth);
    unitcube();
    glPopMatrix();

   
    glPushMatrix();
    //glColor3f(0.5, 0.35, 0.05); 
    glTranslatef(0, leg_height + seat_height + backrest_height / 2.0, -depth / 2.0);
    glScalef(width, backrest_height, leg_width);
    unitcube();
    glPopMatrix();

    // Front left leg
    glPushMatrix();
    //glColor3f(0.5, 0.5, 0.5); //Grey color
    glTranslatef(-width / 2.0 - leg_width / 2.0, leg_height / 2.0, depth / 2.0 - leg_width / 2.0);
    glScalef(leg_width, leg_height, leg_width);
    unitcube();
    glPopMatrix();

    // Front right leg
    glPushMatrix();
    //glColor3f(0.5, 0.5, 0.5); // Gray color
    glTranslatef(width / 2.0 - leg_width / 2.0, leg_height / 2.0, depth / 2.0 - leg_width / 2.0);
    glScalef(leg_width, leg_height, leg_width);
    unitcube();
    glPopMatrix();

    // Back left leg
    glPushMatrix();
    //glColor3f(0.5, 0.5, 0.5); // Gray color 
    glTranslatef(-width / 2.0 -leg_width / 2.0, leg_height / 2.0, -depth / 2.0 + leg_width / 2.0);
    glScalef(leg_width, leg_height, leg_width);
    unitcube();
    glPopMatrix();

    // Back right leg
    glPushMatrix();
    //glColor3f(0.5, 0.5, 0.5); // Gray color for the legs
    glTranslatef(width / 2.0 - leg_width / 2.0, leg_height / 2.0, -depth / 2.0 + leg_width / 2.0);
    glScalef(leg_width, leg_height, leg_width);
    unitcube();
    glPopMatrix();
}
static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-5, 5, -5, 5, 2.0, 100.0);
    //monitor(1.5, 0.3, 0.2);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyeX, eyeY, eyeZ, 0, 0, 0, 0, 1, 0);
    glViewport(0, 0, width, height);
    glRotatef(rot, 0, 0, 1);
    glRotatef(rot, 1, 0, 0);
    glRotatef(rot, 0, 1, 0);

    //glColor3f(0.949, 0.949, 0.914);
    for (int i = -5; i <= 5; i += 8){
        for (int j = 1; j <= 5; j++) {
            glPushMatrix();
            glTranslatef(i, -2, 3 + j * 5);
            table(2, 2);
            glPopMatrix();
        }
        i += 2;
    }

    for (int i = -5; i <= 5; i += 8){
        for (int j = 1; j <= 5; j++) {
            glPushMatrix();
            glTranslatef(i + 0.9, -5, 2 + j * 5); // Adjust the position of the chair
            chair(2, 1, 1); // Adjust chair dimensions as needed
            glPopMatrix();
        }
        i += 2;
    }

    room();
/*    glPushMatrix();
    glTranslatef(0.0, 10.0, 0.0); // Position the fan at the ceiling
    glRotatef(rot, 0, 1, 0); // Rotate the fan
    fan();
    glPopMatrix();
    */
    for (int i = -5; i <= 5; i += 8){
        for (int j = 1; j <= 5; j++) {
            glPushMatrix();
            glTranslatef(i +0.5, -2, 2 + j * 5); // Adjust the position of the computer on the table
            computer(); // Draw a computer
            glPopMatrix();
        }
        i += 2;
    }
    for (int i = -5; i <= 5; i += 8){
        for (int j = 1; j <= 5; j++) {
            glPushMatrix();
            glTranslatef(i +0.7, -1, 3+ j * 5); // Adjust the position of the computer on the table
            monitor(); // Draw a computer
            glPopMatrix();
        }
        i += 2;
    }

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

    case 'u':
        eyeY++;
        break;
    case 'n':
        eyeY--;
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

    glutCreateWindow("3D Table");

    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);

    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    light();

    glutMainLoop();

    return EXIT_SUCCESS;
}