#include <Edge.h>

Edge::Edge(unsigned int from, unsigned int to)
{
    _from   = from;
    _to     = to;
}

bool Edge::operator<(const Edge& e) const
{
    return _from < e._from || (_from == e._from && _to < e._to);
}
