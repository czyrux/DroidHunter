#include <particle.h>
#include <iostream>

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Particle::Particle(_hierarchyObject *objeto, int ticksTotales, _vertex3f posInicial , float factorEscala , string tipo , Character *p) {
    this->initialize(objeto,ticksTotales,posInicial,factorEscala,tipo,p);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Particle::~Particle() {
    this->_object=0;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Particle::parameters (_hierarchyObject *objeto,int ticksTotales , _vertex3f posInicial , float factorEscala , string tipo , Character *p){
    this->initialize(objeto,ticksTotales,posInicial,factorEscala,tipo,p);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

//FUNCIONES PRIVADAS
void Particle::initialize (_hierarchyObject *objeto,int ticksTotales , _vertex3f posInicial, float factorEscala , string tipo , Character *personaje) {
    this->_object=objeto;
    this->_stateObject = _object->getState();
    this->_spinNow=this->_spinEnd=0;
    this->_tick=0;
    this->_tickTotal=ticksTotales;
    this->_tickTotalSpin=ticksTotales/4;
    this->_state=search_Goal;
    this->_posBegin=this->_posNow=this->_posEnd=posInicial;
    this->_orientation.x=0; this->_orientation.y=0 ; this->_orientation.z=1;
    this->_radiusCollision=this->_object->getRadioCollision();
    this->_scaleFactor=factorEscala;
    this->_movLineal = true;
    this->_pursuitCharacter = false;

    this->_speed = 5 ;
    this->_elevation=0;
    this->tickAccion=0;
    this->_type=tipo;
    this->personaje=personaje;
    srand(time(NULL));
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Particle::calculateObjetive() {
    _posEnd.x= (rand() % 200 + 1)-100;
    _posEnd.z= (rand() % 200 + 1)-100;

    this->calculeTicks();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Particle::moveParticle() {
    _tick++;
    if (_tick<=_tickTotal && _posNow != _posEnd) {
        float t = (float)_tick / (float)_tickTotal;
        if (this->_movLineal)
            _posNow = _posBegin*(1-t)+_posEnd*t;
        else
            _posNow = _posBegin*(1-sin(t))+_posEnd*sin(t); //movimiento senosoidal
    }else {
        _posBegin=_posNow;
        //Si no estamos asustados, buscamos otro objetivo, sino permanecemos quietos
        if (_stateObject == _screaming ) {
            _state=screamed;
        }else if ( _pursuitCharacter ) { //si llegamos al objetivo que buscabamos, vemos si atacamos
            _state=attacking;
            _stateObject = _shooting;
        }else {
            //q_state=(rand () % 3 == 1 )? search_Goal:working;
            _state=search_Goal;
        }
        _tick=0;
        tickAccion=0;
    }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Particle::calculateSpin() {
    //calculamos el nuevo vector de orientacion
    _vertex3f nuevo;
    nuevo=_posEnd-_posBegin;
    nuevo.normalize();

    //guardamos el anterior giro
    _spinBegin=normalize(_spinNow);

    //calculamos el giro de destino
    _spinEnd = atan2(nuevo.x,nuevo.z)/M_PI*180.0;
    _spinEnd = this->normalize(_spinEnd);

    //Calculamos el signo del incremento en el giro
    int signo;
    if ( quadrant(_spinBegin) < 3 ) { //alfa en 1º y 2º cuadrante
        if ( _spinEnd < _spinBegin || _spinEnd > normalize(_spinBegin+180) )
            signo = -1;
        else
            signo = 1;
    }else { //alfa en 3º y 4º cuadrante
        if ( _spinEnd > _spinBegin || _spinEnd < _spinBegin-180 )
            signo = 1;
        else
            signo = -1;
    }

    //Calculamos el incremento
    if ( fabs(_spinEnd-_spinBegin) > 180) {
        if ( quadrant(_spinBegin) < 3 ) {
            _incSpin = (fabs((360-_spinEnd)+_spinBegin) / this->_tickTotalSpin) * signo;
        }else {
            _incSpin = (fabs(_spinEnd+(360-_spinBegin)) / this->_tickTotalSpin) * signo;
        }
    }else {
        _incSpin = (fabs(_spinEnd-_spinBegin) / this->_tickTotalSpin) * signo;
    }

    //ticks actuales
    _tick = 0;

}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Particle::spinningParticle(){
    //Aumento de tickActual
    _tick++;

    if ( _tick <= this->_tickTotalSpin) {
        _spinNow += _incSpin;
    }else {
        _spinNow = normalize(_spinNow);
        _tick=0;
        _state=walking;
        if ( _stateObject!=_screaming )_stateObject = _moving;
    }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Particle::scream() {
    tickAccion++;
    _tick++;
    //movemos el droid
    if ( tickAccion%11 == 0 ) {
        (_posNow.y == 0 ) ?_posNow.y+=4 :_posNow.y-=4;
        tickAccion=0;
    }

    //vemos si es la hora de dejar de asustarnos
    if ( _tick>=TICK_TOP/2 ) {
        _posNow.y=0;
        _tick=0;
        tickAccion=0;
        _state=search_Goal;
        _stateObject=_normal;
    }

}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Particle::attack() {
    //si le doy
    if (personaje->collision(_posNow,this->_object->getWidth())) {
            this->personaje->setState(_dead);
        //buscamos otro objetivo
            _pursuitCharacter = false;
            _state = search_Goal;
            _posBegin=_posNow;
            tickAccion = 0;
            _tick = 0;
            if ( _stateObject!=_screaming )_stateObject = _moving;
    }else {
            _pursuitCharacter = false;
            _state = search_Goal;
            _posBegin=_posNow;
            tickAccion = 0;
            _tick = 0;
            if ( _stateObject!=_screaming )_stateObject = _moving;
    }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Particle::work() {
    tickAccion++;
    //_tick++;

    if ( (tickAccion % (TICK_TOP/50+1)) == 0 ) {
        _stateObject=(_stateObject == _takeHammer )?_hitHammer:_takeHammer;
        tickAccion = 0;
    }

    /*if ( _tick >= TICK_TOP ) {
        _state = search_Goal;
        tickAccion = 0;
        _tick = 0;
    }*/
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

//FUNCIONES PUBLICAS
void Particle::animate() {
    switch (_state) {
    case search_Goal:
        calculateObjetive();
        _state=calculate_Spin;
        break;
    case calculate_Spin:
        calculateSpin();
        _state=spinning;
        if (_stateObject!=_screaming )
            (_type=="wasp")?_stateObject = _flying:_stateObject=_normal;
        break;
    case spinning:
        spinningParticle();
        break;
    case walking:
        moveParticle();
        break;
    case screamed:
        scream();
        break;
    case attacking:
        attack();
        break;
    case working:
        work();
        break;
    default:
        break;
    }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Particle::draw( drawMode d ) {
    _object->setState(this->_stateObject);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(_posNow.x,_posNow.y-_elevation,_posNow.z);
    glScalef(_scaleFactor,_scaleFactor,_scaleFactor);
    glRotatef(_spinNow,0,1,0);
    _object->draw(d);
    if(_type=="wasp")((Wasp*)_object)->drawRange();
    glPopMatrix();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

float Particle::normalize(float angle) {
    while (angle>360)
        angle-=360;
    while (angle<0)
        angle+=360;
    return angle;
}


int Particle::quadrant (float angle) {
    if ( angle >= 0 && angle < 90 )
        return 1;
    else if ( angle >= 90 && angle < 180 )
        return 2;
    else if ( angle >= 180 && angle < 270 )
        return 3;
    else
        return 4;
}

float Particle::distance (_vertex3f v1 , _vertex3f v2 ) {
    return sqrt ( pow(v1.x-v2.x,2)+pow(v1.z-v2.z,2));
}

void Particle::calculeTicks() {
    float d =this->distance(_posEnd,_posBegin);
    this->_tickTotal = d / _speed;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

_vertex3f Particle::getPosition() {
    return this->_posNow;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

float Particle::getCollisionRadius() {
    return this->_radiusCollision*this->_scaleFactor;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

float Particle::getRangeAction() {
    return this->_object->getRange()*this->_scaleFactor;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Particle::setScaleFactor( float x) {
    this->_scaleFactor=x;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

bool Particle::collision( _vertex3f centro , float radio ) {
    bool colision = false;
    float d = sqrt( pow(centro.x-_posNow.x,2)+pow(centro.z-_posNow.z,2) );

    if ( (this->_radiusCollision*_scaleFactor)+radio>d )
        colision = true;

    return colision;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Particle::avoidCollision() {
    if (_state==walking) {
        //Nos ponemos donde estabamos en el tick anterior
        _tick--;
        float t = (float)_tick / (float)_tickTotal;
        if (_movLineal)
            _posNow = _posBegin*(1-t)+_posEnd*t;
        else
            _posNow = _posBegin*(1-sin(t))+_posEnd*sin(t); //movimiento senosoidal
        _posBegin=_posNow;

        _state = search_Goal;
        _tick=0;
    }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Particle::pursuitOn( ) {
    if ( !_pursuitCharacter ) {
        this->_pursuitCharacter = true;
        _state=calculate_Spin;
        _posBegin=_posNow;
        _posEnd = personaje->getPosition();
        calculeTicks();
        _tick=0;
        tickAccion=0;
        if ( _posEnd == _posNow ) {
            _state = attacking;
        }
    }
}

bool Particle::pursuitCharacter() {return _pursuitCharacter;}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*void Particle::addTicks( int n ) {
    if ( this->_tickTotal+n > 0) this->_tickTotal+=n;
    if (this->_tickTotalSpin+n > 0) this->_tickTotalSpin+=n;
    if (_state==spinning) {
        _spinNow = normalize(_spinEnd);
        _tick=0;
        _state=walking;
    }
}*/

void Particle::speedUp() {
    if (this->_speed < 10 ) {
        _speed++;
        if (_state==spinning) {
            _spinNow = normalize(_spinEnd);
            _tick=0;
            _state=walking;
        }
    }
}
void Particle::speedDown() {
    if ( this->_speed > 1 ) {
        _speed--;
        if (_state==spinning) {
            _spinNow = normalize(_spinEnd);
            _tick=0;
            _state=walking;
        }
    }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Particle::movLineal() {
    cout << "Movimiento lineal"<<endl;_movLineal = true;}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Particle::movSenosoidal() {cout << "Movimiento senosoidal"<<endl;_movLineal = false;}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Particle::setGoal(_vertex3f pos ) {
    _posBegin=_posNow;
    _posEnd = pos;
    _state = calculate_Spin;
    calculeTicks();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Particle::setState(stateObject d) {
    _stateObject = d;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

stateObject Particle::getState() {
    return _stateObject;
}

void Particle::setStateParticle(State d) {
    _state = d;
}
