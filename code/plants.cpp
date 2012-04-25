#include "plants.h"
#include <iostream>

Plants::Plants( int anchura , float scale) {
    this->_scale = scale;
    this->_width=anchura;

    string fichero,path="./resources/";
    fichero=path+"grass.ply";
    _plant = new Object3DPly((char *)fichero.c_str());

    _plant->setMaterial(bronzeColor);
}

Plants::~Plants() {
    delete this->_plant;
}

void Plants::draw( drawMode d) {

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glScalef(_scale,_scale/2,_scale);
    _plant->draw(d);
    glPopMatrix();
}
