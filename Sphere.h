#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "Geode.h"

class Sphere: public Geode {
    protected:
        float size, r, g, b;
    public:
        Sphere() : size(0.0), r(1.0), g(0.0), b(0.0) {}
        Sphere(string n, float x) : size(x), r(1.0), g(0.0), b(0.0) 
            {this->name = n;}
        bool isInBoundingSphere(Matrix4);
        void setColor(float x, float y, float z) {r=x;g=y;b=z;}
        void draw(Matrix4);
};

#endif
