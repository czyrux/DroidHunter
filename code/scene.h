/*************************************************************************/
/*                                                                       */
/*         Copyright (C) Antonio Gutierrez Martinez [2010]               */
/*                                                                       */
/*         License: GPL3                                                 */
/*                                                                       */
/*************************************************************************/
/**
 * @file scene.h
 * @brief Implementation of scene of game
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

#ifndef SCENE_H
#define SCENE_H

#include <QImage>
#include <QGLWidget>
#include "axis.h"
#include "objects.h"
#include "particle.h"
#include "character.h"
#include "plants.h"
#include "materials.h"
#include "map.h"
#include "droid.h"
#include "wasp.h"
#include "ball_monster.h"
#include "starship.h"
#include <vector>

class Scene {
    private:
        _hierarchyObject *_primary;
        _hierarchyObject *_secondary;
        _hierarchyObject *_wasp;
        _hierarchyObject *_minDroid;
        _hierarchyObject *_starship;
        Map *_map;
        Axis _axis;
        bool _showAxis;
        drawMode _drawMode;

        vector<material> materiales;
        vector<Particle> _wasps;
        vector<Particle> _droids;
        vector<Character> _droidsDied;
        Character *personaje , *_personajeDied;
        int numeroTicks;
        int _tick;
        int _scene;

        _vertex3f _shipPosition;
        float _shipRange;

        int _galleryElement;
        int _elements;

        void colisiones(); //Para gestion colisiones
        void restrictedArea(); //Para la gestion de seguimiento del androide
        void scream(); //Para la gestion de la accion de miedo
        void newCharacter(); //Regenera al personaje al morir
        void captureDroid();

    public:
        Scene();
        ~Scene();
        void setScene( int );
        void animate();
        void draw();
        void speedUp();
        void speedDown();
        void moveRight();
        void moverLeft();
        void moveForward();
        void moveBackward();
        void axis();

        stateObject getCharacterState();
        void setCharacterState(stateObject d);

        _vertex3f getCharacterPosition();
        float getCharacterSpin();

        void setDrawMode(drawMode d);

        void changeElement();

};

#endif

