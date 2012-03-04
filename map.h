/*************************************************************************/
/*                                                                       */
/*         Copyright (C) Antonio Gutierrez Martinez [2010]               */
/*                                                                       */
/*         License: GPL3                                                 */
/*                                                                       */
/*************************************************************************/
/**
 * @file map.h
 * @brief Implementation of scenario in 3D
 * @author Antonio Gutierrez Martinez
 *
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

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
#include "plants.h"

class Map {
private:
    GLuint _list;
    QImage _image , _skyImg , _landImg , _earthImg;
    GLuint _sky , _land , _earth ;
    Pyramid *_mountains;
    Cube *_cube;
    vector<_vertex3f> _positionsCube;
    Plants *_plants;
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
