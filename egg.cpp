#include "egg.h"

Sphere Egg::_object(1,20);

Egg::Egg() {
    this->_radious=0;
    this->_position.x=this->_position.y=this->_position.z=0;
}

Egg::Egg ( _vertex3f posicion , float radio  ) {
    this->_position=posicion;
    this->_radious=radio;

    this->_object.setMaterial(eggColor);
}

void Egg::draw() {
    //pintamos huevo
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(_position.x,_position.y+_radious*5/3,_position.z);
    glScalef(_radious,_radious*5/3,_radious);
    _object.draw(gouraud);
    glPopMatrix();
}

_vertex3f Egg::getPosition() {
    return _position;
}
float Egg::getRadiousCollision() {
    return _radious;
}

void Egg::parameters(_vertex3f posicion, float radio) {
    this->_position=posicion;
    this->_radious=radio;

    this->_object.setMaterial(eggColor);
}
