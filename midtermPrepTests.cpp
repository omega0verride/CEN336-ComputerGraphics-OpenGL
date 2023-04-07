#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

double theta = 0.0;


GLfloat eyex = 0.0, eyey = 0.0, eyez = 9.0; // on startup the camera is moved 9 units away from the center (in this case the object we are drawing)
// these properties correspond to the position of the camera in space
// eyex controls the position in the x axis (moves the camera left and right)
// eyey controls the position in the y axis (moves the camera up and down)
// eyez controls the position in the z axis (moves the camera forward or backwards)

GLfloat centerX = 0.0, centerY = 0.0, centerZ = 0.0;
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
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
}

void draw4CubesAsAxis(){
	glColor3f(1.0, 1.0, 1.0);
	glutSolidCube(0.2);
	
	glTranslatef(0.2, 0.0, 0.0);
	glColor3f(1.0, 0.0, 0.0);
	glutSolidCube(0.2);
	glTranslatef(-0.2, 0.0, 0.0);

	glTranslatef(0.0, 0.2, 0.0);
	glColor3f(0.0, 1.0, 0.0);
	glutSolidCube(0.2);
	glTranslatef(0.0, -0.2, 0.0);

	glTranslatef(0.0, 0.0, 0.2);
	glColor3f(0.0, 0.0, 1.0);
	glutSolidCube(0.2);
	glTranslatef(0.0, 0.0, -0.2);
	
}

void displayWhiteCube(){

	glColor3f(1.0, 1.0, 1.0); // set the color to white (pg. 38, 197)

	/*modeling tranformations*/
	
	// change center of rotation
	// glRotatef(30, 0.0, 0.0, 1.0);
	// glTranslatef(1.0, 0.0, 0.0);

	// glTranslatef(1.0, 0.0, 0.0);
	// glRotatef(theta, 1.0, 0.0, 1.0);


    // glRotatef(theta, 1.0, 1.0, 1.0);
	
	// glutWireCube(0.4);
	glutWireCone(0.2, 0.5, 16, 16);
	/*viewing transformation*/
	// syntax: gluLookAt(double eyex, double eyey, double eyez, 
	//                   double centerx, double centery, double centerz, 
	//					 double upx, double upy, double upz);
	// defines a viewing matrix and multiplies it to the right of the current matrix
	// The desired viewpoint is specified by eyex, eyey, eyez.
	// The centerx, centery and centerz arguments specify any point along the 
	// desired line of sight, but typically they specify some point at the center 
	// of the scene being looked at. The upx, upy, upz arguments indicate which
	// direction is up (that is, the direction from the bottom to the top of the
	// viewing volume).
	// gluLookAt(eyex, eyey, eyez, centerX, centerY, centerZ, upX, upY, upZ);

}

void display(void)
{

	glClearColor(0.0, 0.0, 0.0, 0.0); // to clear an RGB(A) mode window to black. A is alpha. 
                                      // inputs: (red, green, blue, alpha) all in the range (0, 1).

	// pg. 251: Alpha values controls blending. When blending is enabled, the alpha value is often used 
	// to combine the color value of the fragment being processed with that of the pixel already
	// stored in the buffer.

	glClearDepth(1.0); // clears the buffers of the screen, the default depth-clearing value is 1.0.

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // pg. 35, 36, pg. 496
	//clear the color buffer or the the depth buffer.

	// pg. 130. load the identity matrix. 
	glLoadIdentity();
	gluLookAt(eyex, eyey, eyez, centerX, centerY, centerZ, upX, upY, upZ);
	
	// displayWhiteCube();
	// glRotatef(theta, 0.0, 0.0, 1.0);
	glTranslatef(0.0, 0.0, -5.0);
	draw4CubesAsAxis();
	
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
	
}

void mouse(int btn, int state, int x, int y)
{

if(btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN) 
exit(0);

}


void reshape(int w, int h)
{
// While reshaping sets the size of the viewport
// the same as the size of the viewing window
glViewport(0, 0, (GLsizei) w, (GLsizei) h);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();

gluPerspective(30.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
	/* void gluPerspective(GLdouble fovy, GLdouble aspect, GLdouble near, GLdouble far)
	   Creates a matrix for a symmetric perspective-view frustrum and multiplies the current matrix by it.
	   fovy is the angle of the field of view in the yz-plane; its value must be in the range [0.0, 180.0].
	   aspect is the aspect ratio of the frustrum, its width divided by its height. near and far values
	   are the distances between the viewpoint and the clipping planes, along the negative z-axis. They
	   should always be positive (see fig. 3-14 pg. 155)*/
glMatrixMode(GL_MODELVIEW); // sets gluLookAt(...)
glLoadIdentity(); // assure reshaping
gluLookAt(eyex, eyey, eyez, centerX, centerY, centerZ, upX, upY, upZ);

}

void spin()
{
	theta += (double)0.01;
	if(theta > 360.0) theta -=360.0;
	glutPostRedisplay();

}

int main(int argc, char** argv)
{

glutInit(&argc, argv);

glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // pg. 732: Specifies a display mode
  // for windows created when glutCreateWindow() is called. In the command seen here, GLUT_DOUBLE
  // and GLUT_RGBA are the arguments, whereas GLUT_DEPTH is the buffer-enabling flag. The command
  // shown here creates a double buffered RGBA mode window with a depth.

glutInitWindowSize(500,500);
glutInitWindowPosition(100,100);
glutCreateWindow("Cube"); 
init();
glutDisplayFunc(display);
glutReshapeFunc(reshape);
glutMouseFunc(mouse);
glutIdleFunc(spin);
glutMainLoop();

return 0;
}