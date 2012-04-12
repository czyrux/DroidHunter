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

/**
  * @brief Define the possible states of the object. Using to modelate the behaviour and
  * look of object.
  */
enum stateObject { _MOVING , _SCREAMING , _NORMAL , _TAKE_HAMMER , _HIT_HAMMER,
                   _INANIMATE, _FLYING , _OPEN , _CLOSE , _DEAD, _SHOOTING };

/**
  * @brief Class hierarchyObject, using to define a form for all of the hierarchycal objects,
  * that's mean, object make using differents objects3D
  */
class _hierarchyObject {
protected:
    /** @brief Scale value for the width */
    float _width;
    /** @brief Scale value for the high*/
    float _high;
    /** @brief DrawMode of object */
    drawMode _drawMode;
    /** @brief Holds the state of the object */
    stateObject _state;
public:

    /**
      * @brief Constructor of class
      */
    _hierarchyObject() {
        this->_width = this->_high = 0;
        _drawMode = gouraud;
        this->_state = _INANIMATE;
    }

    /**
      * @brief Destructor of class. Empty
      */
    ~_hierarchyObject(){}

    /**
      * @brief Set the width and high of object
      * @param value of width. Default 1.0
      * @param value of high. Default 2.0
      */
    void parameters( float width=1.0 , float high=2.0) {
        this->_width = width;
        this->_high = high;
    }

    /**
      * @brief Set the drawMode for the object
      * @param drawMode
      */
    void setDrawMode ( drawMode d ) { this->_drawMode = d; }

    /**
      * @brief Get the width of object
      * @return value of width
      */
    float getWidth() { return _width;}

    /**
      * @brief Get the high of object
      * @return value of high
      */
    float getHigh() { return _high; }

    /**
      * @brief
      * @param
      * @return
      */
    void setState( stateObject state ) { this->_state = state; }

    /**
      * @brief
      * @param
      * @return
      */
    stateObject getState() { return _state;}

    /**
      * @brief
      * @param
      * @return
      */
    virtual void setColor(vector<material> )=0;

    /**
      * @brief
      * @param
      * @return
      */
    virtual float getRadioCollision(){ return 0.0;}

    /**
      * @brief
      * @param
      * @return
      */
    virtual float getRange(){return 0.0;}

    /**
      * @brief
      * @param
      * @return
      */
    virtual void draw( drawMode d)=0;

};

#endif // HIERARCHYOBJECT_H
