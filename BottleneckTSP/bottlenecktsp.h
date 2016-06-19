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
    ///after function recursively retreive information about orginal graph
    Graph* unpackGraph(Graph*);

    ///find original edge represented by input edge
    Edge* unpackEdge(Edge*);

    ///find Nodes and Edges represented by packedNode (created during contracting forest
    void unpackNodes(vector<Node*>* outNodeVector, vector<Edge*>* outEdgeVector, Node* packedNode);

    ///At the beginning we store nodes and edges in vectors and nodes don't know about each other.
    ///In this function we want to create standard tree with root, children nodes and parents
    Graph* createStandardTree(Graph*);

    ///function finding children of a node in given graph
    void findChildren(Node* node, Graph* graph);

    ///function creating BTSP graph from mbstTree
    Graph* createBTSPGraph(Graph* graph);


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
