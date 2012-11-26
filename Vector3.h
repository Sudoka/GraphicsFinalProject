#ifndef _VECTOR3_H_
#define _VECTOR3_H_

#include <math.h>
#include <iostream>

class Vector3
{
    protected:
        float x, y, z;
    
    public:
        Vector3();
        Vector3(float, float, float);
        void set(float, float, float);
        float get(int);
        float operator[](int);
        Vector3 add(Vector3);
        Vector3 operator+(Vector3);
        Vector3 subtract(Vector3);
        Vector3 operator-(Vector3);
        Vector3 operator*(double);
        Vector3 operator*(float);
        void negate();
        void negate(Vector3 &);
        void scale(float);
        void scale(float, Vector3 &);
        float dot(Vector3 &);
        Vector3 cross(Vector3 &);
        float magnitude();
        void normalize();
        void print();
};

#endif
