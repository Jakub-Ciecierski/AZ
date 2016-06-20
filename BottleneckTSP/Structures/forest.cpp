#include "forest.h"
#include <iostream>
Forest::Forest()
{

}
Forest::Forest(vector<Edge *> *edgeVector, int graphSize)
{
    ///while preventing cycles in graph we may remove some edges.
    ///Edges not removed from initial set are stored in tmpEdgeVector which will be assigned to initial vector
    vector<Edge*> tmpEdgeVector;

    //try to add each edge to a forest
    for(int i=0;i<edgeVector->size();i++)
    {
        ///check if nodes from edge are in a given tree of a forest. If both nodes are in the same component
        /// than we don't add this edge to a forest. If each node is in two different components than we merge
        /// these component's. If only only one node is in a given component than we add edge to this component.

        int firstNodeInComp = -1;
        int secondNodeInComp = -1;

        firstNodeInComp = edgeVector->at(i)->nodes[0]->compNum;
        secondNodeInComp = edgeVector->at(i)->nodes[1]->compNum;

        //add edge only to component containing second node
        if(firstNodeInComp == -1 && secondNodeInComp != -1)
        {
            componentEdges.at(secondNodeInComp).push_back(edgeVector->at(i));
            componentNodes.at(secondNodeInComp).push_back(edgeVector->at(i)->nodes[0]);
            edgeVector->at(i)->nodes[0]->compNum = secondNodeInComp;
            tmpEdgeVector.push_back(edgeVector->at(i));
        }
        //add edge only to component containing first node
        else if(firstNodeInComp != -1 && secondNodeInComp == -1)
        {
            componentEdges.at(firstNodeInComp).push_back(edgeVector->at(i));
            componentNodes.at(firstNodeInComp).push_back(edgeVector->at(i)->nodes[1]);
            edgeVector->at(i)->nodes[1]->compNum = firstNodeInComp;

            tmpEdgeVector.push_back(edgeVector->at(i));
        }
        else if(firstNodeInComp != -1 && secondNodeInComp != -1)
        {
            if(firstNodeInComp == secondNodeInComp)
            {
                //DO NOTHING
            }
            else //MERGE COMPONENTS
            {
                for(int j=0;j<componentEdges.at(firstNodeInComp).size();j++)
                {
                    componentEdges.at(secondNodeInComp).push_back(componentEdges.at(firstNodeInComp).at(j));
                }
                for(int j=0;j<componentNodes.at(firstNodeInComp).size();j++)
                {
                    componentNodes.at(secondNodeInComp).push_back(componentNodes.at(firstNodeInComp).at(j));
                    componentNodes.at(firstNodeInComp).at(j)->compNum = secondNodeInComp;
                }
                //adding current checked edge to merged component
                componentEdges.at(secondNodeInComp).push_back(edgeVector->at(i));

                componentEdges.at(firstNodeInComp).clear();
                componentNodes.at(firstNodeInComp).clear();

                tmpEdgeVector.push_back(edgeVector->at(i));
            }
        }
        else
        {
            int newComponentIndex = componentNodes.size();

            vector<Edge*> newComponentEdges;
            newComponentEdges.push_back(edgeVector->at(i));
            tmpEdgeVector.push_back(edgeVector->at(i));
            vector<Node*> newComponentNodes;
            newComponentNodes.push_back(edgeVector->at(i)->nodes[0]);
            newComponentNodes.push_back(edgeVector->at(i)->nodes[1]);
            edgeVector->at(i)->nodes[0]->compNum = newComponentIndex;
            edgeVector->at(i)->nodes[1]->compNum = newComponentIndex;

            componentEdges.push_back(newComponentEdges);
            componentNodes.push_back(newComponentNodes);
        }
    }
    for(int i =0; i<componentNodes.size();i++)
    {
        if(componentNodes.at(i).size() == 0)
        {
            componentNodes.erase(componentNodes.begin()+i);
            componentEdges.erase(componentEdges.begin()+i);
            i--;
        }
    }
    if(graphSize != componentNodes.at(0).size())
    {
    edgeVector->clear();
    for(int i=0;i<tmpEdgeVector.size();i++)edgeVector->push_back(tmpEdgeVector.at(i));
    }
    this->size = componentEdges.size();
    this->spannedNodes = componentNodes.at(0).size();

    ///reset compNum
    for(int i=0; i< componentNodes.size();i++)
    {
        for(int j=0;j<componentNodes.at(i).size();j++)
        {
            componentNodes.at(i).at(j)->compNum = -1;
        }
    }
}
