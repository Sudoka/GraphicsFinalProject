#ifndef _TORUS_H_
#define _TORUS_H_

#include "Geode.h"

class Torus: public Geode {
    protected:
        float inner, outer, r, g, b;
    public:
        Torus() : inner(0.0), outer(0.0), r(1.0), g(0.0), b(0.0) {}
        Torus(string n, float i, float o) : 
            inner(i), outer(o), r(1.0), g(0.0), b(0.0) 
            {this->name = n;}
        bool isInBoundingSphere(Matrix4);
        void setColor(float x, float y, float z) { r=x; g=y; b=z;}
        void draw(Matrix4);
};

#endif
