#include "edge.h"
#include "math.h"
Edge::Edge(Node* firstNode, Node* secondNode)
{
    nodes.push_back(firstNode);
    nodes.push_back(secondNode);
    weight = sqrt(pow(firstNode->getX()-secondNode->getX(),2)+pow(firstNode->getY()-secondNode->getY(),2));
    this->parent = nullptr;
}
