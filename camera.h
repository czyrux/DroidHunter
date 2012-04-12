/*************************************************************************/
/*                                                                       */
/*         Copyright (C) Antonio Gutierrez Martinez [2010]               */
/*                                                                       */
/*         License: GPL3                                                 */
/*                                                                       */
/*************************************************************************/
/**
 * @file camera.h
 * @brief Implementation of camera in OpenGL
 * @author Antonio Gutierrez Martinez
 * @date April 2012
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

#ifndef CAMERA_H
#define CAMERA_H

#include <vertex.h>
#include <matrix.h>
#include <gl.h>
#include <glu.h>

#define LIMIT_DOWN 15
#define LIMIT_TURN 8

class Camera {
private:
    /** @brief Indicates the position of camera. Called View Reference Point (VRP)*/
    _vertex3f _vrp;
    /** @brief Indicates the direction "up" on camera. Called View Up (VUP) */
    _vertex3f _vup;
    /** @brief Indicates the direction where the camera looks. Called View Plane Normal(VPN) */
    _vertex3f _vpn;

    /** @brief Angle of rotation about the X axis in degrees */
    float _alpha;
    /** @brief Angle of rotation about the Y axis in degrees */
    float _beta;
    /** @brief Angle of rotation about the Z axis in degrees */
    float _gamma;

    /** @brief Z axis of the coordinate system of view */
    _vertex3f _n;
    /** @brief X axis of the coordinate system of view */
    _vertex3f _u;
    /** @brief Y axis of the coordinate system of view */
    _vertex3f _v;

    /** 
     * @brief Calculates the angles _alpha, _beta and gamma, necessary for the transformation
     * of view.
     */
    void viewingTransformation();

    /**
     * @brief Calculates the value of the vectors _n, _u and _v, used to calculate the angles of the
     * transformation of view, and then, call the method @ref viewingTransformation.
     * @param vrp vector that represent the View Reference Point.
     * @param vpn vector that represent the View Plane Normal.
     * @param vup vector that represent the el View Up.
     */
    void initialize(_vertex3f vrp,_vertex3f vpn,_vertex3f vup);

    /**
     * @brief Normalize the angle in the range [0º,360º].
     * @param angle to normalize.
     * @return angle normalized.
     */
    float normalizeAngle ( float angle );

    int _turnsX;
    int _turnsY;
    int _turnsZ;

    bool _freeMoving;

public:

    /**
     * @brief Constructor by default.
     */
    Camera();
	
    /**
     * @brief Constructor with parameters.
     * @param vrp View Reference Point
     * @param vpn View Plane Normal
     * @param vup View Up
     */
    Camera(_vertex3f vrp,_vertex3f vpn,_vertex3f vup);

    /**
     * @brief Get the value of VRP.
     * @return Vector
     */
    _vertex3f getVRP ();
    /**
     * @brief Get the value of VPN.
     * @return Vector
     */
    _vertex3f getVPN ();
    /**
     * @brief Get the value of VUP.
     * @param Vector
     */
    _vertex3f getVUP ();

    /**
     * @brief Set the value of VRP, VPN y VUP.
     * @param Value of VRP
     * @param Value of VPN
     * @param Value of VUP
     */
    void set(_vertex3f vrp,_vertex3f vpn,_vertex3f vup);

    /**
     * @brief Define a viewing transformation.
     */
    void lookat();

    /**
     * @brief Change the angle of inclination of the camera 'rv' units about the X axis.
     * @param rv units to rotate
     */
    void rotateX ( float rv );//inclinacion pitch
    /**
     * @brief Change the angle of rotation of the camera 'rh' units about the Y axis.
     * @param rh units to rotate
     */
    void rotateY ( float rh );//rotacion rotate
    /**
     * @brief Change the angle of turn of the camera 'rl' units about the Z axis.
     * @param rl units to rotate
     */
    void rotateZ ( float rl );//viraje yaw

    /**
     * @brief Translade the camera 'dx' units about the X axis.
     * @param dx units to translate
     */
    void translateX ( float dx );
    /**
     * @brief Translade the camera 'dy' units about the Y axis.
     * @param dy units to translate
     */
    void translateY ( float dy );
    /**
     * @brief Translade the camera 'dz' units about the Z axis.
     * @param dz units to translate
     */
    void translateZ ( float dz );

    /**
      * @brief If 'b' is true not allow the camera to turn. If 'b' is true
      * the turning is allow.
      */
    void fixedCamera( bool b );

};
#endif // CAMERA_H
