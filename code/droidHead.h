/*************************************************************************/
/*                                                                       */
/*         Copyright (C) Antonio Gutierrez Martinez [2010]               */
/*                                                                       */
/*         License: GPL3                                                 */
/*                                                                       */
/*************************************************************************/
/**
 * @file droidHead.h
 * @brief Implementation of object headDroid in 3D. Inherits from HierarchycalObject
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

#ifndef DROIDHEAD_H
#define DROIDHEAD_H

#include "objects.h"
#include "vertex.h"
#include "hierarchyObject.h"

//CLASS DROIDHEAD
class DroidHead : public _hierarchyObject {
private:
    Cylinder *_antenna;
    Sphere *_eye;
    SemiSphere *_face;
    material _eyeColor , _faceColor;
public:
    DroidHead( float width=1.0 , float hight=1.0 );
    ~DroidHead();
    void draw( drawMode d );
    void setColor(vector<material> );
};

#endif // DROIDHEAD_H
