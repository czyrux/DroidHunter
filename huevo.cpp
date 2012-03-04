#include "huevo.h"

Sphere Huevo::objeto(1,20);

Huevo::Huevo() {
    this->radio=0;
    this->posicion.x=this->posicion.y=this->posicion.z=0;
}

Huevo::Huevo ( _vertex3f posicion , float radio  ) {
    this->posicion=posicion;
    this->radio=radio;

    this->objeto.setMaterial(eggColor);
}

void Huevo::draw() {
    //pintamos huevo
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(posicion.x,posicion.y+radio*5/3,posicion.z);
    glScalef(radio,radio*5/3,radio);
    objeto.draw(gouraud);
    glPopMatrix();
}

_vertex3f Huevo::getPosicion() {
    return posicion;
}
float Huevo::getRadioColision() {
    return radio;
}

void Huevo::parameters(_vertex3f posicion, float radio) {
    this->posicion=posicion;
    this->radio=radio;

    this->objeto.setMaterial(eggColor);
}
