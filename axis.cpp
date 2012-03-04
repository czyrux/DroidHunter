#include "axis.h"

Axis::Axis() {

}

void Axis::draw() {
        glLineWidth(2);
	glBegin(GL_LINES);
// eje X, color rojo
	glColor3f(0.7,0,0);
        glVertex3f(-AXIS_SIZE,0.1,0);
        glVertex3f(0,0.1,0);
	glColor3f(1,0,0);
        glVertex3f(0,0.1,0);
        glVertex3f(AXIS_SIZE,0.1,0);
// eje Y, color verde
	glColor3f(0,0.7,0);
	glVertex3f(0,-AXIS_SIZE,0);
	glVertex3f(0,0,0);
	glColor3f(0,1,0);
	glVertex3f(0,0,0);
	glVertex3f(0,AXIS_SIZE,0);
// eje Z, color azul
	glColor3f(0,0,0.7);
        glVertex3f(0,0.1,-AXIS_SIZE);
        glVertex3f(0,0.1,0);
	glColor3f(0,0,1);
        glVertex3f(0,0.1,0);
        glVertex3f(0,0.1,AXIS_SIZE);
	glEnd();
        glLineWidth(1);
}

