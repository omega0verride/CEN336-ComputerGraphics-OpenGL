#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

GLfloat theta = 0, theta1 = 0, theta2 = 0;

void init(void)
{

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);

}

void displayCubes() {

	/*modeling tranformations*/
	glTranslatef(1.0, 1.0, 1.0);
	glColor3f(1.0, 0.0, 0.0); // set the color to red (pg. 38, 197)
	glutWireCube(0.3);

	/*modeling tranformations*/
	glTranslatef(-3.0, -3.0, -3.0);
	glColor3f(1.0, 0.0, 1.0); // set the color to magenta (pg. 38, 197)
	glutWireCube(0.3);

}

void display(void) {

	// pg. 35, 36: To clear both of the color buffer and the depth buffer
	// use the next three commands:
	glClearColor(0.0, 0.0, 0.0, 0.0); // to clear an RGB(A) mode window to black. A is alpha. 
	// inputs: (red, green, blue, alpha) all in the range (0, 1).

// pg. 251: Alpha values controls blending. When blending is enabled, the alpha value is often used 
// to combine the color value of the fragment being processed with that of the pixel already
// stored in the buffer.
	glClearDepth(1.0); // clears the buffers of the screen, the default depth-clearing value is 1.0.

	// pg. 493: The color buffer is the one which is used for drawing. In general, the color buffer contains
	// color data in RGB and may also contain Alpha values.

	// pg. 494: Depth buffer: stores a depth value for each pixel. The depth is measured in terms of
	// the distance to the eye, so pixels with larger depth-buffer values are overwritten by pixels
	// with smaller values.

	// pg. 494: The stencil buffer is used to restrict drawing to certain portions of the screen.
	// For example the program draws all of the instruments and components of a car once, and 
	// as the car moves, only the outside scene needs to be updated.

	// pg. 494: The accumulation buffer holds RGBA color data just as the color buffer does in RGBA mode.
	// The use of the accumulation buffer is usually that one of accumulating a series of images into a
	// final, composite image. Usually the programmer do not draw directly in the accumulation buffer.
	// Usually accumulation operations are transfers of data to or from a color buffer.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // pg. 35, 36, pg. 496

	glPushMatrix();

	glColor3f(1.0, 1.0, 1.0);

	// glTranslate{fd}(TYPE x, TYPE y, TYPE z); pg. 141
	// Multiplies the current matrix by a matrix that moves (translates) an
	// object by the given x, y, and z values.
	glTranslatef(0.0, 0.0, -5.0);
	///Input Starts here

	glLoadIdentity();
	glRotated(theta, 0.0, 0.0, 1.0);
	if (theta >= 0.0 && theta <= 90) {
		glColor3f(1.0, 0.0, 0.0);
	}
	else if (theta > 90.0 && theta <= 360.0) {
		glColor3f(0.0, 1.0, 1.0);
	}
	glutWireSphere(0.2, 15.0, 16);

	glLoadIdentity();
	glColor3f(1.0, 1.0, 1.0);
	glRotated(theta1, 1.0, 0.0, 0.0);
	glutWireSphere(0.3, 25, 16);
		

		


	glLoadIdentity();
	glTranslatef(0.0, 0.0, 0);
	glRotatef(theta2, 1.0, 0.0, 0.0);
	glTranslatef(0.0, 0.5, 0);
	glColor3f(1.0, 0.0, 1.0);
	glutWireSphere(0.1, 25, 16);

	glLoadIdentity();
	glTranslatef(0.0, -0.5, 0);
	glRotatef(theta2, 0.0, 1.0, 0.0);
	glTranslatef(0.8, 0.5, 0);
	glColor3f(1.0, 0.0, 1.0);
	glutWireSphere(0.1, 25, 16);


	/// Your Input ends here


		// Removes the topmost matrix
		// The second from the top matrices
		// becomes the topmost matrix
	glPopMatrix();

	// pg. 38, 39: glFlush() is a command that is used when writing a program
	// which we want to work properly both with and without a network.
	// Usually the client gathers a collection of commands into a single network 
	// packet before sending it. glFlush() forces the client to send the network packet 
	// even though the network packet might not be full.
	// forces prevously issued commands to 
	// begin execution ('try to remove glFlush();')
	glFlush();

	// Try to remove the instruction glutSwapBuffers();
	// pg. 22, 23, 25. In the animation of this program the object cube is redrawn with
	// two different buffers. To clear the screen and to draw a frame it takes some time. 
	// If the object is programmed to be redrawn at a time that is greater than the CPU
	// time to clear the screen and to draw the frame, then the animation results in
	// poor animation. Most OpenGL implementations provide the program with double buffering,
	// which is the use of two color buffers. One buffer is displayed while the other buffer
	// is being drawn. When drawing of a frame is complete, the two buffers are swapped.
	// This is like a movie projector with only two frames (the buffer contains the frame)
	// in a loop: while one frame is being projected on the screen, an 'artist' is quick enough 
	// to erase and redrawing the frame that is not visible and which is going to be displayed next.
	glutSwapBuffers();

}/*end of display*/

void mouse(int btn, int state, int x, int y)
{

	if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
		exit(0);

}

void reshape(int w, int h)
{
	// While reshaping sets the size of the viewport
	// the same as the size of the viewing window
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	// Load the Identity Matrix
	glLoadIdentity();

	// pg. 132, 133: Two basic types of projections are provided by OpenGL. One type is the 
	// perspective projection (pg. 153), which matches how you see things in daily life. Perspective 
	// makes objects that are farther away appear smaller, for example, it makes railroad 
	// tracks appear to converge. The perspective projection is governed through the command:
	// gluPerspective(GLdouble fovy, GLdouble aspect, GLdouble near, GLdouble far) see figure 3-14
	// pg. 155.

	// The other type of projection is the orthographic (pg. 157) which 
	// maps directly onto the screen without affecting their relative sizes. 
	// The orthographic projection is governed through the command:
	// glOrtho(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble near, GLdouble far)
	// see figure 3-15 pg. 157.

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

}

void spin(void)
{

	theta += (double)0.01;
	if (theta > 360.0) theta -= 360.0;

	theta1 += (double)0.05;
	if (theta1 > 360.0) theta1 -= 360.0;

	theta2 += (double)0.15;
	if (theta2 > 360.0) theta2 -= 360.0;

	glutPostRedisplay();

}

int main(int argc, char** argv)
{

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // pg. 732: Specifies a display mode
	// for windows created when glutCreateWindow() is called. In the command seen here, GLUT_DOUBLE
	// and GLUT_RGBA are the arguments, whereas GLUT_DEPTH is the buffer-enabling flag. The command
	// shown here creates a double buffered RGBA mode window with a depth.

	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("CubesSpheres");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutIdleFunc(spin);

	glutMainLoop();

}