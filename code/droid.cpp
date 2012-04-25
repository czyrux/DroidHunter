#include "droid.h"
#include <iostream>

/**********************************/
//CLASS DROID
/**********************************/
Droid::Droid( float width , float high , bool range){
    this->_width=width;
    this->_high=high;
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

    this->_state = _NORMAL;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Droid::~Droid() {
    if (this->_head ) delete this->_head;
    if (this->_hand ) delete this->_hand;
    if (this->_body) delete this->_body;
    if (this->_hammer) delete this->_hammer;
    if (this->_radius) delete this->_radius;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

float Droid::getRadioCollision() {
    return this->_width+_width;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Droid::draw( drawMode d ) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    if(_state==_SCREAMING || _state==_MOVING)glRotatef(10,1,0,0);
    if ( _state == _DEAD ) {
        glRotatef(-90,1,0,0);
    }else
        glTranslatef(0,_high,0);

        //pintamos cabeza
        glPushMatrix();
        glTranslatef(0,(_high/2)+(_high/6),0);
        glScalef(_width,_high/3,_width);
        if (_state==_SCREAMING) glRotatef(-15,1,0,0);
        _head->draw(d);
        glPopMatrix();

        //pintamos tronco
        this->_body->setMaterial(this->_color);
        glPushMatrix();
        glScalef(_width,_high,_width);
        _body->draw(d);
        glPopMatrix();

        //pintamos brazos
        if ( _state == _TAKE_HAMMER ) {
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

        } else if (_state==_HIT_HAMMER){
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

        } else if (_state==_SCREAMING) {
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
    if (_range && _state!=_DEAD)this->_radius->draw();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

float Droid::getRange() {
    return _rangeRadius;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Droid::setColor(vector<material> m ) {
    this->_color = m.at(0);
    vector<material> material_color;
    material_color.push_back(m.at(0));
    material_color.push_back(m.at(1));
    this->_hand->setColor(material_color);
    this->_head->setColor(material_color);
}
