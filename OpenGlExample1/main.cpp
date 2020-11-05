// This program is from the OpenGL Programming Guide.  It shows a robot. 
// This program is a modified version of the original source codes https://cs.lmu.edu/~ray/notes/openglexamples/
// This program runs well under the settings you have done for the Assignment1. Please go back to settings if you have compile or link errors for this program.

#include <GL/glut.h> 
#include <stdio.h>
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "functions.h"

#define BODY_WIDTH 2 
#define BODY_HEIGHT 4 
#define BODY_DEPTH 1 


static int shoulderAngle = 0, elbowAngle = 0;
bool solid = false;
bool baxis = true;
bool axes = true;

//actualvectorrepresentingthecamera'sdirection
float lx =0.0f,lz = -1.0f;
//XZpositionofthecamera
float x=0.0f,z=5.0f;//allvariablesinitializedto1.0,meaning
					//thetrianglewillinitiallybewhite
float red=1.0f,blue=1.0f,green=1.0f;//angleforrotatingtriangle
float angle=0.0f;


void drawAxes() { // Draw a red x-axis, a green y-axis, and a blue z-axis.   
	if (axes == true) {
		glBegin(GL_LINES);
		//X IS  red
		glColor3f(1, 0, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(5, 0, 0);

		//Y is Green
		glColor3f(0, 1, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 5, 0);

		//Z is blue
		glColor3f(0, 0, 1);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 5);
		glEnd();
	}	
}

void drawScene() {
	//ClearColorandDepthBuffers
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	//Resettransformations
	glLoadIdentity();
	//Setthecamera
	gluLookAt(x, 1.0f, z, x + lx, 1.0f, z + lz, 0.0f, 1.0f, 0.0f);
	//Drawtheground(aplane)
	glColor3f(0.9f, 0.9f, 0.9f); glBegin(GL_QUADS);
	glVertex3f(-100.0f, 0.0f, -100.0f);
	glVertex3f(-100.0f, 0.0f, 100.0f);
	glVertex3f(100.0f, 0.0f, 100.0f);
	glVertex3f(100.0f, 0.0f, -100.0f);
	glEnd();
	if (solid == false) {

		for (int i = -3; i < 3; i++) {
			for (int j = -3; j < 3; j++) {
				glPushMatrix();
				glColor3f(0.0, 0.0, 1.0);
				glTranslatef(i * 10.0, 0, j * 10.0);
				// Draw the upper body at the orgin 
				glPushMatrix();
				glTranslatef(0.0, 3.0, 0.0);
				glColor3f(0.0, 0.0, 1.0);
				glutWireSphere(.95, 20, 20);
				glPopMatrix();

				wireBox(BODY_WIDTH, BODY_HEIGHT, BODY_DEPTH);

				//right arm shoulder
				glColor3f(0.0, 0.0, 1.0);
				glTranslatef(1.0, 1.5, 0.0); // (4) move to the right end of the upper body (attachment)
				glRotatef((GLfloat)shoulderAngle, 0.0, 0.0, 1.0); //(3) then rotate shoulder 
				glTranslatef(1.0, 0.0, 0.0); // (2) shift to the right on the x axis to have the  left end at the origin
				wireBox(2.0, 0.4, 1.0); // (1) draw the upper arm box
				//lower
				glTranslatef(1.0, 0.0, 0.0); // (4) move to the right end of the upper arm 
				glRotatef((GLfloat)elbowAngle, 0.0, 0.0, 1.0); // (3) rotate 
				glTranslatef(1.0, 0.0, 0.0); // (2) shift to the right on the x axis to have the left end at the origin
				wireBox(2.0, 0.4, 1.0); // (1) draw the lower arm 

				//Left Arm
				glColor3f(0.0, 0.0, 1.0);
				glTranslatef(-3.0, 0.0, 0.0); // (4) move to the right end of the upper body (attachment)
				glRotatef(-(GLfloat)shoulderAngle, 0.0, 0.0, 1.0); //(3) then rotate shoulder 
				glTranslatef(-3.0, 0.0, 0.0); // (2) shift to the right on the x axis to have the  left end at the origin
				wireBox(2.0, 0.4, 1.0); // (1) draw the upper arm box
				
				//lower
				glTranslatef(-6.0, 0.0, 0.0); // (4) move to the right end of the upper arm 
				glRotatef(-(GLfloat)elbowAngle, 0.0, 0.0, 1.0); // (3) rotate 
				glTranslatef(-6.0, 0.0, 0.0); // (2) shift to the right on the x axis to have the left end at the origin
				wireBox(2.0, 0.4, 1.0); // (1) draw the lower arm 

				glPopMatrix();

				
			}
		}
	}
	else {
		for (int i = -3; i < 3; i++) {
			for (int j = -3; j < 3; j++) {
				glPushMatrix();
				glColor3f(0.0, 0.0, 1.0);
				glTranslatef(i * 10.0, 0, j * 10.0);
				// Draw the upper body at the orgin 
				glPushMatrix();
				glTranslatef(0.0, 3.0, 0.0);
				glutSolidSphere(.95, 20, 20);
				glPopMatrix();

				solidBox(BODY_WIDTH, BODY_HEIGHT, BODY_DEPTH);

				//right arm shoulder
				glColor3f(0.0, 0.0, 1.0);
				glTranslatef(1.0, 1.5, 0.0); // (4) move to the right end of the upper body (attachment)
				glRotatef((GLfloat)shoulderAngle, 0.0, 0.0, 1.0); //(3) then rotate shoulder 
				glTranslatef(1.0, 0.0, 0.0); // (2) shift to the right on the x axis to have the  left end at the origin
				solidBox(2.0, 0.4, 1.0); // (1) draw the upper arm box
				//lower
				glTranslatef(1.0, 0.0, 0.0); // (4) move to the right end of the upper arm 
				glRotatef((GLfloat)elbowAngle, 0.0, 0.0, 1.0); // (3) rotate 
				glTranslatef(1.0, 0.0, 0.0); // (2) shift to the right on the x axis to have the left end at the origin
				solidBox(2.0, 0.4, 1.0); // (1) draw the lower arm 

				//Left Arm
				glColor3f(0.0, 0.0, 1.0);
				glTranslatef(-3.0, 0.0, 0.0); // (4) move to the right end of the upper body (attachment)
				glRotatef(-(GLfloat)shoulderAngle, 0.0, 0.0, 1.0); //(3) then rotate shoulder 
				glTranslatef(-3.0, 0.0, 0.0); // (2) shift to the right on the x axis to have the  left end at the origin
				solidBox(2.0, 0.4, 1.0); // (1) draw the upper arm box

				//lower
				glTranslatef(-6.0, 0.0, 0.0); // (4) move to the right end of the upper arm 
				glRotatef(-(GLfloat)elbowAngle, 0.0, 0.0, 1.0); // (3) rotate 
				glTranslatef(-6.0, 0.0, 0.0); // (2) shift to the right on the x axis to have the left end at the origin
				solidBox(2.0, 0.4, 1.0); // (1) draw the lower arm 

				glPopMatrix();
			}
		}
	}
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	drawScene(); // draw a robot 
	drawAxes(); // draw axes 
	glFlush(); 
}
 
