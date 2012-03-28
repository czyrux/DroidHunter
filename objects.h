/*************************************************************************/
/*                                                                       */
/*         Copyright (C) Antonio Gutierrez Martinez [2010]               */
/*                                                                       */
/*         License: GPL3                                                 */
/*                                                                       */
/*************************************************************************/
/**
 * @file objects.h
 * @brief Define the abstract class object3D, such that the follows objects 3D:
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

//using namespace std;

/**
 * @brief Structure used to define a face.
 */
struct face {
    int v1;
    int v2;
    int v3;
};

/**
 * @brief Define the different ways for draw an object.
 */
enum drawMode { points , lines , rgb ,  chess , plane , gouraud , texture };

/*************************************************/
//CLASS _OBJECT3D
/*************************************************/
/**
 * @brief Abstract class of an object 3D that define the main characteristics and
 * behaviour of an object 3D.
 */
class _object3D
{
protected:
    /** @brief Holds the minimum value of coordenate Y in object */
    float _Ymin;
    /** @brief Holds the maximum value of coordenate Y in object */
    float _Ymax;
    /** @brief Holds the maximum value of coordenate X in object */
    float _Xmax;
    /** @brief Holds the minimum value of coordenate X in object */
    float _Xmin;
    /** @brief Holds the maximum value of coordenate Z in object */
    float _Zmax;
    /** @brief Holds the minimum value of coordenate Z in object */
    float _Zmin;

    /** @brief Array that holds the vertices of object 3D */
    vector<_vertex3f> _vertices;
    /** @brief Array that holds the face of object */
    vector<face> _faces;
    /** @brief Array that holds the normal vector of a vertex using for intensity of light */
    vector<_vertex3f> _normal_vertices;
    /** @brief Array that holds the normal vector of a face using for intensity of light*/
    vector<_vertex3f> _normal_faces;

    /** @brief Holds the RGB color of object */
    _vertex3f _colorRGB;
    /** @brief Holds the material color of object */
    material _colors;
   /** @brief Object of class Qimage using for store the image for a texture */
    QImage _image;
    /** @brief Holds the value of the texture previously charged */
    GLuint _texture ;

    /** @brief Array that holds the display lists with the differences types of show the object */
    GLuint _list[6] ;
    /** @brief Boolean value used to know if the display lists are charged or not */
    bool _compiled;

    /**
      * @brief Calculate the normals of vertex and faces.
      */
    void createNormals();
    /**
      * @brief Calculate value of box that involve the object.
      */
    void calculateBox();
    /**
      * @brief Compile the display lists.
      */
    void compile();

    /**
      * @brief Draw object in mode points.
      */
    void drawPoints();
    /**
      * @brief Draw object in mode lines.
      */
    void drawLines();
    /**
      * @brief Draw object using RGB color.
      */
    void drawRGB();
    /**
      * @brief Draw object in mode chess.
      */
    void drawChess();
    /**
      * @brief Draw object in mode plane.
      */
    void drawPlane();
    /**
      * @brief Draw object in mode gouraud.
      */
    void drawGouraud();
    /**
      * @brief Draw object with texture.
      */
    void drawTexture();

    /**
      * @brief Abstract method who creates the object 3D.
      */
    virtual void createObject()=0;

public:
    /**
      * @brief Constructor of class
      */
    _object3D();
    /**
      * @brief Destructor of class
      */
    ~_object3D();

    /**
      * @brief Set color RGB for object
      * @param c Vertex that define the color
      */
    void setColor ( const _vertex3f &c);
    /**
      * @brief Get color RGB.
      * @return vertex that holds the color.
      */
    _vertex3f getColor ();
    /**
      * @brief Set vertices to object
      * @param v array of _vertex3f
      */
    void setVertices( const vector<_vertex3f> &v);
    /**
      * @brief Get vertices of object.
      * @return array of _vertex3f that holds the vertices.
      */
    vector<_vertex3f> getVertices();
    /**
      * @brief Set faces of object.
      * @param v array of faces.
      */
    void setFaces( const vector<face> &v);
    /**
      * @brief Get faces of object.
      * @return array that holds the faces of object.
      */
    vector<face> getFaces();
    /**
      * @brief Set material color to the object.
      * @param m material that holds the color.
      */
    void setMaterial( const material &);
    /**
      * @brief Set texture to the object.
      * @param file path with the texture.
      */
    void setTexture ( const char * );

