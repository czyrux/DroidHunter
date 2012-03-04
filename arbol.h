#ifndef ARBOL_H
#define ARBOL_H

#include "objects.h"

class Arbol {
private:
    static Cylinder _trunk;
    static Cone _leafs;

    _vertex3f _position;
    float _width;
    float _hight;
public:
    Arbol(_vertex3f posicion, float ancho=2 , float alto=5);
    void parameters(_vertex3f posicion, float ancho=2 , float alto=5);
    float getCollisionRadius();
    _vertex3f getPosition();
    void draw();
};
#endif // ARBOL_H
