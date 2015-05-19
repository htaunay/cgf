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

        enum Method
        {
            Corner,
            CHE
        };

        static std::vector<int>
        BuildOpposites(Method method, std::string fileName);

    private:

        static std::vector<unsigned int> loadIndexes(std::string fileName);

        static unsigned int nextCorner(unsigned int corner);
        static unsigned int prevCorner(unsigned int corner);

        static std::map<Edge, unsigned int>
        buildEdges(std::vector<unsigned int> vertices);

        static std::vector<Node*> buildGraph(
                std::vector<unsigned int> vertices);

        static std::vector<int> buildOpposites(Method method,
                std::map<Edge,unsigned int> edges, std::vector<Node*> nodes,
                unsigned int numvertices);
};

#endif
