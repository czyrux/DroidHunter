#include "camera.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Camera::Camera() {
    //View Reference Point by default
    this->_vrp.x = this->_vrp.y = this->_vrp.z = 0.0;

    //View Plane Normal by default
    //ORIGINAL this->_vpn.x=0;this->_vpn.y=1;this->_vpn.z=1;
    this->_vpn.x=0.0;this->_vpn.y=0.0;this->_vpn.z=1.0;
    this->_vpn.normalize();

    //View Up by default
    this->_vup.x=0.0;this->_vup.y=1.0;this->_vup.z=0.0;
    this->_vup.normalize();

    //Angles by default
    this->_gamma = 0.0;
    this->_beta = 0.0;
    this->_alpha = 0.0;

    this->initialize(this->_vrp,this->_vpn,this->_vup);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Camera::Camera(_vertex3f vrp,_vertex3f vpn,_vertex3f vup) {
    initialize(vrp,vpn,vup);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Camera::viewingTransformation()
{
    _matrix4f Mx, My;
    _vertex3f np,up,upp;

    //Calculating alpha rotating about the X axis
    this->_alpha = (atan2(this->_n.y,this->_n.z) / M_PI) * 180.0;
    this->_alpha = normalizeAngle(this->_alpha);
    Mx.rotate_axis_x(this->_alpha);
    np = this->_n * Mx;
    np.normalize();
    up = this->_u * Mx;
    up.normalize();

    //Calculating beta rotating about the Y axis
    this->_beta = (atan2(np.x,np.z)/M_PI) * 180.0;
    this->_beta = normalizeAngle(this->_beta);
    My.rotate_axis_y(-this->_beta);
    upp = up * My;
    upp.normalize();

    //Calculating gamma rotating about the Z axis
    this->_gamma = (atan2(upp.y,upp.x)/M_PI * 180.0);
    this->_gamma = normalizeAngle(this->_gamma);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Camera::initialize(_vertex3f vrp,_vertex3f vpn,_vertex3f vup) {

    this->_turnsX = this->_turnsY = this->_turnsZ = 0;
    this->_fixed = false;

    this->_vrp=vrp;
    this->_vpn=vpn.normalize();
    this->_vup=vup.normalize();

    //calculing n , u y v
    this->_n = this->_vpn.normalize();
    this->_u = this->_vup.cross_product(this->_n).normalize();
    this->_v = this->_n.cross_product(this->_u).normalize();

    //calculamos la transformacion de vista
    this->viewingTransformation();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Camera::lookat(  )
{
     //gluLookAt (_vrp.x,_vrp.y,_vrp.z,_vpn.x,_vpn.y,_vpn.z,_vup.x,_vup.y,_vup.z);
     //apply the transformation
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
     glRotatef(-_gamma,0,0,1);
     glRotatef(-_beta,0,1,0);
     glRotatef(_alpha,1,0,0);
     glTranslatef(-this->_vrp.x,-this->_vrp.y,-this->_vrp.z);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Camera::set(_vertex3f vrp, _vertex3f vpn, _vertex3f vup) {
    this->initialize(vrp,vpn,vup);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

_vertex3f Camera::getVRP () { return this->_vrp; }
_vertex3f Camera::getVPN () { return this->_vpn; }
_vertex3f Camera::getVUP () { return this->_vup; }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

float Camera::normalizeAngle(float angle)
{
     while (angle>360)
         angle-=360;
     while (angle<0)
         angle+=360;

     return angle;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Camera::translateX(float dx)
{
    if (!_fixed) {
        //_vertex3f vrp__ = _vrp;
        this->_vrp += this->_u * dx;
        //if (this->_vrp.y < LIMIT_DOWN ) this->_vrp = vrp__; //para no salga por debajo del mapa
    }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Camera::translateY(float dy)
{
    if (!_fixed) {
        //_vertex3f vrp__ = _vrp;
        this->_vrp += this->_v * dy;
        //if (this->_vrp.y < LIMIT_DOWN ) this->_vrp = vrp__; //para no salga por debajo del mapa
    }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Camera::translateZ(float dz)
{
    if (!_fixed) {
        ///_vertex3f vrp__ = _vrp;
        this->_vrp -= this->_n * dz;
        //if (this->_vrp.y < LIMIT_DOWN ) this->_vrp = vrp__; //para no salga por debajo del mapa
    }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Camera::rotateX(float rv)
{
    if ( !_fixed && ((rv > 0 && _turnsX+1 < LIMIT_TURN) || (rv < 0 && _turnsX-1 > -LIMIT_TURN)) ){
        (rv < 0 )?_turnsX--:_turnsX++; //actualizamos el numero de giros
        float angle = rv*M_PI/180;
        _vertex3f t = _n;

        // Rotate 'n' y 'v'
        this->_n = t*cos(angle) - this->_v*sin(angle);
        this->_v = t*sin(angle) + this->_v*cos(angle);

        //Calculate the viewing transformation
        this->viewingTransformation();
    }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Camera::rotateY(float rh)
{
    if ( !_fixed && ((rh > 0 && _turnsY+1 < LIMIT_TURN) || (rh < 0 && _turnsY-1 > -LIMIT_TURN)) ){
        (rh < 0 )?_turnsY--:_turnsY++; //actualizamos el numero de giros

        float angle = rh*M_PI/180;
        _vertex3f t = _u;

        // Rotate 'u' y 'n'
        this->_u = t*cos(angle) - this->_n*sin(angle);
        this->_n = t*sin(angle) + this->_n*cos(angle);

        //Calculate the viewing transformation
        this->viewingTransformation();
    }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Camera::rotateZ(float rl)
{
    if (!_fixed) {
        float angle = rl*M_PI/180;
        _vertex3f t = _u;

        // Rotating 'u' y 'v'
        this->_u = t*cos(angle) - this->_v*sin(angle);
        this->_v = t*sin(angle) + this->_v*cos(angle);

        //Calculate the viewing transformation
        this->viewingTransformation();
    }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Camera::fixedCamera( bool fixed ) {
    this->_fixed = fixed;
}
