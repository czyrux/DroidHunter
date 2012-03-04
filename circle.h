#ifndef CIRCLE_H
#define CIRCLE_H

#include <vector>
#include <cmath>
#include <gl.h>
#include "vertex.h"

using namespace std;

class Circle {
public:
    Circle( float radius=1.0 , int points=20 , float line=2 , bool _continue=true );
    float getRadius();
    void draw();
    void setColor( _vertex3f rgb );
    void setRadius( float radius);
private:
    vector<_vertex3f> _vertices;
    _vertex3f _colorRGB;
    float _radius;
    float _line;
    int _points;
    bool _continue;
    void create_object();

};

#endif // CIRCLE_H
