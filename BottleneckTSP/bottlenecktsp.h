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

    Forest* createForest(vector<Edge*> *edgeVector);

    float computeMedianWeight(Graph* graph);

    float findMedian(float *v, int n, int k);

    //////HELPER FUNCTIONS/////

    vector<Edge*>* biggerThanMedian(vector<Edge*> *edgeVector,
                                    float median);
    vector<Edge*>* smallerThanMedian(vector<Edge*> *edgeVector,
                                     float median);

};

#endif // BOTTLENECKTSP_H
