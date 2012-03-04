#ifndef PLANTAS_H
#define PLANTAS_H

#include "objects.h"

class Plantas {
private:
    int _width;
    float _scale;
    _object3D *planta;
public:
    Plantas( int width , float scale=0.05);
    ~Plantas();
    void draw(drawMode d);
};
#endif // PLANTAS_H
