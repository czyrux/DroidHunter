#ifndef PARTICULA_H
#define PARTICULA_H

#include <cmath>
#include "objects.h"
#include "vertex.h"
#include "character.h"
#include "random.h"
#include "wasp.h"
#include "droid.h"

enum State {spinning,walking,calculate_Spin,search_Goal,screamed , attacking , working };

#define TICK_TOP 300

class Particle {
private:
    _hierarchyObject *_object;
    _vertex3f _posBegin;
    _vertex3f _posNow;
    _vertex3f _posEnd;
    State _state;
    stateObject _stateObject;
    _vertex3f _orientation;
    float _spinBegin;
    float _spinNow;
    float _spinEnd;
    int _tick;
    int _tickTotal;
    int _tickTotalSpin;
    float _incSpin;
    float _radiusCollision;
    float _elevation;
    float _scaleFactor;
    bool _movLineal;
    float _speed;

    bool _pursuitCharacter;
    int tickAccion;
    //int tickPonerHuevo;
    string _type; //"droid o wasp"
    Character *personaje; //referencia al jugador de la partida

    //metodos privados
    void calculateObjetive();
    void moveParticle();
    void spinningParticle();
    void calculateSpin();
    void scream();
    void attack();
    void work();
    void initialize (_hierarchyObject *objeto,int ticksTotales , _vertex3f posInicial, float factorEscala , string tipo , Character *personaje);

    float normalize(float angle);
    int quadrant (float angle);
    void calculeTicks();
    float distance (_vertex3f v1 , _vertex3f v2 );

public:
    Particle(_hierarchyObject *objeto,int ticksTotales , _vertex3f posInicial, float factorEscala , string tipo , Character *personaje);
    ~Particle();
    void parameters (_hierarchyObject *objeto,int ticksTotales , _vertex3f posInicial , float factorEscala , string tipo , Character *personaje);
    void animate();
    bool collision( _vertex3f centro , float radio );
    void draw( drawMode );
    _vertex3f getPosition();
    float getCollisionRadius();
    float getRangeAction();
    void setScaleFactor(float x);
    void avoidCollision(); //Una vez colisionado
    void speedUp();
    void speedDown();
    void movLineal();
    void movSenosoidal();
    void setState(stateObject d);
    stateObject getState();
    void setGoal(_vertex3f pos);
    void setStateParticle(State d);

    void pursuitOn();
    bool pursuitCharacter();

};
#endif // PARTICULA_H
