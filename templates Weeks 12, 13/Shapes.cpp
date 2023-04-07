// The commented lines here reported are found in:
// Dave Shreiner (2010). OPEN GL Programming Guide 7th edition. 
// The Official Guide to Learning Open GL, Versions 3.0 and 3.1. 	
// The Khronos OPENGL ARB Working Group.
#include <stdio.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

GLfloat thetay = 0.0, thetaz = 0.0;
GLfloat rot = 1.0;
GLfloat lookx = -100, looky = -100, lookz = -100;

/*
F.S. Hill, JR., Stephen M. (2007). Kelley Computer Graphics, Using Open GL. Pearson International Edition
*/

void init(void)
{
	// to clear an RGB(A) mode window to black. A is alpha. 
    // inputs: (red, green, blue, alpha) all in the range (0, 1).
	glClearColor(0.0, 0.0, 0.0, 0.0);

	// glShadeModel(GLenum mode): pg. 200; Sets the shading model. The mode parameter can be either
	// GL_SMOOTH (which is the default) or GL_FLAT. With flat shading (GL_FLAT), the color at each 
	// vertex is the same, whereas with smoooth shading (GL_SMOOTH), the color at each vertex is treated 
	// individually. For instance when using GL_SMOOTH in drawing a line, the colors along the line 
	// segments are interpolated between the vertex colors.
	glShadeModel(GL_FLAT);
}

void spin(void)
{

// ' theta ' is the angle that updates itself at steps of ' 0.01 '
// the effect is to create animation. The frames displayed on the
// OpenGL window are visualized after the call to the function
// ' glutDisplayFunc(display) ' located in the main function of
// the program. Without call to ' glutDisplayFunc(display) ' no
// frames can be displayed. Also, frames are visualized after 
// a call to ' glutPostRedisplay() '.
	
// Each frame is animated through the call to the function 
// ' glutIdleFunc(spin) '. The program would not display any
// animated frames if the update
// of the angle ' theta ' would not be followed by the call to the
// function ' glutPostRedisplay() ' The function ' glutPostRedisplay() '
// together with the call to ' glutDisplayFunc(display) ' and the call 
// to the function ' glutIdleFunc(spin) 'allows animated visualization 

// Try to comment ' glutPostRedisplay() ' to see no animation. 
// Try to comment ' glutIdleFunc(spin) ' to see no animation.

thetay += (double)0.01;
if(thetay > 360.0) thetay -=360.0;

thetaz += (double)0.05;
if(thetaz > 360.0) thetaz -=360.0;

// void glutPostRedisplay(void). Marks the current window as needing 
// to be redrawn. At the next opportunity, the callback function 
// registered by glutDisplayFunc() will be called. (pg. 734)

glutPostRedisplay();  // try to comment this call to see no animation

}

void display(void)
{
	// ' glClear(GLbitfield mask) ' (pg. 496) Clears the specified buffers. 
	// The value of mask is the bitwise logical OR of some combination of 
	// GL_COLOR_BUFFER_BIT, GL_DEPTH_BUFFER_BIT, GL_STENCIL_BUFFER_BIT, 
	// and GL_ACCUM_BUFFER_BIT to identify which buffers are to be cleared.
	// The command can also be used with a single label such as in this
	// case is used to clear the color buffer only. 
	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix(); // pg. 166 and Figure 3-21: void glPushMatrix(void);

	glColor3f(1.0, 0.0, 0.0);
	

	// Step 1:
	glRotatef(thetaz, 0.0, 0.0, 1.0);	


	// Step 2:
	glutWireOctahedron();

	
	glPopMatrix(); // pg. 166 and Figure 3-21: void glPopMatrix(void);




	glPushMatrix(); // pg. 166 and Figure 3-21: void glPushMatrix(void);

	glColor3f(0.0, 1.0, 0.0);


	// Step 3:
	glRotatef(thetay, 0.0, 1.0, 0.0);

	// Step 4:
	glutWireSphere(1.0, 12, 12);

	
	glPopMatrix(); // pg. 166 and Figure 3-21: void glPopMatrix(void);
	
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

}

void mouse(int btn, int state, int x, int y)
{

// if the user right click the OpenGL window the program exits
if(btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN) exit(0);

}

