#ifndef BOTTLENECKTSP_H
#define BOTTLENECKTSP_H
#include "Structures/graph.h"
#include "Structures/forest.h"

class BottleneckTSP
{
public:
    BottleneckTSP();

    Graph* BTSPApprox(Graph* graph);

private:

    Graph* MBST(Graph*);

    Graph* MBSTContract(Forest* forest, vector<Edge*> *edges);

    float computeMedianWeight(Graph* graph);

    float findMedian(float *v, int n, int k);
};

#endif // BOTTLENECKTSP_H
