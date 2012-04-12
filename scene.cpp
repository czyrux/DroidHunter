#include "scene.h"
#include <iostream>

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Scene::Scene(){
    //inicializacion de semilla para escena
    srand(time(0));

    //DEFINIMOS EL NUMERO DE TICKS
    this->numeroTicks=40;
    _tick = 0;

    //PONEMOS EL PERSONAJE
    _vertex3f pos;
    float scaleW = 3 , scaleD = 2;

    //Creamos objetos para escena
    pos.x=-100;pos.z=-100;pos.y=0;
    this->_primary = new Droid();
    vector<material> material_color;
    material_color.push_back(rojizoColor); //color body
    material_color.push_back(blackColor); //color eyes
    this->_primary->setColor(material_color);
    this->_secondary = new BallMonster();
    this->personaje = new Character (_primary,_secondary,this->numeroTicks,pos,scaleW);
    this->_personajeDied = NULL;
    this->_wasp = new Wasp();
    this->_wasp->setState(_MOVING);
    this->_minDroid = new Droid(.5,2.,false);
    material_color[0] = pearlColor;
    material_color[1] = rubyColor;
    this->_minDroid->setColor(material_color);
    this->_minDroid->setState(_MOVING);


    this->_starship = new Starship(60.0,60.0);
    _shipPosition.x = -150.0 ;_shipPosition.z = -150.0; _shipPosition.y=0;
    _shipRange = 60.0;

    //COLOCAMOS Las figuras
    _random r(-100,100);
    pos.x=r.value();
    pos.z=r.value();
    _wasps.clear();
    _droids.clear();
    Particle aux(_minDroid,this->numeroTicks,pos,scaleD,"droid",this->personaje);
    _droids.push_back(aux);

    //put watchers
    for ( int i=0 ; i<3 ; i++ ) {
        pos.x=r.value();
        pos.z=r.value();
        aux.parameters(_wasp,this->numeroTicks,pos,scaleW,"wasp",personaje);
        _wasps.push_back(aux);
    }

    //put mini droids
    for ( int i=0 ; i<8 ; i++ ) {
        pos.x=r.value();
        pos.z=r.value();
        aux.parameters(_minDroid,this->numeroTicks,pos,scaleD,"droid",personaje);
        _droids.push_back(aux);
    }


    //Definimos el tipo de dibujado
    this->_drawMode = gouraud;

    //Definimos la escena del juego
    this->_scene=1;

    //Mapa
    _map = new Map(300.0);

    //Elementos de la galleria
    _galleryElement = 0 ;
    _elements = 9;

    _showAxis = true;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Scene::~Scene(){
    if (personaje) delete this->personaje;
    this->_droids.clear();
    this->_wasps.clear();
    if (_map) delete this->_map;
    if (_primary) delete this->_primary;
    if (_personajeDied) delete this->_personajeDied;
    if (_secondary) delete this->_secondary;
    if (_wasp) delete this->_wasp;
    if (_minDroid) delete this->_minDroid;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Scene::setScene(int f) {
     this->_scene=f;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Scene::draw(){

     //Pinta los ejes
     if ( _showAxis ) _axis.draw();

     //definimos la luz de la escena
     GLfloat Luz0[4]={1,1,1,0};
     glLightfv(GL_LIGHT0,GL_POSITION,Luz0);

     switch (_drawMode ){
     case gouraud:
     case plane:
     case chess:
         glPolygonMode(GL_FRONT,GL_FILL);
         break;
     case points:
         glPolygonMode(GL_FRONT,GL_POINT);
         break;
     case lines:
         glPolygonMode(GL_FRONT,GL_LINES);
         break;
     default:
         break;
     }
     glPolygonMode(GL_FRONT_AND_BACK,GL_LINES);
     stateObject old;

     //pintamos mapa
     this->_map->draw(_drawMode);

     //Segun el escenario
     switch (this->_scene){
     case 1: //juego

         //pintamos personaje
         personaje->draw(_drawMode);

         //Pintamos las abejas
         for ( int i=0 ; i<_wasps.size() ; i++ )
            _wasps[i].draw(_drawMode);

         //Pintamos los droides
         for ( int i=0 ; i<_droids.size() ; i++ )
            _droids[i].draw(_drawMode);

         //Pintamos la nave
         glPushMatrix();
         glTranslatef(-150,30,-150);
         _starship->draw(_drawMode);
         glPopMatrix();
         glPushMatrix();
         glTranslatef(-150,0,-150);
         ((Starship*)_starship)->drawRange();
         glPopMatrix();

         //pintamos el cadaver
         if ( _personajeDied ) _personajeDied->draw(_drawMode);

         break;
    case 2: //galeria
         glPushMatrix();
         glRotatef(90,0,1,0);
         switch (_galleryElement){
         case 0:
            old = this->_primary->getState();
            this->_primary->setState(_NORMAL);
            _primary->draw(_drawMode);
            this->_primary->setState(old);
            break;
         case 1:
            old = this->_primary->getState();
            this->_primary->setState(_TAKE_HAMMER);
            _primary->draw(_drawMode);
            this->_primary->setState(old);
            break;
         case 2:
            old = this->_primary->getState();
            this->_primary->setState(_HIT_HAMMER);
            _primary->draw(_drawMode);
            this->_primary->setState(old);
            break;
         case 3:
            old = this->_primary->getState();
            this->_primary->setState(_SCREAMING);
            _primary->draw(_drawMode);
            this->_primary->setState(old);
            break;
         case 4:
            old = this->_primary->getState();
            this->_primary->setState(_DEAD);
            _primary->draw(_drawMode);
            this->_primary->setState(old);
            break;
         case 5:
             old = this->_wasp->getState();
             this->_wasp->setState(_NORMAL);
             this->_wasp->draw(_drawMode);
             this->_wasp->setState(old);
             break;
         case 6:
             glPushMatrix();
             glScalef(0.75,0.75,0.75);
             this->_minDroid->draw(_drawMode);
             glPopMatrix();
             break;
         case 7:
             this->_secondary->setState(_OPEN);
             this->_secondary->draw(_drawMode);
             break;
         case 8:
             glPushMatrix();
             glTranslatef(0,3,0);
             glScalef(0.07,0.07,0.07);
             this->_starship->draw(_drawMode);
             glPopMatrix();
             break;
         default:
             break;
         }
         glPopMatrix();
         break;
    default:
        break;
    }



}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Scene::animate() {
    if (this->_scene==1) {
        if (this->personaje->getState()==_DEAD) newCharacter();

        this->personaje->animate();

        //pedimos que se animen
        for (int i=0 ; i<_droids.size() ; i++ )
            _droids[i].animate();

        //pedimos que se animen
        for (int i=0 ; i<_wasps.size() ; i++ )
            _wasps[i].animate();

        //vemos si colisionan
        colisiones();

        //vemos si entran en la captura
        captureDroid();

    }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Scene::colisiones() {
    bool colision;

    //Comprobamos los choques de droides
    for ( int i=0 ; i<_droids.size() ; i++ ) {
        //Comprobamos que las particulas no choquen entre si
        for ( int j=0 ; j<i ; j++ ){
            if (j!=i) {
                colision = _droids[i].collision(_droids[j].getPosition(),_droids[j].getCollisionRadius());
                if ( colision ) {
                    _droids[i].avoidCollision();
                    _droids[j].avoidCollision();
                    break;
                }
            }
        }

        //Comprobamos si chocan con el personaje
        colision = _droids[i].collision(personaje->getPosition(),personaje->getCollisionRadius());
        if ( colision ) {
            _droids[i].avoidCollision();
            personaje->avoidCollision();
        }
    }//end for droids

    //Comprobamos los choques de wasps
    for ( int i=0 ; i<_wasps.size() ; i++ ) {
        //Comprobamos que las particulas no choquen entre si
        for ( int j=0 ; j<i ; j++ ){
            if (j!=i) {
                colision = _wasps[i].collision(_wasps[j].getPosition(),_wasps[j].getCollisionRadius());
                if ( colision ) {
                    _wasps[i].avoidCollision();
                    _wasps[j].avoidCollision();
                    break;
                }
            }
        }
    }//end for _wasps

    //Comprobamos si el droid entra en rango de accion de _wasps
    restrictedArea();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Scene::speedUp() {
    for ( int  i=0 ; i<_droids.size() ; i++ ) {
        _droids[i].speedUp();
    }
    for ( int  i=0 ; i<_wasps.size() ; i++ ) {
        _wasps[i].speedUp();
    }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Scene::speedDown(){
    for ( int  i=0 ; i<_droids.size() ; i++ ) {
        _droids[i].speedDown();
    }
    for ( int  i=0 ; i<_wasps.size() ; i++ ) {
        _wasps[i].speedDown();
    }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Scene::moveRight() {
    personaje->spinRight();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Scene::moverLeft() {
    personaje->spinLeft();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Scene::moveForward() {
    personaje->forward();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Scene::moveBackward() {
    personaje->backward();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

stateObject Scene::getCharacterState() {
    return personaje->getState();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Scene::setCharacterState( stateObject d) {
    if ( personaje->getState() != _DEAD) {//si no esta muerto
        personaje->setState(d);
        if ( d==_HIT_HAMMER ) this->scream();
    }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Scene::setDrawMode(drawMode d) {
    _drawMode = d;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Scene::scream() {
    bool colision;
    //Comprobamos si hay algun droide en nuestro rango de accion
    for ( int i=0 ; i<_droids.size() ; i++ ) {
        colision = _droids[i].collision(personaje->getPosition(),personaje->getRangeAction());
        if ( colision ) {
            float angle=this->personaje->getSpin();
            _vertex3f pos =_droids[i].getPosition();
            int D = 40;
            pos.x+=D*sin(angle*PI/180.);
            pos.z+=D*cos(angle*PI/180.);
            _droids[i].setState(_SCREAMING);
            _droids[i].setGoal(pos);
        }
    }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Scene::restrictedArea() {
    bool colision;
    //Comprobamos si el droid esta en nuestro campo de accion
    for ( int i=0 ; i<_wasps.size() ; i++ ) {
        if ( !_wasps[i].pursuitCharacter() && personaje->getState()!=_DEAD) {
        colision = personaje->collision(_wasps[i].getPosition(),_wasps[i].getRangeAction());
        if ( colision ) {
            _wasps[i].pursuitOn();
        }
        }
    }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Scene::newCharacter() {
    _tick++;

    if ( _tick >= numeroTicks*2 ) {
        //Creamos el cadaver
        this->numeroTicks=40;
        _vertex3f pos = personaje->getPosition();
        float scaleW = 3 ;

        _personajeDied = new Character(_primary,_secondary,this->numeroTicks,pos,scaleW);
        _personajeDied->setState(_DEAD);

        //Regeneramos el personaje
        pos.x=-100;pos.z=-100;pos.y=0;
        personaje->setPosition(pos);
        personaje->setState(_NORMAL);
        _tick = 0;
    }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Scene::captureDroid() {
    _shipPosition.x = -150.0;
    _shipPosition.z = -150.0;
    _shipRange = 60.0;

    bool colision = false;

    for ( int i= 0 ; i<_droids.size() ; i++ ) {
        colision = _droids[i].collision(_shipPosition,_shipRange);
        if (colision )
                _droids[i].setStateParticle(working);
    }


}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

_vertex3f Scene::getCharacterPosition() {
    return this->personaje->getPosition();
}

float Scene::getCharacterSpin() {
     return this->personaje->getSpin();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Scene::changeElement() {
    _galleryElement = (_galleryElement + 1 ) % _elements;
}

void Scene::axis() {
    _showAxis=(_showAxis)?false:true;
}
