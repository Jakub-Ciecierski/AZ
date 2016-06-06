#include "bottlenecktsp.h"

BottleneckTSP::BottleneckTSP()
{


}

Graph* BottleneckTSP::BTSPApprox(Graph *graph)
{

}

Graph* BottleneckTSP::MBST(Graph* graph)
{
    if(graph->edgesVector->size() == 1)
    {
        return graph;
    }

    float median = computeMedianWeight(graph);
    vector<Edge*> *vectorA = biggerThanMedian(graph->edgesVector,median);
    vector<Edge*> *vectorB = smallerThanMedian(graph->edgesVector,median);

    if(vectorB->size() == graph->edgesVector->size())
    {
        vectorA->push_back(vectorB->at(vectorB->size()-1));
        vectorB->pop_back();
    }

    Forest* forest = createForest(vectorB);
    //check
    if(forest->size == 1)
    {
        Graph* graphPrime = new Graph(graph->nodeVector,vectorB);
        return MBST(graphPrime);
    }
    else{
        Graph* graphPrime = MBSTContract(forest,vectorA,graph->nodeVector);

        //return sum of forest and MBST(graphPrime)
    }
}

Graph* BottleneckTSP::MBSTContract(Forest *forest, vector<Edge *> *edges, vector<Edge*> allNodes)
{
    vector<Node*> *nodeVector;
    vector<Edge*> *edgeVector;
    //first add nodes representing component of F
    for(int i=0;i<forest->size;i++)
    {
        Node* node = new Node(forest->componentNodes.at(i),forest->componentEdges.at(i));
        nodeVector->push_back(node);
    }

    for(int i=0;i<allNodes.size();i++)
    {
     bool isNotInclued = true;

     for(int j=0;j<forest->size;j++)
     {
         for(int k=0;k<forest->componentNodes.at(j).size();k++)
         {
            if(forest->componentNodes.at(j).at(k) == allNodes.at(i))
            {
                isNotInclued = false;
                break;
            }
         }
         if(!isNotInclued)break;
     }

     if(isNotInclued)
     {
        nodeVector->push_back(allNodes.at(i));
     }
    }
}
Forest* BottleneckTSP::createForest(vector<Edge *> *edgeVector)
{
    return new Forest(edgeVector);
}


float BottleneckTSP::computeMedianWeight(Graph *graph)
{
    float* weights = new float[graph->edgesVector->size()];
    for(int i=0;i<graph->edgesVector->size();i++)
    {
        weights[i] = graph->edgesVector->at(i)->weight;
    }
    return findMedian(weights,graph->edgesVector->size(),0);
}

float BottleneckTSP::findMedian(float *v, int n, int k)
{
   // int find_kth(int *v, int n, int k) {
        if (n == 1 && k == 0) return v[0];

        int m = (n + 4)/5;
        float *weights = new float[m];
        for (int i=0; i<m; i++) {
            if (5*i + 4 < n) {
                float *w = v + 5*i;
                for (int j0=0; j0<3; j0++) {
                    int jmin = j0;
                    for (int j=j0+1; j<5; j++) {
                        if (w[j] < w[jmin]) jmin = j;
                    }
                    swap(w[j0], w[jmin]);
                }
                weights[i] = w[2];
            } else {
                weights[i] = v[5*i];
            }
        }

        float pivot = findMedian(weights, m, m/2);
        delete [] weights;

        for (int i=0; i<n; i++) {
            if (v[i] == pivot) {
                swap(v[i], v[n-1]);
                break;
            }
        }

        int store = 0;
        for (int i=0; i<n-1; i++) {
            if (v[i] < pivot) {
                swap(v[i], v[store++]);
            }
        }
        swap(v[store], v[n-1]);

        if (store == k) {
            return pivot;
        } else if (store > k) {
            return findMedian(v, store, k);
        } else {
            return findMedian(v+store+1, n-store-1, k-store-1);
        }

}

vector<Edge*>* BottleneckTSP::biggerThanMedian(vector<Edge *> *edgeVector,
                                               float median)
{

}

vector<Edge*>* BottleneckTSP::smallerThanMedian(vector<Edge *> *edgeVector,
                                               float median)
{

}
