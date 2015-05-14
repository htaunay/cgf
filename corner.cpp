#include <stdio.h>
#include <stdlib.h>

#include <map>
#include <vector>

#include "node.h"
#include "edge.h"

std::vector<int> V({0,1,3,1,2,4,1,4,3,3,4,5});

std::map<Edge,unsigned int> edges;
void buildEdges()
{
    unsigned int size = V.size();
    for(unsigned int i = 0; i < size; i+=3)
    {
        edges[Edge(V[i  ], V[i+1])] = i+1;
        edges[Edge(V[i+1], V[i+2])] = i+2;
        edges[Edge(V[i+2], V[i  ])] = i;
    }
}

unsigned int nextCorner(unsigned int corner)
{
    return (3 * (corner/3)) + ((corner+1) % 3);
}

Node* root;
Node** nodes = new Node*[6];
void buildGraph()
{
    // Initialize nodes list
    for(unsigned int i = 0; i < 6; i++)
        nodes[i] = new Node(i);
    
    unsigned int size = V.size();
    for(unsigned int i = 0; i < size; i+=3)
    {
        nodes[V[i  ]]->addConnection(nodes[V[i+1]]);
        nodes[V[i+1]]->addConnection(nodes[V[i+2]]);
        nodes[V[i+2]]->addConnection(nodes[V[i  ]]);
    }   
}

int* O = new int[V.size()];
void buildOpposites()
{
    unsigned int size = V.size();
    for(unsigned int i = 0; i < size; i++)
        O[i] = -1;

    std::vector<Node*> queue;
    queue.push_back(nodes[0]);
    nodes[0]->setVisited(true);
    while(!queue.empty())
    {
        Node* node = queue.front();
        std::vector<Node*> connections = node->getConnections();

        for(unsigned int i = 0; i < connections.size(); i++)
        {
            if(!connections[i]->wasVisited())
            {
                queue.push_back(connections[i]);
                connections[i]->setVisited(true);
            }

            int from    = node->getID();
            int to      = connections[i]->getID(); 
            Edge current(from, to);
            Edge candidate(to, from);

            if(edges.find(candidate) != edges.end())
            {
                O[nextCorner(edges[candidate])] = nextCorner(edges[current]);
                O[nextCorner(edges[current])]   = nextCorner(edges[candidate]);
            }
        }
    
        connections.clear();
        queue.erase(queue.begin());
    }

    for(unsigned int i = 0; i < size; i++)
        printf("O[%d] = %d\n", i, O[i]);

    queue.clear();
    delete [] O;
}

int main(void)
{
    buildEdges();
    buildGraph();
    buildOpposites();

    V.clear();
    edges.clear();

    for(unsigned int i = 0; i < 6; i++)
         delete nodes[i];
    delete [] nodes;
}
