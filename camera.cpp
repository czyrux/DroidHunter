#include "camera.h"

/**********************************************************************/

Camera::Camera() {
    this->_vrp.x=0;this->_vrp.y=0;this->_vrp.z=0;
    this->_vpn.x=0;this->_vpn.y=1;this->_vpn.z=1;
    this->_vup.x=0;this->_vup.y=1;this->_vup.z=0;

    this->_gamma = 0;
    this->_beta = 0;
    this->_alpha = 0;

    this->initialize(this->_vrp,this->_vpn,this->_vup);
}

/**********************************************************************/

Camera::Camera(_vertex3f vrp,_vertex3f vpn,_vertex3f vup) {
    initialize(vrp,vpn,vup);
}

/**********************************************************************/

void Camera::viewingTransformation()
{
    _matrix4f mat;
    _vertex3f np,up,upp;

    //primero calculamos la rotacion de alfa respecto al eje X
    _alpha=atan2(_n.y,_n.z)*180/M_PI;
    np=_n*mat.rotate_axis_x(_alpha);
    up=_u*mat.rotate_axis_x(_alpha);

    //calculamos la rotacion beta respecto del eje Y
    _beta=atan2(_n.x,np.z)*180/M_PI;
    upp=up*mat.rotate_axis_y(-_beta);

    //calculamos la rotacion gamma respecto del eje z
    _gamma=atan2(upp.y,upp.x)*180/M_PI;
}

/**********************************************************************/

void Camera::initialize(_vertex3f vrp,_vertex3f vpn,_vertex3f vup) {

    this->_turnsX = this->_turnsY = this->_turnsZ = 0;
    this->_freeMoving = false;

    this->_vrp=vrp;
    this->_vpn=vpn.normalize();
    this->_vup=vup.normalize();

    //calculamos n , u y v
    _n=_vrp-_vpn;
    _u=_vup.cross_product(_n);
    _v=_n.cross_product(_u);

    //normalizamos
    _n.normalize();
    _u.normalize();
    _v.normalize();

    //calculamos la transformacion de vista
    this->viewingTransformation();
}

/**********************************************************************/

void Camera::lookat( bool opengl )
{
    if ( opengl ) {
        gluLookAt (_vrp.x,_vrp.y,_vrp.z,_vpn.x,_vpn.y,_vpn.z,_vup.x,_vup.y,_vup.z);
    }else{
     //aplicamos la transformacion
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
     glRotatef(-_gamma,0,0,1);
     glRotatef(-_beta,0,1,0);
     glRotatef(_alpha,1,0,0);
     glTranslatef(-this->_vrp.x,-this->_vrp.y,-this->_vrp.z);
    }
}

/**********************************************************************/

void Camera::set(_vertex3f vrp, _vertex3f vpn, _vertex3f vup)
{
    this->initialize(vrp,vpn,vup);
}

/*
void Camera::setVRP (_vertex3f vrp) { this->initialize(vrp,this->_vpn,this->_vup); }

void Camera::setVPN (_vertex3f vpn){ this->initialize(this->_vrp,vpn,this->_vup); }

void Camera::setVUP (_vertex3f vup) { this->initialize(this->_vrp,this->_vpn,vup); }
*/
_vertex3f Camera::getVRP () { return this->_vrp; }

_vertex3f Camera::getVPN () { return this->_vpn; }

_vertex3f Camera::getVUP () { return this->_vup; }

/**********************************************************************/

float Camera::normalizeAngle(float angle)
{
     while (angle>360)
         angle-=360;
     while (angle<0)
         angle+=360;

     return angle;
}

/**********************************************************************/

void Camera::translateX(float d)
{
    _vertex3f vrp__ = _vrp;
    this->_vrp += this->_u * d;
    if (this->_vrp.y < LIMIT_DOWN ) this->_vrp = vrp__; //para no salga por debajo del mapa
}

/**********************************************************************/

void Camera::translateY(float d)
{
    _vertex3f vrp__ = _vrp;
    this->_vrp += this->_v * d;
    if (this->_vrp.y < LIMIT_DOWN ) this->_vrp = vrp__; //para no salga por debajo del mapa
}


/**********************************************************************/

void Camera::translateZ(float d)
{
    _vertex3f vrp__ = _vrp;
    this->_vrp -= this->_n * d;
    if (this->_vrp.y < LIMIT_DOWN ) this->_vrp = vrp__; //para no salga por debajo del mapa
}
/**********************************************************************/

void Camera::rotateX(float rv)
{
    if ( !_freeMoving && ((rv > 0 && _turnsX+1 < LIMIT_TURN) || (rv < 0 && _turnsX-1 > -LIMIT_TURN)) ){
        (rv < 0 )?_turnsX--:_turnsX++; //actualizamos el numero de giros
        float angle = rv*M_PI/180;
        _vertex3f t = _n;

        // Rotamos 'n' y 'v'
        this->_n = t*cos(angle) - this->_v*sin(angle);
        this->_v = t*sin(angle) + this->_v*cos(angle);

        //calculamos la transformacion de vista
        this->viewingTransformation();
    }
}

/**********************************************************************/

void Camera::rotateY(float rh)
{
    if ( !_freeMoving && ((rh > 0 && _turnsY+1 < LIMIT_TURN) || (rh < 0 && _turnsY-1 > -LIMIT_TURN)) ){
        (rh < 0 )?_turnsY--:_turnsY++; //actualizamos el numero de giros

        float angle = rh*M_PI/180;
        _vertex3f t = _u;

        // Rotamos 'u' y 'n'
        this->_u = t*cos(angle) - this->_n*sin(angle);
        this->_n = t*sin(angle) + this->_n*cos(angle);

        //calculamos la transformacion de vista
        this->viewingTransformation();
    }
}

/**********************************************************************/

void Camera::rotateZ(float rl)
{
    float angle = rl*M_PI/180;
    _vertex3f t = _u;

    // Rotamos 'u' y 'v'
    this->_u = t*cos(angle) - this->_v*sin(angle);
    this->_v = t*sin(angle) + this->_v*cos(angle);

    //calculamos la transformacion de vista
    this->viewingTransformation();
}

/**********************************************************************/
