#include "Torus.h"

extern float planes[6][4];
extern bool isCulling;

bool Torus::isInBoundingSphere(Matrix4 m)
{
    Vector3 p = Vector3(m.get(0,3), m.get(1,3), m.get(2,3));
    double myRadius = fabs(outer);
    for (int i = 0; i < 6; ++i)
    {
        Vector3 n(planes[i][0], planes[i][1], planes[i][2]);
        if (n.dot(p) + planes[i][3] <= -myRadius)
            return false;
    }
    return true;
}

void Torus::draw(Matrix4 m)
{
    if (isCulling && !isInBoundingSphere(m)) return;
    glColor3f(r,g,b);
    glLoadMatrixd(m.getGLPointer());
    glutSolidTorus(inner,outer, 50, 50);
}
