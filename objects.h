/*************************************************************************/
/*                                                                       */
/*         Copyright (C) Antonio Gutierrez Martinez [2010]               */
/*                                                                       */
/*         License: GPL3                                                 */
/*                                                                       */
/*************************************************************************/
/**
 * @file objects.h
 * @brief Define the class object3D, such that the follows objects 3D:
 *      objectPly3D, Sphere, SemiSphere, Pyramid, Triangle, Square
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

#ifndef OBJECTS_H
#define OBJECTS_H

#include <vector>
#include <cmath>
#include <gl.h>
#include <QImage>
#include <QGLWidget>
#include "vertex.h"
#include "file_ply_stl.h"
#include "materials.h"

using namespace std;

/**
 * @brief Estructura usada para definir una cara.
 */
struct face {
    int v1;
    int v2;
    int v3;
};

/**
 * @brief Distintos modos de dibujado
 */
enum drawMode { points , lines , rgb ,  chess , plane , gouraud , texture };

/*************************************************/
//CLASS _OBJECT3D
/*************************************************/
/**
 * @brief Clase abstracta objeto 3D.
 */
class _object3D {
protected:
    float _Ymin;
    float _Ymax;
    float _Xmax;
    float _Xmin;
    float _Zmax;
    float _Zmin;
    vector<_vertex3f> _vertices;
    vector<face> _faces;
    vector<_vertex3f> _normal_vertices;
    vector<_vertex3f> _normal_faces;
    _vertex3f _colorRGB;
    material _colors;
    QImage _image;
    GLuint _texture ;
    GLuint _list[6] ;
    bool _compiled;

    void createNormals();
    void calculateBox();
    void compile();

    void drawPoints();
    void drawLines();
    void drawRGB();
    void drawChess();
    void drawPlane();
    void drawGouraud();
    void drawTexture();

    virtual void createObject()=0;

public:
    _object3D();
    ~_object3D();

    void setColor ( const _vertex3f &c);
    _vertex3f getColor ();
    void setVertices( const vector<_vertex3f> &v);
    vector<_vertex3f> getVertices();
    void setFaces( const vector<face> &v);
    vector<face> getFaces();
    void setMaterial( const material &);
    void setTexture ( const char * );

    void draw ( drawMode d );

    float collisionRadius();
    float Ymin();
    float Ymax();
    float Xmax();
    float Xmin();
    float Zmax();
    float Zmin();
};

/*************************************************/
//CLASS OBJECTPLY
/*************************************************/
/**
 * @brief Implementacion de la clase objeto Ply. Clase usada para cargar un objeto
 * 3D en formato .ply
 */
class Object3DPly : public _object3D {
    char *_path;
    void createObject();
public:
    Object3DPly( char *);
};

/*************************************************/
//CLASS CONE
/*************************************************/
/**
 * @brief Clase que implementa un cono en 3D.
 */
class Cone: public _object3D {
private:
    float _radius;
    float _high;
    int _numFaces;
    void createObject();
public:
    Cone(float radius=1.0 ,float high=1.0 ,int faces=20);
    void Parameters(float radius=1.0 ,float high=1.0 ,int faces=10);
    float getHight();
    float getRadius();
    int getNumFaces();
};

/*************************************************/
//CLASS CUBE
/*************************************************/
/**
 * @brief Clase que implementa un cubo en 3D.
 */
class Cube: public _object3D {
private:
    float _side;
    void createObject();
public:
    Cube(float side=1.0);
    void Parameters(float side=1.0);
    float getSide();
};

/*************************************************/
//CLASS Cylinder
/*************************************************/
/**
 * @brief Clase que implementa un cilindro en 3D.
 */
class Cylinder: public _object3D {
private:
    float _radius;
    float _high;
    int _numFaces;
    void createObject();

public:
    Cylinder(float radius=1.0, float high=1.0 , int faces=20);
    void Parameters(float radius=1.0, float high=1.0 , int faces=20);
    float getHigh();
    float getRadius();
    int getNumFaces();
};

/*************************************************/
//CLASS SPHERE
/*************************************************/
/**
 * @brief Clase que implementa una esfera en 3D.
 */
class Sphere: public _object3D {
private:
    float _radius;
    int _numFaces;
    void createObject();
public:
    Sphere(float radius=1.0, int faces=20);
    void Parameters(float radius=1.0 , int faces=20 );
    float getRadius();
};

/*************************************************/
//CLASS SEMISPHERE
/*************************************************/
/**
 * @brief Clase que implementa una semiesfera en 3D.
 */
class SemiSphere: public _object3D {
private:
    float _radius;
    int _numFaces;
    void createObject();
public:
    SemiSphere(float radius=1.0, int faces=20);
    void Parameters(float radius=1.0 , int faces=20 );
    float getRadius();
};

/*************************************************/
//CLASS PYRAMID
/*************************************************/
/**
 * @brief Clase que implementa una piramide en 3D.
 */
class Pyramid: public _object3D {
private:
    float _high;
    float _side;
    void createObject();
public:
    Pyramid(float hight=1.0, float side=1.0) ;
    void Parameters(float hight=1.0, float side=1.0 );
    float getSide();
    float getHigh();
};

#endif // OBJECTS_H
