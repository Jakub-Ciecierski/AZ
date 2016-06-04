#ifndef EDGE_H
#define EDGE_H
#include "Structures/node.h"

class Edge
{
public:
    Edge(Node* firstNode, Node* secondNode);
    Node* nodes[2];
    float weight;
};

#endif // EDGE_H
