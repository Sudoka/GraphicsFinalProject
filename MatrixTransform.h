#ifndef _MATRIXTRANSFORM_H_
#define _MATRIXTRANSFORM_H_

#include "Group.h"

class MatrixTransform: public Group {
    public:
        Matrix4 curMatrix;
        MatrixTransform(string);
        MatrixTransform(string, Matrix4);
        MatrixTransform(string, MatrixTransform *);
        ~MatrixTransform()
        {
            for (int i = 0; i < list.size(); ++i)
                delete list[i];
        }
        void addChild(Node *);
        void removeChild(Node *);
        void draw(Matrix4);
};

#endif
