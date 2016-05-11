#ifndef NODE_H
#define NODE_H


class Node
{
public:
    Node();
    Node(float x, float y);

    float getX();
    void setX(float x);
    float getY();
    void setY(float y);
private:
    float x;
    float y;
};

#endif // NODE_H
