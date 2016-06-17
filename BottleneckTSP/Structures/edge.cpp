#include "edge.h"

Edge::Edge(Node* firstNode, Node* secondNode)
{
    nodes.push_back(firstNode);
    nodes.push_back(secondNode);
    this->parent = nullptr;
}
