#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>

GLfloat thetaSun = 0, thetaMoon=0, thetaOther = 0, thetaSaturnMoon=0;

GLfloat rot = 1.0;

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
// we do not have to work with the up vector for now

void init(void)
{

	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
}

void DrawSun(void) {

	glColor3f(1.0, 1.0, 0.0);
	glRotatef(thetaSun, 0.0, rot, 0.0);
	GLUquadric* quad;
	quad = gluNewQuadric();
	gluSphere(quad, 0.5, 50, 16);


}

void DrawMars(void) {


	glColor3f(1.0, 0.0, 0.0);
	glRotatef(thetaSun, rot, 0.5, 0.0);
	glTranslatef(0.0, 0.0, 1.0);
	glutWireSphere(0.13, 20, 16);


}

void DrawMarsMoon(void) {

	glColor3f(1.0, 1.0, 1.0);
	glRotatef(thetaMoon, 0.0, rot, 0.0);
	glTranslatef(0.3, 0.0, 0.0);
	glutWireSphere(0.03, 20, 16);


}

void DrawVenus(void) {

	glColor3f(1.0, 0.0, 1.0);
	glRotatef(thetaSun, 1.0, 0.5, 0.0);
	//glTranslatef(-1.2, 0.5, 0.0);
	glTranslatef(0.0, 0.0, -1.8);
	glutWireSphere(0.13, 20, 16);



}

void DrawVenusMoon(void)
{


	glColor3f(1.0, 0.7, 0.5);
	glRotatef(thetaMoon, 0.0, rot, 0.0);
	glTranslatef(0.0, 0.0, 0.3);
	glutWireSphere(0.05, 20, 16);


}

void DrawSaturn(void) {

	glColor3f(1.0, 0.3, 0.5);
	glRotatef(thetaSun, 0.0, 1.0, 1.0);
	glTranslatef(1.5, 0.0, 0.0);
	glutWireSphere(0.13, 20, 16);
	glutWireSphere(0.13, 20, 16);
}


void DrawSaturnMoon() {
	glColor3f(1.0, 0.7, 0.5);
	glRotatef(thetaSaturnMoon, 0.0, 0.0, 1.0);
	glTranslatef(0.3, 0.0, 0.0);
	glutWireSphere(0.05, 20, 16);
}

void DrawCircle(double radius) {
	int i;
	int lineAmount = 100; //# of triangles used to draw circle

	//GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 2.0f * 3.14;

	glBegin(GL_LINE_LOOP);
	for (i = 0; i <= lineAmount; i++) {
		glVertex2f(
			0 + (radius * cos(i * twicePi / lineAmount)),
			0 + (radius * sin(i * twicePi / lineAmount))
		);
	}
	glEnd();
}


void DrawSaturnRings(void)
{

	glColor3f(1.0, 0.7, 0.5);
	DrawCircle(0.2);
	DrawCircle(0.3);
}


void display(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();
	gluLookAt(eyex, eyey, eyez, angleX, angleY, angleZ, upX, upY, upZ);
	glPushMatrix();

	DrawSun();

	glLoadIdentity();
	gluLookAt(eyex, eyey, eyez, angleX, angleY, angleZ, upX, upY, upZ);
	DrawMars();
	DrawMarsMoon();

	glLoadIdentity();
	gluLookAt(eyex, eyey, eyez, angleX, angleY, angleZ, upX, upY, upZ);
	DrawVenus();
	DrawVenusMoon();

	glLoadIdentity();
	gluLookAt(eyex, eyey, eyez, angleX, angleY, angleZ, upX, upY, upZ);
	DrawSaturn();
	DrawSaturnRings();
	DrawSaturnMoon();
	

	glPopMatrix();

	glutSwapBuffers();

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
	glLoadIdentity(); // assure reshaping
	gluLookAt(eyex, eyey, eyez, angleX, angleY, angleZ, upX, upY, upZ);

}

void spin(void)
{

	thetaSun += (double)0.05;
	if (thetaSun > 360.0) thetaSun -= 360.0;

	thetaMoon += (double)0.23;
	if (thetaMoon > 360.0) thetaMoon -= 360.0;

	thetaOther += (double)0.20;
	if (thetaOther > 360.0) thetaOther -= 360.0;

	thetaSaturnMoon += (double)0.23;
	if (thetaSaturnMoon > 360.0) thetaSaturnMoon -= 360.0;

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
	if (diffY < 0){
		angleY += mouseSensitivity;
	}
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



int main(int argc, char** argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1000, 800);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("SolarSystem");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(spin);

	glutMouseFunc(mouse);		// called on mouse click events
	glutMotionFunc(mouseMove);	// called on mouse move events
	glutKeyboardFunc(keyboard); // called on keyboard event

	glutMainLoop();

}