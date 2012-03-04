/**
 * @file camera.h
 * @brief Clase Camera. Implementa una camara de opengl.
 * @author Antonio M. Gutierrez Martinez
 * @date
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
    /** @brief La posicion donde se encuentra la camara. Denominado View Reference Point.*/
    _vertex3f _vrp;
    /** @brief Indica el sentido "hacia arriba" en la camara. Denominado View Up */
    _vertex3f _vup;
    /** @brief Indica la orientacion hacia donde mira la camara. Denominada View Plane Normal */
    _vertex3f _vpn;

    /** @brief Angulo de rotacion sobre el eje X en grados*/
    float _alpha;
    /** @brief Angulo de rotacion sobre el eje Y en grados*/
    float _beta;
    /** @brief Angulo de rotacion sobre el eje Z en grados*/
    float _gamma;

    /** @brief Eje Z del sistema de coordenadas de vista */
    _vertex3f _n;
    /** @brief Eje X del sistema de coordenadas de vista */
    _vertex3f _u;
    /** @brief Eje Y del sistema de coordenadas de vista */
    _vertex3f _v;

    /** 
     * @brief Calcula los angulos _alpha, _beta y _gamma, necesarios para realizar la transformacion
     * de vista.
     */
    void viewingTransformation();

    /**
     * @brief Calcula los valores de los vectores _n , _u y _v necesarios para poder calcular los
     * angulos para la transformacion de vista.
     * @param vrp Vector que representa el View Reference Point.
     * @param vpn Vector que representa el View Plane Normal.
     * @param vup Vector que representa el View Up.
     */
    void initialize(_vertex3f vrp,_vertex3f vpn,_vertex3f vup);

    /**
     * @brief Normaliza el angulo pasado como argumento a [0º,360º].
     * @param angle Angulo a normalizar.
     * @return Angulo normalizado.
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
     * @brief Asigna el valor de VRP.
     * @param vrp Vector a asignar
     */
    void setVRP (_vertex3f vrp) {this->initialize(vrp,this->_vpn,this->_vup);}
    /**
     * @brief Asigna el valor de VPN.
     * @param vpn Vector a asignar
     */
    void setVPN (_vertex3f vpn) {this->initialize(this->_vrp,vpn,this->_vup);}
    /**
     * @brief Asigna el valor de VUP.
     * @param vup Vector a asignar
     */
    void setVUP (_vertex3f vup) {this->initialize(this->_vrp,this->_vpn,vup);}
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
    void rotateX ( float r );//inclinacion pitch
    /**
     * @brief Cambia el angulo de rotacion de la camara 'r' unidades. Respecto al eje Y.
     * @param r unidades a rotar
     */
    void rotateY ( float r );//rotacion rotate
    /**
     * @brief Cambia el angulo de viraje de la camara 'r' unidades. Respecto al eje Z.
     * @param r unidades a rotar
     */
    void rotateZ ( float r );//viraje yaw

    /**
     * @brief Traslada la camara 'd' unidades en el eje X
     * @param d cantidad a trasladar
     */
    void translateX ( float d );
    /**
     * @brief Traslada la camara 'd' unidades en el eje Y
     * @param d cantidad a trasladar
     */
    void translateY ( float d );
    /**
     * @brief Traslada la camara 'd' unidades en el eje Z
     * @param d cantidad a trasladar
     */
    void translateZ ( float d );

};
#endif // CAMERA_H
