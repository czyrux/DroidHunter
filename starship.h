#ifndef STARSHIP_H
#define STARSHIP_H

#include "objects.h"
#include "hierarchyObject.h"
#include "circle.h"
#include <vector>


class Starship : public _hierarchyObject
{
private:
    SemiSphere *_hood;
    Sphere *_body;
    Cone *_legs;
    Cylinder *_lights;

    bool _range;
    Circle *_radius;
    float _rangeRadius;

    material _principal , _secondary ;
public:
    Starship( float width=10 , float high=10 , bool = true);
    ~Starship();
    void draw( drawMode d );
    void drawRange();
    float getRange();
    void setColor( material _principal , material _secondary );

};

#endif // STARSHIP_H
