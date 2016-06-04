#include "graph.h"

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
}

Graph::Graph(vector<Node *> *nodeVector, vector<Edge *> *edgesVector)
{
    this->nodeVector = nodeVector;
    this->edgesVector = edgesVector;
}
