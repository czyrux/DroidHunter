#include "character.h"
#include <iostream.h>

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Character::Character(_hierarchyObject *objeto,_hierarchyObject *objeto2,int ticksTotales , _vertex3f posInicial, float factorEscala ) {
    initialize(objeto,objeto2,ticksTotales,posInicial,factorEscala);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Character::~Character() {
    _my = 0;
    _secondary = 0;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Character::parameters (_hierarchyObject *objeto,_hierarchyObject *objeto2,int ticksTotales , _vertex3f posInicial , float factorEscala) {
    initialize(objeto,objeto2,ticksTotales,posInicial,factorEscala);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Character::initialize(_hierarchyObject *objeto,_hierarchyObject *objeto2,int ticksTotales , _vertex3f posInicial, float factorEscala ) {
    this->_my = objeto;
    this->_secondary = objeto2;
    this->_spin=0;
    this->_tickTotal=ticksTotales;
    this->_tickAction = 0;
    this->_posNow=posInicial;
    this->_orientation.x=0; this->_orientation.y=0 ; this->_orientation.z=1;
    this->_collisionRadius=this->_my->getRadioCollision();
    this->_scaleFactor=factorEscala;
    this->_elevation=0;
    this->_state = _NORMAL;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Character::animate() {
    if ( _state != _DEAD ) {
    this->_tickAction++;

    if ( _tickAction >= _tickTotal/4 ) {
        _tickAction = 0;
        switch (_state) {
        case _SCREAMING:
            _state = _NORMAL;
            break;
        case _HIT_HAMMER:
            _state = _TAKE_HAMMER;
            break;
        default:
            break;
        }
        ((BallMonster*)this->_secondary)->changeState();
    }
    }

}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

bool Character::collision( _vertex3f centro , float radio ) {
    bool colision = false;
    float d = sqrt( pow(centro.x-_posNow.x,2)+pow(centro.z-_posNow.z,2) );

    if ( (_collisionRadius*_scaleFactor)+radio>d )
        colision = true;

    return colision;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Character::draw( drawMode d) {
    _my->setState(_state);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(_posNow.x,_posNow.y-_elevation,_posNow.z);
    glScalef(_scaleFactor,_scaleFactor,_scaleFactor);
    glRotatef(_spin,0,1,0);
    _my->draw(d);
    glPopMatrix();

    if (_secondary!= NULL && _state != _DEAD ) {
        glPushMatrix();
        glTranslatef(_my->getHigh()*_scaleFactor/2,_my->getHigh()*_scaleFactor*2,-_my->getHigh()*_scaleFactor/2);
        glTranslatef(_posNow.x,_posNow.y-_elevation,_posNow.z);
        glScalef(_scaleFactor/3,_scaleFactor/3,_scaleFactor/3);
        glRotatef(_spin,0,1,0);
        _secondary->draw(d);
        glPopMatrix();
    }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

_vertex3f Character::getPosition() {
    return this->_posNow;
}

void Character::setPosition(_vertex3f pos) { _posNow = _posOld = pos; }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

float Character::getCollisionRadius() {
    return (this->_collisionRadius/2)*this->_scaleFactor;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

float Character::getRangeAction() {
    return this->_my->getRange()*this->_scaleFactor;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Character::setScaleFactor(float x) {
    this->_scaleFactor=x;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Character::avoidCollision(){
    _posNow=_posOld;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Character::spinRight() {
    if ( this->_state != _DEAD ) {
        _spin-=20;
        _spin=normalize(_spin);
    }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Character::spinLeft() {
    if ( this->_state != _DEAD ) {
        _spin+=20;
        _spin=normalize(_spin);
    }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Character::forward() {
    if ( this->_state != _DEAD ) {
        int D=10;
        //guardamos la posicion anterior
        _posOld=_posNow;
        //avanzamos
        _posNow.x+=D*sin(_spin*M_PI/180.);
        _posNow.z+=D*cos(_spin*M_PI/180.);
    }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Character::backward() {
    if ( this->_state != _DEAD ) {
        int D=10;
        //guardamos la posicion anterior
        _posOld=_posNow;
        //avanzamos
        _posNow.x-=D*sin(_spin*M_PI/180.);
        _posNow.z-=D*cos(_spin*M_PI/180.);
    }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

float Character::normalize(float angle) {
    while (angle>360)
        angle-=360;
    while (angle<0)
        angle+=360;
return angle;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

stateObject Character::getState( ) {
    return _state;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Character::setState(stateObject d) {
    _state = d;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

float Character::getSpin() {
    return this->_spin;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

