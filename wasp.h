#ifndef WASP_H
#define WASP_H

#include "objects.h"
#include "vertex.h"
#include "circle.h"
#include "hierarchyObject.h"


//CLASS WASP
class WaspHead {
private:
    Sphere *_eye;
    SemiSphere *_face;
    Cylinder *_antenna;
    material _eyeColor , _faceColor;
    float _width;
    float _high;
public:
    WaspHead( float width=1.0 , float high=1.0 );
    ~WaspHead();
    void draw( drawMode d  );
    void setColor ( material faceColor , material eyeColor );
};

class Wasp : public _hierarchyObject{
private:
    WaspHead *_head;
    Cylinder *_body;
    Cylinder *_body2;
    Cone *_stinger;
    SemiSphere *_upStinger;
    Sphere *_wingCircle;
    Cube *_wing;
    Cylinder *_shadow;
    Cylinder *_shot;
    material _first , _second ;

    bool _range;
    Circle *_radius;
    float _rangeRadius;

public:
    Wasp( float width=.5 , float high=2.0 , bool range=true);
    ~Wasp();
    float getRadioCollision();
    void draw( drawMode d );
    void drawRange();
    float getRange();
    void setColor (material firstColor , material secondColor );
};

#endif // WASP_H
