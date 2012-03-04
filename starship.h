/*************************************************************************/
/*                                                                       */
/*         Copyright (C) Antonio Gutierrez Martinez [2010]               */
/*                                                                       */
/*         License: GPL3                                                 */
/*                                                                       */
/*************************************************************************/
/**
 * @file starship.h
 * @brief Implementation of starship in 3D
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
