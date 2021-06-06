#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <iostream>
#include <time.h>
#include <sys/timeb.h>
using namespace std;



#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glut32.lib")



void InitGraphics(int argc, char* argv[]);
 
/**
Sets the logical coordinate system we will use to specify
our drawings.
*/
void SetTransformations();

/**
Handles the paint event. This event is triggered whenever
our displayed graphics are lost or out-of-date.
ALL rendering code should be written here.
*/
void OnDisplay();

/**
Handles the key press. This event is whenever
a normal ASCII character is being pressed.
*/
void DrawCircle(GLfloat a, GLfloat b, GLfloat radius);

void DrawClock();
void ClockSticks();
void MainNum();

float SRot = 0, MRot = 0 ,HRot=0;
int main(int argc, char* argv[])
{
	
	InitGraphics(argc, argv);
	return 0;
}

/**
Creates the main window, registers event handlers, and
initializes OpenGL stuff.
*/
void InitGraphics(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	//Create an 800x600 window with its top-left corner at pixel (100, 100)
	glutInitWindowPosition(100, 100); //pass (-1, -1) for Window-Manager defaults
	glutInitWindowSize(800, 600);
	glutCreateWindow("Clock");
	//OnDisplay will handle the paint event
	glutDisplayFunc(OnDisplay);
	// here is the setting of the idle function
	glutIdleFunc(OnDisplay);
	// here is the setting of the key function
	//glutKeyboardFunc(OnKeyPress);
	SetTransformations();

	glutMainLoop();
}

/**
Sets the logical coordinate system we will use to specify
our drawings.
*/
void SetTransformations() {
	//set up the logical coordinate system of the window: [-100, 100] x [-100, 100]
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-100, 100, -100, 100);
	glMatrixMode(GL_MODELVIEW);
}

/**
Handles the paint event. This event is triggered whenever
our displayed graphics are lost or out-of-date.
ALL rendering code should be written here.
*/
void OnDisplay()
{

	// clear the transformation matrix
	glLoadIdentity();

	//set the background color to white
	glClearColor(0, 0, 0, 1);
	//fill the whole color buffer with the clear color
	glClear(GL_COLOR_BUFFER_BIT);
	/////////////////////////////////////////////////////////////////////////////////
	glColor3f(1, 1, 1);
	
	DrawClock();
	ClockSticks();
	MainNum();
	
	/////////////////////////////////////////////////////////////////////////////////

	// swapping the buffers causes the rendering above to be 
	// shown
	glutSwapBuffers();

}

/**
Handles the key press. This event is whenever
a normal ASCII character is being pressed.
*/

void DrawCircle(GLfloat a, GLfloat b, GLfloat radius) {

	float PI = 3.14;
	int lineAmount = 36; //# of triangles used to draw circle

	GLfloat twicePi = 2.0f * PI;

	glLineWidth(5);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i <= lineAmount; i++) {

		float theta = i * twicePi / lineAmount;

		glVertex2f(
			a + (radius * cos(theta)),
			b + (radius * sin(theta))
		);
	}
	glEnd();
}
void DrawClock()
{

	DrawCircle(0, 0, 64);
	for (int i = 0,fRot = 0; i <= 12; i++, fRot +=30)
	{
		glPointSize(10);
		glPushMatrix();
		glRotatef(fRot, 0, 0, 1);
		glTranslatef(60, 0, 0);
		glBegin(GL_POINTS);
		glVertex3f(0, 0, 0);
		glEnd();
		glPopMatrix();

	}
	for (int i = 0, fRot = 0; i <= 360; i++, fRot += 6)
	{
		glPointSize(4);
		glPushMatrix();
		glRotatef(fRot, 0, 0, 1);
		glTranslatef(60, 0, 0);
		glBegin(GL_POINTS);
		glVertex3f(0, 0, 0);
		glEnd();
		glPopMatrix();

	}
}
void MainNum()
{
	// 12
	glColor3f(1, 1, 1);
	glLineWidth(2);
	glBegin(GL_LINE_STRIP);
	glVertex3f(-3, 66, 0);
	glVertex3f(-3, 75, 0);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex3f(-1, 75, 0);
	glVertex3f(2, 75, 0);
	glVertex3f(2, 70, 0);
	glVertex3f(-1, 70, 0);
	glVertex3f(-1, 66, 0);
	glVertex3f(2, 66, 0);
	glEnd();
	
	// 6
	glBegin(GL_LINE_STRIP);
	glVertex3f(2, -66, 0);
	glVertex3f(-1, -66, 0);
	glVertex3f(-1, -72, 0);
	glVertex3f(2, -72, 0);
	glVertex3f(2, -69, 0);
	glVertex3f(-1, -69, 0);
	glEnd();

	// 3
	glBegin(GL_LINE_STRIP);
	glVertex3f(66, 4, 0);
	glVertex3f(69, 4, 0);
	glVertex3f(69, 0, 0);
	glVertex3f(66, 0, 0);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex3f(69, 0, 0);
	glVertex3f(69, -4, 0);
	glVertex3f(66, -4, 0);
	glEnd();


	// 9

	glBegin(GL_LINE_LOOP);
	glVertex3f(-66, 4, 0);
	glVertex3f(-69, 4, 0);
	glVertex3f(-69, 0, 0);
	glVertex3f(-66, 0, 0);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex3f(-66, 0, 0);
	glVertex3f(-66, -4, 0);
	glVertex3f(-69, -4, 0);
	glEnd();



}
void ClockSticks()
{
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POINT_SMOOTH);
	glPushMatrix();
	glRotatef(SRot -= 0.01, 0, 0, 1);
	glColor3f(1, 0, 0);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 50, 0);
	glEnd();
	glPopMatrix();
	
	glPushMatrix();
	glRotatef(MRot -= 0.0001, 0, 0, 1);
	glLineWidth(3);
	glColor3f(0, 0, 1);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 40, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(HRot -= 0.00001, 0, 0, 1);
	glLineWidth(3);
	glColor3f(1, 1, 0);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 30, 0);
	glEnd();
	glPopMatrix();
	DrawCircle(0, 0, 3);
}


