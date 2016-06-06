#include "forest.h"

Forest::Forest()
{

}
Forest::Forest(vector<Edge *> *edgeVector)
{
    //try to add each edge to a forest
    for(int i=0;i<edgeVector->size();i++)
    {
        ///check if nodes from edge are in a given tree of a forest. If both nodes are in the same component
        /// than we don't add this edge to a forest. If each node is in two different components than we merge
        /// these component's. If only only one node is in a given component than we add edge to this component.

        int firstNodeInComp = -1;
        int secondNodeInComp = -1;

        for(int j=0;j<componentNodes.size();j++)
        {
            for(int k=0;k<componentNodes.at(j).size();k++)
            {
                //PORÓWNANIE REFERENCJI A NIE WSKAŹNIKA?
                if(componentNodes.at(j).at(k) == edgeVector->at(i)->nodes[0])
                {
                    firstNodeInComp = j;
                }
                else if(componentNodes.at(j).at(k) == edgeVector->at(i)->nodes[1])
                {
                    secondNodeInComp = j;
                }
            }
        }
        //add edge only to component containing second node
        if(firstNodeInComp == -1 && secondNodeInComp != -1)
        {
            componentEdges.at(secondNodeInComp).push_back(edgeVector->at(i));
            componentNodes.at(secondNodeInComp).push_back(edgeVector->at(i)->nodes[0]);
            componentNodes.at(secondNodeInComp).push_back(edgeVector->at(i)->nodes[1]);
        }
        //add edge only to component containing first node
        else if(firstNodeInComp != -1 && secondNodeInComp == -1)
        {
            componentEdges.at(firstNodeInComp).push_back(edgeVector->at(i));
            componentNodes.at(firstNodeInComp).push_back(edgeVector->at(i)->nodes[0]);
            componentNodes.at(firstNodeInComp).push_back(edgeVector->at(i)->nodes[1]);
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
                }
                componentEdges.erase(componentEdges.begin()+firstNodeInComp);
                componentNodes.erase(componentNodes.begin()+firstNodeInComp);
            }
        }
        else
        {
            int newComponentIndex = componentNodes.size();

            vector<Edge*> newComponentEdges;
            newComponentEdges.push_back(edgeVector->at(i));
            vector<Node*> newComponentNodes;
            newComponentNodes.push_back(edgeVector->at(i)->nodes[0]);
            newComponentNodes.push_back(edgeVector->at(i)->nodes[1]);

            componentEdges.push_back(newComponentEdges);
            componentNodes.push_back(newComponentNodes);
        }
    }

    size = componentEdges.size();
}
