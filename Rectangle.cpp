#include "Rectangle.h"

extern float planes[6][4];
extern bool isCulling;

bool Rectangle::isInBoundingSphere(Matrix4 m)
{
    Vector3 p = Vector3(m.get(0,3), m.get(1,3), m.get(2,3));
    double myRadius = max(fabs(width/float(2)), 
                      max(fabs(base/float(2)), fabs(height/(float(2)))));
    for (int i = 0; i < 6; ++i)
    {
        Vector3 n(planes[i][0], planes[i][1], planes[i][2]);
        if (n.dot(p) + planes[i][3] <= -myRadius)
            return false;
    }
    return true;
}

void Rectangle::draw(Matrix4 m)
{
    if (isCulling && !isInBoundingSphere(m)) return;
    glColor3d(r,g,b);
    m.scale(1.0, height/base, width/base);
    glLoadMatrixd(m.getGLPointer());
    glutSolidCube(base);
}


