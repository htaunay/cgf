#include "node.h"

Node::Node(unsigned int id)
{
    _id = id;
    _visited = false;
}

unsigned int Node::getID()
{
    return _id;
}

bool Node::wasVisited()
{
    return _visited;
}

void Node::setVisited(bool visited)
{
    _visited = visited;
}

void Node::addConnection(Node* node)
{
    _connections.push_back(node);
}

bool Node::hasConnection(Node* node)
{
    return false;
}

std::vector<Node*> Node::getConnections()
{
    return _connections;
}
