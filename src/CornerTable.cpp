#include <stdio.h>
#include <stdlib.h>

#include <map>
#include <vector>
#include <string>

#include <Node.h>
#include <Edge.h>

#define MAX_CHARS_PER_LINE 512

int* O;
Node** nodes;
std::vector<int> V;
unsigned int numVertices;
std::map<Edge,unsigned int> edges;

void loadFile(std::string fileName)
{
	FILE * file;
	file = fopen(fileName.c_str(), "r");

	int numTriangles;
	fscanf(file, "%d %d", &numVertices, &numTriangles);

	float a,b,c;
	for(int i = 0; i < numVertices; i++)
		fscanf(file, "%f %f %f", &a, &b, &c);

	int line, p1, p2, p3;
	for(int i = 0; i < numTriangles; i++)
	{
		fscanf(file, "%d %d %d %d", &line, &p1, &p2, &p3);
		V.push_back(p1);
		V.push_back(p2);
		V.push_back(p3);
	}

	fclose(file);
}

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

void buildGraph()
{
    for(unsigned int i = 0; i < numVertices; i++)
        nodes[i] = new Node(i);
    
    unsigned int size = V.size();
    for(unsigned int i = 0; i < size; i+=3)
    {
        nodes[V[i  ]]->addConnection(nodes[V[i+1]]);
        nodes[V[i+1]]->addConnection(nodes[V[i+2]]);
        nodes[V[i+2]]->addConnection(nodes[V[i  ]]);
    }   
}

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
        printf("%d ", O[i]);
	printf("\n");

    queue.clear();
    delete [] O;
}

int main(int argc, char** argv)
{
	std::string fileName(argv[1]);
	loadFile(fileName);

	nodes = new Node*[numVertices];
	O = new int[V.size()];

    buildEdges();
    buildGraph();
    buildOpposites();

    V.clear();
    edges.clear();

    for(unsigned int i = 0; i < numVertices; i++)
         delete nodes[i];
    delete [] nodes;
}
