#include "droidHead.h"

/**********************************/
//CLASS DROIDHEAD
/**********************************/
DroidHead::DroidHead( float width , float high ) {
    this->_width = width;
    this->_high = high;

    //definimos colores
    this->_eyeColor = blackPlasticColor;
    this->_faceColor = emeraldColor;

    //asignamos partes
    this->_face = new SemiSphere (1.0,20);
    this->_antenna = new Cylinder(1.0,1.0,20);
    this->_eye = new Sphere (1.0,20);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

DroidHead::~DroidHead() {
    if (this->_antenna ) delete this->_antenna;
    if (this->_eye ) delete this->_eye;
    if (this->_face ) delete this->_face;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void DroidHead::setColor ( vector<material> m ) {
    this->_eyeColor = m.at(1);
    this->_faceColor = m.at(0);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void DroidHead::draw( drawMode d ) {

    //pintamos cara
    this->_face->setMaterial(this->_faceColor);
    glPushMatrix();
    glScalef(_width,_high,_width);
    _face->draw(d);
    glPopMatrix();

    //pintamos ojos
    this->_eye->setMaterial(this->_eyeColor);
    glPushMatrix();
    glTranslatef(_width/3,_high/3*2,_width/2);
    glScalef(_width/10,_high/3,_width/10);
    _eye->draw(d);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-_width/3,_high/3*2,_width/2);
    glScalef(_width/10,_high/3,_width/10);
    _eye->draw(d);
    glPopMatrix();

    //pintamos antenas
    this->_antenna->setMaterial(this->_faceColor);
    glPushMatrix();
    glRotatef(30,0,0,1);
    glTranslatef(-_width/4,_high+_high/4,-_width/3);
    glScalef(_width/15,_high,_width/15);
    _antenna->draw(d);
    glPopMatrix();

    glPushMatrix();
    glRotatef(-30,0,0,1);
    glTranslatef(_width/4,_high+_high/4,-_width/3);
    glScalef(_width/15,_high,_width/15);
    _antenna->draw(d);
    glPopMatrix();
}

