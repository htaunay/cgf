#ifndef __CORNER_TABLE__
#define __CORNER_TABLE__

#include <map>
#include <string>
#include <vector>

#include <Edge.h>
#include <Node.h>

class CornerTable
{
    public:
        static std::vector<int> BuildCornerTable(std::string fileName);
        static std::vector<int> BuildCHE(std::string fileName);

    private:

        static std::vector<unsigned int> loadIndexes(std::string fileName);

        static unsigned int nextCorner(unsigned int corner);
        static unsigned int prevCorner(unsigned int corner);

        static std::map<Edge, unsigned int>
        buildEdges(std::vector<unsigned int> vertices);

        static std::vector<Node*> buildGraph(
                std::vector<unsigned int> vertices);

        static std::vector<int> buildOpposites(
                std::map<Edge,unsigned int> edges, std::vector<Node*> nodes,
                unsigned int numvertices);

        static std::vector<int> buildHalfEdges(
                std::map<Edge,unsigned int> edges, std::vector<Node*> nodes,
                unsigned int numvertices);
};

#endif
