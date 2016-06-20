#include "btsp_bruteforce.h"
#include <stdexcept>
#include <iostream>

using namespace std;

BTSPBruteforce::BTSPBruteforce(Graph* graph) :
    graph(graph){
    count = 0;
}


void BTSPBruteforce::solve(int rootIndex){
    int nodeCount = graph->nodeVector.size();
    if(rootIndex < 0 || rootIndex >= nodeCount){
        throw std::invalid_argument("Invalid root index");
    }

    int startIndex = 0;
    int endIndex = nodeCount -1;

    vector<vector<int>> sequences;
    vector<int> initSequence;

    for(int i = 0; i < nodeCount; i++){
        initSequence.push_back(i);
    }

    do{
        sequences.push_back(initSequence);
        for(int i = 0; i < nodeCount; i++){
            cout << initSequence[i] << ", ";
        }
        cout << endl;
    }while(!permutate(initSequence.data(), nodeCount));
}

void BTSPBruteforce::rotate(int vec[], int size){
    int i, j, first;

    first = vec[0];
    for(j = 0, i = 1; i < size; i++, j++)
    {
        vec[j] = vec[i];
    }
    vec[j] = first;
}

int BTSPBruteforce::permutate(int *start, int size)
{
    static int fact;

    if(size > 1) {
        if(permutate(start + 1, size - 1))
        {
            rotate(start, size);
        }
        fact *= size;
    }
    else{
        count++;
        fact = 1;
    }

    return !(count % fact);
}
