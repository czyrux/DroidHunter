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

    /**
      * @brief Calculate the normals of vertex and faces.
      */
    void createNormals();
    /**
      * @brief Calculate value of box that involve the object.
      */
    void calculateBox();

    /**
      * @brief Abstract method who creates the object 3D.
      */
    virtual void createObject()=0;

private:
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

    /** @brief Array that holds the display lists with the differences types of show the object */
    GLuint _list[6] ;
    /** @brief Boolean value used to know if the display lists are charged or not */
    bool _compiled;

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
      * @brief Get vertices of object.
      * @return array of _vertex3f that holds the vertices.
      */
    vector<_vertex3f> getVertices();
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
      * @brief Get the collision radius of the object.
      * @return the radius.
      */
    float collisionRadius();
};

/*************************************************/
//CLASS OBJECTPLY
/*************************************************/
/**
 * @brief Class that implement a object PLY. Is used to charge
 * an object in ply format.
 */
class Object3DPly : public _object3D
{
private:
    /** @brief Holds the path of file .ply */
    char *_path;

    /**
      * @brief Create the geometry of object
      */
    void createObject();

public:
    /**
      * @brief Constructor of class
      * @param file file with the data of .ply object
      */
    Object3DPly( char *);
};

/*************************************************/
//CLASS CONE
/*************************************************/
/**
 * @brief Class that implement a cone in 3D.
 */
class Cone: public _object3D {
private:
    /** @brief Holds radiuos of object */
    float _radius;
    /** @brief Holds high of cone */
    float _high;
    /** @brief Holds number of lateral faces of cone */
    int _numFaces;

    /**
      * @brief Create the geometry of object
      */
    void createObject();

public:
    /**
      * @brief Constructor of class
      * @param radius of object. Default value 1.0
      * @param high of object. Default value 1.0
      * @param faces of object. Default value 20
      */
    Cone(float radius=1.0 ,float high=1.0 ,int faces=20);
    /**
      * @brief Change the parameters of object
      * @param radius of object. Default value 1.0
      * @param high of object. Default value 1.0
      * @param faces of object. Default value 20
      */
    void Parameters(float radius=1.0 ,float high=1.0 ,int faces=10);
    /**
      * @brief Get high of object
      * @return value of high
      */
    float getHigh();
    /**
      * @brief Get radius of object
      * @return value of radius
      */
    float getRadius();
    /**
      * @brief Get the number of faces from object
      * @return number of faces
      */
    int getNumFaces();
};

/*************************************************/
//CLASS CUBE
/*************************************************/
/**
 * @brief Class that implement a cube in 3D.
 */
class Cube: public _object3D {
private:
    /** @brief Holds long of side in object */
    float _side;

    /**
      * @brief Create the geometry of object
      */
    void createObject();

public:
    /**
      * @brief Constructor of class
      * @param side of object. Default value 1.0
      */
    Cube(float side=1.0);
    /**
      * @brief Set parameters
      * @param side of object. Default value 1.0
      */
    void Parameters(float side=1.0);
    /**
      * @brief Get side of object
      * @return value of side
      */
    float getSide();
};

/*************************************************/
//CLASS Cylinder
/*************************************************/
/**
 * @brief Class that implement a cylinder in 3D.
 */
class Cylinder: public _object3D {
private:
    /** @brief Holds radius of object */
    float _radius;
    /** @brief Holds high of object */
    float _high;
    /** @brief Holds the number of faces in object */
    int _numFaces;

    /**
      * @brief Create the geometry of object
      */
    void createObject();

public:
    /**
      * @brief Constructor of class
      * @param radius of object. Default value 1.0
      * @param high of object. Default value 1.0
      * @param faces of object. Default value 20
      */
    Cylinder(float radius=1.0, float high=1.0 , int faces=20);
    /**
      * @brief Set parameters of object
      * @param radius of object. Default value 1.0
      * @param high of object. Default value 1.0
      * @param faces of object. Default value 20
      */
    void Parameters(float radius=1.0, float high=1.0 , int faces=20);
    /**
      * @brief Get high of object
      * @return value of high.
      */
    float getHigh();
    /**
      * @brief Get radius of object
      * @return value of radius
      */
    float getRadius();
    /**
      * @brief Get the number of faces in object
      * @return number of faces
      */
    int getNumFaces();
};

/*************************************************/
//CLASS SPHERE
/*************************************************/
/**
 * @brief Class that implement a sphere in 3D.
 */
class Sphere: public _object3D {
private:
    /** @brief Holds radius of sphere */
    float _radius;
    /** @brief Holds the number of faces of sphere */
    int _numFaces;

    /**
      * @brief Create the geometry of object
      */
    void createObject();
public:
    /**
      * @brief Constructor
      * @param radius of object. Default value 1.0
      * @param faces number of faces of object. Default value 20.
      */
    Sphere(float radius=1.0, int faces=20);
    /**
      * @brief Set parameters of object
      * @param radius of object. Default value 1.0
      * @param faces number of faces of object. Default value 20.
      */
    void Parameters(float radius=1.0 , int faces=20 );
    /**
      * @brief get radius of object
      * @return value of radius.
      */
    float getRadius();
};

/*************************************************/
//CLASS SEMISPHERE
/*************************************************/
/**
 * @brief Class that implement a semisphere in 3D.
 */
class SemiSphere: public _object3D {
private:
    /** @brief Holds radius of semisphere */
    float _radius;
    /** @brief Holds the number of faces of semisphere */
    int _numFaces;

    /**
      * @brief Create the geometry of object
      */
    void createObject();

public:
    /**
      * @brief Constructor
      * @param radius of object. Default value 1.0
      * @param faces number of faces of object. Default value 20.
      */
    SemiSphere(float radius=1.0, int faces=20);
    /**
      * @brief Set parameters of object
      * @param radius of object. Default value 1.0
      * @param faces number of faces of object. Default value 20.
      */
    void Parameters(float radius=1.0 , int faces=20 );
    /**
      * @brief get radius of object
      * @return value of radius.
      */
    float getRadius();
};

/*************************************************/
//CLASS PYRAMID
/*************************************************/
/**
 * @brief Class that implement a pyramid in 3D.
 */
class Pyramid: public _object3D {
private:
    /** @brief Holds high of object */
    float _high;
    /** @brief Holds side of object */
    float _side;

    /**
      * @brief Create the geometry of object
      */
    void createObject();

public:
    /**
      * @brief Constructor of class
      * @param high of object. Default value 1.0
      * @param side of object. Default value 1.0
      */
    Pyramid(float high=1.0, float side=1.0) ;
    /**
      * @brief Set parameters of object
      * @param high of object. Default value 1.0
      * @param side of object. Default value 1.0
      */
    void Parameters(float high=1.0, float side=1.0 );
    /**
      * @brief Get side of object
      * @return value of side.
      */
    float getSide();
    /**
      * @brief Get high of object
      * @return value of high
      */
    float getHigh();
};

#endif // OBJECTS_H