    /**
      * @brief Draw the object depending of the drawMode passed in the function.
      * @param d drawMode
      */
    void draw ( drawMode d );

    /**
      * @brief Get the collision radious of the object.
      * @return the radious.
      */
    float collisionRadius();
    /**
      * @brief
      * @return
      */
    float Ymin();
    /**
      * @brief
      * @return
      */
    float Ymax();
    /**
      * @brief
      * @return
      */
    float Xmax();
    /**
      * @brief
      * @return
      */
    float Xmin();
    /**
      * @brief
      * @return
      */
    float Zmax();
    /**
      * @brief
      * @param
      * @return
      */
    float Zmin();
};

/*************************************************/
//CLASS OBJECTPLY
/*************************************************/
/**
 * @brief Implementacion de la clase objeto Ply. Clase usada para cargar un objeto
 * 3D en formato .ply
 */
class Object3DPly : public _object3D
{
private:
    /** @brief  */
    char *_path;

    /**
      * @brief
      * @param
      * @return
      */
    void createObject();

public:
    /**
      * @brief
      * @param
      * @return
      */
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
    /** @brief  */
    float _radius;
    /** @brief  */
    float _high;
    /** @brief  */
    int _numFaces;

    /**
      * @brief
      * @param
      * @return
      */
    void createObject();

public:
    /**
      * @brief
      * @param
      * @return
      */
    Cone(float radius=1.0 ,float high=1.0 ,int faces=20);
    /**
      * @brief
      * @param
      * @return
      */
    void Parameters(float radius=1.0 ,float high=1.0 ,int faces=10);
    /**
      * @brief
      * @param
      * @return
      */
    float getHight();
    /**
      * @brief
      * @param
      * @return
      */
    float getRadius();
    /**
      * @brief
      * @param
      * @return
      */
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
    /** @brief  */
    float _side;

    /**
      * @brief
      * @param
      * @return
      */
    void createObject();

public:
    /**
      * @brief
      * @param
      * @return
      */
    Cube(float side=1.0);
    /**
      * @brief
      * @param
      * @return
      */
    void Parameters(float side=1.0);
    /**
      * @brief
      * @param
      * @return
      */
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
    /** @brief  */
    float _radius;
    /** @brief  */
    float _high;
    /** @brief  */
    int _numFaces;

    /**
      * @brief
      * @param
      * @return
      */
    void createObject();

public:
    /**
      * @brief
      * @param
      * @return
      */
    Cylinder(float radius=1.0, float high=1.0 , int faces=20);
    /**
      * @brief
      * @param
      * @return
      */
    void Parameters(float radius=1.0, float high=1.0 , int faces=20);
    /**
      * @brief
      * @param
      * @return
      */
    float getHigh();
    /**
      * @brief
      * @param
      * @return
      */
    float getRadius();
    /**
      * @brief
      * @param
      * @return
      */
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
    /** @brief  */
    float _radius;
    /** @brief  */
    int _numFaces;

    /**
      * @brief
      * @param
      * @return
      */
    void createObject();
public:
    /**
      * @brief
      * @param
      * @return
      */
    Sphere(float radius=1.0, int faces=20);
    /**
      * @brief
      * @param
      * @return
      */
    void Parameters(float radius=1.0 , int faces=20 );
    /**
      * @brief
      * @param
      * @return
      */
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
    /** @brief  */
    float _radius;
    /** @brief  */
    int _numFaces;

    /**
      * @brief
      * @param
      * @return
      */
    void createObject();

public:
    /**
      * @brief
      * @param
      * @return
      */
    SemiSphere(float radius=1.0, int faces=20);
    /**
      * @brief
      * @param
      * @return
      */
    void Parameters(float radius=1.0 , int faces=20 );
    /**
      * @brief
      * @param
      * @return
      */
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
    /** @brief  */
    float _high;
    /** @brief  */
    float _side;

    /**
      * @brief
      * @param
      * @return
      */
    void createObject();

public:
    /**
      * @brief
      * @param
      * @return
      */
    Pyramid(float hight=1.0, float side=1.0) ;
    /**
      * @brief
      * @param
      * @return
      */
    void Parameters(float hight=1.0, float side=1.0 );
    /**
      * @brief
      * @param
      * @return
      */
    float getSide();
    /**
      * @brief
      * @param
      * @return
      */
    float getHigh();
};

#endif // OBJECTS_H
