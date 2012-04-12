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
     * @brief Normalize the angle passed like parameter in the range [0º,360º].
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
     * @brief Constructor por defecto.
     */
    Camera();
	
    /**
     * @brief Constructor con parametros.
     * @param vrp View Reference Point
     * @param vpn View Plane Normal
     * @param vup View Up
     */
    Camera(_vertex3f vrp,_vertex3f vpn,_vertex3f vup);

    /**
     * @brief Obtiene el valor de VRP.
     * @return Vector
     */
    _vertex3f getVRP ();
    /**
     * @brief Obtiene el valor de VPN.
     * @param Vector
     */
    _vertex3f getVPN ();
    /**
     * @brief Obtiene el valor de VUP.
     * @param vrp Vector a asignar
     */
    _vertex3f getVUP ();
    /**
     * @brief Asigna el valor de VRP, VPN y VUP.
     * @param vrp Vector a asignar a VRP
     * @param vpn Vector a asignar a VPN
     * @param vup Vector a asignar a VUP
     */
    void set(_vertex3f vrp,_vertex3f vpn,_vertex3f vup);

    /**
     * @brief Realiza la transformacion de vista.
     */
    void lookat( bool opengl = false );

    /**
     * @brief Cambia el angulo de inclinacion de la camara 'r' unidades. Respecto al eje X.
     * @param r unidades a rotar
     */
    void rotateX ( float rv );//inclinacion pitch
    /**
     * @brief Cambia el angulo de rotacion de la camara 'r' unidades. Respecto al eje Y.
     * @param r unidades a rotar
     */
    void rotateY ( float rh );//rotacion rotate
    /**
     * @brief Cambia el angulo de viraje de la camara 'r' unidades. Respecto al eje Z.
     * @param r unidades a rotar
     */
    void rotateZ ( float rl );//viraje yaw

    /**
     * @brief Traslada la camara 'd' unidades en el eje X
     * @param d cantidad a trasladar
     */
    void translateX ( float dx );
    /**
     * @brief Traslada la camara 'd' unidades en el eje Y
     * @param d cantidad a trasladar
     */
    void translateY ( float dy );
    /**
     * @brief Traslada la camara 'd' unidades en el eje Z
     * @param d cantidad a trasladar
     */
    void translateZ ( float dz );

};
#endif // CAMERA_H
