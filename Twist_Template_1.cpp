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

GLfloat lookx = -100, looky = -100, lookz = -100;
GLfloat upx = 0, upy = 1, upz = 0;
GLfloat eyex = 0, eyey = 0, eyez = 0;

GLfloat theta;

void init(void)
{

	glClearColor(0.0, 0.0, 0.0, 0.0);

	// glShadeModel(GLenum mode): pg. 200; Sets the shading model. The mode parameter can be either
	// GL_SMOOTH (which is the default) or GL_FLAT. With flat shading (GL_FLAT), the color at each
	// vertex is the same, whereas with smoooth shading (GL_SMOOTH), the color at each vertex is treated
	// individually. For instance when using GL_SMOOTH in drawing a line, the colors along the line
	// segments are interpolated between the vertex colors.
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
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

	gluLookAt(eyex, eyey, eyez, lookx, looky, lookz, upx, upy, upz);

	glScalef((GLfloat)1, (GLfloat)0.8, (GLfloat)0.6);

	glRotatef(theta, 1.0, 0.0, 0.0);

	glutWireSphere(1.0, 25, 16);

	// Removes the topmost matrix
	// The second from the top matrices
	// becomes the topmost matrix
	glPopMatrix();

	// swap buffers
	// (You have 2 buffers:
	// see *** in the main function of the program)
	glutSwapBuffers();
}

/*reshaping routine called whenever window is resized or moved*/
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
}

void spin(void)
{
	theta += (double)0.1;
	if (theta > 360.0)
		theta -= 360;
	glutPostRedisplay();
}

void SpecialKeys(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		eyex += (GLfloat)0.1;
		if (eyex >= 5)
			eyex -= (GLfloat)0.1;
		upx += (GLfloat)0.1;
		if (upx >= 5)
			upx -= (GLfloat)0.1;
		lookx += (GLfloat)0.1;
		if (lookx >= 5)
			lookx -= (GLfloat)0.1;
		break;
	case GLUT_KEY_DOWN:
		eyex -= (GLfloat)0.1;
		if (eyex <= -5)
			eyex += (GLfloat)0.1;
		upx -= (GLfloat)0.1;
		if (upx <= -5)
			upx += (GLfloat)0.1;
		lookx -= (GLfloat)0.1;
		if (lookx <= -5)
			lookx += (GLfloat)0.1;
		break;
	case GLUT_KEY_LEFT:
		eyey += (GLfloat)0.1;
		if (eyey >= 5)
			eyey -= (GLfloat)0.1;
		upy += (GLfloat)0.1;
		if (upy >= 5)
			upy -= (GLfloat)0.1;
		looky += (GLfloat)0.1;
		if (looky >= 5)
			looky -= (GLfloat)0.1;
		break;
	case GLUT_KEY_RIGHT:
		eyey -= (GLfloat)0.1;
		if (eyey <= -5)
			eyey += (GLfloat)0.1;
		upy -= (GLfloat)0.1;
		if (upy <= -5)
			upy += (GLfloat)0.1;
		looky -= (GLfloat)0.1;
		if (looky <= -5)
			looky += (GLfloat)0.1;
		break;
	case GLUT_KEY_PAGE_UP:
		eyez += (GLfloat)0.1;
		if (eyez >= 5)
			eyez -= (GLfloat)0.1;
		upz += (GLfloat)0.1;
		if (upz >= 5)
			upz -= (GLfloat)0.1;
		lookz += (GLfloat)0.1;
		if (lookz >= 5)
			lookz -= (GLfloat)0.1;
		break;
	case GLUT_KEY_PAGE_DOWN:
		eyez -= (GLfloat)0.1;
		if (eyez <= -5)
			eyez += (GLfloat)0.1;
		upz -= (GLfloat)0.1;
		if (upz <= -5)
			upz += (GLfloat)0.1;
		lookz -= (GLfloat)0.1;
		if (lookz <= -5)
			lookz += (GLfloat)0.1;
		break;
	case GLUT_KEY_F1:
		lookx = -100, looky = -100, lookz = -100;
		upx = 0, upy = 1, upz = 0;
		eyex = 0, eyey = 0, eyez = 0;
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

	glutInitWindowSize(winx, winy);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Twist");
	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(SpecialKeys);

	// specifies the function, 'spin' in this
	// case, to be executed, if no other events
	// are pending. If NULL is passed
	// as argument, then the execution is disabled
	glutIdleFunc(spin);

	glutMainLoop();

	return 0;
}
