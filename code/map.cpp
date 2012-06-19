#include "map.h"
#include <iostream>

Map::Map( int width ) {
    this->_width = width;

    //Cargamos las texturas
    string fichero,path="./resources/";
    fichero=path+"stars.gif";//"stars.jpg";
    if (!_image.load( fichero.c_str() ) ) {
        printf ("Error al cargar la imagen: %s",fichero.c_str());
        exit(-1);
    }

    _skyImg = QGLWidget::convertToGLFormat( _image );
    glGenTextures( 1, &_sky );

    fichero=path+"land.jpg";
    if (!_image.load( fichero.c_str() ) ) {
            printf ("Error al cargar la imagen: %s",fichero.c_str());
            exit(-1);
    }

    _landImg = QGLWidget::convertToGLFormat( _image );
    glGenTextures( 2, &_land );

    fichero=path+"earth.jpg";
    if (!_image.load( fichero.c_str() ) ) {
            printf ("Error al cargar la imagen: %s",fichero.c_str());
            exit(-1);
    }

    _earthImg = QGLWidget::convertToGLFormat( _image );
    glGenTextures( 3, &_earth );

    //Piramides/montañas
    _mountains = new Pyramid(1.0,1.0);
    //fichero=path+"land.jpg";
    //_mountains->setTexture((char *)fichero.c_str());
    //_cube->setTexture((char *)fichero.c_str());
    _mountains->setMaterial(copperColor);


    //Colocamos varias plantas por la zona
    _plants = new Plants(10,0.03);
    _positionsPlants.clear();
    _vertex3f pos;
    pos.x=-100;pos.z=0;pos.y=0;
    _positionsPlants.push_back(pos);
    pos.x=-50;pos.z=100;pos.y=0;
    _positionsPlants.push_back(pos);
    pos.x=50;pos.z=-40;pos.y=0;
    _positionsPlants.push_back(pos);
    pos.x=50;pos.z=-200;pos.y=0;
    _positionsPlants.push_back(pos);
    pos.x=70;pos.z=-200;pos.y=0;
    _positionsPlants.push_back(pos);
    pos.x=50;pos.z=-220;pos.y=0;
    _positionsPlants.push_back(pos);
    pos.x=70;pos.z=-220;pos.y=0;
    _positionsPlants.push_back(pos);

    //Ponemos piedras voladoras
    _cube = new Cube(1.0);
    _cube->setMaterial(goldColor);
    _positionsCube.clear();
    pos.x=200;pos.z=-100;pos.y=50.0;pos.u=10.0;
    _positionsCube.push_back(pos);
    pos.x=0;pos.z=20;pos.y=150.0;pos.u=20.0;
    _positionsCube.push_back(pos);

    //Compilacion de la escena
    _compiled = false;
}

Map::~Map() {
    //this->_mountains.clear();
    if ( this->_mountains ) delete this->_mountains;
    if ( this->_cube ) delete this->_cube;
    if ( this->_plants ) delete this->_plants;
    glDeleteTextures(1,&_sky);
    glDeleteTextures(2,&_land);
    glDeleteTextures(3,&_earth);
    _positionsPlants.clear();
    _positionsCube.clear();
}


void Map::draw( drawMode d ) {
    if (!_compiled) {this->compile();}

    //Pintamos
    glCallList(_list);

    //Pintamos montañas
    //glMatrixMode(GL_MODELVIEW);
    for ( int i=0 ; i<6 ; i++) {
        glPushMatrix();
        glTranslatef(-260+50.0*i,0,100+40.0*i);
        glScalef(80.0,60.0,80.0);
        glTranslatef(0,_mountains->getSide()/2,0);
        _mountains->draw(d);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-260+50.0*i,0,150+40.0*i);
        glScalef(80.0,60.0,80.0);
        glTranslatef(0,_mountains->getSide()/2,0);
        _mountains->draw(d);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-260+50.0*i,0,200+40.0*i);
        glScalef(80.0,60.0,80.0);
        glTranslatef(0,_mountains->getSide()/2,0);
        _mountains->draw(d);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(260-50.0*i,0,100+40.0*i);
        glScalef(80.0,60.0,80.0);
        glTranslatef(0,_mountains->getSide()/2,0);
        _mountains->draw(d);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(260-50.0*i,0,50+40.0*i);
        glScalef(80.0,60.0,80.0);
        glTranslatef(0,_mountains->getSide()/2,0);
        _mountains->draw(d);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(260-50.0*i,0,200+40.0*i);
        glScalef(80.0,60.0,80.0);
        glTranslatef(0,_mountains->getSide()/2,0);
        _mountains->draw(d);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(260-50.0*i,0,150+40.0*i);
        glScalef(80.0,60.0,80.0);
        glTranslatef(0,_mountains->getSide()/2,0);
        _mountains->draw(d);
        glPopMatrix();
    }


    //Pintamos plantas
    for ( int i=0 ; i<_positionsPlants.size()  ; i++) {
        glPushMatrix();
        glTranslatef(_positionsPlants[i].x,0,_positionsPlants[i].z);
        glTranslatef(10,1,20);
        this->_plants->draw(d);
        glPopMatrix();
    }

    //Pintamos cubos
    for ( int i=0 ; i<_positionsCube.size() ; i++) {
        glPushMatrix();
        glRotatef(45,0,0,1);
        glTranslatef(_positionsCube[i].x,_positionsCube[i].y,_positionsCube[i].z);
        glScalef(_positionsCube[i].u,_positionsCube[i].u,_positionsCube[i].u);
        glTranslatef(0,_cube->getSide()/2,0);
        _cube->draw(d);
        glPopMatrix();
    }
}

