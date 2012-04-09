/*************************************************************************/
/*                                                                       */
/*         Copyright (C) Antonio Gutierrez Martinez [2010]               */
/*                                                                       */
/*         License: GPL3                                                 */
/*                                                                       */
/*************************************************************************/
/**
 * @file hierarchyObject.h
 * @brief Implementation of class hierarchyObject. Using like interface for
 *      hierarchycal objects
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

#ifndef HIERARCHYOBJECT_H
#define HIERARCHYOBJECT_H

#include "objects.h"

enum stateObject { _MOVING , _SCREAMING , _NORMAL , _TAKE_HAMMER , _HIT_HAMMER,
                   _INANIMATE, _FLYING , _OPEN , _CLOSE , _DEAD, _SHOOTING };

class _hierarchyObject {
protected:
    float _width;
    float _high;
    drawMode _drawMode;
    stateObject _state;
public:

    _hierarchyObject() {
        this->_width = this->_high = 0;
        _drawMode = gouraud;
        this->_state = _INANIMATE;
    }

    ~_hierarchyObject(){}

    void parameters( float width=1.0 , float high=2.0) {
        this->_width = width;
        this->_high = high;
    }

    void setDrawMode ( drawMode d ) { this->_drawMode = d; }
    float getWidth() { return _width;}
    float getHigh() { return _high; }
    void setState( stateObject state ) { this->_state = state; }
    stateObject getState() { return _state;}

    virtual void setColor(vector<material> )=0;
    virtual float getRadioCollision(){ return 0.0;}
    virtual float getRange(){return 0.0;}
    virtual void draw( drawMode d)=0;

};

#endif // HIERARCHYOBJECT_H
