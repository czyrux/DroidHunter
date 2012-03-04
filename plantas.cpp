#include "plantas.h"
#include <iostream>

Plantas::Plantas( int anchura , float scale) {
    this->_scale = scale;
    this->_width=anchura;

    string fichero,path="./resources/";
    fichero=path+"grass.ply";
    planta = new Object3DPly((char *)fichero.c_str());

    planta->setMaterial(bronzeColor);
}

Plantas::~Plantas() {
    delete this->planta;
}

void Plantas::draw( drawMode d) {

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glScalef(_scale,_scale/2,_scale);
    planta->draw(d);
    glPopMatrix();
}
