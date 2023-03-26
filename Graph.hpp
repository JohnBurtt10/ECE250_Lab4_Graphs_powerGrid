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
    typedef std::tuple<unsigned int, unsigned int, unsigned int> idk; 
    bool V[50001] = {false}; 
    vector <edge> E; 
    unsigned int numberOfVertices = 0;
    vector <unsigned int>adjacent[50001];
    // Constructor 
    Graph(); 
    ~Graph();
    // Command handlers 
    bool insert(unsigned int a, unsigned int b, unsigned int w); 
    void print(unsigned int a); 
    void graphDelete(unsigned int a);
    vector <edge> MST();

    // helper function 
    void addEdges(vector <edge> &Q, unsigned int v);
    unsigned int w(unsigned int u, unsigned int v);
    void minHeapify(vector<unsigned int>& heap, unsigned int i, int (&position)[50000], unsigned int (&keys)[50000]);
    unsigned int heapExtractMin(vector<unsigned int>& heap, int (&position)[50000], unsigned int (&keys)[50000]);
    void heapInsert(vector<unsigned int>& heap, unsigned int newEdge, int (&position)[50000], unsigned int (&keys)[50000]);
    void updateHeap(vector<unsigned int>& heap, unsigned int index, int (&position)[50000], unsigned int (&keys)[50000]);
    
};
#endif