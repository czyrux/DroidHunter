#include "arbol.h"
#include <iostream>

Cylinder Arbol::_trunk(1.0,1.0,20);//inicializamos la variable estatica
Cone Arbol::_leafs(1.0,1.0,20);


Arbol::Arbol(_vertex3f position, float width , float hight) {
    this->_position=position;
    this->_width=width;
    this->_hight=hight;

    this->_trunk.setMaterial(rojizoColor);
    this->_leafs.setMaterial(greenColor);
}

float Arbol::getCollisionRadius() {
    return _width/2;
}

_vertex3f Arbol::getPosition() {
    return this->_position;
}

void Arbol::draw() {
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

void Arbol::parameters(_vertex3f position, float width , float hight) {
    this->_position=position;
    this->_width=width;
    this->_hight=hight;
}
