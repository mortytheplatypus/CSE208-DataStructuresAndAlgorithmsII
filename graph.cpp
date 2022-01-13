#include <bits/stdc++.h>
using namespace std;

class Graph {
    int vertices;
    vector<vector<int>> adjacencyList;
    bool CycleDetectorUtil(int vertex, bool visited[], bool onStack[]);
    void TopologicalSortUtil(int vertex, bool visited[], stack<int>&s);
    void DFSUtil(int vertex, bool visited[]);
    void FillOrder(int vertex, bool visited[], stack<int>&s);
public:
    Graph(int vertices) {
        this->vertices = vertices;
        adjacencyList.resize(vertices);
    }

    void newEdge(int vertex, int adjacent) {
        adjacencyList[vertex].push_back(adjacent);
    }

    void BFS(int vertex);

    void DFS(int vertex);

    bool CycleDetector(); 

    void TopologicalSort();

    bool Bipartite(int vertex, bool visited[], int color[]);

    Graph Transpose();

    void PrintSCCs();
};

void Graph::BFS(int vertex) {
    vector<bool> visited(vertices, false);

    queue<int> q;
    q.push(vertex);
    visited[vertex] = true;

    while (!q.empty()) {
        vertex = q.front();
        cout << vertex << " ";
        q.pop();
        int adjacentSize = adjacencyList[vertex].size();

        for (int i=0; i<adjacentSize; i++) {
            if (!visited[adjacencyList[vertex][i]]) {
                visited[adjacencyList[vertex][i]] = true;
                q.push(adjacencyList[vertex][i]);
            }
        }
    }
    
}

void Graph::DFS(int vertex) {
    vector<bool>visited(vertices, false);

    stack<int> s;
    s.push(vertex);

    while (!s.empty()) {
        vertex = s.top();
        cout << vertex << " ";
        s.pop();

        if (!visited[vertex]) {
            visited[vertex] = true;
            int adjacentSize = adjacencyList[vertex].size();

            for (int i=0; i<adjacentSize; i++) {
                if (!visited[adjacencyList[vertex][i]]) {
                    s.push(adjacencyList[vertex][i]);
                }
            }
        }
    }
}

bool Graph::CycleDetectorUtil(int vertex, bool visited[], bool onStack[]) {
    if (!visited[vertex]) {
        visited[vertex] = onStack[vertex] = true;

        int adjacentSize = adjacencyList[vertex].size();

        for (int i=0; i<adjacentSize; i++) {
            if (!visited[i] && CycleDetectorUtil(i, visited, onStack)) {
                return true;
            } else if (onStack[i]) {
                return true;
            }
        }
    }
    onStack[vertex] = false;
    return false;
}

bool Graph::CycleDetector() {
    vector<bool>visited(vertices, false), onStack(vertices, false);
    
    for (int i=0; i<vertices; i++) {
        if (CycleDetectorUtil(i, visited, onStack)) {
            return true;
        }
    }

    return false;
}

void Graph::TopologicalSortUtil(int vertex, bool visited[], stack<int>&s) {
    visited[vertex] = true;
    int adjacentSize = adjacencyList[vertex].size();

    for (int i=0; i<adjacentSize; i++) {
        if (!visited[i]) {
            TopologicalSortUtil(i, visited, s);
        }
    }

    s.push(vertex);
}

void Graph::TopologicalSort() {
    vector<int>visited(vertices, false);
    stack<int> s;

    for (int i=0; i<vertices; i++) {
        if (!visited[i]) {
            TopologicalSortUtil(i, visited, s);
        }
    }
}

bool Graph::Bipartite(int vertex, bool visited[], int color[]) {
    int adjacentSize = adjacencyList[vertex].size();
    for (int i=0; i<adjacentSize; i++) {
        if (!visited[i]) {
            visited[i] = true;
            color[i] = !color[v];
            if (!Bipartite(i, visited, color)) {
                return false;
            } 
        } else if (color[i] == color[vertex]) {
            return false;
        }
    } 

    return true;
}
    
void Graph::DFSUtil(int vertex, bool visited[]) {
    visited[vertex] = true;
    cout << vertex << " ";
    int adjacentSize = adjacencyList[vertex].size();

    for (int i=0; i<adjacentSize; i++) {
        if (!visited[i]) {
            DFSUtil(i, visited);
        }
    }
}

void Graph::FillOrder(int vertex, bool visited[], stack<int>&s) {
    visited[vertex] = true;
    int adjacentSize = adjacencyList[vertex].size();

    for (int i=0; i<adjacentSize; i++) {
        if (!visited[i]) {
            FillOrder(i, visited, s);
        }
    }

    s.push(vertex);
}

Graph Graph::Transpose() {
    Graph graph(vertices);

    for (int i=0; i<vertices; i++) {
        int adjacentSize = adjacencyList[i].size();
        for (int j=0; j<adjacentSize; j++) {
            graph.adjacencyList[j].push_back(i);
        }
    }

    return graph;
}

void Graph::PrintSCCs() {
    vector<int>visited(vertices, false);
    stack<int> s;

    for (int i=0; i<vertices; i++) {
        if (!visited[i]) {
            FillOrder(i, visited, s);
        }
    }

    Graph graph = this->Transpose();

    for (int i=0; i<vertices; i++) {
        visited[i] = false;
    }

    while (!s.empty()) {
        int vertex = s.top();
        s.pop();
        if (!visited[vertex]) {
            graph.DFSUtil(vertex, visited);
            cout << endl;
        }
    }
}
int main() {
    Graph graph(5);
    graph.newEdge(0, 1);
    graph.newEdge(0, 4);
    graph.newEdge(1, 2);
    graph.newEdge(2, 0);
    graph.newEdge(2, 3);
    graph.newEdge(4, 3);

 
    return 0;
}





























    // for (int i=0; i<4; i++) {
    //     cout << i << ":";
    //     for (int j=0; j<adjacencyList[i].size(); j++) {
    //         cout << "\t" << adjacencyList[i][j];
    //     }
    //     cout << endl;
    // }