#ifndef DROIDHAND_H
#define DROIDHAND_H

#include "objects.h"
#include "vertex.h"
#include "hierarchyObject.h"

class DroidHand : public _hierarchyObject{
private:
    Cylinder *_hand;
    Sphere *_ball;
    material _color;
public:
    DroidHand(float width=.25 , float high=1.0);
    ~DroidHand();
    void draw( drawMode d );
    float getHight();
    void setColor ( material color );
};

#endif // DROIDHAND_H
