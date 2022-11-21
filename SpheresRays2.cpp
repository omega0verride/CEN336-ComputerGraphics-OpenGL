#include <stdlib.h>
#include <math.h>
#include <gl/glut.h>
#include <gl/gl.h>
#include <gl/glu.h>

/* It was possible to make this program through the use of the books:

Dave Shreiner. (2010). OPENGL Programming Guide 7th edition.
The Official Guide to Learning Open GL, Versions 3.0 and 3.1.
The Khronos OPENGL ARB Working Group.

and

F.S. Hill, JR., Stephen M. (2007). Kelley Computer Graphics Using Open GL.
Pearson International Edition

*/

#define winx 400
#define winy 400
#define M_PI 3.14
#define M 2.0

GLfloat theta;
GLfloat rot = 1.0;
GLfloat lookx = -100, looky = -100, lookz = -100;
int mode;
int ox, oy;

void init(void)
{
	// Clear the color of the window and set the color 
	// to (0.0, 0.0, 0.0, 0.0)
	glClearColor(0.0, 0.0, 0.0, 0.0);

}

void Magenta(void)
{
	// set the Shade Model to GL_SMOOTH
	glShadeModel(GL_SMOOTH);

	// Create the Light Source specified by GL_LIGHT3 with the 
	// characteristic to be a positioned light at the position
	// indicated through GLfloat positionMagenta [] = {-1.0, 1.0, 0.0, 1.0};
	GLfloat positionMagenta[] = { -1.0, 1.0, 0.0, 1.0 };
	GLfloat Magenta[] = { 1.0, 0.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT3, GL_DIFFUSE, Magenta);
	glLightfv(GL_LIGHT3, GL_POSITION, positionMagenta);

	// The Light Source assigned to the identifier
	// GL_LIGHT3 is enabled
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT3);
	glEnable(GL_DEPTH_TEST);

	// Add a sphere to the scene
	glutWireSphere(0.3, 25, 16);
}


void Yellow(void)
{

	// set the Shade Model to GL_SMOOTH
	glShadeModel(GL_SMOOTH);
	// Create the Light Source specified by GL_LIGHT2 with the 
	// characteristic to be a positioned light at the position
	// indicated through GLfloat positionYellow [] = {1.0, -1.0, 0.0, 1.0};
	GLfloat positionYellow[] = { 1.0, -1.0, 0.0, 1.0 };
	GLfloat Yellow[] = { 1.0, 1.0, 0.0, 1.0 };
	glLightfv(GL_LIGHT2, GL_DIFFUSE, Yellow);
	glLightfv(GL_LIGHT2, GL_POSITION, positionYellow);

	// The Light Source assigned to the identifier
	// GL_LIGHT2 is enabled
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT2);
	glEnable(GL_DEPTH_TEST);

	// Add a sphere to the scene
	glutWireSphere(0.3, 25, 16);
}

void Red(void)
{

	int nRows = 7;
	int nCols = 7;
	float length = 1.0;

	// set the Shade Model to GL_SMOOTH
	glShadeModel(GL_SMOOTH);

	// Create the Light Source specified by GL_LIGHT1 with the 
	// characteristic to be a positioned light at the position
	// indicated through GLfloat positionRed [] = {1.0, 1.0, 0.0, 1.0};
	GLfloat positionRed[] = { 1.0, 1.0, 0.0, 1.0 };
	GLfloat Red[] = { 1.0, 0.0, 0.0, 1.0 };
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Red);
	glLightfv(GL_LIGHT1, GL_POSITION, positionRed);

	// The Light Source assigned to the identifier
	// GL_LIGHT1 is enabled
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);
	glEnable(GL_DEPTH_TEST);

	// Add a sphere to the scene
	glutWireSphere(0.3, 25, 16);
	// disable the Light Source
	glDisable(GL_LIGHTING);

	// Trace the rays
	for (int row = 1; row < nRows; row++)
	{
		for (int col = 1; col < nCols; col++)
		{
			// compute the rays directions						
			glBegin(GL_LINES);
			glVertex2f(0.0, 0.0);
			glVertex2f(length - row, length - col);
			glEnd();
		}
	}

}

