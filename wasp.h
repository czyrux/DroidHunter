/*************************************************************************/
/*                                                                       */
/*         Copyright (C) Antonio Gutierrez Martinez [2010]               */
/*                                                                       */
/*         License: GPL3                                                 */
/*                                                                       */
/*************************************************************************/
/**
 * @file wasp.h
 * @brief Implementation of object wasp in 3D. Inherits from HierarchycalObject
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

#ifndef WASP_H
#define WASP_H

#include "objects.h"
#include "vertex.h"
#include "circle.h"
#include "hierarchyObject.h"
#include "droidHead.h"


//CLASS WASP

class Wasp : public _hierarchyObject{
private:
    DroidHead *_head;
    Cylinder *_body;
    Cylinder *_body2;
    Cone *_stinger;
    SemiSphere *_upStinger;
    Sphere *_wingCircle;
    Cube *_wing;
    Cylinder *_shadow;
    Cylinder *_shot;
    material _first , _second ;

    bool _range;
    Circle *_radius;
    float _rangeRadius;

public:
    Wasp( float width=.5 , float high=2.0 , bool range=true);
    ~Wasp();
    float getRadioCollision();
    void draw( drawMode d );
    void drawRange();
    float getRange();
    void setColor(vector<material> m);
};

#endif // WASP_H
