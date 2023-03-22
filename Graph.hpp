#ifndef Graph_h
#define Graph_h
// #include <tuple> 
#include "Edge.hpp"
using namespace std;
class Graph {
private:
public:
    // u: vertex, v: vertex, w: weight
    typedef std::tuple<unsigned int, unsigned int, unsigned int> edge; 
    vector <Vertex> V; 
    vector <edge> E; 
    unsigned int m; 
    // Constructor 
    Graph(); 
    ~Graph();
    // Command handlers 
    // void load(string word);
    void insert(int a, int b, int w); 
    void print(int a); 
    void graphDelete(int a);
    void MST();
    void cost();

    // helper function 
    unsigned int w(unsigned int u, unsigned int v);

    
};
#endif