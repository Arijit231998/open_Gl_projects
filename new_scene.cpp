#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h> // Add this header for random tree placement




const int width = 3000;
const int height = 2060;
GLfloat eyeX = 0;
GLfloat eyeY = 5;
GLfloat eyeZ = 40;

// Define lighting control variables
bool amb1 = false;
bool diff1 = false;
bool spec1 = false;

bool amb2 = false;
bool diff2 = false;
bool spec2 = false;

bool switchLamp = false;
bool amb3 = false;
bool diff3 = false;
bool spec3 = false;
GLfloat refX = 0.0;
GLfloat refY = 0.0;
GLfloat refZ = 0.0;

bool switchOne = false;
bool switchTwo = false;

float rot = 0;
GLfloat light0_position[] = { 2.0, 5.0, 2.0, 1.0 };
GLfloat light1_position[] = { -2.0, 5.0, -2.0, 1.0 };

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

GLubyte v_indices[6][4] =
{
    {0, 1, 2, 3},
    {1, 5, 6, 2},
    {2, 6, 7, 3},
    {5, 4, 7, 6},
    {1, 5, 4, 0},
    {0, 4, 7, 3}
};

static void getNormal3p(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2, GLfloat x3, GLfloat y3, GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2 - x1;
    Uy = y2 - y1;
    Uz = z2 - z1;

    Vx = x3 - x1;
    Vy = y3 - y1;
    Vz = z3 - z1;

    Nx = Uy * Vz - Uz * Vy;
    Ny = Uz * Vx - Ux * Vz;
    Nz = Ux * Vy - Uy * Vx;

    glNormal3f(Nx, Ny, Nz);
}

void unitcube(GLfloat R, GLfloat G, GLfloat B)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { R * 0.2, G * 0.2, B * 0.2, 1.0 };
    GLfloat mat_diffuse[] = { R * 0.8, G * 0.8, B * 0.8, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 32.0 };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glBegin(GL_QUADS);
    for (GLint i = 0; i < 6; i++)
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
    // Light 0
    GLfloat light0_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat light0_diffuse[] = { 1.7, 1.7, 1.7, 1.0 };
    GLfloat light0_specular[] = { 1.7, 1.7, 1.7, 1.0 };
    GLfloat light0_position[] = { 2.0, 5.0, 2.0, 1.0 };

    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    //Light 1
    GLfloat light1_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat light1_diffuse[] = { 1.7, 1.7, 1.7, 1.0 };
    GLfloat light1_specular[] = { 1.7, 1.7, 1.7, 1.0 };
    GLfloat light1_position[] = { 2.0, 5.0, 2.0, 1.0 };

    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);

    //Light2
    GLfloat light2_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat light2_diffuse[] = { 1.7, 1.7, 1.7, 1.0 };
    GLfloat light2_specular[] = { 1.7, 1.7, 1.7, 1.0 };
    GLfloat light2_position[] = { 2.0, 5.0, 2.0, 1.0 };

    glEnable(GL_LIGHT2);
    glLightfv(GL_LIGHT2, GL_AMBIENT, light2_ambient);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
    glLightfv(GL_LIGHT2, GL_SPECULAR, light2_specular);
    glLightfv(GL_LIGHT2, GL_POSITION, light2_position);



}
void land() {
    // Calculate the center of the land
  
    glPushMatrix();
    glTranslatef(0, -5, 0);
    glScalef(100, 1, 100);
    unitcube(0, 1, 0.271); 
    glPopMatrix();
}

void grassBlade() {
    glPushMatrix();
    glBegin(GL_TRIANGLES);
    // Define the vertices for a single grass blade (triangle)
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(-0.1, 0.4, 0.0);
    glVertex3f(0.1, 0.4, 0.0);
    glEnd();
    glPopMatrix();
}
void tree()
{
    // Tree trunk
    
    glPushMatrix();
    glTranslatef(0, -5, 0);
    glScalef(1, 7, 1);
    unitcube(0.545, 0.271, 0.075); // Brown color for the trunk
    glPopMatrix();

    
    glPushMatrix();
    glTranslatef(0, 9, 0);
    glScalef(4, 5 , 4);
    unitcube(0, 1, 0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 5, 0);
    glScalef(1, 7, 1);
    unitcube(0.545, 0.271, 0.075); // Brown color for the trunk
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 2, 0);
    glScalef(5, 5, 4);
    unitcube(0, 1, 0);
    glPopMatrix();


    
    GLfloat vertices[8][3] = {
        {0.0, 0.0, 1.0},  // Vertex 0
        {1.0, 0.0, 0.0},  // Vertex 1
        {0.0, 0.0, -1.0}, // Vertex 2
        {-1.0, 0.0, 0.0}, // Vertex 3
        {0.0, 2.0, 1.0},  // Vertex 4
        {1.0, 2.0, 0.0},  // Vertex 5
        {0.0, 2.0, -1.0}, // Vertex 6
        {-1.0, 2.0, 0.0}  // Vertex 7
    };

    

    GLubyte indices[6][4] = {
        {0, 1, 5, 4}, // Bottom face
        {1, 2, 6, 5}, // Right face
        {2, 3, 7, 6}, // Top face
        {3, 0, 4, 7}, // Left face
        {0, 1, 2, 3}, // Front face
        {4, 5, 6, 7}  // Back face
    };

   
    glBegin(GL_QUADS);
    for (GLint i = 0; i < 6; i++)
    {
        for (GLint j = 0; j < 4; j++)
        {
            glVertex3fv(&vertices[indices[i][j]][0]);
        }
    }
    glEnd();
    glPopMatrix();
}

