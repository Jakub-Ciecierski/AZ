#ifndef NODE_H
#define NODE_H
#include <vector>

class Node
{
public:
    Node();
    Node(float x, float y);

    std::vector<Node*> nodeVector;

    float getX();
    void setX(float x);
    float getY();
    void setY(float y);
private:
    float x;
    float y;
};

#endif // NODE_H
