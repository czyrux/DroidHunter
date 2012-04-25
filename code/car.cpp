#include "car.h"
#include "iostream"

Cylinder Wheel::_base(1.0,1.0,20);//inicializamos la variable estatica
Cylinder Wheel::_tire(1.0,1.0,20);
Cone Car_headlight::_base(1.0,1.0,20);

//CLASS CAR

Car::Car( float ancho , float alto , float largo){
    this->_width=ancho;
    this->_hight=alto;
    this->_long=largo;

    this->_front = new Axis_wheels(this->_width,this->_hight/4,this->_hight/4);
    this->_back = new Axis_wheels(this->_width,this->_hight/4,this->_hight/4);
    this->_chasis = new Chasis (this->_width,this->_hight,this->_long);
    this->_hood = new Cube();
}

Car::~Car(){

    delete this->_front;
    delete this->_back;
    delete this->_chasis;
    delete this->_hood;
}

void Car::draw(){

    glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();
    glPushMatrix();
    glTranslated(0,-this->_hight/2,(this->_long/5)*1.5);
    this->_front->draw();
    glPopMatrix();

    glPushMatrix();
    glTranslated(0,-this->_hight/2,(this->_long/5)*-1.5);
    this->_back->draw();
    glPopMatrix();

    this->_chasis->draw();

    glPushMatrix();
    glTranslated(0,(this->_hight/2)+this->_hight/3,-this->_long/8);
    glScalef(this->_width/3*2,this->_hight/3*2 ,this->_long/3*2);
    this->_hood->draw(rgb);
    glPopMatrix();

}

void Car::draw_chess(){
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    glTranslated(0,-this->_hight/2,(this->_long/5)*1.5);
    this->_front->draw_chess();
    glPopMatrix();

    glPushMatrix();
    glTranslated(0,-this->_hight/2,(this->_long/5)*-1.5);
    this->_back->draw_chess();
    glPopMatrix();

    this->_chasis->draw_chess();

    glPushMatrix();
    glTranslated(0,(this->_hight/2)+this->_hight/3,-this->_long/8);
    glScalef(this->_width/3*2,this->_hight/3*2 ,this->_long/3*2);
    this->_hood->draw(chess);
    glPopMatrix();
}

void Car::setColor( const _vertex3f &chasis, const _vertex3f &faros,const _vertex3f &ruedas,const _vertex3f &capota ) {
    this->_front->setColor(ruedas);
    this->_back->setColor(ruedas);
    this->_chasis->setColor(chasis,faros);
    this->_hood->setColor(capota);
}

//CLASS WHEEL
Wheel::Wheel(float radio,float ancho){
    this->_radius=radio;
    this->_width=ancho;
}

void Wheel::draw(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glRotated(90,0,0,1);

    glPushMatrix();
    glScalef((this->_radius/3)*2,this->_width+0.1,(this->_radius/3)*2);
    this->_tire.draw(rgb);
    glPopMatrix();

    glPushMatrix();
    glScalef(this->_radius,this->_width,this->_radius);
    this->_base.draw(rgb);
    glPopMatrix();

    glPopMatrix();
}

void Wheel::draw_chess(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glRotated(90,0,0,1);
    glScalef(this->_radius,this->_width,this->_radius);
    this->_base.draw(chess);
    glPopMatrix();
}

void Wheel::setColor(const _vertex3f &c){
    this->_base.setColor(c);
}

//CLASS AXIS_WHEEL
Axis_wheels::Axis_wheels( float separacion, float ancho_rueda, float radio_rueda) {
    this->_left_wheel = new Wheel(radio_rueda,ancho_rueda);
    this->_right_wheel = new Wheel(radio_rueda,ancho_rueda);
    this->_long=separacion;
}

Axis_wheels::~Axis_wheels(){
    delete this->_right_wheel;
    delete this->_left_wheel;
}

void Axis_wheels::draw(){
    glMatrixMode(GL_MODELVIEW);
    //rueda derecha
    glPushMatrix();
    glTranslatef(this->_long/2,0,0);
    this->_right_wheel->draw();
    glPopMatrix();
    //rueda izq
    glPushMatrix();
    glTranslatef(-this->_long/2,0,0);
    this->_left_wheel->draw();
    glPopMatrix();
}

void Axis_wheels::draw_chess(){
    glMatrixMode(GL_MODELVIEW);
    //rueda derecha
    glPushMatrix();
    glTranslatef(this->_long/2,0,0);
    this->_right_wheel->draw_chess();
    glPopMatrix();
    //rueda izq
    glPushMatrix();
    glTranslatef(-this->_long/2,0,0);
    this->_left_wheel->draw_chess();
    glPopMatrix();
}

void Axis_wheels::setColor( const _vertex3f &c ){
    this->_right_wheel->setColor(c);
    this->_left_wheel->setColor(c);
}

//CLASS CHASIS

Chasis::Chasis(float ancho , float alto , float largo){
    this->_width=ancho;
    this->_hight=alto;
    this->_long=largo;
    this->r = new Cube();
    this->_right_light = new Car_headlight(_width/12,1.0);
    this->_left_light = new Car_headlight(_width/12,1.0);
}

Chasis::~Chasis() {
    delete this->r;
    delete this->_right_light;
    delete this->_left_light;

}

void Chasis::draw(){
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    glScalef(this->_width,this->_hight,this->_long);
    this->r->draw(rgb);
    glPopMatrix();

    //faro derecha
    glPushMatrix();
    glTranslatef((this->_width/6)*-1.5,this->_hight/4,this->_long/2);
    this->_right_light->draw();
    glPopMatrix();
    //faro izq
    glPushMatrix();
    glTranslatef((this->_width/6)*1.5,this->_hight/4,this->_long/2);
    this->_left_light->draw();
    glPopMatrix();
}

void Chasis::draw_chess(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glScalef(this->_width,this->_hight,this->_long);
    this->r->draw(chess);
    glPopMatrix();

    //faro derecha
    glPushMatrix();
    glTranslatef((this->_width/6)*-1.5,this->_hight/4,this->_long/2);
    this->_right_light->draw_chess();
    glPopMatrix();
    //faro izq
    glPushMatrix();
    glTranslatef((this->_width/6)*1.5,this->_hight/4,this->_long/2);
    this->_left_light->draw_chess();
    glPopMatrix();
}

void Chasis::setColor( const _vertex3f &chasis, const _vertex3f &faros){
    this->_right_light->setColor(faros);
    this->_left_light->setColor(faros);
    this->r->setColor(chasis);
}

//CLASS CAR_HEADLIGHT

Car_headlight::Car_headlight( float radio , float altura) {
    this->_radius=radio;
    this->_hight=altura;
}

void Car_headlight::draw(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glRotated(-90,1,0,0);
    glScalef(this->_radius,this->_hight,this->_radius);
    _base.draw(rgb);
    glPopMatrix();
}

void Car_headlight::draw_chess(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glRotated(-90,1,0,0);
    glScalef(this->_radius,this->_hight,this->_radius);
    _base.draw(chess);
    glPopMatrix();
}

void Car_headlight::setColor( const _vertex3f &c ){
    this->_base.setColor(c);
}