void Blue(void)
{

	int nRows = 7;
	int nCols = 7;
	float length = 1.0;

	// set the Shade Model to GL_SMOOTH
	glShadeModel(GL_SMOOTH);

	// Create the Light Source specified by GL_LIGHT0 with the 
	// characteristic to be a positioned light at the position
	// indicated through GLfloat positionBlue [] = {-1.0, -1.0, 0.0, 1.0};
	GLfloat positionBlue[] = { -1.0, -1.0, 0.0, 1.0 };
	GLfloat Blue[] = { 0.0, 0.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, Blue);
	glLightfv(GL_LIGHT0, GL_POSITION, positionBlue);

	// The Light Source assigned to the identifier
	// GL_LIGHT0 is enabled
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

	// Trace the rays
	for (int row = 0; row < nRows; row++)
	{
		for (int col = 0; col < nCols; col++)
		{
			// compute the rays directions						
			glBegin(GL_LINES);
			glVertex2f(0.0, 0.0);
			glVertex2f(length + row, length + col);
			glEnd();
		}
	}

	// Add a sphere to the scene
	glutWireSphere(0.3, 25, 16);

}

void Green(void)
{

	// set the Shade Model to GL_SMOOTH
	glShadeModel(GL_SMOOTH);

	// Create the Light Source specified by GL_LIGHT4 with the 
	// characteristic to be a positioned light at the position
	// indicated through GLfloat positionGreen [] = {-1.0, 1.0, 0.0, 1.0};
	GLfloat positionGreen[] = { -1.0, 1.0, 0.0, 1.0 };
	GLfloat Green[] = { 0.0, 1.0, 0.0, 1.0 };
	glLightfv(GL_LIGHT4, GL_DIFFUSE, Green);
	glLightfv(GL_LIGHT4, GL_POSITION, positionGreen);

	// The Light Source assigned to the identifier
	// GL_LIGHT0 is enabled
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT4);
	glEnable(GL_DEPTH_TEST);

	// add a sphere to the scene
	glutWireSphere(0.3, 25, 16);

}

void rayTracing(void)
{
	int nRows = 20;
	int nCols = 20;
	float length = 1.0;

	// The topmost matrix is copied 
	// so that its contents are duplicated 
	// and located in the topmost and 
	// second from the top matrices
	glPushMatrix();

	// The Light Source is temporarily disabled
	glDisable(GL_LIGHTING);
	// The color is set to (0.0, 0.0, 0.0)
	glColor3f(0.0, 0.0, 0.0);
	// The Light Source assigned to the identifier
	// GL_LIGHT0 is enabled
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// The rotations about the Z, Y and X
	// axis are given to the rays just
	// to be traced below
	glRotatef(theta, 0.0, 0.0, rot);
	glRotatef(theta, 0.0, rot, 0.0);
	glRotatef(theta, rot, 0.0, 0.0);

	// Trace the rays
	for (int row = 0; row < nRows; row++)
	{
		for (int col = 0; col < nCols; col++)
		{
			// compute the rays directions						
			glBegin(GL_LINES);
			glVertex2f(0, 0);
			glVertex2f(length + row, length + col);
			glEnd();
		}
	}

	// Removes the topmost matrix
// The second from the top matrices
// becomes the topmost matrix
	glPopMatrix();

}
void display(void)
{

	// Clear either the COLOR_BUFFER 
	// or the DEPTH_BUFFER (used for hidden
	// surfaces removal)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// The topmost matrix is copied 
	// so that its contents are duplicated 
	// and located in the topmost and 
	// second from the top matrices
	glPushMatrix();

	// Step 1:
	// Positioning of the Scene
	// Translate of (0.0, 0.0, -5.0);
	glTranslatef(0.0, 0.0, -5.0);

	// Step 2:
	// A. Rotation of 'theta' about the line defined through: (rot, rot, 0.0);
	// B. Rotation of 'theta' about the line defined through: (rot, 0.0, rot);
	// C. Rotation of 'theta' about the line defined through: (0.0, rot, rot);
	glRotatef(theta, rot, rot, 0.0);
	glRotatef(theta, rot, 0.0, rot);
	glRotatef(theta, 0.0, rot, rot);


	// Step 3:
	// Call the function ' rayTracing() '
	rayTracing();



	// Step 4:
	// The topmost matrix is copied 
	// so that its contents are duplicated 
	// and located in the topmost and 
	// second from the top matrices
	glPushMatrix();

	// Step 5:
	// A. translate of (1.0, 1.0, 0.0);
	// B. use ' glDisable(GL_LIGHTING); '
	// C. set the color to red
	// D. wire a cube of 0.1 edge
	// E. call the function ' Red() '
	glTranslatef(1.0, 1.0, 0.0);
	glDisable(GL_LIGHTING);
	glColor3f(1.0, 0.0, 0.0);
	glutWireCube(0.1);
	Red();





	// Step 6:
	glTranslatef(-2.0, -2.0, 0.0);
	glDisable(GL_LIGHTING);
	glColor3f(0.0, 0.0, 1.0);
	glutWireCube(0.1);
	Blue();
	// A. translate of (-2.0, -2.0, 0.0);
	// B. use ' glDisable(GL_LIGHTING); '
	// C. set the color to blue
	// D. wire a cube of 0.1 edge
	// E. call the function ' Blue() '






	// Step 7:
	// A. translate of (0.0, 2.0, 0.0);
	// B. use ' glDisable(GL_LIGHTING); '
	// C. set the color to magenta
	// D. wire a cube of 0.1 edge
	// E. call the function ' Magenta() '
	glTranslatef(0.0, 2.0, 0.0);
	glDisable(GL_LIGHTING);
	glColor3f(1.0, 0.0, 1.0);
	glutWireCube(0.1);
	Magenta();





	// Step 8:
	// A. translate of (2.0, -2.0, 0.0);
	// B. use ' glDisable(GL_LIGHTING); '
	// C. set the color to yellow
	// D. wire a cube of 0.1 edge
	// E. call the function ' Yellow() '
	glTranslatef(2.0, -2.0, 0.0);
	glDisable(GL_LIGHTING);
	glColor3f(1.0, 1.0, 0.0);
	glutWireCube(0.1);
	Yellow();




	// Step 9:
	// A. translate of (-1.0, 1.0, 0.0);
	// B. use ' glDisable(GL_LIGHTING); '
	// C. set the color to green
	// D. wire a cube of 0.1 edge
	// E. call the function ' Green() '
	glTranslatef(-1.0, 1.0, 0.0);
	glDisable(GL_LIGHTING);
	glColor3f(0.0, 1.0, 0.0);
	glutWireCube(0.1);
	Green();





	// Step 10:
	// Removes the topmost matrix
	// The second from the top matrices
	// becomes the topmost matrix
	glPopMatrix();


	// Step 11:
	// Removes the topmost matrix
	// The second from the top matrices
	// becomes the topmost matrix
	glPopMatrix();


	// Step 12:
	// forces previously issued commands to 
	// begin execution ('try to remove glFlush();')
	glFlush();


}

