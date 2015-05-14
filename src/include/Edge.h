class Edge
{
    public:
 
        Edge(unsigned int from, unsigned int to);
        
        bool operator<(const Edge& e) const;

    private:

        unsigned int _from;
        unsigned int _to;
};