void reshape(GLint w, GLint h) { 
	glViewport(0, 0, w, h); 
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 
	
	
	gluPerspective(65.0, GLfloat(w) / GLfloat(h), 1.0, 20.0);
}
void processSpecialKeys(int key, int xx, int yy) {
	float fraction = 0.1f; 
	switch (key) { 
		case GLUT_KEY_LEFT:
			angle -= 0.01f;
			lx = sin(angle);
			lz = -cos(angle);
			break;
		case GLUT_KEY_RIGHT:
			angle += 0.01f;
			lx = sin(angle);
			lz = -cos(angle);
			break;
		case GLUT_KEY_UP:
			x += lx * fraction;
			z += lz * fraction;
			break;
		case GLUT_KEY_DOWN:
			x -= lx * fraction;
			z -= lz * fraction;
			break;
		case GLUT_KEY_F4: elbowAngle -= 5;
			break;
		case GLUT_KEY_F5: shoulderAngle -= 5;
			break;
	}
	glutPostRedisplay();
}
void procKeys(unsigned char key, int x, int y) {
	switch (key) {
	case '1': solid = false;
		break;
	case '2': solid = true;	
		break;
	case '3':
		if (axes == true) {
			axes = false;
		}
		else {
			axes = true;
		}
		break;
	case '4': elbowAngle += 5;
		break;
	case '5': shoulderAngle += 5;
		break;
	case 'F4': elbowAngle -= 5;
		break;
	case 'F5': shoulderAngle -= 5;
		break;
	case 'ESC': exit(0);
		break;
	case 27: exit(0);
		break;
	} 
	glutPostRedisplay();
}

// Perfroms application specific initialization: turn off smooth shading, // sets the viewing transformation once and for all.  In this application we // won't be moving the camera at all, so it makes sense to do this. 
void init() { 
	glShadeModel(GL_FLAT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(1, 2, 8, 0, 0, 0, 0, 1, 0);
}

// Initializes GLUT, the display mode, and main window; registers callbacks; 
// does application initialization; enters the main event loop. 
int main(int argc, char** argv) {
	std::cout << "---------------------------------------------------------------------- -" << std::endl;
	std::cout << "Jeremiah Heck's Assignment 2." << std::endl;
	std::cout << " - 'a': toggle on off to draw axes " << std::endl;
	std::cout << " - '1': Wire shapes " << std::endl;
	std::cout << " - '2': Solid shapes " << std::endl;
	std::cout << " - '3': toggle on off to draw axes " << std::endl;
	std::cout << " - '4': increase elbow angle " << std::endl;
	std::cout << " - '5': increase shoulder angle  " << std::endl;
	std::cout << " - 'F4': decrease elbow angle " << std::endl;
	std::cout << " - 'F5': decrease shoulder angle  " << std::endl;
	std::cout << " - LEFT ARROW: to move camera left    " << std::endl;
	std::cout << " - RIGHT ARROW: to move camera right   " << std::endl;
	std::cout << " - UP ARROW: to move camera forward  " << std::endl;
	std::cout << " - DOWN ARROW: to move camera backward  " << std::endl;
	std::cout << " - ESC: to quit" << std::endl;
	std::cout << "---------------------------------------------------------------------- - " << std::endl;

	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
	glutInitWindowPosition(80, 80); 
	glutInitWindowSize(800, 600); 
	glutCreateWindow("Robot Arm");
	glutDisplayFunc(display); 
	glutReshapeFunc(reshape); 
	glutKeyboardFunc(procKeys); 
	glutSpecialFunc(processSpecialKeys);
	init(); 
	glutMainLoop();
}