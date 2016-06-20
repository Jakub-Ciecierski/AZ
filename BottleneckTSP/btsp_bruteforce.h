#ifndef BTSP_BRUTEFORCE_H
#define BTSP_BRUTEFORCE_H

#include "Structures/graph.h"

class BTSPBruteforce
{
private:
    Graph* graph;

    int count;

    void rotate(int vec[], int size);
    int permutate(int *start, int size);

public:
    BTSPBruteforce(Graph* graph);

    void solve(int rootIndex);

};

#endif // BTSP_BRUTEFORCE_H
