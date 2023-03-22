#ifndef Edge_h
#define Edge_h
// #include <cstdlib>
#include "Vertex.hpp"
using namespace std;
class Edge {
private:
public:
    Vertex vertexA; 
    Vertex vertexB;
    int weight; 

    // Constructor 
    // Edge(int vertexA, int vertexB, int weight); 
    Edge(int vertexA, int vertexB, int weight); 


};
#endif