#ifndef Vertex_h
#define Vertex_h
#include <vector> 
#include <cstdlib>
#include <iostream>
using namespace std; 
class Vertex {
private:
public:
    int value; 
    int key; 
    Vertex* parent; 
    // vector <Vertex> adjacent;

    // Constructor 
    Vertex (int value = 0);

};
#endif