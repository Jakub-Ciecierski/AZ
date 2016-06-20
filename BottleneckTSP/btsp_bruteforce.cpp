#include "btsp_bruteforce.h"
#include <stdexcept>
#include <iostream>
#include "math.h"

using namespace std;

BTSPBruteforce::BTSPBruteforce(Graph* graph) :
    graph(graph){
    count = 0;
}

Graph* BTSPBruteforce::solve(int rootIndex){
    int nodeCount = graph->nodeVector.size();
    if(rootIndex < 0 || rootIndex >= nodeCount){
        throw std::invalid_argument("Invalid root index");
    }

    vector<vector<int>> sequences = getAllSequences(rootIndex, nodeCount);
    vector<int> btspSequence = getLeastBottleneckSequence(sequences);
    Graph* btspGraph = constructGraph(btspSequence);

    return btspGraph ;
}

std::vector<vector<int>> BTSPBruteforce::getAllSequences(int rootIndex,
                                                         int count){
    vector<vector<int>> sequences;
    vector<int> initSequence;

    for(int i = 0; i < count; i++){
        initSequence.push_back(i);
    }

    do{
        if(initSequence[0] == rootIndex){
            vector<int> seq = initSequence;
            seq.push_back(rootIndex);
            sequences.push_back(seq);
        }
    }while(!permutate(initSequence.data(), count));

    return sequences;
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

vector<int> BTSPBruteforce::getLeastBottleneckSequence(vector<vector<int>>& sequences){
    float leastBottleneck = 999999.9f;
    int leastBottleneckIndex = -1;
    for(unsigned int i = 0; i < sequences.size(); i++){
        vector<int>& seq = sequences[i];
        float bottleneck = calculateBottleneck(seq);
        if(leastBottleneck > bottleneck){
            leastBottleneckIndex = 1;
            leastBottleneck = bottleneck;
        }
    }

    return sequences[leastBottleneckIndex];
}

float BTSPBruteforce::calculateBottleneck(vector<int>& seq){
    float bottleneck = 0;
    for(int i = 1; i < seq.size(); i++){
        Node* n1 = graph->nodeVector[seq[i-1]];
        Node* n2 = graph->nodeVector[seq[i]];

        float weight = calculateWeight(n1, n2);
        if(weight > bottleneck){
            bottleneck = weight;
        }
    }
    return bottleneck;
}


float BTSPBruteforce::calculateWeight(Node* n1, Node* n2){
    float weight = sqrt(pow(n1->getX() - n2->getX(), 2) +
                        pow(n1->getY() - n2->getY(), 2));
    return weight;
}


Graph* BTSPBruteforce::constructGraph(vector<int>& sequence){
    Graph* btspGraph = new Graph();
    vector<Node*> nodes = graph->nodeVector;
    vector<Edge*> edges;

    for(unsigned int i = 1; i < sequence.size(); i++){
        Edge* edge = new Edge(nodes[sequence[i-1]], nodes[sequence[i]]);
        edges.push_back(edge);
    }

    btspGraph->edgesVector = edges;
    btspGraph->nodeVector = nodes;

    return btspGraph;
}
