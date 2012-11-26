#ifndef _VECTOR4_H_
#define _VECTOR4_H_

#include <math.h>
#include <iostream>
#include "Vector3.h"

class Vector4
{
    protected:
    float x, y, z, w;
    
    public:
    Vector4();
    Vector4(float, float, float, float);
    Vector4(float[4]);
    void set(float, float, float, float);
    float get(int);
    float operator[](int);
    Vector4 add(Vector4 &);
    Vector4 operator+(Vector4 &);
    Vector4 subtract(Vector4 &);
    Vector4 operator-(Vector4 &);
    float multiply(Vector4);
    void dehomogenize();
    void print();
    bool equals(Vector4 &);
    void scale(float);
    Vector3 getVector3();
};

#endif
