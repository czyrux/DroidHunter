#include "circle.h"

Circle::Circle( float radius, int points , float line , bool continu ) {
    this->_radius = radius;
    this->_points = points;
    this->_line = line;
    this->_continue = continu;

    create_object();
}

void Circle::create_object() {
    _vertices.clear();

    _vertex3f aux;
    //Creamos circulo
    for ( int i=0 ; i<this->_points ; i++) {
        aux.x=this->_radius*sin( (2*PI*i)/this->_points);
        aux.y=0.2;
        aux.z=this->_radius*cos( (2*PI*i)/this->_points);
        _vertices.push_back(aux);
    }
}

float Circle::getRadius() {
    return this->_radius;
}

void Circle::setRadius(float radius){
    this->_radius = radius;
    create_object();
}

void Circle::draw() {

    glLineWidth(_line);
    glBegin(GL_LINES);
    glColor3f(_colorRGB.r,_colorRGB.g,_colorRGB.b);
    for (int i=0 ; i<_vertices.size() ; i++ ) {
        if ( (i%2==0 && !_continue) || _continue ) { //si es discontinuo, solo pintamos las pares
            glVertex3f(_vertices[i].x,_vertices[i].y,_vertices[i].z);
            if (i!=_vertices.size()-1) {
                glVertex3f(_vertices[i+1].x,_vertices[i+1].y,_vertices[i+1].z);
            }else
                glVertex3f(_vertices[0].x,_vertices[0].y,_vertices[0].z);
        }
    }
    glEnd();
    glLineWidth(1);
}

void Circle::setColor( _vertex3f rgb ) {
    this->_colorRGB = rgb;
}
