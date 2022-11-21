#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>

GLfloat thetaSun = 0, thetaMoon=0, thetaOther = 0, thetaSaturnMoon=0;
GLfloat centerX= 0.0, centerY= 0.0, centerZ= 0.0, upX= 0.0, upY=1.0, upZ=0.0;
GLfloat rot = 1.0;
GLfloat eyex = 0.0, eyey = 0.0, eyez = -9.0;

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
	gluLookAt(eyex, eyey, eyez, centerX, centerY, centerZ, upX, upY, upZ);
	glPushMatrix();

	DrawSun();

	glLoadIdentity();
	gluLookAt(eyex, eyey, eyez, centerX, centerY, centerZ, upX, upY, upZ);
	DrawMars();
	DrawMarsMoon();

	glLoadIdentity();
	gluLookAt(eyex, eyey, eyez, centerX, centerY, centerZ, upX, upY, upZ);
	DrawVenus();
	DrawVenusMoon();

	glLoadIdentity();
	gluLookAt(eyex, eyey, eyez, centerX, centerY, centerZ, upX, upY, upZ);
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
	gluLookAt(eyex, eyey, eyez, centerX, centerY, centerZ, upX, upY, upZ);

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
	// The mouse function uses the right button (GLUT_RIGHT_BUTTON) 
	// to exit the program in the state clicked (GLUT_DOWN).
	if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
		exit(0);

}


void main(int argc, char** argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1000, 800);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("SolarSystem");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutIdleFunc(spin);
	glutMainLoop();

}
