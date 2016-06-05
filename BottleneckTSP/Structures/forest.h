#ifndef FOREST_H
#define FOREST_H

#include "Structures/edge.h"

using namespace std;
class Forest
{
public:
    Forest();
    Forest(vector<Edge*> *edgeVector);

    vector<vector<Edge*>> componentEdges;
    vector<vector<Node*>> componentNodes;
    int size;
};

#endif // FOREST_H
