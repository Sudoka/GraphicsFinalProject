#include "MatrixTransform.h"

MatrixTransform::MatrixTransform(string name)
{
    this->name = name;
    this->curMatrix.identity();
}

MatrixTransform::MatrixTransform(string name, Matrix4 n) 
{
    this->name = name;
    this->curMatrix = n;
}

MatrixTransform::MatrixTransform(string name, MatrixTransform * m)
{
    this->name = name;
    this->curMatrix = m->curMatrix;
    this->list = vector<Node*>(m->list);
}

void MatrixTransform::addChild(Node * node)
{
    list.push_back(node);
}

void MatrixTransform::removeChild(Node * node)
{
    for (vector<Node *>::iterator it = list.begin(); it < list.end(); ++it)
    {
        if ((*it)->getName().compare(name) == 0)
        {
            list.erase(it);
            break;
        }
    }
}

void MatrixTransform::draw(Matrix4 m)
{
    for (vector<Node*>::iterator it = list.begin(); it < list.end(); ++it)
    {
        (*it)->draw(m.multiply(curMatrix)); // TODO: might have to flip order
    }
}
