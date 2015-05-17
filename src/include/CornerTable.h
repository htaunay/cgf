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

        static std::map<Edge, unsigned int>
        buildEdges(std::vector<uint> vertices);

        static uint nextCorner(uint corner);

        static std::vector<Node*> buildGraph(std::vector<uint> vertices);

        static std::vector<int> buildOpposites(std::map<Edge,
                unsigned int> edges, std::vector<Node*> nodes,
                unsigned int numVertices);
};
