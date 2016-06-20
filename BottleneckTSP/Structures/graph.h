#ifndef GRAPH_H
#define GRAPH_H
#include "Structures/node.h"
#include "Structures/edge.h"
#include <vector>
#include <string>

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

    std::vector<string>  toString();

    int size;

    vector<Node*> nodeVector;
    vector<Edge*> edgesVector;

    Node* root;

    int bottleneckIndex;
    float sumOfWeights;
    float bottleneckWeight;

    bool isInit = false;

    std::string name;
};

#endif // GRAPH_H
