#include "Camera.h"

using namespace std;

Camera::Camera()
{
    C.identity();
}

Camera::Camera(Vector3 e, Vector3 d, Vector3 up)
{
    this->e = e;
    this->d = d;
    this->up = up;
    Vector3 z = e.subtract(d);
    z.scale(1.0 / z.magnitude());
    Vector3 x = (up.cross(z));
    x.scale(1.0 / x.magnitude());
    Vector3 y = z.cross(x);
    C = Matrix4(x.get(0), y.get(0), z.get(0), e.get(0),
                    x.get(1), y.get(1), z.get(1), e.get(1),
                    x.get(2), y.get(2), z.get(2), e.get(2),
                    0.0, 0.0, 0.0, 1.0);
    /*Matrix4 temp(x.get(0), x.get(1), x.get(2), 0.0,
                    y.get(0), y.get(1), y.get(2), 0.0,
                    z.get(0), z.get(1), z.get(2), 0.0,
                    e.get(0), e.get(1), e.get(2), 1.0);*/
    //C.set(temp);
}

Matrix4 Camera::getCameraMatrix()
{
    return C;
}

Vector3 Camera::getEye()
{
    return e;
}

Vector3 Camera::getLookat()
{
    return d;
}

Vector3 Camera::getUp()
{
    return up;
}

void Camera::resetCamera()
{
    C.identity();
    e.set(0,0,0);
    d.set(0,0,0);
    up.set(0,1,0);
}
