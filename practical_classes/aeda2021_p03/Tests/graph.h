#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <class N, class E> class Edge;

template <class N>
class NodeAlreadyExists;

template <class N>
class NodeDoesNotExist;

template <class N>
class EdgeAlreadyExists;

template <class N>
class EdgeDoesNotExist;

template <class N, class E>
class Node {
public:
    N info;
    vector< Edge<N,E> > edges;

    /**
     * Create a node with a name
     * @param inf - node name
     */
    explicit Node(N inf) {
        info = inf;
    }

    /**
     * Get number of edges beginning at the node
     * @return number of edges
     */
    unsigned getNumEdges() const {
        return edges.size();
    }

    /**
     * Add edge beginning at the node
     * @param edge - to add
     */
    void addEdge(const Edge<N,E>& edge){
        edges.push_back(edge);
    }
};

template <class N, class E>
class Edge {
public:
    E value;
    Node<N,E> *destination;

    /**
     * Create an edge with a destination and a value
     * @param dest - points to the end node
     * @param val - edge value
     */
    Edge(Node<N,E> *dest, E val) {
        value = val;
        destination = dest;
    }

    /**
     * Checks if two edges are equal (same destination)
     * @param e2 - edge to compare to
     * @return equality result
     */
    bool operator==(const Edge& e2) const {
        return destination == e2.destination;
    }
};

template <class N, class E>
class Graph {
    vector< Node<N,E> *> nodes;
public:

    /**
     * Construct a new graph without nodes
     */
    Graph() : nodes(vector<Node<N,E>*>()){

    }

    /**
     * Destructs nodes of the graph
     */
    ~Graph(){
        for (auto& n: nodes){
            delete n;
        }
    }

    /**
     * Adds node to the graph. If it already exists, throws NodeAlreadyExists
     * @param inf - node name
     * @return pointer to the graph
     */
    Graph& addNode(const N& inf){
        for (const auto& n: nodes){
            if (n->info == inf){
                throw NodeAlreadyExists<N>(inf);
            }
        }
        nodes.push_back(new Node<N,E>(inf));
        return *this;
    }

    /**
     * Add edge beginning and ending at desired nodes. If nodes aren't found
     * or edge already exists, throws respective exception
     * @param begin - begin node info
     * @param end - end node info
     * @param val - edge value
     * @return pointer to the graph
     */
    Graph& addEdge(const N &begin, const N &end, const E &val) {
        // search for end node
        bool foundEnd = false;
        Node<N,E>* endNode;
        for (auto& n: nodes){
            if (n->info == end){
                foundEnd = true;
                endNode = n;
            }
        }
        if (!foundEnd){
            throw NodeDoesNotExist<N>(end);
        }

        // search for begin node
        bool foundBegin = false;
        Node<N,E>* beginNode;
        for (auto& n: nodes){
            if (n->info == begin){
                foundBegin = true;
                beginNode = n;
            }
        }
        if (!foundBegin){
            throw NodeDoesNotExist<N>(begin);
        }

        // confirm edge does not already exist
        if (find_if(beginNode->edges.begin(),beginNode->edges.end(),[endNode,val](const Edge<N,E> e)
        { return Edge<N,E>(endNode,val) == e;}) != beginNode->edges.end()){
            throw EdgeAlreadyExists<N>(begin,end);
        }

        beginNode->addEdge(Edge<N,E>(endNode,val));
        return *this;
    }

    /**
     * Removes edge connecting two desired nodes. If begin node isn't found or
     * edge does not exist, adequate exception is thrown
     * @param begin - begin node info
     * @param end - end node info
     * @return pointer to the graph
     */
    Graph & removeEdge(const N &begin, const N &end){
        for (const auto& beginNode: nodes){
            if (beginNode->info == begin){
                for (auto it = beginNode->edges.begin(); it != beginNode->edges.end(); ++it){
                    if (it->destination->info == end) {
                        beginNode->edges.erase(it);
                        return *this;
                    }
                }
                throw EdgeDoesNotExist<N>(begin, end);
            }
        }
        throw NodeDoesNotExist<N>(begin);
    }


    /**
     * Gets value of the edge connecting two desired nodes. If begin node
     * isn't found or edge does not exist will throw adequate exception
     * @param begin - begin node info
     * @param end - end node info
     * @return pointer to the value of the found edge
     */
    E & edgeValue(const N &begin, const N &end){
        for (const auto& beginNode: nodes){
            if (beginNode->info == begin){
                for (auto& edge: beginNode->edges) {
                    if (edge.destination->info == end) {
                        return edge.value;
                    }
                }
                throw EdgeDoesNotExist<N>(begin, end);
            }
        }
        throw NodeDoesNotExist<N>(begin);
    }

    /**
     * Gets number of edges the graph has
     * @return total number of edges (sum for each node)
     */
    unsigned numEdges() const{
        unsigned sum = 0;
        for (const auto& n: nodes){
            sum += n->getNumEdges();
        }
        return sum;
    }

    /**
     * Gets number of nodes the graph has
     * @return number of nodes
     */
    unsigned numNodes() const{
        return nodes.size();
    }

    /**
     * Output graph nodes and respective edges in the format
     * " ( NODE_INFO[ EDGE_DEST EDGE_VAL] ... ) ... "
     * @param os - stream to output to
     */
    void print(std::ostream &os) const{
        for (const Node<N,E>* n: nodes){
            os << "( " << n->info;
            for (const Edge<N,E>& e: n->edges){
                os << "[ " << e.destination->info << " " << e.value << "] ";
            }
            os << ") ";
        }
    }
};

template <class N, class E>
std::ostream & operator<<(std::ostream &out, const Graph<N,E> &g){
    g.print(out);
}


// exception NodeAlreadyExists
template <class N>
class NodeAlreadyExists
{
public:
    N info;
    explicit NodeAlreadyExists(N inf) { info=inf; }
};

template <class N>
std::ostream & operator<<(std::ostream &out, const NodeAlreadyExists<N> &no)
{ out << "Node already exists: " << no.info; return out; }


// exception NodeDoesNotExist
template <class N>
class NodeDoesNotExist {
public:
    N info;
    explicit NodeDoesNotExist(N inf) {
        info = inf;
    }
};

template <class N>
std::ostream & operator<<(std::ostream &out, const NodeDoesNotExist<N> &no)
{ out << "Node does not exist: " << no.info; return out; }


// exception EdgeAlreadyExists
template <class N>
class EdgeAlreadyExists {
public:
    N begin;
    N destination;
    EdgeAlreadyExists(N begin, N destination) :
        begin(begin), destination(destination){};
};

template <class N>
std::ostream & operator<<(std::ostream &out, const EdgeAlreadyExists<N> &e)
{ out << "Edge already exists: " << e.begin <<
" , " << e.destination; return out; }


// exception EdgeDoesNotExist
template <class N>
class EdgeDoesNotExist {
public:
    N begin;
    N destination;
    EdgeDoesNotExist(N begin, N destination) :
            begin(begin), destination(destination){};
};

template <class N>
std::ostream & operator<<(std::ostream &out, const EdgeDoesNotExist<N> &e)
{ out << "Edge does not exist: " << e.begin <<
      " , " << e.destination; return out; }
