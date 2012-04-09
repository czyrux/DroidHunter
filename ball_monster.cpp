#include "ball_monster.h"

BallMonster::BallMonster( float width ) {
    this->_width = width;

    this->_faceColor = copperColor;//orangeColor;
    this->_toothColor = whitePlasticColor;//eggColor;
    this->_eyeColor = blackPlasticColor;

    this->_body = new Sphere (1.0,20);//&sphere;
    this->_tooth = new SemiSphere (1.0,20);//&semisphere;

    _state = _OPEN;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

BallMonster::~BallMonster() {
    if (this->_body ) delete this->_body;
    if (this->_tooth ) delete this->_tooth;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void BallMonster::draw( drawMode d ) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0,_width+_width/4,0);
    this->_body->setMaterial(this->_faceColor);
    this->_tooth->setMaterial(this->_toothColor);

    //cuerpo
    glPushMatrix();
    glScalef(_width,_width,_width);
    this->_body->draw(d);
    glPopMatrix();

    //boca
    glPushMatrix();
    glRotatef(180,0,0,1);
    glTranslatef(0,0,_width/5+_width/8);
    (_state == _OPEN )?glScalef(_width*4/5,_width*4/5,_width*4/5)
                     :glScalef(_width*4/5,_width/5,_width*4/5);
     //abierta
     //cerrada
    this->_tooth->draw(d);
    glPopMatrix();

    //ojo
    glPushMatrix();
    glRotatef(0,0,1,0);
    glTranslatef(_width,_width,0);
    glScalef(_width/4,_width/4,_width/4);
    this->_body->draw(d);
    glPopMatrix();

    //iris
    this->_body->setMaterial(this->_eyeColor);
    glPushMatrix();
    glRotatef(0,0,1,0);
    glTranslatef(_width,_width,0);
    glTranslatef(0,0,_width/15+0.01);
    glScalef(_width/5,_width/5,_width/5);
    this->_body->draw(d);
    glPopMatrix();

    glPopMatrix();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

float BallMonster::getRadioCollision() {
    return this->_width;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void BallMonster::setColor (material colorBody , material colorTooth ) {
    this->_faceColor = colorBody;
    this->_toothColor = colorTooth;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void BallMonster::changeState ( ) {
    (_state==_OPEN)?_state=_CLOSE:_state=_OPEN;
}
