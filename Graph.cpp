#include "Graph.hpp"
#include <tuple>
#include <vector> 
#include <iostream> 
typedef std::tuple<unsigned int, unsigned int, unsigned int> edge; 
using namespace std; 
// Constructor 
Graph::Graph()
{
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
    vector <edge> A;
    // Initialize keys array to infinity
    bool visited[50000] = {false};
  
    // Create priority queue Q of edges
    vector <edge> Q;

    //root 
    unsigned int i = 0;
    while (!V[i]) { 
        i++;
    }
    addEdges(Q, i); 
    minHeapify(Q, 0);
    edge edge; 
    unsigned int nodeIndex; 
    visited[i] = true;
    while (!Q.empty() && A.size() < numberOfVertices) {
        edge = heapExtractMin(Q);
        nodeIndex = std::get<1>(edge);
        if (visited[nodeIndex]) { 
            continue;
        }
        visited[nodeIndex] = true;
        A.push_back(edge);

        addEdges(Q, std::get<1>(edge)); 
    }
    return A; 
}

// Heapify is the process of creating a heap data structure from a binary tree
void Graph::minHeapify(vector<edge>& heap, unsigned int i) {
    // Find the indices of the left and right children of i
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // Find the index of the smallest element among i, left, and right
    int smallest = i;

    if (left < heap.size() && std::get<2>(heap[left]) < std::get<2>(heap[smallest])) {
        smallest = left;
    }

    if (right < heap.size() && std::get<2>(heap[right]) < std::get<2>(heap[smallest])) {
        smallest = right;
    }

    edge temp; 
    if (smallest != i) {
        // swap heap[i] with heap[smallest]
        temp = heap[i]; 
        heap[i] = heap[smallest];
        heap[smallest] = temp;
        minHeapify(heap, smallest);
    }
}

edge Graph::heapExtractMin(vector<edge>& heap) { 
    edge max = heap[0]; 
    heap[0] = heap[heap.size()-1]; 
    heap.pop_back();
    minHeapify(heap, 0);

    return max;
}

void Graph::heapInsert(vector<edge>& heap, edge newEdge) {
    // Add the new element to the end of the heap
    heap.push_back(newEdge);

    // Get the index of the new element
    int index = heap.size() - 1;

    // Compare the new element with its parent and swap if necessary
    while (index > 0 && std::get<2>(heap[index]) < std::get<2>(heap[(index-1)/2])) {
        swap(heap[index], heap[(index-1)/2]);
        index = (index-1)/2;
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

void Graph::addEdges(vector <edge> &Q, unsigned int firstVertex) { 
     for (auto& adjacentVertex : adjacent[firstVertex]) {
        if (adjacentVertex != 0) {
            heapInsert(Q, (edge(firstVertex, adjacentVertex, w(firstVertex,adjacentVertex))));
        }
     }
}





