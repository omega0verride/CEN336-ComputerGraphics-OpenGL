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
#define speed 3.14

/*globals*/
int mode;
int ox = 0, oy = 0;
float eyey = 0, eyez = 0;
float angle = 0;
double scale = 1.0;

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

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClearDepth(1.0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();

	glTranslatef(0.0, 0.0, -5.0);

	glRotatef(90.0, 1.0, 0.0, 0.0);

	glScalef((GLfloat)1.0, (GLfloat)0.6, (GLfloat)0.6);

	glutWireSphere(1.0, 25, 16);

	// Removes the topmost matrix
	// The second from the top matrices
	// becomes the topmost matrix
	glPopMatrix();

	// swap buffers
	// (You have 2 buffers:
	// see *** in the main function of the program)
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
		eyez += ((GLfloat)(x - ox) / winx) * speed;
		eyey += ((GLfloat)(y - oy) / winy) * speed;
		glTranslatef(0.0, eyey, 0.0);
		glRotatef((GLfloat)eyey, 0.0, 0.0, 1.0);
		angle += 0.13;
		if (angle >= 360)
			angle -= 360;
		glRotatef((GLfloat)angle, 0.0, 0.0, 1.0);
		glTranslatef(0.0, 0.0, eyez);
		
		glutPostRedisplay();
		
		ox=x;
		oy=y;
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
	glutMotionFunc(motion);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();

	return 0;
}
