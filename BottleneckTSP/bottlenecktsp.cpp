#include "bottlenecktsp.h"

BottleneckTSP::BottleneckTSP()
{


}

Graph* BottleneckTSP::BTSPApprox(Graph *graph)
{

}

Graph* BottleneckTSP::MBST(Graph* graph)
{

}

Graph* BottleneckTSP::MBSTContract(Forest *forest, vector<Edge *> *edges)
{

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
