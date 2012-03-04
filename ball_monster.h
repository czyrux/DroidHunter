#ifndef BALL_MONSTER_H
#define BALL_MONSTER_H

#include "objects.h"
#include "vertex.h"
#include "hierarchyObject.h"

//CLASS Ball

class Ball: public _hierarchyObject {
private:
    Sphere *_body;
    SemiSphere *_tooth;
    material _eyeColor , _faceColor , _toothColor;
public:
    Ball( float width=1.0 );
    ~Ball();
    void draw( drawMode d );
    float getRadioCollision();
    void changeState ( );
    void setColor (material colorBody , material colorTooth );
};

#endif // BALL_MONSTER_H
