#include "droid.h"
#include <iostream>

/**********************************/
//CLASS DROID
/**********************************/
Droid::Droid( float width , float hight , bool range){
    this->_width=width;
    this->_high=hight;
    this->_range = range;

    if ( range ) {
        this->_rangeRadius = _high*3;
        this->_radius = new Circle(_rangeRadius,40,2,false);
        _vertex3f color;
        color.r=1;color.g=1;color.b=0;
        this->_radius->setColor(color);
    }else
        this->_radius = NULL;

    this->_head = new DroidHead();
    this->_hand = new DroidHand();
    this->_body = new Cylinder(1.0,1.0,20);
    this->_hammer = new Cylinder(1.0,1.0,20);

    this->_color = emeraldColor;

    this->_state = _normal;
}

Droid::~Droid() {
    if (this->_head ) delete this->_head;
    if (this->_hand ) delete this->_hand;
    if (this->_body) delete this->_body;
    if (this->_hammer) delete this->_hammer;
    if (this->_radius) delete this->_radius;
}

float Droid::getRadioCollision() {
    return this->_width+_width;
}

void Droid::draw( drawMode d ) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    if(_state==_screaming || _state==_moving)glRotatef(10,1,0,0);
    if ( _state == _dead ) {
        glRotatef(-90,1,0,0);
    }else
        glTranslatef(0,_high,0);

        //pintamos cabeza
        glPushMatrix();
        glTranslatef(0,(_high/2)+(_high/6),0);
        glScalef(_width,_high/3,_width);
        if (_state==_screaming) glRotatef(-15,1,0,0);
        _head->draw(d);
        glPopMatrix();

        //pintamos tronco
        this->_body->setMaterial(this->_color);
        glPushMatrix();
        glScalef(_width,_high,_width);
        _body->draw(d);
        glPopMatrix();

        //pintamos brazos
        if ( _state == _takeHammer ) {
            glPushMatrix();
            glRotatef(0,1,0,0);
            glPushMatrix();
            glTranslatef(-_width-_width/5,_width*2,0);
            glScalef(_width*2/3,(_high*2/3)*2,_width*2/3);
            glRotatef(-180,1,0,0);
            this->_hand->draw(d);
            glPopMatrix();

            this->_hammer->setMaterial(silverColor);
            glPushMatrix();
            glTranslatef(-_width-_width/5,_width*2+_high,0);
            glScalef(_width+_width*3/4,_width+_width*3/4,_high*3/4);
            glRotatef(-90,1,0,0);
            this->_hammer->draw(d);
            glPopMatrix();
            glPopMatrix();

            glPushMatrix();//izq
            glTranslatef(_width+_width/5,_high*.15,0);
            glScalef(_width*2/3,_high*2/3,_width*2/3);
            this->_hand->draw(d);
            glPopMatrix();

        } else if (_state==_hitHammer){
            glPushMatrix();
            glRotatef(60,1,0,0);
            glPushMatrix();
            glTranslatef(-_width-_width/5,_width*2,0);
            glScalef(_width*2/3,(_high*2/3),_width*2/3);
            glRotatef(-180,1,0,0);
            this->_hand->draw(d);
            glPopMatrix();

            this->_hammer->setMaterial(silverColor);
            glPushMatrix();
            glTranslatef(-_width-_width/5,/*_width*2+*/_high,0);
            glScalef(_width+_width/3,_width+_width/2.5,_high);
            glRotatef(-90,1,0,0);
            this->_hammer->draw(d);
            glPopMatrix();
            glPopMatrix();

            glPushMatrix();//izq
            glTranslatef(_width+_width/5,_high*.15,0);
            glScalef(_width*2/3,_high*2/3,_width*2/3);
            this->_hand->draw(d);
            glPopMatrix();

        } else if (_state==_screaming) {
            glPushMatrix(); //drcha
            glRotatef(20,0,0,1);
            glRotatef(20,1,0,0);
            glPushMatrix();
            glTranslatef(-_width+_width/2,_width*3,0);
            glScalef(_width*2/3,_high*2/3,_width*2/3);
            glRotatef(-180,1,0,0);
            this->_hand->draw(d);
            glPopMatrix();
            glPopMatrix();

            glPushMatrix();//izq
            glRotatef(-20,0,0,1);
            glRotatef(20,1,0,0);
            glPushMatrix();
            glTranslatef(_width-_width/2,_width*3,0);
            glScalef(_width*2/3,_high*2/3,_width*2/3);
            glRotatef(-180,1,0,0);
            this->_hand->draw(d);
            glPopMatrix();
            glPopMatrix();

            glLineWidth(2);
            glBegin(GL_LINES);
            glColor3f(0,0,0);
            glVertex3f(0,(_high/2)+(_high/6),_width+_width/2);
            glVertex3f(0,(_high/2)+(_high/6),_width*3+_width/2);

            glVertex3f(_width/2,(_high/2)+(_high/6),_width+_width/2);
            glVertex3f(_width*2,(_high/2)+(_high/6),_width*3+_width/2);

            glVertex3f(-_width/2,(_high/2)+(_high/6),_width+_width/2);
            glVertex3f(-_width*2,(_high/2)+(_high/6),_width*3+_width/2);
            glEnd();
            glLineWidth(1);
        }else {
            glPushMatrix();//drcha
            glTranslatef(-_width-_width/5,_high*.15,0);
            glScalef(_width*2/3,_high*2/3,_width*2/3);
            this->_hand->draw(d);
            glPopMatrix();

            glPushMatrix();//izq
            glTranslatef(_width+_width/5,_high*.15,0);
            glScalef(_width*2/3,_high*2/3,_width*2/3);
            this->_hand->draw(d);
            glPopMatrix();
        }

        //pintamos piernas
        glPushMatrix();
        glTranslatef(_width/3,-_high/2,0);
        glScalef(_width*.8,_high*2/3,_width*.8);
        this->_hand->draw(d);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-_width/3,-_high/2,0);
        glScalef(_width*.8,_high*2/3,_width*.8);
        this->_hand->draw(d);
        glPopMatrix();

    glPopMatrix();

    //pintamos rango accion
    if (_range && _state!=_dead)this->_radius->draw();
}

void Droid::setColor (material colorBody , material colorEyes ) {
    this->_color = colorBody;
    this->_hand->setColor(colorBody);
    this->_head->setColor(colorBody,colorEyes);
}

float Droid::getRange() {
    return _rangeRadius;
}

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

DroidHead::~DroidHead() {
    if (this->_antenna ) delete this->_antenna;
    if (this->_eye ) delete this->_eye;
    if (this->_face ) delete this->_face;
}

void DroidHead::setColor ( material faceColor , material eyeColor ) {
    this->_eyeColor = eyeColor;
    this->_faceColor = faceColor;
}

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

DroidHand::~DroidHand() {
    if (this->_ball ) delete this->_ball;
    if (this->_hand ) delete this->_hand;
}

void DroidHand::setColor ( material color ) {
    this->_color  = color;
}

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

float DroidHand::getHight() {
    return _high+_width;
}