void reshape(int w, int h)
{

	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	glMatrixMode(GL_PROJECTION); // sets gluPerspective(...)
	glLoadIdentity(); // assure reshaping

	gluPerspective(30.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
	/* void gluPerspective(GLdouble fovy, GLdouble aspect, GLdouble near, GLdouble far)
	   Creates a matrix for a symmetric perspective-view frustrum and multiplies the current matrix by it.
	   fovy is the angle of the field of view in the yz-plane; its value must be in the range [0.0, 180.0].
	   aspect is the aspect ratio of the frustrum, its width divided by its height. near and far values
	   are the distances between the viewpoint and the clipping planes, along the negative z-axis. They
	   should always be positive (see fig. 3-14 pg. 155)*/

	glMatrixMode(GL_MODELVIEW); // sets gluLookAt(...)

}

// sets the value of the 
// rotational angle theta
void spin(void)
{

	theta += (double)0.05;
	if (theta > 360.0) theta -= 360.0;

	glutPostRedisplay();

}

int main(int argc, char** argv)
{

	glutInit(&argc, argv);

	// specifies a display mode, in this case the
	// display mode is either a single buffer (GLUT_SINGLE)
	// or a RGB color model (GLUT_RGB) or a depth buffer (GLUT_DEPTH)
	// used to remove hidden surfaces
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

	// sets the Viewing Window Size
	glutInitWindowSize(500, 500);

	// set the Viewing Window position onto the screen
	glutInitWindowPosition(100, 100);

	// Create the Viewing Window and assign it with
	// the name which is the argument passed to the
	// function glutCreateWindow()
	glutCreateWindow("Planetary System");

	// call the function init()
	init();
	// receives as input the display function
	glutDisplayFunc(display);
	// receives as input the reshape function
	glutReshapeFunc(reshape);
	// specifies the function, 'spin' in this 
	// case, to be executed, if no other events
	// are pending. If NULL is passed
	// as argument, then the execution is disabled
	glutIdleFunc(spin);
	// enters the GLUT processing loop never to return
	glutMainLoop();

	return 0;             /* ANSI C requires main to return int. */

}