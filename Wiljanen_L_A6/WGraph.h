// Luke Wiljanen
// 2448331
// wiljanen@chapman.edu
// CPSC-350-03
// A6 Spanning the Gamut

#ifndef W_GRAPH_H
#define W_GRAPH_H


#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <unordered_map>
#include <limits> // For numeric limits to indicate infinity for conn matrix
#include <fstream>
#include "PQueue.h"

// CLASS TO REPRESENT EACH VERTEX
template <typename T>
class Vertex {
public:
    int name; // Each vertex has a 'name' of type T
    Vertex(T n); // Constructor
    Vertex(); // Default constructor
    ~Vertex(); // Destructor

    bool operator<(const Vertex<T>& other) const;
    bool operator==(const Vertex<T>& other) const;
};

template <typename T>
Vertex<T>::Vertex(T n) { name = n; } // Assign 'name' during construction

template <typename T>
Vertex<T>::~Vertex() {} // No specific cleanup needed for Vertex

template <typename T>
bool Vertex<T>::operator<(const Vertex<T>& other) const {
    return name < other.name; // Compare vertices based on their name
}

//comparison operator for vertex when checking to see if they are equal
template <typename T>
bool Vertex<T>::operator==(const Vertex<T>& other) const{
    return name == other.name;
}


// CLASS TO REPRESENT AN EDGE
template <typename T>
class Edge {
public:
    Vertex<T>* v1; // Pointer to the first vertex
    Vertex<T>* v2;    // Pointer to the second vertex
    double weight; // Weight of the edge
    Edge(Vertex<T>* v1, Vertex<T>* v2, double w); // Constructor
    ~Edge(); // Destructor

    bool operator<(const Edge& other) const;

};

template <typename T>
Edge<T>::Edge(Vertex<T>* vertex1, Vertex<T>* vertex2, double w) {
    v1 = vertex1;
    v2 = vertex2;
    weight = w;
}

template <typename T>
Edge<T>::~Edge() {
    v1 = NULL;
    v2 = NULL;
} 

template <typename T>
bool Edge<T>::operator<(const Edge& other) const {
    return weight < other.weight; // Compare edges based on their weight
}

// CLASS TO REPRESENT A WEIGHTED GRAPH
template <typename T>
class WGraph {
public:
    WGraph(int sz); // Constructor to initialize graph of a given size
    ~WGraph(); // Destructor to clean up dynamic allocations


    void addVertex(T name);
    void addEdge(T name1, T name2, int weight);
    void removeEdge(T name1, T name2);
    bool areAdjacent(T name1, T name2);
    int getWeight(T name1, T name2);
    std::vector<T> dfs(T startVertex);
    std::vector<T> bfs(T startVertex);
    int findIslands();
    double cheapestCost(T i, T j); // Find the cheapest path between two vertices, uses calcFW()
    void calcFW(); // Calculate the Floyd-Warshall algorithm to find shortest paths

    void computeMST(std::string inputFile); 
    void generateGraphFromFile(std::string inputFile);

private:
    int m_size; // Maximum number of vertices in the graph
    double** m_adj; // 2D array representing adjacency matrix for edge weights
    std::vector<Vertex<T> > m_vertices; // List of vertices
    std::unordered_map<T, int> m_nameToIndex; // Map to track each vertex's index by name

    // FW code
    bool recalcFW;               // Flag to determine if Floyd-Warshall needs recalculation
    double** m_conn;                // Matrix to store shortest paths between all pairs of vertices
    int rows;
    int cols;
    double cost;
};

// CONSTRUCTOR
template <typename T>
WGraph<T>::WGraph(int sz) {
    m_size = sz;
    m_adj = new double*[m_size];
    m_conn = new double*[m_size]; // Allocate memory for m_conn
    for (int i = 0; i < m_size; ++i) {
        m_adj[i] = new double[m_size];
        m_conn[i] = new double[m_size];
        for (int j = 0; j < m_size; ++j) {
            m_adj[i][j] = std::numeric_limits<double>::max(); // std::numeric_limits<int>::max() indicates infinity/ no edge
            m_conn[i][j] = std::numeric_limits<double>::max(); // Initialize m_conn with infinity
        }
        m_conn[i][i] = 0; // Distance to self is 0
    }
    recalcFW = true; // Initially set to true
}

// DESTRUCTOR
template <typename T>
WGraph<T>::~WGraph() {
    for (int i = 0; i < m_size; ++i) {
        delete[] m_adj[i];
        delete[] m_conn[i];
    }
    delete[] m_adj;
    delete[] m_conn;
}

// Add a new vertex to the graph
template <typename T>
void WGraph<T>::addVertex(T name) {
    if (m_vertices.size() < m_size) {
        m_vertices.push_back(Vertex<T>(name));
        m_nameToIndex[name] = m_vertices.size() - 1;
    } else {
        std::cerr << "Graph capacity reached. Cannot add more vertices." << std::endl;
    }
}

