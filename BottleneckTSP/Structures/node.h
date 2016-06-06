#ifndef NODE_H
#define NODE_H
#include <vector>

using namespace std;
class Edge;
class Node
{
public:
    Node();
    Node(float x, float y);
    Node(vector<Node*> reprNodes,vector<Edge*> reprEdges);

    vector<Node*> nodeVector;

    /// vectors storing pointers to nodes and edges
    /// represented by this node after MTSB-Contract. Should be null if its normal node

    vector<Node*> reprNodes;
    vector<Edge*> reprEdges;

    float getX();
    void setX(float x);
    float getY();
    void setY(float y);
private:
    float x;
    float y;
};

#endif // NODE_H
