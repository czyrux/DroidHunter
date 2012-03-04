/*************************************************************************/
/*                                                                       */
/*         Copyright (C) Antonio Gutierrez Martinez [2010]               */
/*                                                                       */
/*         License: GPL3                                                 */
/*                                                                       */
/*************************************************************************/
/**
 * @file ball_monster.h
 * @brief Implementation of character ball_monster in 3D
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

#ifndef BALL_MONSTER_H
#define BALL_MONSTER_H

#include "objects.h"
#include "vertex.h"
#include "hierarchyObject.h"

//CLASS Ball

class Ball: public _hierarchyObject {
private:
    Sphere *_body;
    SemiSphere *_tooth;
    material _eyeColor , _faceColor , _toothColor;
public:
    Ball( float width=1.0 );
    ~Ball();
    void draw( drawMode d );
    float getRadioCollision();
    void changeState ( );
    void setColor (material colorBody , material colorTooth );
};

#endif // BALL_MONSTER_H