void Map::compile() {

    _list = glGenLists(1);
    glNewList(_list, GL_COMPILE);
    glColor3f(1.0,1.0,1.0);
    glEnable(GL_TEXTURE_2D);

    //Pintamos el suelo
    glBindTexture( GL_TEXTURE_2D, _land );
    glTexImage2D( GL_TEXTURE_2D, 0, 3, _landImg.width(), _landImg.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, _landImg.bits() );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f,0.0f);glVertex3f(-_width,-0.1,-_width);
    glTexCoord2f(0.0f,1.0f);glVertex3f(-_width,-0.1,_width);
    glTexCoord2f(1.0f,1.0f);glVertex3f(_width,-0.1,_width);
    glTexCoord2f(1.0f,0.0f);glVertex3f(_width,-0.1,-_width);
    glEnd();

    //Pintamos el cielo
    glBindTexture( GL_TEXTURE_2D, _sky );
    glTexImage2D( GL_TEXTURE_2D, 0, 3, _skyImg.width(), _skyImg.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, _skyImg.bits() );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    //techo
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f,0.0f);glVertex3f(_width,_width,_width);
    glTexCoord2f(0.0f,1.0f);glVertex3f(-_width,_width,_width);
    glTexCoord2f(1.0f,1.0f);glVertex3f(-_width,_width,-_width);
    glTexCoord2f(1.0f,0.0f);glVertex3f(_width,_width,-_width);
    glEnd();

    glBegin(GL_QUADS);//espalda
    glTexCoord2f(0.0f,0.0f);glVertex3f(-_width,-1,_width);
    glTexCoord2f(0.0f,1.0f);glVertex3f(-_width,_width+1,_width);
    glTexCoord2f(1.0f,1.0f);glVertex3f(_width,_width+1,_width);
    glTexCoord2f(1.0f,0.0f);glVertex3f(_width,-1,_width);
    glEnd();
    glBegin(GL_QUADS);//frontal
    glTexCoord2f(0.0f,0.0f);glVertex3f(_width,-1,-_width);
    glTexCoord2f(0.0f,1.0f);glVertex3f(_width,_width+1,-_width);
    glTexCoord2f(1.0f,1.0f);glVertex3f(-_width,_width+1,-_width);
    glTexCoord2f(1.0f,0.0f);glVertex3f(-_width,-1,-_width);
    glEnd();
    glBegin(GL_QUADS);//lateraldrcho
    glTexCoord2f(0.0f,0.0f);glVertex3f(_width,-0.1,_width+1);
    glTexCoord2f(0.0f,1.0f);glVertex3f(_width,_width+1,_width+1);
    glTexCoord2f(1.0f,1.0f);glVertex3f(_width,_width+1,-_width-1);
    glTexCoord2f(1.0f,0.0f);glVertex3f(_width,-0.1,-_width-1);
    glEnd();

    glBegin(GL_QUADS);//lateraliza
    glTexCoord2f(0.0f,0.0f);glVertex3f(-_width,-1,-_width);
    glTexCoord2f(0.0f,1.0f);glVertex3f(-_width,_width+1,-_width);
    glTexCoord2f(1.0f,1.0f);glVertex3f(-_width,_width+1,0);
    glTexCoord2f(1.0f,0.0f);glVertex3f(-_width,-1,0);
    glEnd();

    //trasero tierra
    glBindTexture( GL_TEXTURE_2D, _earth );
    glTexImage2D( GL_TEXTURE_2D, 0, 3, _earthImg.width(), _earthImg.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, _earthImg.bits() );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f,0.0f);glVertex3f(-_width,-1,0);
    glTexCoord2f(0.0f,1.0f);glVertex3f(-_width,_width+1,0);
    glTexCoord2f(1.0f,1.0f);glVertex3f(-_width,_width+1,_width);
    glTexCoord2f(1.0f,0.0f);glVertex3f(-_width,-1,_width);
    glEnd();

    glDisable(GL_TEXTURE_2D);

    glEndList();
    _compiled = true;
}
