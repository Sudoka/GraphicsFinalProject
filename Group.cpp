#include "Group.h"

void Group::addChild(Node * node)
{
    list.push_back(node);
}

void Group::removeChild(Node * node)
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

void Group::draw(Matrix4 m)
{
    for (int i = 0; i < list.size(); ++i)
        list[i]->draw(m);
}
