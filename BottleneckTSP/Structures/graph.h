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
    Graph(vector<Node*> &nodeVector,vector<Edge*> &edgesVector);

    float computeWeight(Node* firstNode, Node* secondNode);
    float getBottleneck();
    float calculateSumOfWeights();

    int size;

    vector<Node*> nodeVector;
    vector<Edge*> edgesVector;

    Node* root;

    int bottleneckIndex;

    bool isInit = false;
};

#endif // GRAPH_H
