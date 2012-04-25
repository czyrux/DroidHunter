/*************************************************************************/
/*                                                                       */
/*         Copyright (C) Antonio Gutierrez Martinez [2010]               */
/*                                                                       */
/*         License: GPL3                                                 */
/*                                                                       */
/*************************************************************************/
/**
 * @file tree3D.h
 * @brief Implementation of tree in 3D
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

#ifndef TREE3D_H
#define TREE3D_H

#include "objects.h"

class Tree3D {
private:
    static Cylinder _trunk;
    static Cone _leafs;

    _vertex3f _position;
    float _width;
    float _hight;
public:
    Tree3D(_vertex3f posicion, float ancho=2 , float alto=5);
    void parameters(_vertex3f posicion, float ancho=2 , float alto=5);
    float getCollisionRadius();
    _vertex3f getPosition();
    void draw();
};
#endif // TREE3D_H
