#ifndef HUEVO_H
#define HUEVO_H

#include "objects.h"

class Huevo {
private:
    static Sphere objeto;
    float radio;
    _vertex3f posicion;
public:
    Huevo();
    Huevo (_vertex3f posicion , float radio=2 );
    void parameters(_vertex3f posicion , float radio=2);
    void draw();
    _vertex3f getPosicion();
    float getRadioColision();
};

#endif // HUEVO_H
