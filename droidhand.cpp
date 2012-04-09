#include "droidhand.h"

/**********************************/
//CLASS DROIDHAND
/**********************************/
DroidHand::DroidHand( float width , float hight ) {
    this->_width = width;
    this->_high = hight;

    //definimos colores
    this->_color = emeraldColor;

    //asignamos partes
    this->_hand = new Cylinder(1.0,1.0,20);
    this->_ball = new Sphere (1.0,20);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

DroidHand::~DroidHand() {
    if (this->_ball ) delete this->_ball;
    if (this->_hand ) delete this->_hand;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void DroidHand::setColor ( material color ) {
    this->_color = color;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void DroidHand::draw( drawMode d ) {

    //pintamos el brazo
    this->_hand->setMaterial(this->_color);
    glPushMatrix();
    glScalef(_width,_high,_width);
    _hand->draw(d);
    glPopMatrix();

    //pintamos terminaciones
    this->_ball->setMaterial(this->_color);
    glPushMatrix();
    glTranslatef(0,-_high/2,0);
    glScalef(_width,_width,_width);
    _ball->draw(d);
    glPopMatrix();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

float DroidHand::getHight() {
    return _high+_width;
}