// Add an edge with a weight between two vertices
template <typename T>
void WGraph<T>::addEdge(T name1, T name2, int weight) {
    if (m_nameToIndex.count(name1) > 0 && m_nameToIndex.count(name2) > 0) {
        int i = m_nameToIndex[name1];
        int j = m_nameToIndex[name2];
        m_adj[i][j] = weight;
        m_adj[j][i] = weight; // Symmetric for undirected graph
    } else {
        std::cerr << "One or both vertices not found in the graph." << std::endl;
    }
}

// Remove an edge between two vertices
template <typename T>
void WGraph<T>::removeEdge(T name1, T name2) {
    if (m_nameToIndex.count(name1) > 0 && m_nameToIndex.count(name2) > 0) {
        int i = m_nameToIndex[name1];
        int j = m_nameToIndex[name2];
        m_adj[i][j] = std::numeric_limits<int>::max();
        m_adj[j][i] = std::numeric_limits<int>::max();
    } else {
        std::cerr << "One or both vertices not found in the graph." << std::endl;
    }
}

// Check if two vertices are adjacent
template <typename T>
bool WGraph<T>::areAdjacent(T name1, T name2) {
    if (m_nameToIndex.count(name1) > 0 && m_nameToIndex.count(name2) > 0) {
        int i = m_nameToIndex[name1];
        int j = m_nameToIndex[name2];
        return m_adj[i][j] != std::numeric_limits<int>::max(); // True if weight is not infinity/ std::numeric_limits<int>::max()
    }
    return false;
}

// Get the weight of an edge
template <typename T>
int WGraph<T>::getWeight(T name1, T name2) {
    if (m_nameToIndex.count(name1) > 0 && m_nameToIndex.count(name2) > 0) {
        int i = m_nameToIndex[name1];
        int j = m_nameToIndex[name2];
        return m_adj[i][j];
    }
    return std::numeric_limits<int>::max(); // Return std::numeric_limits<int>::max() if no edge exists
}

// DFS traversal
template <typename T>
std::vector<T> WGraph<T>::dfs(T startVertex) {
    std::vector<T> visited_order;
    if (m_nameToIndex.count(startVertex) == 0) return visited_order;

    int startIndex = m_nameToIndex[startVertex];
    std::stack<int> stk;
    std::set<int> visited;

    stk.push(startIndex);
    while (!stk.empty()) {
        int current = stk.top();
        stk.pop();

        if (visited.count(current) != 0) continue;

        visited.insert(current);
        visited_order.push_back(m_vertices[current].name);

        for (int k = 0; k < m_size; ++k) {
            if (m_adj[current][k] != std::numeric_limits<int>::max() && visited.count(k) == 0) {
                stk.push(k);
            }
        }
    }
    return visited_order;
}

// BFS traversal
template <typename T>
std::vector<T> WGraph<T>::bfs(T startVertex) {
    std::vector<T> visited_order;
    if (m_nameToIndex.count(startVertex) == 0) return visited_order;

    int startIndex = m_nameToIndex[startVertex];
    std::queue<int> q;
    std::set<int> visited;

    q.push(startIndex);
    visited.insert(startIndex);

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        visited_order.push_back(m_vertices[current].name);

        for (int k = 0; k < m_size; ++k) {
            if (m_adj[current][k] != std::numeric_limits<int>::max() && visited.count(k) == 0) {
                q.push(k);
                visited.insert(k);
            }
        }
    }
    return visited_order;
}
 

// Floyd-Warshall Algorithm
template <typename T>
void WGraph<T>::calcFW() {
    std::cout << "*** Calculating Floyd-Warshall *** " << std::endl;

    // Step 1: Initialize the connection matrix (m_conn) with the adjacency matrix (m_adj)
    // This step sets the initial shortest paths between directly connected nodes.
    for (int i = 0; i < m_size; ++i) {
        for (int j = 0; j < m_size; ++j) {
            // If there's an edge between i and j (indicated by m_adj[i][j] != std::numeric_limits<int>::max()),
            // copy the weight of the edge into m_conn.
            m_conn[i][j] = m_adj[i][j];
        }
        // The distance from a node to itself is always infinity, so we set m_conn[i][i] = std::numeric_limits<int>::max().
        m_conn[i][i] = std::numeric_limits<int>::max();
    }

    // Step 2: Apply the Floyd-Warshall algorithm to compute shortest paths
    // This triple nested loop iterates through all possible paths in the graph,
    // considering each node (im) as an intermediate point.

    for (int im = 0; im < m_size; ++im) { // Loop over all nodes as intermediate points
        for (int source = 0; source < m_size; ++source) { // Loop over all nodes as source points
            for (int sink = 0; sink < m_size; ++sink) { // Loop over all nodes as sink points
                // Step 2.1: Skip invalid cases
                // If either the source to intermediate (source -> im) or
                // intermediate to sink (im -> sink) path is unreachable,
                // then we skip the update for source -> sink.
                if (m_conn[source][im] == std::numeric_limits<int>::max() ||
                    m_conn[im][sink] == std::numeric_limits<int>::max()) {
                    continue; // No valid path exists through the intermediate node
                }

                // Step 2.2: Update shortest path using the intermediate node
                // If the path from source -> sink through im is shorter than the current
                // shortest path from source -> sink, update it.
                if (m_conn[source][sink] > m_conn[source][im] + m_conn[im][sink]) {
                    // Update the shortest path from source to sink
                    m_conn[source][sink] = m_conn[source][im] + m_conn[im][sink];
                }
            }
        }
    }

    // Step 3: Reset the flag to indicate that Floyd-Warshall results are up-to-date
    recalcFW = false;
}

