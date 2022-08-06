#include <bits/stdc++.h>
using namespace std;

#define INF 1000000007

class Graph {
    int vertices;
    vector< vector<int> > graph, residualGraph;
public:
    Graph(int);

    void addEdge(int u, int v, int capacity) {
        residualGraph[u][v] = graph[u][v] = capacity;
    }

    bool bfs(int, int, vector<int>&);
    int EdmondsKarp(int, int);
};

int main() {
    freopen("EdmondsKarp.txt", "r", stdin);

    int vertices, c; 
    cin >> vertices;

    Graph graph(vertices);

    for (int i=0; i<vertices; i++) {
        for (int j=0; j<vertices; j++) {
            cin >> c;
            graph.addEdge(i, j, c);
        }
    }

    cout << graph.EdmondsKarp(0, 5) << "\n";

    return 0;
}

// Done
Graph::Graph(int vertices) {
    this->vertices = vertices;
        
    graph.resize(vertices);
    residualGraph.resize(vertices);
        
    for (int i=0; i<vertices; i++) {
        graph[i].resize(vertices);
        residualGraph[i].resize(vertices);
    }
}

// Done
bool Graph::bfs(int s, int t, vector<int>&parent) {
    vector<bool>visited(vertices, false);
    queue<int> q;

    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v=0; v<vertices; v++) {
            if (!visited[v] && residualGraph[u][v] > 0) {
                parent[v] = u;
                if (v==t) {
                    return true;
                }
                q.push(v);
                visited[v] = true;
            }
        }
    }
    return false;
}

// Done
int Graph::EdmondsKarp(int source, int destination) {
    vector<int>parent(vertices); 
    int maxFlow = 0; 
    
    while (bfs(source, destination, parent)) {
        int pathFlow = INF;
        for (int i=destination; i != source; i=parent[i]) {
            pathFlow = min(pathFlow, residualGraph[parent[i]][i]);
        }

        for (int i=destination; i != source; i=parent[i]) {
            residualGraph[parent[i]][i] -= pathFlow;
            residualGraph[i][parent[i]] += pathFlow;
        }

        maxFlow += pathFlow;
    }

    return maxFlow;
}

//