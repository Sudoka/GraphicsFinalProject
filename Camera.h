#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4.h"
#include <math.h>
#include <iostream>
#include <GL/glut.h>

class Camera
{
    public:
    Vector3 e;
    Vector3 d;
    Vector3 up;
    Matrix4 C;

    Camera();
    Camera(Vector3, Vector3, Vector3);
    Vector3 getEye();
    Vector3 getLookat();
    Vector3 getUp();
    Matrix4 getCameraMatrix();
    void resetCamera();
};

#endif
