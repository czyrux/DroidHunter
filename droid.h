/*************************************************************************/
/*                                                                       */
/*         Copyright (C) Antonio Gutierrez Martinez [2010]               */
/*                                                                       */
/*         License: GPL3                                                 */
/*                                                                       */
/*************************************************************************/
/**
 * @file droid.h
 * @brief Implementation of object droid in 3D. Inherits from HierarchycalObject
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

#ifndef DROID_H
#define DROID_H

#include "objects.h"
#include "vertex.h"
#include "circle.h"
#include "hierarchyObject.h"

//CLASS DROIDHEAD
class DroidHead {
private:
    Cylinder *_antenna;
    Sphere *_eye;
    SemiSphere *_face;
    material _eyeColor , _faceColor;
    float _width;
    float _high;
public:
    DroidHead( float width=1.0 , float hight=1.0 );
    ~DroidHead();
    void draw( drawMode d );
    void setColor ( material faceColor , material eyeColor );
};

//CLASS HAND
class DroidHand {
private:
    Cylinder *_hand;
    Sphere *_ball;
    material _color;
    float _width;
    float _high;
public:
    DroidHand(float width=.25 , float high=1.0);
    ~DroidHand();
    void draw( drawMode d );
    float getHight();
    void setColor ( material color );
};

//CLASS DROID
class Droid: public _hierarchyObject {
private:
    DroidHead *_head;
    Cylinder *_body;
    DroidHand *_hand;
    material _color;
    Cylinder *_hammer;
    Circle *_radius;
    bool _range;
    float _rangeRadius;
public:
    Droid( float width=.5, float high=2.0 , bool range=true );
    ~Droid();
    float getRadioCollision();
    void draw( drawMode d );
    float getRange();
    void setColor (material colorBody , material colorEyes );
};

#endif // DROID_H