// Find the cheapest path
template <typename T>
double WGraph<T>::cheapestCost(T i, T j) {
    if (m_nameToIndex.count(i) == 0 || m_nameToIndex.count(j) == 0) {
        throw std::invalid_argument("One or both vertices not found in the graph.");
    }

    int source = m_nameToIndex[i];
    int sink = m_nameToIndex[j];

    if (recalcFW) {
        calcFW();
    }

    return m_conn[source][sink];
}

//generates a 2d array from a file to be used to assign vales to the adjacency matrix to be used 
//in my computeMST function
template <typename T>
void WGraph<T>::generateGraphFromFile(std::string inputFile) {
    std::ifstream inFile(inputFile);
    std::string line;
    inFile >> rows;
    cols = rows;

    //populate the adjacency matrix with the values from the file
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            inFile >> m_adj[i][j];
        }
    }

    inFile.close();
}

template <typename T>
void WGraph<T>::computeMST(std::string inputFile){


    cost = 0;   //set original cost to 0 so that it can be added to later as edges are added to the MST


    //generate graph from file and store in 2d array. Also sets the num of rows and cols
    generateGraphFromFile(inputFile);

    //vector containing all edges in the graph
    std::vector<Edge<T> > edges;

    PQueue<Edge<T> > edgeQueue(true); //create a min queue to sort edges by minimum weight

    //create edges from the graph. if the weight is not 0, create an edge with both vertices and the weight
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            if (m_adj[i][j] != 0){
                Vertex<T>* vertex1 = new Vertex<T>(i);
                Vertex<T>* vertex2 = new Vertex<T>(j);
                Edge<T> edge(vertex1, vertex2, m_adj[i][j]);
                edgeQueue.add(edge);   
                m_adj[i][j] = 0;    //set weight to 0 so that it is not added to the queue again
                m_adj[j][i] = 0;
            }
        }
    }

    //create set of vertices
    std::set<std::set<Vertex<T> > > vertices;
    //create a set for each vertex with the vertex as the only element at the start then add it to the set of all vertices
    for (int i = 0; i < rows; i++){
        std::set<Vertex<T> > verticeSet;
        Vertex<T> v(i);
        verticeSet.insert(v);
        vertices.insert(verticeSet);
    }

    //A collection of edges comprising the minimum spanning tree, initially empty.
    std::vector<Edge<T> > resultsList;

    //while there are more than 1 set of vertices and the queue is not empty
    //remove the edge with the smallest weight from the queue
    //if the vertices of the edge are in different sets, add the edge to the results list and add the 
    //weight to the cost
    while (vertices.size() > 1 && !edgeQueue.isEmpty()){
        Edge<T> nextEdge = edgeQueue.remove();
        T vertexName1 = nextEdge.v1->name;
        T vertexName2 = nextEdge.v2->name;
        std::set<Vertex<T> > set1;
        std::set<Vertex<T> > set2;

        //find the sets in verticies that contain the vertices of the edge
        for (const auto& s : vertices){
            for (Vertex<T> v : s){
                if (v.name == vertexName1){
                    set1 = s;
                }
                if (v.name == vertexName2){
                    set2 = s;
                }
            }
        }

        //if the vertices are in different sets, add the edge to the results list and add the weight to the cost
        if (set1 != set2){
            resultsList.push_back(nextEdge);
            cost += nextEdge.weight;
            vertices.erase(set1);
            vertices.erase(set2);
            
            for (Vertex<T> v : set2){   //merge the sets
                set1.insert(v);
            }
            vertices.insert(set1);  //add the merged set back to the set of vertices
        }  
    }
    //make a adjacency matrix with created results list set
    double** endGraph = new double*[rows];
    //create 2d array to represent the graph in a 2d matrix for printing
    for (int i = 0; i < rows; i++){
        endGraph[i] = new double[cols];
    }
    //set all values to 0
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            endGraph[i][j] = 0.0;
        }
    }
    //set the values of the edges in the results list to the weight of the edge
    for (Edge<T> e : resultsList){
        endGraph[e.v1->name][e.v2->name] = e.weight; 
        endGraph[e.v2->name][e.v1->name] = e.weight;
    }
    
    std::cout << "The MST Cost is: " << cost << std::endl;

    //print graph
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            std::cout << endGraph[i][j] << " ";
        }
        std::cout << std::endl;
    }

    //delete all dynamically allocated memory
    delete m_adj;
    for (int i = 0; i < rows; i++){
        delete[] endGraph[i];
    }
    delete[] endGraph;
}
    

#endif

