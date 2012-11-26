#ifndef _NODE_H_
#define _NODE_H_

#include "Matrix4.h"
#include "Camera.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <GL/glut.h>
#include <math.h>

using namespace std;

class Node {
    protected:
        string name;
        Node * parent;
        //bounding box

    public:
        virtual void draw(Matrix4 m) = 0;
        string getName() { return name; }
};

#endif
