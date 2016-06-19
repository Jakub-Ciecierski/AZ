#include "node.h"

Node::Node()
{
   this->parent = nullptr;
   this->wasVisited = false;
}
Node::Node(float x, float y)
{
    this->x = x;
    this->y = y;
    this->parent = nullptr;
    this->wasVisited = false;
}

Node::Node(vector<Node *> reprNodes, vector<Edge *> reprEdges)
{
    this->reprNodes = reprNodes;
    this->reprEdges = reprEdges;
    this->parent = nullptr;
    this->wasVisited = false;

}

float Node::getX(){return x;}

float Node::getY(){return y;}

void Node::setX(float x){ this->x = x;}

void Node::setY(float y){ this->y = y;}

