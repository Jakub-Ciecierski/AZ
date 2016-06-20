#ifndef BTSP_BRUTEFORCE_H
#define BTSP_BRUTEFORCE_H

#include "Structures/graph.h"

/**
 * Solves BTSP problem with Bruteforce.
 * Finds all permutations representing hamiltonian cycles.
 * Chooses the one with least heaviest weight edge.
 * */
class BTSPBruteforce
{
private:
    Graph* graph;

    int count;

    std::vector<vector<int>> getAllSequences(int rootIndex, int count);
    void rotate(int vec[], int size);
    int permutate(int *start, int size);

    vector<int> getLeastBottleneckSequence(vector<vector<int>>& sequences);
    float calculateBottleneck(vector<int>& seq);
    float calculateWeight(Node* n1, Node* n2);

    Graph* constructGraph(vector<int>& sequence);

public:
    BTSPBruteforce(Graph* graph);

    Graph*  solve(int rootIndex);

};

#endif // BTSP_BRUTEFORCE_H
