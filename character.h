#ifndef PERSONAJE_H
#define PERSONAJE_H

#include "objects.h"
#include "vertex.h"
#include "droid.h"
#include "ball_monster.h"

class Character {
private:
    _hierarchyObject *_my;
    _hierarchyObject *_secondary;
    _vertex3f _posOld;
    _vertex3f _posNow;
    _vertex3f _orientation;
    stateObject _state;
    float _spin;
    int _elevation;
    int _tickTotal;
    int _tickAction;
    float _collisionRadius;
    float _scaleFactor;

    float normalize(float angle);
    void initialize(_hierarchyObject *objeto,_hierarchyObject *objeto2,int ticksTotales , _vertex3f posInicial, float factorEscala);
public:
    Character(_hierarchyObject *objeto,_hierarchyObject *objeto2,int ticksTotales , _vertex3f posInicial, float factorEscala);
    ~Character();
    void parameters (_hierarchyObject *objeto,_hierarchyObject *objeto2,int ticksTotales , _vertex3f posInicial , float factorEscala);
    void animate(); //calculo de posicion
    bool collision( _vertex3f centro , float radio );
    void draw(drawMode d);
    _vertex3f getPosition();
    void setPosition(_vertex3f pos);
    float getSpin();
    float getCollisionRadius();
    float getRangeAction();
    void setScaleFactor(float x);

    void avoidCollision();
    void spinRight();
    void spinLeft();
    void forward(); //void avanza();
    void backward(); //void atras();

    stateObject getState();
    void setState(stateObject d);

};
#endif // PERSONAJE_H
