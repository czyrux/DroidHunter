#ifndef HIERARCHYOBJECT_H
#define HIERARCHYOBJECT_H

#include "objects.h"

enum stateObject { _moving , _screaming , _normal , _takeHammer , _hitHammer,
                   /*_small ,*/ _flying , /*_nailed,*/ _open , _close , /*_inmovil ,*/
                 _dead, _shooting };

class _hierarchyObject {
protected:
    float _width;
    float _high;
    drawMode _drawMode;
    stateObject _state;
public:
    _hierarchyObject() {
    this->_width = this->_high = 0;
    _drawMode = gouraud;
    }

    ~_hierarchyObject(){}

    void parameters( float width=1.0 , float high=2.0) {
        this->_width = width;
        this->_high = high;
    }

    virtual float getRadioCollision(){ return 0.0;}
    virtual float getRange(){return 0.0;}
    void setDrawMode ( drawMode d ) { this->_drawMode = d; }
    virtual void setColor( material , material ){ }
    float getWidth() { return _width;}
    float getHigh() { return _high; }
    void setState( stateObject state ) { this->_state = state; }
    stateObject getState() { return _state;}

    virtual void draw( drawMode d){}

};

#endif // HIERARCHYOBJECT_H
