#ifndef FOREST_H
#define FOREST_H

#include "Structures/edge.h"

using namespace std;
class Forest
{
public:
    Forest();
    Forest(vector<Edge*> *edgeVector, int graphSize);

    vector<vector<Edge*>> componentEdges;
    vector<vector<Node*>> componentNodes;
    int size;
    int spannedNodes;
};

#endif // FOREST_H
