#ifndef _MATRIX4_H_
#define _MATRIX4_H_

#include <math.h>
#include "Vector3.h"
#include "Vector4.h"

class Matrix4
{
  public:
    double m[4][4];   // matrix elements
    
    Matrix4();        // constructor
    Matrix4(double, double, double, double, 
            double, double, double, double, 
            double, double, double, double, 
            double, double, double, double);
    Matrix4(double [4][4]);
    Matrix4(const Matrix4 &);
    Matrix4 multiply(Matrix4);
    Vector4 multiply(Vector4);
    Matrix4 add(Matrix4);
    void originMultiply(Matrix4);
    double * getPointer();  // return pointer to matrix elements
    double * getGLPointer();
    void identity();  // create identity matrix
    void rotateX(double);
    void rotateY(double); // rotation about y axis
    void rotateZ(double);
    void rotateA(Vector4 &, double);
    void scale(double, double, double);
    void scale(double);
    double get(int,int);
    void set(Matrix4 );
    void translate(double, double, double);
    void transpose();
    void negate();
    void invert();
    void print();
};

#endif
