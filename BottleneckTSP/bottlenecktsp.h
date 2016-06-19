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

    Graph* MBSTContract(Forest* forest, vector<Edge*> *edges,
                        vector<Node*> *allNodes);
    Graph* unpackGraph(Graph*);

    Edge* unpackEdge(Edge*);

    void unpackNodes(vector<Node*>* outNodeVector, vector<Edge*>* outEdgeVector, Node* packedNode);

    Forest* createForest(vector<Edge*> *edgeVector, int graphSize);

    float computeMedianWeight(Graph* graph);

    float findMedian(float *v, int n, int k);

    float findMedian(float *v, int size);

    //////HELPER FUNCTIONS/////

    vector<Edge*>* biggerThanMedian(vector<Edge*> *edgeVector,
                                    float median);
    vector<Edge*>* smallerOrEqualThanMedian(vector<Edge*> *edgeVector,
                                     float median);

    void divideEdgesByMedian(vector<Edge*> *edgeVector,
                             float median,vector<Edge*> *vectorA,vector<Edge*> *vectorB);
};

#endif // BOTTLENECKTSP_H
