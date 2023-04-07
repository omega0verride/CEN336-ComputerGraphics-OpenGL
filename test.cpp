#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>

/* It was possible to make this program through the use of the books:

Dave Shreiner. (2010). OPENGL Programming Guide 7th edition.
The Official Guide to Learning Open GL, Versions 3.0 and 3.1.
The Khronos OPENGL ARB Working Group.

and

F.S. Hill, JR., Stephen M. (2007). Kelley Computer Graphics Using Open GL.
Pearson International Edition

*/

GLfloat theta;
GLfloat rot = 1.0;
GLfloat lookx = -100, looky = -100, lookz = -100;

int oldMouseX, oldMouseY;
// used to keep track of old mouse position, declared global since these will be overwritten each time the mouse event is called by glut itslef

double mouseSensitivity = 0.05; // the change of camera rotation on a signle mouse drag diff
double speed = 0.5;				// amount of translation/"movement" per keypress

GLfloat eyex = 0.0, eyey = 0.0, eyez = -9.0; // on startup the camera is moved 9 units away from the center (in this case the object we are drawing)
// these properties correspond to the position of the camera in space
// eyex controls the position in the x axis (moves the camera left and right)
// eyey controls the position in the y axis (moves the camera up and down)
// eyez controls the position in the z axis (moves the camera forward or backwards)

GLfloat angleX = 0.0, angleY = 0.0, angleZ = 0.0;
// angleX corresponds left-right rotation of the camera
// angleY corresponds up-down rotation of the camera
// angleZ corresponds tilt
// https://i.stack.imgur.com/fUBKD.gif

GLfloat upX = 0.0, upY = 1.0, upZ = 0.0;
// https://stackoverflow.com/questions/10635947/what-exactly-is-the-up-vector-in-opengls-lookat-function
// we do not have to work with the up vector for now
// in simple terms it defines which direction is considered to be "up"

void init(void)
{
	// Clear the color of the window and set the color
	// to (0.0, 0.0, 0.0, 0.0)
	glClearColor(0.0, 0.0, 0.0, 0.0);

	// defines the Shade Model either
	// FLAT with each pixel treated with
	// same shading, or SMOOTH with each pixel's
	// color resulting from interpolation
	glShadeModel(GL_SMOOTH);

	// Enable the Light Source and
	// assign it to the identifier GL_LIGHT0
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// used to eliminate hidden surface
	// (try to remove glEnable(GL_DEPTH_TEST);)
	glEnable(GL_DEPTH_TEST);
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

	gluLookAt(eyex, eyey, eyez, angleX, angleY, angleZ, upX, upY, upZ);
	glRotatef(180, 1.0, 0.0, 0.0);
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
	// sets a position
	GLfloat position[] = {0.0, 0.0, 1.5, 1.0};

	// Clear the COLOR_BUFFER
	// and the DEPTH_BUFFER (used for hidden
	// surfaces removal)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// The topmost matrix is copied
	// so that its contents are duplicated
	// and located in the topmost and
	// second from the top matrices
	glPushMatrix();

	// Positioning of the Scene
	// at (0.0, 0.0, -5.0)
	glTranslatef(0.0, 0.0, -5.0);

	// Rotation of the Torus about the Z axis
	// glRotatef(theta, 0.0, 0.0, rot);

	// projects the rays of light
	rayTracing();

	// Rotation of the Light Source GL_LIGHT0
	// and the Torus: Choose a set of custom
	// rotations
	// glRotatef(theta, rot, rot, 0.0);
	// glRotatef(theta, rot, 0.0, rot);
	// glRotatef(theta, 0.0, rot, rot);

	// Create the Light Source specified by GL_LIGHT0 with the
	// characteristic to be a positioned light at the position
	// indicated through GLfloat position [] = {0.0, 0.0, 1.5, 1.0};
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	// Enable the Light Source
	// GL_LIGHT0 again
	glEnable(GL_LIGHTING);

	// Define (-100, -100, -100) as the point in the center of the scene being looked at
	// Since the command gluLookAt defines a viewing matrix, the point (-100, -100, -100)
	// becomes practically the center of the scene
	gluLookAt(eyex, eyey, eyez, angleX, angleY, angleZ, upX, upY, upZ);

	// Draw Torus
	// void SolidTorus(GLdouble innerRadius, GLdouble outerRadius, GLint nsides, GLint rings)
	glutSolidTorus(0.275, 0.85, 8, 15);

	// Removes the topmost matrix
	// The second from the top matrices
	// becomes the topmost matrix
	glPopMatrix();

	// swap buffers
	// (You have 2 buffers:
	// see *** in the main function of the program)
	glutSwapBuffers();
}

