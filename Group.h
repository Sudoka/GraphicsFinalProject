#ifndef _GROUP_H_
#define _GROUP_H_

#include "Node.h"
#include <vector>

class Group: public Node {
    protected:
        vector< Node* > list;
    public:
        virtual void addChild(Node *) = 0;
        virtual void removeChild(Node *) = 0;
        void draw(Matrix4);
};

#endif
