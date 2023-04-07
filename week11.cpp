// The commented lines here reported are found in:
// Dave Shreiner (2010). OPEN GL Programming Guide 7th edition.
// The Official Guide to Learning Open GL, Versions 3.0 and 3.1.
// The Khronos OPENGL ARB Working Group.

#include <stdio.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <iostream>

using namespace std;

double SCALE = 10;

double cosine = 0.0, sine = 0.0;
double thetax = 0.0, thetay = 0.0;
long int counter = 0;

#define S 1
#define C 0

void init(void)
{

// pg. 35, 36: To clear both of the color buffer and the depth buffer
// use the next three commands:
glClearColor(0.0, 0.0, 0.0, 0.0); // to clear an RGB(A) mode window to black. A is alpha.
// inputs: (red, green, blue, alpha) all in the range (0, 1).

// pg. 251: Alpha values controls blending. When blending is enabled, the alpha value is often used
// to combine the color value of the fragment being processed with that of the pixel already
// stored in the buffer.

// pg. 133, 135, 166: The command glMatrixMode() used with argument GL_PROJECTION indicates
// that the current matrix specifies the projection transformation and that subsequent
// transformation calls affect the projection matrix. The command glMatrixMode() used
// with argument GL_MODELVIEW as the argument indicates that the susequent transformations
// now affect the modelview matrix instead of the projection matrix.
glMatrixMode(GL_PROJECTION); // Set projection parameters.

// void gluOrtho2D(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top);
// Parameters: left, right
// Specify the coordinates for the left and right vertical clipping planes.
// Parameters: bottom, top
// Specify the coordinates for the bottom and top horizontal clipping planes.
// Description: gluOrtho2D sets up a two-dimensional orthographic viewing region.
gluOrtho2D(0.0, 400.0, 0.0, 400.0);

}

void display(void)
{
double pi = 3.141592;

glClear(GL_COLOR_BUFFER_BIT);

glColor3f(1.0, 0.0, 0.0);

//x axis
glBegin(GL_LINES);
glVertex2d(50, 200);
glVertex2d(350, 200);
glEnd();
//x axis


//y axis
glBegin(GL_LINES);
glVertex2d(200, 50);
glVertex2d(200, 350);
glEnd();
//y axis

//draw radius
glColor3f(0.0,0.0,1.0);
glBegin(GL_LINES);
glVertex2d(200, 200);
glVertex2d(200 + cosine / SCALE, 200 + sine / SCALE);
glEnd();

// draw circle
glPushMatrix();
glTranslatef(200, 200, 1.0);
double radius = sqrt(((double)cosine / SCALE) *
((double)cosine / SCALE) +
((double)sine / SCALE) *
((double)sine / SCALE));
glutWireSphere(radius, 100, 100);
glPopMatrix();

// draw axis in green
glColor3f(0.0, 1.0, 0.0);
glBegin(GL_LINES);
glVertex2d(200 + cosine / SCALE, 200 + sine / SCALE);
glVertex2d(200, 200 + sine/SCALE);
glVertex2d(200 + cosine / SCALE, 200 + sine / SCALE);
glVertex2d(200 + cosine / SCALE, 200);
glEnd();
glutSwapBuffers();
glFlush();

}

void menu_select(int item)
{
double pi = 3.141592;

if (item == S)

std::cout << "The Sine is: " << ((double)2.0 * pi * sine / (counter * SCALE)) << endl;

else if (item == C)

std::cout << "The Cosine is: " << ((double)2.0 * pi * cosine / (counter * SCALE)) << endl;

}

void animate(void)
{
double pi = 3.141592;

thetax += 0.001;
thetay += 0.001;

cosine += (double)cos((double)thetax);
sine += (double)sin((double)thetay);
counter++;

if (cosine > 2.0 * pi * 100)
cosine -= (double)cos((double)thetax);

if (sine > 2.0 * pi * 100)
sine -= (double)sin((double)thetay);

glutPostRedisplay();



}

void mouse(int btn, int state, int x, int y)
{

// if the user right click the OpenGL window the program exits
if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) exit(0);

}

int main(int argc, char** argv)
{

// pgs. 18, 732: Initializes the GLUT library and takes
// in any input parameters given to the program through the main function.
glutInit(&argc, argv);

// ' glutInitDisplayMode() ' pg. 732: Specifies a display mode
// for windows created when glutCreateWindow() is called.
// if you want a window with double buffering, the RGBA color model,
// and a depth buffer, you might call:
// glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH)
glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

glutInitWindowSize(400, 300); // pg. 733: Sets the window size.

glutInitWindowPosition(100, 100); // pg. 733: Sets the window position.

// pg. 733: Opens a window and the window
// is not initially displayed until glutMainLoop() is entered.
glutCreateWindow("Cosine & Sine");

init(); // call to the init() function
// pg. 733: Specifies the function that is called ('display' in this case)
// whenever the contents of the window need to be redrawn.

glutDisplayFunc(display);
glutIdleFunc(animate);

// menu related functions (begin)
glutCreateMenu(menu_select);

glutAddMenuEntry("Calculate Sine", S);
glutAddMenuEntry("Calculate Cosine", C);
glutAttachMenu(GLUT_LEFT_BUTTON);
// menu related functions (ends)

// pg. 734: void glutMouseFunc(void (*func)(int button, int state, int x, int y));
// Specifies the function ( ' func ' ) that’s called when a mouse button is pressed
// or released. The button callback parameter is GLUT_LEFT_BUTTON,
// GLUT_MIDDLE_BUTTON, or GLUT_RIGHT_BUTTON. The state callback
// parameter is either GLUT_UP or GLUT_DOWN, depending on whether
// the mouse has been released or pressed. The x and y callback parameters
// indicate the location (in window-relative coordinates) of the mouse when
// the event occurred.
glutMouseFunc(mouse);

glutMainLoop(); // pg. 737: Enters the GLUT processing loop, never to return.

return 0;
} /* ANSI C requires main to return int. */