static void display(void) {
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

    

    land();


int numRows = 10;
int numCols = 10;
float stepX = 100.0 / numRows;
float stepZ = 100.0 / numCols;
float treeSizeX = stepX * 0.8;
float treeSizeZ = stepZ * 0.8;
float landCenterX = 0.0;
float landCenterZ = 0.0;

float grassSizeX = stepX * 0.5; // Define the size of the grass patch
float grassSizeZ = stepZ * 0.5;

for (int i = 0; i < numRows; i++) {
    for (int j = 0; j < numCols; j++) {
        float x = landCenterX - 1.0 + i * stepX;
        float z = landCenterZ - 1.0 + j * stepZ;
        float minX = x - treeSizeX / 2.0;
        float maxX = x + treeSizeX / 2.0;
        float minZ = z - treeSizeZ / 2.0;
        float maxZ = z + treeSizeZ / 2.0;

        if (minX >= -100.0 && maxX <= 100.0 && minZ >= -100.0 && maxZ <= 100.0) {
            glPushMatrix();
            glTranslatef(x, 0, z);
            tree();
            glPopMatrix();

            // Draw grass blades in between the trees
            float grassX = x - grassSizeX / 1.0;
            float grassZ = z - grassSizeZ / 1.0;

            for (int k = 0; k < 5; k++) { // Draw 5 grass blades in between each tree
                for (int l = 0; l < 5; l++) {
                    glPushMatrix();
                    glTranslatef(grassX + k * (grassSizeX / 4.0), -4.9, grassZ + l * (grassSizeZ / 4.0));
                    grassBlade(); // Draw a single blade of grass
                    glPopMatrix();
                }
            }
        }
    }
}
    glutSwapBuffers();
}


void myKeyboardFunc(unsigned char key, int x, int y) {
    switch (key) {
        case 'w': // move eye point upwards along Y axis
            eyeY += 1.0;
            break;
        case 's': // move eye point downwards along Y axis
            eyeY -= 1.0;
            break;
        case 'a': // move eye point left along X axis
            eyeX -= 1.0;
            break;
        case 'd': // move eye point right along X axis
            eyeX += 1.0;
            break;
        case 'o':  // zoom out
            eyeZ += 1;
            break;
        case 'i': // zoom in
            eyeZ -= 1;
            break;
        case 'q': // back to default eye point and ref point
            eyeX = 7.0; eyeY = 2.0; eyeZ = 7.0;
            refX = 0.0; refY = 0.0; refZ = 0.0;
            break;
        case 'j': // move ref point upwards along Y axis
            refY += 1.0;
            break;
        case 'n': // move ref point downwards along Y axis
            refY -= 1.0;
            break;
        case 'b': // move ref point left along X axis
            refX -= 1.0;
            break;
        case 'm': // move ref point right along X axis
            refX += 1.0;
            break;
        case 'k':  // move ref point away from screen/ along z axis
            refZ += 1;
            break;
        case 'l': // move ref point towards screen/ along z axis
            refZ -= 1;
            break;
        case '1': // to turn on and off light one
            if (switchOne == false) {
                switchOne = true; amb1 = true; diff1 = true; spec1 = true;
                glEnable(GL_LIGHT0);
                break;
            } else if (switchOne == true) {
                switchOne = false; amb1 = false; diff1 = false; spec1 = false;
                glDisable(GL_LIGHT0);
                break;
            }
        case '2': // to turn on and off light two
            if (switchTwo == false) {
                switchTwo = true; amb2 = true; diff2 = true; spec2 = true;
                glEnable(GL_LIGHT1);
                break;
            } else if (switchTwo == true) {
                switchTwo = false; amb2 = false; diff2 = false; spec2 = false;
                glDisable(GL_LIGHT1);
                break;
            }
        case '3': // to turn on and off light three
            if (switchLamp == false) {
                switchLamp = true; amb3 = true; diff3 = true; spec3 = true;
                glEnable(GL_LIGHT2);
                break;
            } else if (switchLamp == true) {
                switchLamp = false; amb3 = false; diff3 = false; spec3 = false;
                glDisable(GL_LIGHT2);
                break;
            }
        case '4': // turn on/off ambient light 1
            if (amb1 == false) {
                amb1 = true;
                break;
            } else {
                amb1 = false;
                break;
            }
        // Rotation keys
        case 'r': // Rotate about Y axis
            rot += 1.0;
            break;
        case 't': // Rotate about X axis
            rot -= 1.0;
            break;
        case 'Y': // Rotate about Z axis
            // Implement Z-axis rotation logic here if needed
            break;
        

        case 27: // Escape key
            exit(1);
    }

    glutPostRedisplay();
}


int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(10, 10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("3D Forest");

    glutDisplayFunc(display);
    glutKeyboardFunc(myKeyboardFunc);  // Corrected function reference

    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    light();
    glutMainLoop();

    return EXIT_SUCCESS;
}