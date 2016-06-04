#ifndef GRAPH_H
#define GRAPH_H
#include "Structures/node.h"
#include "Structures/edge.h"
#include <vector>

using namespace std;

class Graph
{
public:
    Graph();
    Graph(vector<Node*> *nodeVector,float minX, float maxX, float minY, float maxY);
    Graph(vector<Node*> *nodeVector,vector<Edge*> *edgesVector);

    vector<Node*> *nodeVector;
    vector<Edge*> *edgesVector;
    bool isInit = false;
};

#endif // GRAPH_H
