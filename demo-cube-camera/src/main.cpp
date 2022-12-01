#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>

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

	glEnable(GL_DEPTH_TEST);							// this is a nice touch that we will notice on SolarSystem.cpp, it enables depth and objects can hide behind other objects
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear color and buffer on startup

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
}

void DrawCube(void)
{
	glColor3f(1.0, 1.0, 0.0);
	glRotatef(45.0, 1.0, 0.5, 0.5);
	glutWireCube(0.5);
}

void display(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(eyex, eyey, eyez, angleX, angleY, angleZ, upX, upY, upZ);
	glPushMatrix();
	DrawCube();
	glPopMatrix();

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	glMatrixMode(GL_PROJECTION); // sets gluPerspective(...)
	glLoadIdentity();			 // assure reshaping

	gluPerspective(30.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);

	glMatrixMode(GL_MODELVIEW); // sets gluLookAt(...)
	glLoadIdentity();			// assure reshaping
	gluLookAt(eyex, eyey, eyez, angleX, angleY, angleZ, upX, upY, upZ);
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
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1000, 800);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("SolarSystem");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glutMouseFunc(mouse);		// called on mouse click events
	glutMotionFunc(mouseMove);	// called on mouse move events
	glutKeyboardFunc(keyboard); // called on keyboard event

	glutMainLoop();
}


// there is a problem on how look at is calculated
// the moment we rotate left and right we are NOT rotating the camera itself but changing the vector of the object we are looking at
// this is similiar to rotating your eyes but not your body
// the moment we move forward/backwords we will move on the original axis
// we should instead calculate the vector based on the look at vector
// (this is just a quick investigation, this may consume some take some time to debug so I am leaving it as it is)