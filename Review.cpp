// The commented lines here reported are found in:
// Dave Shreiner (2010). OPEN GL Programming Guide 7th edition.
// The Official Guide to Learning Open GL, Versions 3.0 and 3.1.
// The Khronos OPENGL ARB Working Group.
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#define winx 400
#define winy 400
#define M_PI 3.14

/*globals*/
int mode;
int ox = 0, oy = 0;
float eyey = 0, eyez = 0;
float angle = 0;

void reshape(int w, int h);
void init(void);
void display(void);
void motion(int x, int y);
void mouse(int btn, int state, int x, int y);

void init(void)
{

	glClearColor(0.0, 0.0, 0.0, 0.0);

	// glShadeModel(GLenum mode): pg. 200; Sets the shading model. The mode parameter can be either
	// GL_SMOOTH (which is the default) or GL_FLAT. With flat shading (GL_FLAT), the color at each
	// vertex is the same, whereas with smoooth shading (GL_SMOOTH), the color at each vertex is treated
	// individually. For instance when using GL_SMOOTH in drawing a line, the colors along the line
	// segments are interpolated between the vertex colors.
	glShadeModel(GL_FLAT);
}

void display(void)
{

	// pg. 491, 492, Whenever data is stored uniformly for each pixel, such storage for all
	// of the pixels is called a buffer. Assume that the color screen is a 24-bit color screen,
	// then 24 bits (there are 2^24 different colors that can be displayed)
	// translate to 3 bytes.

	// Color buffer: In the aforementioned example, the color buffer has to store at least 3
	// bytes of data. Any color buffer has the same amount of data saved for each pixel on the screen.

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

	// pg. 35, 36: To clear both of the color buffer and the depth buffer
	// use the next three commands:
	glClearColor(0.0, 0.0, 0.0, 0.0); // to clear an RGB(A) mode window to black. A is alpha.
									  // inputs: (red, green, blue, alpha) all in the range (0, 1).

	// pg. 251: Alpha values controls blending. When blending is enabled, the alpha value is often used
	// to combine the color value of the fragment being processed with that of the pixel already
	// stored in the buffer.
	glClearDepth(1.0); // clears the buffers of the screen, the default depth-clearing value is 1.0.

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // pg. 35, 36, pg. 496

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

	// pg. 133, 135, 166: The command glMatrixMode() used with argument GL_PROJECTION indicates
	// that the current matrix specifies the projection transformation and that subsequent
	// transformation calls affect the projection matrix. The command glMatrixMode() used
	// with argument GL_MODELVIEW as the argument indicates that the susequent transformations
	// now affect the modelview matrix instead of the projection matrix.

	glMatrixMode(GL_MODELVIEW);
	// glLoadIdentity();
	//  pg. 130, 131. load the identity matrix.
	//  the instruction glLoadIdentity(); will prevent the program to function correctly (try it)
	//  this is because the effect of the command glLoadIdentity() is that one of clearing the
	//  current matrix transformation.

	glColor3f(1.0, 1.0, 1.0);

	glPushMatrix(); // see fig. 3-21 pg. 166
	// glTranslate{fd}(TYPE x, TYPE y, TYPE z); pg. 141
	// Multiplies the current matrix by a matrix that moves (translates) an
	// object by the given x, y, and z values.
	glTranslatef(0.0, 0.0, -5.0);

	// Multiplies the current matrix by a matrix that rotates the object (or the local coordinate
	// system) of an angle 'angle' in a counterclokwise direction about the ray from the origin
	// through the point (x, y, z).
	// void glRotate{fd}(TYPE angle, TYPE x, TYPE y, TYPE z)
	glRotatef(90.0, 1.0, 0.0, 0.0);

	// glScale{fd}(TYPE x, TYPE y, TYPE z); pg. 142
	// Multiplies the current matrix by a matrix that scales the object along
	// the axes. Each of x, y, or z coordinates of the object is multiplied by the
	// corresponding argument x, y, or z. Scaling with a -1.0 value reflects an
	// object across an axis.
	glScalef((GLfloat)1, (GLfloat)0.6, (GLfloat)0.6);

	// void glutWireSphere(GLdouble radius, GLint, slices, GLint stacks)
	glutWireSphere(1.0, 25, 16); // pgs. 21, 172, 735

	glPopMatrix();

	// pg. 38, 39: glFlush() is a command that is used when writing a program
	// which we want to work properly both with and without a network.
	// Usually the client gathers a collection of commands into a single network
	// packet before sending it. glFlush() forces the client to send the network packet
	// even though the network packet might not be full.
	glFlush();

} /*end of display*/

/*reshaping routine called whenever window is resized or moved*/
void reshape(int w, int h)
{

	// pgs. 41, 134, 159: The command glViewport() sets the size of the viewport to be the entire
	// window. The fact that glViewport() takes the inputs (GLsizei)w, (GLsizei)h which are the
	// same inputs of the reshape(int w, int h), makes it possible to have the viewport size exactly
	// the same size as the viewing window.
	glViewport(0, 0, (GLsizei)w, (GLsizei)h); // The first two inputs: 0 and 0 define the origin
	// of the available screen space within the window. If the window changes size, the viewport
	// needs to change accordingly. The window system, not OpenGL, is responsible for opening a window on the
	// screen. The default size of the viewport is set to be the same size of the viewing window.

	// void glViewport(GLint x, GLint y, GLsizei width, GLsizei height) defines a rectangle where
	// the image is mapped. The (x, y) parameter specifies the lower left corner of the viewport
	// and 'width' and 'height' are the size of viewport rectangle.

	// now alert that the subsequent transformation (matrix): glLoadIdentity();
	// will affect the projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// the effects is that of setting the boundaries of the
	// viewing volume (frustrum) see figure 3-14 pg. 155.
	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);

	// now alert that the subsequent transformation (matrix): glLoadIdentity() in void motion(int x, int y);
	// will affect the modelview matrix
	glMatrixMode(GL_MODELVIEW);
}

void motion(int x, int y)
{

	eyez = 0.0;
	eyey = 0.0;

	if (mode == GLUT_LEFT_BUTTON)
	{

		eyez += ((GLfloat)(x - ox) / winx) * M_PI;
		eyey += ((GLfloat)(y - oy) / winy) * M_PI;

		glTranslatef(0.0, eyey, 0.0);
		glRotatef((GLfloat)eyey, 0.0, 0.0, 1.0);

		angle += 0.1;
		if (angle >= 360)
			angle -= 360;
		glRotatef((GLfloat)angle, 0.0, 0.0, 1.0);

		glTranslatef(0.0, 0.0, eyez);

		// pgs. 19, 302, 734: glutPostRedisplay() causes the glutMainLoop() to call display() and
		// render the scene after other events have been processed: such as the recalculation of
		// the rotational angle 'ang' and the value of 'eyez'.
		glutPostRedisplay();

		ox = x;
		oy = y;
	}
}

void mouse(int btn, int state, int x, int y)
{

	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{

		ox = x;
		oy = y;
	}
}

int main(int argc, char **argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(winx, winy);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Ellipsoid Motion");
	init();
	glutMouseFunc(mouse);
	// glutMotionFunc(motion);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();

	return 0;
}
