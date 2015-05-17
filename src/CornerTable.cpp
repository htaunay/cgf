#include <stdio.h>
#include <stdlib.h>

#include <map>
#include <vector>
#include <string>

#include <CornerTable.h>
#include <Node.h>
#include <Edge.h>

#define MAX_CHARS_PER_LINE 512

std::vector<int> CornerTable::BuildCornerTable(std::string fileName)
{
    std::vector<unsigned int> vertices = loadIndexes(fileName);
    unsigned int numVertices = vertices.size();

    std::map<Edge, unsigned int> edges = buildEdges(vertices);
    std::vector<Node*> nodes = buildGraph(vertices);
    std::vector<int> O = buildOpposites(edges, nodes, numVertices);

    nodes.clear();
    edges.clear();
    vertices.clear();

        return O;
}

std::vector<unsigned int> CornerTable::loadIndexes(std::string fileName)
{
	FILE * file;
	file = fopen(fileName.c_str(), "r");

	unsigned int numIndexes, numTriangles;
	fscanf(file, "%u %u", &numIndexes, &numTriangles);

	float a,b,c;
	for(unsigned int i = 0; i < numIndexes; i++)
		fscanf(file, "%f %f %f", &a, &b, &c);

	int line, p1, p2, p3;
    std::vector<unsigned int> V;
	for(unsigned int i = 0; i < numTriangles; i++)
	{
		fscanf(file, "%d %d %d %d", &line, &p1, &p2, &p3);
		V.push_back(p1);
		V.push_back(p2);
		V.push_back(p3);
	}

	fclose(file);
    return V;
}

std::map<Edge, unsigned int> CornerTable::buildEdges(std::vector<unsigned int> vertices)
{
    std::map<Edge,unsigned int> edges;
    unsigned int size = vertices.size();

    for(unsigned int i = 0; i < size; i+=3)
    {
        edges[Edge(vertices[i  ], vertices[i+1])] = i+1;
        edges[Edge(vertices[i+1], vertices[i+2])] = i+2;
        edges[Edge(vertices[i+2], vertices[i  ])] = i;
    }

    return edges;
}

unsigned int CornerTable::nextCorner(unsigned int corner)
{
    return (3 * (corner/3)) + ((corner+1) % 3);
}

std::vector<Node*> CornerTable::buildGraph(std::vector<unsigned int> vertices)
{
    unsigned int numVertices = vertices.size();
    std::vector<Node*> nodes;
    for(unsigned int i = 0; i < numVertices; i++)
        nodes.push_back(new Node(i));
    
    unsigned int size = vertices.size();
    for(unsigned int i = 0; i < size; i+=3)
    {
        nodes[vertices[i  ]]->addConnection(nodes[vertices[i+1]]);
        nodes[vertices[i+1]]->addConnection(nodes[vertices[i+2]]);
        nodes[vertices[i+2]]->addConnection(nodes[vertices[i  ]]);
    }

    return nodes;
}

std::vector<int> CornerTable::buildOpposites(std::map<Edge,unsigned int> edges,
        std::vector<Node*> nodes, unsigned int numVertices)
{
    std::vector<int> O;
    for(unsigned int i = 0; i < numVertices; i++)
		O.push_back(-1);

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

    queue.clear();
    return O;
}
