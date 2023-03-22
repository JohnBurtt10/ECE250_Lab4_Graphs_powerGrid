#include "Graph.hpp"
#include <tuple>
using namespace std; 
// Constructor 
Graph::Graph()
{
}

// Destructor 
Graph::~Graph() {
}
typedef std::tuple<Vertex, Vertex, unsigned int> edge; 

Vertex Graph::getVertex(int a) { 
    Vertex vertex;
    for (auto & v : V) {
        if (v.value == a) {
            vertex = v; 
        }
    }
    return vertex;
}

bool Graph::insert(int a, int b, int weight) {
    // edge already exists in the graph 
    if (w(a,b)) { 
        return true;
    }
    Vertex vertexA;
    Vertex vertexB; 
    vertexA = getVertex(a);
    // if a vertex with a value a does not already exist, create it
    if (!vertexA.value) { 
        vertexA.value = a; 
        V.push_back(vertexA);
    }
    vertexB = getVertex(b);
    // if a vertex with a value b does not already exist, create it
    if (!vertexB.value) { 
        vertexB.value = b; 
        V.push_back(vertexB);
    }
    // push vertexB to the element of adjacent corresponding to vertexA's adjacent vertices, and vice versa
    adjacent[vertexA.value].push_back(vertexB);
    adjacent[vertexB.value].push_back(vertexA);

    E.push_back(edge(a, b, weight));
    return false;
}

void Graph::print(int a){
    Vertex vertex; 
    vertex = getVertex(a);
    // if a vertex with a value a does not exist, the command fails 
    if (!vertex.value) { 
        std::cout << "failure" << std::endl;
        return;
    }
    // all vertices adjacent to vertex are printed
    for (auto & v : adjacent[vertex.value]) {
        if (v.value != 0) { 
            std::cout << v.value << " "; 
        }
    }
    std::cout << std::endl;
}

void Graph::graphDelete(int a){
    Vertex vertex; 
    bool exists = false;
    for (auto & v : V) {
        if (v.value == a) {
            vertex = v; 
            exists = true; 
            v.value = 0;
        }
    }
    // if a vertex with a value a does not exist, the command fails 
    if (!exists) { 
        std::cout << "failure" << std::endl;
        return;
    }
    // the index of adjacent corresponding to vertex is wiped
    adjacent[vertex.value].clear();
     for (auto& v : V) {
        for (auto& b : adjacent[v.value]) { 
            if (b.value == a) { 
                b.value = 0; 
            }
        }
     }
     // any edge containing vertex is wiped
      for (auto& e : E) {
        if (std::get<0>(e).value == a || std::get<1>(e).value == a) { 
            std::get<0>(e).value = 0; 
        }
    }
    // decrement the number of vertex count for the graph
     m--;
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
    Vertex s = V[0];
    addEdges(Q, s); 
    minHeapify(Q, 0);
    edge edge; 
    unsigned int nodeIndex; 
    visited[s.value] = true;
    while (!Q.empty() && A.size() != m-1) {
        edge = heapExtractMin(Q);
        nodeIndex = std::get<1>(edge).value;
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
        if (std::get<0>(it).value == u && std::get<1>(it).value == v 
        || std::get<0>(it).value == v && std::get<1>(it).value == u) { 
            return std::get<2>(it);
        }
    }
    return 0;
}

void Graph::addEdges(vector <edge> &Q, Vertex s) { 
     for (auto& v : adjacent[s.value]) {
        if (v.value != 0) {
            heapInsert(Q, (edge(s, v, w(s.value,v.value))));
            minHeapify(Q, Q.size()-1);
        }
     }
}





