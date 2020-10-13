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

template <class N, class E>
class Node {
public:
    N info;
    vector< Edge<N,E> > edges;

    Node(N inf) {
        info = inf;
    }

    unsigned getNumEdges() const {
        return edges.size();
    }
};

template <class N, class E>
class Edge {
public:
    E value;
    Node<N,E> *destination;
    Edge(Node<N,E> *dest, E val) {
        value = val;
        destination = dest;
    }
    bool operator==(const Edge& e2){
        return value == e2.value &&
            destination == e2.destination;
    }
};

template <class N, class E>
class Graph {
    vector< Node<N,E> *> nodes;
public:
    Graph() : nodes(vector<Node<N,E>*>()){

    }

    ~Graph(){
        for (auto& n: nodes){
            delete n;
        }
    }

    Graph& addNode(const N& inf){
        for (const auto& n: nodes){
            if (n->info == inf){
                throw NodeAlreadyExists<N>(inf);
            }
        }
        nodes.push_back(new Node<N,E>(inf));
        return *this;
    }

    Graph& addEdge(const N &begin, const N &end, const E &val){
        if (find_if(nodes.begin(),nodes.end(),[begin](const Node<N,E>* n){ return n->info == begin;}) == nodes.end()){
            throw NodeDoesNotExist<N>(begin);
        } else if (find_if(nodes.begin(),nodes.end(),[end](const Node<N,E>* n){ return n->info == end;}) == nodes.end()){
            throw NodeDoesNotExist<N>(begin);
        } else if (find_if(begin.edges.begin(),begin.edges.end(),[val](const vector<Edge<N,E>> e){ return e.info == val;}) != nodes.end()){
            throw EdgeAlreadyExists<N>(begin);
        } else{
            for (auto& n: nodes){
                if (n->info == begin){
                    n->edges.emplace_back(&end,begin);
                    return *this;
                }
            }
        }
    }

//    Graph & removeEdge(const N &begin, const N &end);
//    E & edgeValue(const N &begin, const N &end);

    unsigned numEdges(void) const{
        unsigned sum = 0;
        for (const auto& n: nodes){
            sum += n->getNumEdges();
        }
        return sum;
    }

    unsigned numNodes(void) const{
        return nodes.size();
    }
//    void print(std::ostream &os) const;
};

template <class N, class E>
std::ostream & operator<<(std::ostream &out, const Graph<N,E> &g);


// exception NodeAlreadyExists
template <class N>
class NodeAlreadyExists
{
public:
    N info;
    NodeAlreadyExists(N inf) { info=inf; }
};

template <class N>
std::ostream & operator<<(std::ostream &out, const NodeAlreadyExists<N> &no)
{ out << "Node already exists: " << no.info; return out; }


// exception NodeDoesNotExist
template <class N>
class NodeDoesNotExist {
public:
    N info;
    NodeDoesNotExist(N inf) {
        info = inf;
    }
};

template <class N>
std::ostream & operator<<(std::ostream &out, const NodeDoesNotExist<N> &no)
{ out << "Node does not exist: " << no.info; return out; }


// exception EdgeAlreadyExists
template <class N>
class EdgeAlreadyExists {
    N begin;
    N destination;
    EdgeAlreadyExists(N begin, N destination) :
        begin(begin), destination(destination){};
};

template <class N>
std::ostream & operator<<(std::ostream &out, const EdgeAlreadyExists<N> &e)
{ out << "Edge already exists: from " << e.begin <<
" to " << e.edge.destination; return out; }
