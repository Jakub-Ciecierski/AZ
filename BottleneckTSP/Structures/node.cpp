#include "node.h"

Node::Node()
{

}
Node::Node(float x, float y)
{
    this->x = x;
    this->y = y;
}

Node::Node(vector<Node *> reprNodes, vector<Edge *> reprEdges)
{
    this->reprNodes = reprNodes;
    this->reprEdges = reprEdges;
}

float Node::getX(){return x;}

float Node::getY(){return y;}

void Node::setX(float x){ this->x = x;}

void Node::setY(float y){ this->y = y;}

