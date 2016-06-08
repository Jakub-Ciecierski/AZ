#include "graph.h"
#include <math.h>

Graph::Graph()
{

}

//changing values to floats for drawing purpose
Graph::Graph(vector<Node*> *nodeVector, float minX, float maxX, float minY, float maxY)
{
    isInit = true;
    float divisor;
    if((maxX-minX)>(maxY-minY)) divisor = maxX - minX;
    else divisor = maxY - minY;
    this->nodeVector = nodeVector;

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
    this->edgesVector = new vector<Edge*>();
    this->edgesVector->resize(size);
    int num = 0;
    for(int i=0;i<nodeVector->size()-1;i++)
    {
        for(int j=i+1;j<nodeVector->size();j++)
        {
            Edge* edge = new Edge(nodeVector->at(i),nodeVector->at(j));
            edge->weight = computeWeight(nodeVector->at(i),nodeVector->at(j));
            this->edgesVector->at(num) = edge;
            num++;
        }
    }
}

Graph::Graph(vector<Node *> *nodeVector, vector<Edge *> *edgesVector)
{
    this->nodeVector = nodeVector;
    this->edgesVector = edgesVector;
}

float Graph::computeWeight(Node *firstNode, Node *secondNode)
{
    return sqrt(pow(firstNode->getX()-secondNode->getX(),2)
                +pow(firstNode->getY()-secondNode->getY(),2));
}
