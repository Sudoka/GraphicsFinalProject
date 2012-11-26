#ifndef _GEODE_H_
#define _GEODE_H_

#include "Node.h"

class Geode: public Node {
    virtual bool isInBoundingSphere(Matrix4) = 0;
    virtual void draw(Matrix4) = 0;
};

#endif
