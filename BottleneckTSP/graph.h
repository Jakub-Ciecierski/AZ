#ifndef GRAPH_H
#define GRAPH_H
#include "node.h"
#include <vector>

using namespace std;

class Graph
{
public:
    Graph();
    Graph(vector<Node> *nodeVector,float minX, float maxX, float minY, float maxY);

    vector<Node> *nodeVector;
    bool isInit = false;
};

#endif // GRAPH_H
