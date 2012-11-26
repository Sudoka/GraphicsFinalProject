#ifndef _CONE_H_
#define _CONE_H_

#include "Geode.h"

class Cone: public Geode {
    protected:
        float base, height, r, g, b;
    public:
        Cone() : base(0.0), height(0.0), r(1.0), g(0.0), b(0.0) {}
        Cone(string n, float b, float h) : 
            base(b), height(h), r(1.0), g(0.0), b(0.0) 
            {this->name = n;}
        bool isInBoundingSphere(Matrix4);
        void setColor(float x, float y, float z) { r=x; g=y; b=z;}
        void draw(Matrix4);
};

#endif

