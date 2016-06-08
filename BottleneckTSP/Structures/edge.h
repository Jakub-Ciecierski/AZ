#ifndef EDGE_H
#define EDGE_H
#include "Structures/node.h"

class Edge
{
public:
    Edge(Node* firstNode, Node* secondNode);
    vector<Node*> nodes;

    /// pointer to nodes before MBST-Contract (if have been done)
    Edge* parent;

    float weight;
};

#endif // EDGE_H
