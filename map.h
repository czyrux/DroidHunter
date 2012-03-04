#ifndef MAP_H
#define MAP_H

#include <QImage>
#include <QGLWidget>
#include <cstdlib>
#include <vector>
#include "objects.h"
#include "materials.h"
#include "vertex.h"
#include "random.h"
#include "plantas.h"

class Map {
private:
    GLuint _list;
    QImage _image , _skyImg , _landImg , _earthImg;
    GLuint _sky , _land , _earth ;
    Pyramid *_mountains;
    Cube *_cube;
    vector<_vertex3f> _positionsCube;
    Plantas *_plants;
    vector<_vertex3f> _positionsPlants;

    int _width;
    bool _compiled;

    void compile();
public:
    Map( int width = 100.0 );
    ~Map();
    void draw( drawMode d);

};
#endif // MAP_H
