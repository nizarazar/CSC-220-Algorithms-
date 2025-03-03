#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <vector>
#include <chrono>
using namespace std;


// This is our Graph class
class Graph {
    int V; 
    list<int>* adj; 

//Public class
public:
    Graph(int V); // Constructor
    void addEdge(int v, int w); 
    void BFS(int s); 
    void DFS(int s); 
};

// This is the constructor for the Graph class
Graph::Graph(int V) {
    this->V = V;
    adj = new list<int>[V];
}

// This function adds an edge to the graph
void Graph::addEdge(int v, int w) {
    adj[v].push_back(w); 
}


// This function performs Breadth-First Search (BFS) starting from vertex s
void Graph::BFS(int s) {
    vector<bool> visited(V, false);
    queue<int> queue;
    visited[s] = true;
    queue.push(s);

    while (!queue.empty()) {
        s = queue.front();
        cout << s << " ";
        queue.pop();

        for (auto i = adj[s].begin(); i != adj[s].end(); ++i) {
            if (!visited[*i]) {
                queue.push(*i);
                visited[*i] = true;
            }
        }
    }
}



// This function performs Depth-First Search (DFS) starting from vertex s
void Graph::DFS(int s) {
    vector<bool> visited(V, false);
    stack<int> stack;
    stack.push(s);

    while (!stack.empty()) {
        s = stack.top();
        stack.pop();

        if (!visited[s]) {
            cout << s << " ";
            visited[s] = true;
        }

        for (auto i = adj[s].begin(); i != adj[s].end(); ++i) {
            if (!visited[*i]) {
                stack.push(*i);
            }
        }
    }
}


int main() {
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);
         auto start = std::chrono::high_resolution_clock::now();

    // Test BFS
    cout << "Breadth First Traversal (starting from vertex 2): ";
    g.BFS(2);
    cout << endl;

    // Test DFS
    cout << "Depth First Traversal (starting from vertex 2): ";
    g.DFS(2);
    cout << endl;
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        std::cout << "Time taken by function: "
        << duration.count() << " microseconds" << std::endl;
    return 0;
}
