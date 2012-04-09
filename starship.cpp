#include "starship.h"

Starship::Starship(float width , float high , bool range)
{
    this->_width = width;
    this->_high = high;
    this->_range = range;

    _hood = new SemiSphere(1.0,60);
    _body = new Sphere(1.0,60);
    _legs = new Cone();
    _lights = new Cylinder();

    if ( range ) {
        this->_rangeRadius = _width;
        this->_radius = new Circle(_rangeRadius,40,2,true);
        _vertex3f color;
        color.r=1;color.g=1;color.b=0;
        this->_radius->setColor(color);
    }else
        this->_radius = NULL;

    _principal = orangeColor;//rojizoColor;
    _secondary = jadeColor;
    this->_lights->setMaterial(yellowPlasticColor);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Starship::~Starship() {
    if (_hood) delete _hood;
    if (_body) delete _body;
    if (_legs) delete _legs;
    if (_lights) delete _lights;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Starship::draw( drawMode d ) {
    this->_body->setMaterial(_principal);
    this->_hood->setMaterial(_secondary);
    this->_legs->setMaterial(_principal);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0,_high/6,0);

    //Pintamos el cuerpo de la nave
    glPushMatrix();
    glScalef(_width,_high/6,_width );
    this->_body->draw(d);
    glPopMatrix();

    //Pintamos la critalera
    glPushMatrix();
    glTranslatef(0,_high/12,0);
    glScalef(_width*2/3,_high/5,_width*2/3 );
    this->_hood->draw(d);
    glPopMatrix();

    //Luces
    int points = 6;
    float radius = (_width*3/4);
    for ( int i=0 ; i<points ; i++) {
        glPushMatrix();
        glRotatef(180,0,0,1);
        glTranslatef(radius*sin( (2*PI*i)/points),-_high/9,radius*cos( (2*PI*i)/points));
        glScalef(_width/30,_width/30,_width/30 );
        this->_lights->draw(d);
        glPopMatrix();
    }

    points = 14;
    //Pinchos
    for ( int i=0 ; i<points ; i++) {
        glPushMatrix();
        glRotatef(180,0,0,1);
        glTranslatef(radius*sin( (2*PI*i)/points),_high/5.5,radius*cos( (2*PI*i)/points));
        glScalef(_width/30,_width/3,_width/30 );
        this->_legs->draw(d);
        glPopMatrix();
    }
    glPopMatrix();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Starship::setColor( vector<material> m ) {
    this->_principal = m.at(0);
    this->_secondary = m.at(1);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Starship::drawRange() {
    if (_range) {
        _radius->draw();
    }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

float Starship::getRange() {
    return _rangeRadius;
}
