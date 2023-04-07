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
glShadeModel(GL_FLAT);

}


void display(void)
{

	

}

/*reshaping routine called whenever window is resized or moved*/
void reshape(int w, int h)
{
	// While reshaping sets the size of the viewport
	// the same as the size of the viewing window
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);

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
	gluPerspective(40.0, (GLfloat) w / (GLfloat) h, 1.0, 20.0);

}

void spin(void) 
{


}

void SpecialKeys(int key, int x, int y)
{
	

}

int main(int argc, char** argv)
{

glutInit(&argc,argv);
  
  // specifies a display mode, in this case the
  // display mode is a double buffer (GLUT_DOUBLE):
  // 1. RGB color model (GLUT_RGB) and 2. Depth buffer (GLUT_DEPTH)
  // used to remove hidden surfaces
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

glutInitWindowSize(winx,winy);
glutInitWindowPosition(100,100);
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
