#ifndef Graph_h
#define Graph_h
#include <tuple> 
#include <vector> 
using namespace std;
class Graph {
private:
public:
    // u: vertex, v: vertex, w: weight
    typedef std::tuple<unsigned int, unsigned int, unsigned int> edge; 
    bool V[50001] = {false}; 
    vector <edge> E; 
    unsigned int m = 0;
    vector <int>adjacent[50001];
    // Constructor 
    Graph(); 
    ~Graph();
    // Command handlers 
    bool insert(int a, int b, int w); 
    void print(int a); 
    void graphDelete(int a);
    vector <edge> MST();

    // helper function 
    void addEdges(vector <edge> &Q, unsigned int v);
    unsigned int w(unsigned int u, unsigned int v);
    void minHeapify(vector<edge>& heap, unsigned int i);
    edge heapExtractMin(vector<edge>& heap);
    void heapInsert(vector<edge>& heap, edge newEdge);
    
};
#endif