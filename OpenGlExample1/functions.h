#pragma once


#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <GL/glut.h> 
#include <stdio.h>
#include <iostream>

void wireBox(GLdouble width, GLdouble height, GLdouble depth) {
	glPushMatrix();
		glScalef(width, height, depth);
		glutWireCube(1.0);
	glPopMatrix();
}

void solidBox(GLdouble width, GLdouble height, GLdouble depth) {
	glPushMatrix();
		glScalef(width, height, depth);
		glutSolidCube(1.0);
	glPopMatrix();
}


#endif // !FUNCTIONS.H
