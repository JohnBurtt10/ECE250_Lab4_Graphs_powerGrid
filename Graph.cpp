#include "Graph.hpp"
using namespace std; 
// Constructor 
Graph::Graph()
{
}

// Destructor 
Graph::~Graph() {
}
void Graph::insert(int a, int b, int w) {
    Vertex vertexA;
    Vertex vertexB; 
    bool exists = false; 
    for (auto & v : V) {
        if (v.value == a) {
            vertexA = v; 
            exists = true; 
        }
    }
    if (!exists) { 
        vertexA = Vertex(a); 
        V.push_back(vertexA);
    }
    exists = false;
    for (auto & v : V) {
        if (v.value == b) {
            vertexB = v; 
            exists = true; 
        }
    }
    if (!exists) { 
        vertexB = Vertex(b); 
        V.push_back(vertexB);
    }
    for (auto & v : V) {
        if (v.value == a) {
            v.adjacent.push_back(vertexB); 
        } else if (v.value == b) { 
            v.adjacent.push_back(vertexA);
        }
    }
    E.push_back(edge(a, b, w));
}

void Graph::print(int a){
    Vertex vertex; 
    bool exists = false;
    for (auto & v : V) {
        if (v.value == a) {
            vertex = v; 
            exists = true; 
        }
    }
    for (auto & v : vertex.adjacent) {
        std::cout << v.value << " "; 
    }
    std::cout << std::endl;
}

void Graph::graphDelete(int a){
      Vertex vertex; 
    bool exists = false;
    for (auto & v : V) {
        if (v.key == a) {
            vertex = v; 
            exists = true; 
        }
    }
    vertex.adjacent.clear();
    // for (int i=0;i<50000;i++) { // check this 
    //     for (auto & it : adj[i]) {
    //         if (std::get<0>(it) == a) { 
    //             it = i3tuple(NULL, NULL); // confirm that this changes in place (it should)
    //         }
    //     }
    // }
}

bool inQ(vector <Vertex> Q, Vertex v) { 
    for (auto & it : Q) {
        if (it.value == v.value) {
            return true;
        }
    }
    return false;
}

void MinHeapify(vector<Vertex>& A, unsigned int keys[], int i) {
    int n = A.size();
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int smallest = i;
    if (left < n && keys[A[left].value] < keys[A[smallest].value]) {
        smallest = left;
    }
    if (right < n && keys[A[right].value] < keys[A[smallest].value]) {
        smallest = right;
    }
    if (smallest != i) {
        std::cout << "swapping" << std::endl;
        swap(A[smallest], A[i]);
        MinHeapify(A, keys, smallest);
        return;
    }
    std:cout << "after heapify: " << std::endl;
    for (auto& v : A) {
        std::cout << "v.value: " << v.value << " v.key: " << keys[v.value] << std::endl;
    }
}


void deleteLastNode(vector <Vertex> &A) { 
      if (A.empty()) {
        return;
    }

    // 
    if (A.size() == 1) {
        A.pop_back();
        return;
    }

    A.pop_back();
}

void Graph::MST() {
    vector <edge> A;
    // Initialize keys array to infinity
    unsigned int keys[50000];
    unsigned int parentKeys[50000];
    for (int i = 0; i < 50000; i++) { 
        keys[i] = INT_MAX;
        parentKeys[i] = INT_MAX;

    }
    // Create priority queue Q of vertices
    vector <Vertex> Q = V;

    // Initialize parent pointers to null
    // for (auto& v : Q) {
    //     v.parent = nullptr;
    // }

    // Initialize first vertex as root with key 0
    std::cout << "root: " << Q.back().value << std::endl;
    keys[0] = 0;
    // for (int k=Q.size()/2; k>0;k--) {
    //     Heapify(Q, k, keys);
    // }

    while (!Q.empty() && A.size() < m) {
        // Extract minimum key vertex from Q
        //  std::cout << "before pop" << std::endl;
        //  unsigned int i = 0; 
        // for (auto& v : Q) {
        //     std::cout << "i: " << i << " v.value: " << v.value << " v.key: " << keys[v.value] << " v.parent: " << parentKeys[v.value] << std::endl;
        //     i++;
        // }
    //     for (auto& e : A) {
    //     std::cout << std::get<0>(e) << " " << std::get<1>(e) << " " << std::get<2>(e) << std::endl;
    // }        
    std::cout << std::endl;

        Vertex u = Q.back();
        deleteLastNode(Q);
        // std::cout << "popped: " << u.value << std::endl;
        // std::cout << "after pop" << std::endl;
        // for (auto& v : Q) {
        //     std::cout << "v.value: " << v.value << " v.key: " << keys[v.value] << " v.parent: " << parentKeys[v.value] << std::endl;
        //     i++;
        // }
        // Add u to MST
        if (parentKeys[u.value] != INT_MAX) {
            A.push_back(edge(parentKeys[u.value], u.value, w(parentKeys[u.value], u.value)));
        }

        // Update keys and parent pointers of adjacent vertices
        for (auto& v : u.adjacent) {
            if (inQ(Q,v) && w(u.value, v.value) < keys[v.value]) {
                keys[v.value] = w(u.value, v.value);
                std:cout << "before heapify: " << std::endl;
                unsigned int i = 0;
                for (auto& v : Q) {
                std::cout << "v.value: " << v.value << " v.key: " << keys[v.value] << " v.parent: " << parentKeys[v.value] << std::endl;
                }
                MinHeapify(Q, keys, 0);
                parentKeys[v.value] = u.value;
                i++;
            }
        }
    }

    // Output MST edges
    for (auto& e : A) {
        std::cout << std::get<0>(e) << " " << std::get<1>(e) << " " << std::get<2>(e) << std::endl;
    }
}


unsigned int Graph::w(unsigned int u, unsigned int v) { 
    for (auto & it : E) {
        if (std::get<0>(it) == u && std::get<1>(it) == v 
        || std::get<0>(it) == v && std::get<1>(it) == u) { 
            return std::get<2>(it);
        }
    }
    return 0;
    // std::cout << "there is an issue with Graph::w" << std::endl;
}

void Graph::cost(){}







