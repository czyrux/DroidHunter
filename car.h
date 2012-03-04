/**
 * @brief Implementacion de la clase car
 * @file car.h
 * @author Antonio M. Gutierrez Martinez
 */

#ifndef CAR_H
#define CAR_H

#include "objects.h"
#include <gl.h>
#include <glu.h>
#include <vector>


//CLASS WHEEL
class Wheel {
private:
    float _radius;
    float _width;
public:
    static Cylinder _base;
    static Cylinder _tire;
    Wheel(float radius=1.0,float width=1.0);
    void draw();
    void draw_chess();
    void setColor( const _vertex3f &c );
};

//CLASS AXIS_WHEELS
class Axis_wheels {
private:
    Wheel *_right_wheel;
    Wheel *_left_wheel;
    float _long;
public:
    Axis_wheels( float separacion=6.0, float width=2.0, float radius=3.0);
    ~Axis_wheels();
    void draw();
    void draw_chess();
    void setColor( const _vertex3f &c );
};

//Class Car_headlight
class Car_headlight {
private:
    float _radius;
    float _hight;
public:
    static Cone _base;
    Car_headlight( float radius=1.0 , float hight=1.0 );
    void draw();
    void draw_chess();
    void setColor( const _vertex3f &c );
};

//CLASS CHASIS
class Chasis {
private:
    Car_headlight *_right_light;
    Car_headlight *_left_light;
    Cube *r;
    float _width;
    float _hight;
    float _long;
public:
    Chasis(float width=1.0 , float hight=1.0 , float longit=1.0);
    ~Chasis();
    void setColor( const _vertex3f &chasis, const _vertex3f &lights);
    void draw();
    void draw_chess();

};


//CLASS CAR
class Car {
private:
    Axis_wheels *_front;
    Axis_wheels *_back;
    Chasis *_chasis;
    Cube *_hood;

    float _long;
    float _width;
    float _hight;
public:
    Car(float width=5.0 , float hight=4.0 , float longt=12.0);
    ~Car();
    void draw();
    void draw_chess();
    void setColor( const _vertex3f &chasis, const _vertex3f &lights,const _vertex3f &wheels,const _vertex3f &capota );
};

#endif // CAR_H