void reshape(int w, int h)
{
	GLfloat eyex = -2.7, eyey = -2.7, eyez = -2.7;

	// pg. 159: void glViewport(GLint x, GLint y, GLsizei width, GLsizei height);
	// Defines a pixel rectangle in the window into which the final image is
	// mapped. The (x, y) parameter specifies the lower left corner of the viewport,
	// and width and height are the size of the viewport rectangle. By
	// default, the initial viewport values are (0, 0, winWidth, winHeight),
	// where winWidth and winHeight specify the size of the window.
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);

	// pg. 133, 135, 166: The command glMatrixMode() used with argument GL_PROJECTION indicates
	// that the current matrix specifies the projection transformation and that subsequent 
	// transformation calls affect the projection matrix. The command glMatrixMode() used 
	// with argument GL_MODELVIEW as the argument indicates that the susequent transformations 
	// now affect the modelview matrix instead of the projection matrix. 
	glMatrixMode(GL_PROJECTION); // sets gluPerspective(...)

	// pg. 131: the current matrix is set to the identity matrix with
	// glLoadIdentity(). This step is necessary since most of the transformation
	// commands multiply the current matrix by the specified matrix and then set
	// the result to be the current matrix. If you don�t clear the current matrix by
	// loading it with the identity matrix, you continue to combine previous
	// transformation matrices with the new one you supply. In some cases, you
	// do want to perform such combinations, but you also need to clear the matrix sometimes.
	// pg. 133: Note that glLoadIdentity() is used to initialize the current projection
	// matrix so that only the specified projection transformation has an effect.
	// try to remove: glLoadIdentity(); 
	glLoadIdentity(); // initialize and assures reshaping

	/* void gluPerspective(GLdouble fovy, GLdouble aspect, GLdouble near, GLdouble far)
	Creates a matrix for a symmetric perspective-view frustrum and multiplies the current matrix by it.
	fovy is the angle of the field of view in the yz-plane; its value must be in the range [0.0, 180.0].
	aspect is the aspect ratio of the frustrum, its width divided by its height. near and far values
	are the distances between the viewpoint and the clipping planes, along the negative z-axis. They
	should always be positive (see fig. 3-14 pg. 155)*/
	gluPerspective(30.0, (GLfloat) w / (GLfloat) h, 1.0, 20.0);

	// gluLookAt(), 129, 131, 149, 172, and Figure 3-11 pg. 149
	// void gluLookAt(GLdouble eyex, GLdouble eyey, GLdouble eyez,
    //                GLdouble centerx, GLdouble centery, GLdouble centerz,
    //                GLdouble upx, GLdouble upy, GLdouble upz);
	// Defines a viewing matrix and multiplies it to the right of the current
	// matrix. The desired viewpoint is specified by eyex, eyey, and eyez. The
	// centerx, centery, and centerz arguments specify any point along the desired
	// line of sight, but typically they specify some point in the center of the
	// scene being looked at. The upx, upy, and upz arguments indicate which
	// direction is up (that is, the direction from the bottom to the top of the
	// viewing volume).
	gluLookAt(eyex, eyey, eyez, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	
}

int main(int argc, char **argv)
{
  // pg. 732 ' glutInit() ' should be called before any other GLUT routine, because it
  // initializes the GLUT library. glutInit() will also process command line options
  // The parameters to glutInit() should be the same as those to main()
  glutInit(&argc, argv);

  // ' glutInitDisplayMode() ' pg. 732: Specifies a display mode
  // for windows created when glutCreateWindow() is called. 
  // if you want a window with double buffering, the RGBA color model, 
  // and a depth buffer, you might call:
  // glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH)
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

  // pg. 733: void glutInitWindowSize(int width, int height);
  // and void glutInitWindowPosition(int x, int y);
  // Requests windows created by glutCreateWindow() to have an initial size
  // and position. The arguments (x, y) indicate the location of a corner of the
  // window, relative to the entire display. width and height indicate the window�s
  // size (in pixels). The initial window size and position are hints and
  // may be overridden by other requests.
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(100,100);


  // pg. 733: int glutCreateWindow(char *name);
  // Opens a window with previously set characteristics (display mode, width,
  // height, and so on). The string ' name ' may appear in the title bar if your
  // window system does that sort of thing. The window is not initially displayed
  // until glutMainLoop() is entered, so do not render into the window until then.
  // The value returned is a unique integer identifier for the window. This
  // identifier can be used for controlling and rendering to multiple windows
  // (each with an OpenGL rendering context) from the same application.
  glutCreateWindow("Shapes");

  // procedural call used to setting the background color and coordinate system.
  // In this program ' init() ' is used to clear an RGB(A) mode window to black
  // and to set the shade model
  init();

//  glutDisplayFunc(display) '
//  Specifies the function that�s called whenever the contents of the window need
//  to be redrawn. The contents of the window may need to be redrawn when the
//  window is initially opened, when the window is popped and when 
//  glutPostRedisplay() is explicitly called. (pg. 733)
  glutDisplayFunc(display); // try to comment this call

  // pg. 734: void glutReshapeFunc(void (*func)(int width, int height));
  // Specifies the function that�s called whenever the window is resized or
  // moved. The argument func is a pointer to a function that expects two
  // arguments, the new width and height of the window. Typically, func calls
  // glViewport(), so that the display is clipped to the new size
  glutReshapeFunc(reshape);
  
  // pg. 736: You can specify a function that�s to be executed if no other events are
  // pending�for example, when the event loop would otherwise be idle�with
  // glutIdleFunc(). This is particularly useful for continuous animation or
  // other background processing
  glutIdleFunc(spin); // try to comment this call to see no animation

  // pg. 734: void glutMouseFunc(void (*func)(int button, int state, int x, int y));
  // Specifies the function ( ' func ' ) that�s called when a mouse button is pressed
  // or released. The button callback parameter is GLUT_LEFT_BUTTON,
  // GLUT_MIDDLE_BUTTON, or GLUT_RIGHT_BUTTON. The state callback
  // parameter is either GLUT_UP or GLUT_DOWN, depending on whether
  // the mouse has been released or pressed. The x and y callback parameters
  // indicate the location (in window-relative coordinates) of the mouse when
  // the event occurred.
  glutMouseFunc(mouse); 
  
  // pg. 737 ' glutMainLoop() ' Enters the GLUT processing loop, never to return.
  glutMainLoop();

}


