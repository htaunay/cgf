#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <vector>

class Node
{
    public:
        Node() {}
        int id;
        std::vector<Node*> connections;
};

float array[] = {0,1,2,1,4,2,3,4,1,2,4,5};

std::vector<Node*> nodeList(12);

void connectNodes(Node* a, Node* b)
{
    if(std::find(a->connections.begin(),
                 a->connections.end(),
                 b) == a->connections.end())
    {
        a->connections.push_back(b);
    }

    if(std::find(b->connections.begin(),
                 b->connections.end(),
                 a) == b->connections.end())
    {
        b->connections.push_back(a);
    }
}

void buildNodeList()
{
    for(int i = 0; i < 12; i++)
    {
        nodeList[i] = new Node();
        nodeList[i]->id = i;
    }

    for(int i = 0; i < 12; i += 3)
    {
        connectNodes(nodeList[array[i]],   nodeList[array[i+1]]);
        connectNodes(nodeList[array[i+1]], nodeList[array[i+2]]);
        connectNodes(nodeList[array[i+2]], nodeList[array[i]]);
    }
}

float* buildOppositeArray(float* triangleArray, int arraySize)
{

    return NULL;
}

int main()
{
    buildNodeList();

    for(int i = 0; i < 6; i++)
    {
        printf("Node %d is connected to: ", i);
        for(unsigned int j = 0; j < nodeList[i]->connections.size(); j++)
            printf("%d ", nodeList[i]->connections[j]->id);
        printf("\n");
    }

    return 1;
}
