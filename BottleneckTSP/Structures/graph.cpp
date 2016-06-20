#include "graph.h"
#include <math.h>

Graph::Graph()
{
    root = nullptr;
    sumOfWeights = 0;
    bottleneckWeight = 0;
}

//changing values to floats for drawing purpose
Graph::Graph(vector<Node*> *nodeVector, float minX, float maxX, float minY, float maxY)
{
    root = nullptr;

    isInit = true;
    float divisor;
    if((maxX-minX)>(maxY-minY)) divisor = maxX - minX;
    else divisor = maxY - minY;
    this->nodeVector = *nodeVector;

    for(int i=0;i<nodeVector->size();i++)
    {
        nodeVector->at(i)->setX(((nodeVector->at(i)->getX()-minX)/divisor*2.f)-1.f);
        nodeVector->at(i)->setY(((nodeVector->at(i)->getY()-minY)/divisor*2.f)-1.f);
    }
    //TMP
    int size = 0;

    for(int i=0;i<nodeVector->size()-1;i++)
    {
        for(int j=i+1;j<nodeVector->size();j++)
        {
            size ++;
        }
    }

    this->edgesVector.resize(size);
    int num = 0;
    for(int i=0;i<nodeVector->size()-1;i++)
    {
        for(int j=i+1;j<nodeVector->size();j++)
        {
            Edge* edge = new Edge(nodeVector->at(i),nodeVector->at(j));
            edge->weight = computeWeight(nodeVector->at(i),nodeVector->at(j));
            this->edgesVector.at(num) = edge;
            num++;
        }
    }

    sumOfWeights = 0;
    bottleneckWeight = 0;
}

Graph::Graph(vector<Node *> *nodeVector, vector<Edge *> *edgesVector)
{
    this->nodeVector = *nodeVector;
    this->edgesVector = *edgesVector;
}

Graph::Graph(vector<Node *> &nodeVector, vector<Edge *> &edgesVector)
{
    this->nodeVector.clear();
    this->edgesVector.clear();
    for(int i=0;i<nodeVector.size();i++)
    {
        this->nodeVector.push_back(nodeVector.at(i));
    }
    for(int i=0;i<edgesVector.size();i++)
    {
        this->edgesVector.push_back(edgesVector.at(i));
    }
}

float Graph::computeWeight(Node *firstNode, Node *secondNode)
{
    return sqrt(pow(firstNode->getX()-secondNode->getX(),2)
                +pow(firstNode->getY()-secondNode->getY(),2));
}

float Graph::getBottleneck()
{
    float max = 0;
    for(int i=0;i<edgesVector.size();i++)
    {
        if(edgesVector.at(i)->weight > max) {
            bottleneckIndex = i;
            max = edgesVector.at(i)->weight;
        }
    }
    bottleneckWeight = max;
    return max;
}

float Graph::calculateSumOfWeights(){
    float sumOfWeights = 0;
    for(int i=0;i<edgesVector.size();i++)
    {
        sumOfWeights += edgesVector[i]->weight;
    }
    this->sumOfWeights = sumOfWeights;
    return sumOfWeights;
}


std::vector<string> Graph::toString(){
    vector<string> infos;
    infos.push_back("Name:              " + name);
    infos.push_back("Vertices:          " + std::to_string(this->nodeVector.size()));
    infos.push_back("Edges:             " + std::to_string(this->edgesVector.size()));
    infos.push_back("Sum of Weights:    " + std::to_string(sumOfWeights));
    infos.push_back("Bottleneck Weight: " + std::to_string(bottleneckWeight));

    return infos;
}
