/*************************************************************************/
/*                                                                       */
/*         Copyright (C) Antonio Gutierrez Martinez [2010]               */
/*                                                                       */
/*         License: GPL3                                                 */
/*                                                                       */
/*************************************************************************/
/**
 * @file circle.h
 * @brief Implementation of circle in 2D
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
