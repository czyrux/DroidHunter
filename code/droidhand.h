/*************************************************************************/
/*                                                                       */
/*         Copyright (C) Antonio Gutierrez Martinez [2010]               */
/*                                                                       */
/*         License: GPL3                                                 */
/*                                                                       */
/*************************************************************************/
/**
 * @file droid.h
 * @brief Implementation of object droidHand in 3D. Inherits from HierarchycalObject
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

#ifndef DROIDHAND_H
#define DROIDHAND_H

#include "objects.h"
#include "vertex.h"
#include "hierarchyObject.h"

class DroidHand : public _hierarchyObject{
private:
    Cylinder *_hand;
    Sphere *_ball;
    material _color;
public:
    DroidHand(float width=.25 , float high=1.0);
    ~DroidHand();
    void draw( drawMode d );
    float getHight();
    void setColor(vector<material> );
};

#endif // DROIDHAND_H
