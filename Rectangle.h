#ifndef _Rectangle_H_
#define _Rectangle_H_

#include "Geode.h"

class Rectangle: public Geode {
    protected:
        float base, height, width, r, g, b;
    public:
        Rectangle() : 
            base(0.0), height(0.0), width(0.0), 
            r(1.0), g(0.0), b(0.0) {}
        Rectangle(string n, float b, float h, float w) : 
            base(b), height(h), width(w),
            r(1.0), g(0.0), b(0.0) {this->name = n;}
        bool isInBoundingSphere(Matrix4);
        void setColor(float x, float y, float z) { r=x; g=y; b=z;}
        void draw(Matrix4);
};

#endif

