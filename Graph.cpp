#include "Graph.hpp"
#include <tuple>
#include <vector> 
#include <iostream> 
// value, key, parent
typedef std::tuple<unsigned int, unsigned int, unsigned int> idk; 
typedef std::tuple<unsigned int, unsigned int, unsigned int> edge; 
using namespace std; 
// Constructor 
Graph::Graph(){
}

// Destructor 
Graph::~Graph() {

}

bool Graph::insert(unsigned int a, unsigned int b, unsigned int weight) {
    // edge already exists in the graph 
    if (w(a,b)) { 
        return true;
    }
    if (!V[a]) { 
        V[a] = true;
        numberOfVertices++; 
    }
    if (!V[b]) { 
        V[b] = true; 
        numberOfVertices++;
    }
    // push vertexB to the element of adjacent corresponding to vertexA's adjacent vertices, and vice versa
        adjacent[a].push_back(b);
        adjacent[b].push_back(a);
        // increment the number of vertices in the graph
    E.push_back(edge(a, b, weight));
    return false;
}

void Graph::print(unsigned int a){
    // if a vertex with a value a does not exist, the command fails 
    if (!V[a]) { 
        std::cout << "failure" << std::endl;
        return;
    }
    for (auto& v : adjacent[a]) {
        if (v) { 
            std::cout << v << " "; 
        }
    }

    std::cout << std::endl;
}

void Graph::graphDelete(unsigned int a){
    // if a vertex with a value a does not exist, the command fails 
    if (!V[a]) { 
        std::cout << "failure" << std::endl;
        return;
    }
    V[a] = false;
    // the index of adjacent corresponding to vertex is wiped
    adjacent[a].clear();
    for (unsigned int i = 0; i < 50000; i++) { 
        if (V[i]) { 
            for (auto& v : adjacent[i]) {
                if (v == a) {
                    v = 0;
                }
            }
        }
    }
     // any edge containing vertex is wiped
    for (auto& e : E) {
        if (std::get<0>(e) == a || std::get<1>(e) == a) { 
            std::get<0>(e) = 0; 
        }
    }
    // decrement the number of vertex count for the graph
     numberOfVertices--;
     std::cout << "success" << std::endl;
}

// Uses Prim's algorithm, which is a greedy algorithm that finds a minimum spanning tree for a weighted undirected graph.
vector <edge> Graph::MST() {
    vector <unsigned int> T;
    // position in heap
    int position[50000] = {-1};
  
    // Create priority queue Q of edges
    vector <unsigned int> Q;
    unsigned int value = 0;
    unsigned int i = 0; 
    for (auto& v : V) {
        if (v) { 
            position[value] = i; 
            Q.push_back(value); 
            i++;
        }
        value++; 
    }
    unsigned int keys[50000]; 
    unsigned int parents[50000];
    for (int i = 0; i < 50000; i++) { 
        keys[i] = 4294967295;
        parents[i] = 0;
    }

    //root 
    keys[Q[0]] = 0;
    unsigned int u; 
    while (!Q.empty() && T.size() < numberOfVertices) {
        u = heapExtractMin(Q, position, keys); 
        minHeapify(Q, 0, position, keys);
        T.push_back(u); 
        for (auto& v : adjacent[u]) {
            unsigned int weight = w(u,v); 
            if (position[v] != -1 && weight < keys[v]) { 
                keys[v] = weight;
                updateHeap(Q, position[v], position, keys);
                parents[v] = u;
            }
        }

    }
    vector <edge> A;
    bool firstVertex = true; 
    for (auto& v : T) { 
        if (firstVertex) { 
            firstVertex = false; 
            continue;
        }
        A.push_back(edge(v, parents[v], w(v,parents[v])));
    }
    return A; 
}

// Heapify is the process of creating a heap data structure from a binary tree
void Graph::minHeapify(vector<unsigned int>& heap, unsigned int i, int (&position)[50000], unsigned int (&keys)[50000]) {
    // Find the indices of the left and right children of i
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // Find the index of the smallest element among i, left, and right
    int smallest = i;

    // if (left < heap.size() && std::get<1>(heap[left]) < std::get<1>(heap[smallest])) {
    if (left < heap.size() && keys[heap[left]] < keys[heap[smallest]]) {
        smallest = left;
    }

    // if (right < heap.size() && std::get<1>(heap[right]) < std::get<1>(heap[smallest])) {
    if (right < heap.size() && keys[heap[right]] < keys[heap[smallest]]) {
        smallest = right;
    }

    if (smallest != i) {
        // swap heap[i] with heap[smallest]
        swap(heap[i], heap[smallest]); 
        // temp = heap[i]; 
        // heap[i] = heap[smallest];
        position[heap[smallest]] = smallest; 
        // heap[smallest] = temp;
        position[heap[i]] = i; 
        minHeapify(heap, smallest, position, keys);
    }
}

unsigned int Graph::heapExtractMin(vector<unsigned int>& heap, int (&position)[50000], unsigned int (&keys)[50000]) { 
    unsigned int min = heap[0]; 
    heap[0] = heap[heap.size()-1];
    position[heap[heap.size()-1]] = 0;
    position[min] = -1;
    heap.pop_back();
    minHeapify(heap, 0, position, keys);

    return min;
}

void Graph::updateHeap(vector<unsigned int>& heap, unsigned int index, int (&position)[50000], unsigned int (&keys)[50000]) {
    if (index >= heap.size()) {
    // index is out of range, do something to handle the error
    return;
    }
    int parent = (index - 1) / 2;
    
    // Heapify Up
    while (index > 0 && keys[heap[index]] < keys[heap[parent]]) {
        position[heap[index]] = parent; 
        position[heap[parent]] = index;
        swap(heap[index], heap[parent]);
        index = parent;
        parent = (index - 1) / 2;
    }
    
    // Heapify Down
    int n = heap.size();
    while (true) {
        int left_child = 2 * index + 1;
        int right_child = 2 * index + 2;
        int smallest = index;
        
        if (left_child < n && keys[heap[left_child]] < keys[heap[smallest]]) {
            smallest = left_child;
        }
        
        if (right_child < n && keys[heap[right_child]] < keys[heap[smallest]]) {
            smallest = right_child;
        }
        
        if (smallest != index) {
            position[heap[index]] = smallest; 
            position[heap[smallest]] = index;
            swap(heap[index], heap[smallest]);
            index = smallest;
        }
        else {
            break;
        }
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
}




