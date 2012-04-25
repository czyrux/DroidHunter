#include "tree3D.h"
#include <iostream>

Cylinder Tree3D::_trunk(1.0,1.0,20);//inicializamos la variable estatica
Cone Tree3D::_leafs(1.0,1.0,20);


Tree3D::Tree3D(_vertex3f position, float width , float hight) {
    this->_position=position;
    this->_width=width;
    this->_hight=hight;

    this->_trunk.setMaterial(rojizoColor);
    this->_leafs.setMaterial(greenColor);
}

float Tree3D::getCollisionRadius() {
    return _width/2;
}

_vertex3f Tree3D::getPosition() {
    return this->_position;
}

void Tree3D::draw() {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(_position.x,_position.y,_position.z);
    //pintamos tronco
    glPushMatrix();
    glTranslatef(0,_hight/2,0);
    glScalef(_width,_hight,_width);
    _trunk.draw(gouraud);
    glPopMatrix();
    //pintamos una ramas
    glPushMatrix();
    glTranslatef(0,_hight+_hight/2,0);
    glScalef(_width*2,_hight+_hight/2,_width*2);
    _leafs.draw(gouraud);
    //pintamos otra capa
    glPopMatrix();
    glTranslatef(0,_hight+_hight/2+_hight/4,0);
    glScalef(_width*2,_hight+_hight/4,_width*2);
    _leafs.draw(gouraud);
    glPopMatrix();
    glPopMatrix();
}

void Tree3D::parameters(_vertex3f position, float width , float hight) {
    this->_position=position;
    this->_width=width;
    this->_hight=hight;
}
