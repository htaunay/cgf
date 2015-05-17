#ifndef __NODE__
#define __NODE__

#include <vector>

class Node
{
    public:

        Node(unsigned int id);
        unsigned int getID();

        bool wasVisited();
        void setVisited(bool visited);

        void addConnection(Node* node);
        bool hasConnection(Node* node);
        std::vector<Node*> getConnections();

    private:

        unsigned int _id;
        bool _visited;
        std::vector<Node*> _connections;
};

#endif