void reshape(int w, int h)
{
	// While reshaping sets the size of the viewport
	// the same as the size of the viewing window
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	// When used with the parameter GL_PROJECTION,
	// the command glMatrixMode() specifies that
	// the subsequent transformation matrices are
	// made to the 'Projection Matrix': in this
	// case both of glLoadIdentity() and gluPerspective().
	glMatrixMode(GL_PROJECTION);

	// Load the Identity Matrix
	glLoadIdentity();

	// void gluPerspective(GLdouble fovy, GLdouble aspect, GLdouble near, GLdouble far)
	// Creates a matrix for symmetric perspective-view
	// and multiplies the current matrix by it.
	// fovy is the angle of the field of view in the YZ plane,
	// its value must be in the range [0, 180].
	// aspect is the aspect ratio, which is width divided
	// by height. near and far values are the distances
	// between the viewpoint and the clipping planes along
	// the Z axis. near and far should always be positive.
	// (try remove the command: gluPerspective(40.0, (GLfloat) w / (GLfloat) h, 1.0, 20.0);)
	gluPerspective(40.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);

	// Now the command glMatrixMode() is called
	// with the parameter GL_MODELVIEW, which means
	// that the subsequent transformation matrices
	// will be applied to the 'ModelView' Matrix (The current matrix)
	// instead of the 'Projection Matrix'
	glMatrixMode(GL_MODELVIEW);

	// Load the Identity Matrix
	glLoadIdentity();
}

// sets the value of the
// rotational angle theta
void spin(void)
{

	theta += (double)0.1;
	if (theta > 360.0)
		theta -= 360.0;

	// Practically causes the command:
	// glutMainLoop() to call display()
	// to render again (try remove the
	// command: glutPostRedisplay();)
	glutPostRedisplay();
}

void mouse(int btn, int state, int x, int y)
{
	printf("\"mouseButtonEvent\": {\"btn\": %d, \"btnState\": %d, \"x\": %d, \"y\": %d}\n", btn, state, x, y);

	if (btn == 2)
	{ // reset rotation or right-click
		angleX = 0.0;
		angleY = 0.0;
		glutPostRedisplay();
	}
}

void mouseMove(int mouseX, int mouseY)
{
	printf("\"mouseMoveEvent\": {\"x\": %d, \"y\": %d, \"oldMouseX:\" %d, \"oldMouseY:\" %d}\n", mouseX, mouseY, oldMouseX, oldMouseY);
	double diffY = mouseY - oldMouseY;
	printf("diff: %lf\n", diffY);
	double diffX = mouseX - oldMouseX;
	printf("diff: %lf\n", diffX);

	// Y axis (up/down)
	if (diffY < 0)
		angleY += mouseSensitivity;
	else if (diffY > 0)
		angleY -= mouseSensitivity;

	// X axis (left-right)
	if (diffX < 0)
		angleX += mouseSensitivity;
	else if (diffX > 0)
		angleX -= mouseSensitivity;

	// save old mouse coordinates
	oldMouseX = mouseX;
	oldMouseY = mouseY;
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	if (key == 'w' || key == 'W')
	{
		eyez += speed;
		angleZ += speed;
		glutPostRedisplay();
	}
	else if (key == 's' || key == 'S')
	{
		eyez -= speed;
		angleZ -= speed;
		glutPostRedisplay();
	}
	else if (key == 'a' || key == 'A')
	{
		eyex += speed;
		angleX += speed;
		glutPostRedisplay();
	}
	else if (key == 'd' || key == 'D')
	{
		eyex -= speed;
		angleX -= speed;
		glutPostRedisplay();
	}
	else if (key == 'q' || key == 'Q')
	{
		eyey -= speed;
		angleY -= speed;
		glutPostRedisplay();
	}
	else if (key == 'e' || key == 'E')
	{
		eyey += speed;
		angleY += speed;
		glutPostRedisplay();
	}
	else if (key == 'r' || key == 'R')
	{
		eyex = 0.0, eyey = 0.0, eyez = -9.0;
		glutPostRedisplay();
	}
}

int main(int argc, char **argv)
{

	glutInit(&argc, argv);

	// specifies a display mode, in this case the
	// display mode is a double buffer (GLUT_DOUBLE):
	// 1. RGB color model (GLUT_RGB) and 2. Depth buffer (GLUT_DEPTH)
	// used to remove hidden surfaces
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	// sets the Viewing Window Size
	glutInitWindowSize(500, 500);

	// set the Viewing Window position onto the screen
	glutInitWindowPosition(100, 100);

	// Create the Viewing Window and assign it with
	// the name which is the argument passed to the
	// function glutCreateWindow()
	glutCreateWindow("Light Spin Flash");

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

	glutMouseFunc(mouse);		// called on mouse click events
	glutMotionFunc(mouseMove);	// called on mouse move events
	glutKeyboardFunc(keyboard); // called on keyboard event

	glutMainLoop();

	return 0; /* ANSI C requires main to return int. */
}