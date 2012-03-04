#ifndef DROID_H
#define DROID_H

#include "objects.h"
#include "vertex.h"
#include "circle.h"
#include "hierarchyObject.h"

//CLASS DROIDHEAD
class DroidHead {
private:
    Cylinder *_antenna;
    Sphere *_eye;
    SemiSphere *_face;
    material _eyeColor , _faceColor;
    float _width;
    float _high;
public:
    DroidHead( float width=1.0 , float hight=1.0 );
    ~DroidHead();
    void draw( drawMode d );
    void setColor ( material faceColor , material eyeColor );
};

//CLASS HAND
class DroidHand {
private:
    Cylinder *_hand;
    Sphere *_ball;
    material _color;
    float _width;
    float _high;
public:
    DroidHand(float width=.25 , float high=1.0);
    ~DroidHand();
    void draw( drawMode d );
    float getHight();
    void setColor ( material color );
};

//CLASS DROID
class Droid: public _hierarchyObject {
private:
    DroidHead *_head;
    Cylinder *_body;
    DroidHand *_hand;
    material _color;
    Cylinder *_hammer;
    Circle *_radius;
    bool _range;
    float _rangeRadius;
public:
    Droid( float width=.5, float high=2.0 , bool range=true );
    ~Droid();
    float getRadioCollision();
    void draw( drawMode d );
    float getRange();
    void setColor (material colorBody , material colorEyes );
};

#endif // DROID_H
