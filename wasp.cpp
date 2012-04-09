#include "wasp.h"

/**********************************/
//CLASS WASP
/**********************************/
Wasp::Wasp( float width , float high , bool range){
    this->_width=width;
    this->_high=high;
    this->_range = range;

    if ( range ) {
        this->_rangeRadius = _high * 4;
        this->_radius = new Circle(_rangeRadius,40,2,true);
        _vertex3f color;
        color.r=1;color.g=0;color.b=0;
        this->_radius->setColor(color);
    }else
        this->_radius = NULL;

    this->_second = cyanPlasticColor;
    this->_first = blackPlasticColor;

    this->_head = new DroidHead();
    this->_head->setColor(blackPlasticColor,cyanPlasticColor);
    this->_body = new Cylinder();
    this->_body2 = new Cylinder();
    this->_stinger = new Cone();
    this->_upStinger = new SemiSphere();
    this->_wing = new Cube();
    this->_wingCircle = new Sphere(1.0,40);
    this->_shadow = new Cylinder();
    this->_shot = new Cylinder();
    this->_shadow->setMaterial(blackPlasticColor);
    this->_shot->setMaterial(rubyColor);

    this->_state = _NORMAL;
}

Wasp::~Wasp() {
    if (this->_head ) delete this->_head;
    if (this->_body ) delete this->_body;
    if (this->_body2 ) delete this->_body2;
    if (this->_stinger ) delete this->_stinger;
    if (this->_upStinger ) delete this->_upStinger;
    if (this->_wing ) delete this->_wing;
    if (this->_wingCircle ) delete this->_wingCircle;
    if (this->_shadow) delete this->_shadow;
    if (this->_radius) delete this->_radius;
    if (this->_shot) delete this->_shot;
}

float Wasp::getRadioCollision() {
    return this->_high+_width/2;
}

void Wasp::draw( drawMode d  ) {
    float fly = _high*3;

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    if (_state==_FLYING || _state==_MOVING || _state==_SHOOTING){ glTranslatef(0,fly,0);}
    //if (_state==_nailed)glTranslatef(0,-_high/2,0);
    //if (_state==_small)glScalef(1,0.25,1);
    if (_state==_MOVING) glRotatef(10,1,0,0);
    glPushMatrix();
    glTranslatef(0,_high,0);
        //pintamos cabeza
        glPushMatrix();
        glTranslatef(0,(_high/2)+(_high/6),0);
        glScalef(_width,_high/3,_width);
        _head->draw( d );
        glPopMatrix();

        //pintamos tronco
        this->_body->setMaterial(this->_first);
        glPushMatrix();
        glScalef(_width,_high/3,_width);
        _body->draw(d);
        glPopMatrix();

        this->_body2->setMaterial(this->_second);
        glPushMatrix();
        glTranslatef(0,_high/3,0);
        glScalef(_width,_high/3,_width);
        _body2->draw(d);
        glPopMatrix();

        this->_body2->setMaterial(this->_second);
        glPushMatrix();
        glTranslatef(0,-_high/3,0);
        glScalef(_width,_high/3,_width);
        _body2->draw(d);
        glPopMatrix();

        //pintamos aguijon
        this->_upStinger->setMaterial(_first);
        this->_stinger->setMaterial(_second);
        glPushMatrix();
        glRotatef(180,0,0,1);
            glPushMatrix();
            glTranslatef(0,(_high/3)+_high/5,0);
            glScalef(_width,_width/2,_width);
            this->_upStinger->draw(d);
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0,_high-_width,0);
            glScalef(_width/4,_width*5/3,_width/4);
            this->_stinger->draw(d);
            glPopMatrix();
        glPopMatrix();

        //ala izquierda
        this->_wing->setMaterial(_first);
        this->_wingCircle->setMaterial(_first);
        glPushMatrix();
        glTranslatef(0,_high/3,-_width/2);
        glScalef(_high*3/4,_high/3,_width/10);
        glTranslatef(this->_wing->getSide()/2,0,0);
        this->_wing->draw(d);
        glPopMatrix();
        glPushMatrix();
        glTranslatef(_high*3/4-_width/2,_high/3,-_width/2);
        glScalef(_high/6,_high/6,_width/12);
        glTranslatef(this->_wingCircle->getRadius(),0,0);
        this->_wingCircle->draw(d);
        glPopMatrix();

        glPushMatrix();
        glRotatef(-60,0,0,1);
        glPushMatrix();
        glTranslatef(-_width,_high/3,-_width/2);
        glScalef(_high*2/3,_high/4,_width/10);
        glTranslatef(this->_wing->getSide()/2,0,0);
        this->_wing->draw(d);
        glPopMatrix();
        glPushMatrix();
        glTranslatef(-_width+_high*2/3-_width/2,_high/3,-_width/2);
        glScalef(_high/8,_high/8,_width/12);
        glTranslatef(this->_wingCircle->getRadius(),0,0);
        this->_wingCircle->draw(d);
        glPopMatrix();
        glPopMatrix();

        //ala derecha
        glPushMatrix();
        glTranslatef(0,_high/3,-_width/2);
        glScalef(_high*3/4,_high/3,_width/10);
        glTranslatef(-this->_wing->getSide()/2,0,0);
        this->_wing->draw(d);
        glPopMatrix();
        glPushMatrix();
        glTranslatef(-_high*3/4+_width/2,_high/3,-_width/2);
        glScalef(_high/6,_high/6,_width/12);
        glTranslatef(-this->_wingCircle->getRadius(),0,0);
        this->_wingCircle->draw(d);
        glPopMatrix();

        glPushMatrix();
        glRotatef(60,0,0,1);
        glPushMatrix();
        glTranslatef(_width,_high/3,-_width/2);
        glScalef(_high*2/3,_high/4,_width/10);
        glTranslatef(-this->_wing->getSide()/2,0,0);
        this->_wing->draw(d);
        glPopMatrix();
        glPushMatrix();
        glTranslatef(_width-_high*2/3+_width/2,_high/3,-_width/2);
        glScalef(_high/8,_high/8,_width/12);
        glTranslatef(-this->_wingCircle->getRadius(),0,0);
        this->_wingCircle->draw(d);
        glPopMatrix();
        glPopMatrix();

        //disparo
        if (_state == _SHOOTING ) {
            glPushMatrix();
            //glTranslatef(_width-_high*2/3+_width/2,_high/3,-_width/2);
            glScalef(_width/4,fly,_width/4);
            glTranslatef(0,-_shot->getHigh()/2,0);
            this->_shot->draw(d);
            glPopMatrix();
        }

    glPopMatrix();
    glPopMatrix();
}

void Wasp::setColor (material first , material second ) {
    this->_first = first;
    this->_second = second;
    this->_head->setColor(first,second);
}

void Wasp::drawRange() {
    if (_range) {
        _radius->draw();
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glScalef(_width,0.2,_width);
        glTranslatef(0,this->_shadow->getHigh()/2,0);
        this->_shadow->draw(gouraud);
        glPopMatrix();
    }
}

float Wasp::getRange() {
    return _rangeRadius;
}
