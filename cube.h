#ifndef _CUBE_H_
#define _CUBE_H_


#include "Matrix4.h"
#include "objreader.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <GL/glut.h>
#include "Matrix4.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Camera.h"
#include <math.h>
#include <time.h>
#include <string.h>
#include "Node.h"
#include "Group.h"
#include "MatrixTransform.h"
#include "Sphere.h"
#include "Geode.h"
#include "Torus.h"
#include "Cone.h"
#include "Rectangle.h"
#include "Util.cpp"

struct Color
{
    public:
    double r, g, b;

    Color(double a, double b, double c)
    {
        this->r = a; this->g = b; this->b = c;
    }
};

class Cube
{
  protected:
    Matrix4 matrix;                 // model matrix
                       

  public:
    double angle; // rotation angle [degrees]
    Cube();   // Constructor
    Matrix4& getMatrix();
    void drawHouse();
};

class window	  // output window related routines
{
  public:
    static int width, height; 	            // window size

    static void idleCallback(void);
    static void reshapeCallback(int, int);
    static void displayCallback(void);
};

#endif

