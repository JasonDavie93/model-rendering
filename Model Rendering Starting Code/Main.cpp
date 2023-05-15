

// ----------------------------------------------------------
// Includes
// ----------------------------------------------------------
#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>

// ----------------------------------------------------------
// Global Variables
// ----------------------------------------------------------
double rotate_y = 0;
double rotate_x = 0;

float windowWidth = 500, windowHeight = 500;

// ----------------------------------------------------------
// Function to draw the cube model using primitives
// ----------------------------------------------------------
void drawCube()
{
    // DRAW MODEL

   //Multi-colored side - FRONT
    glBegin(GL_POLYGON);

    glColor3f(0.3, 0.1, 0.3);     glVertex3f(0.5, -0.5, -0.5);      // P1 is red
    glColor3f(0.5, 0.5, 0.5);     glVertex3f(0.5, 0.5, -0.5);      // P2 is green
    glColor3f(0.8, 0.5, 0.7);     glVertex3f(-0.5, 0.5, -0.5);      // P3 is blue
    glColor3f(0.4, 0.2, 0.7);     glVertex3f(-0.5, -0.5, -0.5);      // P4 is purple

    glEnd();

    // White side - BACK
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(0.5, -0.5, 0.5);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(-0.5, 0.5, 0.5);
    glVertex3f(-0.5, -0.5, 0.5);
    glEnd();

    // Purple side - RIGHT
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 1.0);
    glVertex3f(0.5, -0.5, -0.5);
    glVertex3f(0.5, 0.5, -0.5);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(0.5, -0.5, 0.5);
    glEnd();

    // Green side - LEFT
    glBegin(GL_POLYGON);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(-0.5, 0.5, 0.5);
    glVertex3f(-0.5, 0.5, -0.5);
    glVertex3f(-0.5, -0.5, -0.5);
    glEnd();

    // Blue side - TOP
    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(0.5, 0.5, -0.5);
    glVertex3f(-0.5, 0.5, -0.5);
    glVertex3f(-0.5, 0.5, 0.5);
    glEnd();

    // Red side - BOTTOM
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0.5, -0.5, -0.5);
    glVertex3f(0.5, -0.5, 0.5);
    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(-0.5, -0.5, -0.5);
    glEnd();
}

// ----------------------------------------------------------
// display() Callback function
// ----------------------------------------------------------
void display() {

    //  Clear screen and Z-buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    // Reset the matrix
    glLoadIdentity();

    // -----------------------------------------------------
    // PROJECTION MATRIX
    // -----------------------------------------------------

    // Setup
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Clipping planes, used for both Ortho and Perspective
    float clipNear = 1.0f, clipFar = 50.0f;

    //Orthographic view - no perspective. set straight field of view
    //float orthoLeft = -1, orthoRight = 1, orthoTop = 1, orthoBottom = -1;
    //glOrtho(orthoLeft, orthoRight, orthoBottom, orthoTop, clipNear, clipFar);

    //Perspective view - different View based on camera position, views wider field of view
    float fov = 120, aspectRatio = windowWidth / windowHeight;
    gluPerspective(fov, aspectRatio, clipNear, clipFar);
    

    // ------------------------------------------------------
    // VIEW AND MODEL MATRICES COMBINED
    // ------------------------------------------------------

    // Setup the matrix to be edited
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // -----------------------------------------------------
    // VIEW TRANSFORMS
    // -----------------------------------------------------
    float cameraX = 0.2, cameraY = 0.0, cameraZ = -1;
    float lookX = 0, lookY = 0, lookZ = 0;
    float upX = 0, upY = 1, upZ = 0;
    gluLookAt(cameraX, cameraY, cameraZ, lookX, lookY, lookZ,
        upX, upY, upZ);


    // ------------------------------------------------------
    // MODEL TRANSFORMS
    // ------------------------------------------------------
     
    //Translate to set location
    glTranslatef(0.9, 0.9, 0.9);
    
    // Rotate to the correct amgles
    glRotatef(0, 0.0, 0.0, 0.0); // yaw, y axis
    glRotatef(5, 8.0, 0.0, 0.0); // pitch, x axis
    glRotatef(0, 0.0, 0.0, 1.0); // roll, z axis

    // scale to desired dimensions
    glScalef(1.0, 1.0, 1.0);

    

    // MODEL - draw the cube
    drawCube();

    
    // END of display - flush and swap buffers
    glFlush();
    glutSwapBuffers();

}

// ----------------------------------------------------------
// specialKeys() Callback Function
// ----------------------------------------------------------
void specialKeys(int key, int x, int y) {

    //  Right arrow - increase rotation by 5 degree
    if (key == GLUT_KEY_RIGHT)
        rotate_y += 5;

    //  Left arrow - decrease rotation by 5 degree
    else if (key == GLUT_KEY_LEFT)
        rotate_y -= 5;

    else if (key == GLUT_KEY_UP)
        rotate_x += 5;

    else if (key == GLUT_KEY_DOWN)
        rotate_x -= 5;

    //  Request display update
    glutPostRedisplay();

}

// ----------------------------------------------------------
// main() function
// ----------------------------------------------------------
int main(int argc, char* argv[]) {

    //  Initialize GLUT and process user parameters
    glutInit(&argc, argv);

    //  Request double buffered true color window with Z-buffer
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    // Create window
    glutCreateWindow("Awesome Cube");

    //  Enable Z-buffer depth test
    glEnable(GL_DEPTH_TEST);

    // Callback functions
    glutDisplayFunc(display);
    glutSpecialFunc(specialKeys);

    //  Pass control to GLUT for events
    glutMainLoop();

    //  Return to OS
    return 0;

}