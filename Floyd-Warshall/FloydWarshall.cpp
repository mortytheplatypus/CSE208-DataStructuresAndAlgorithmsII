#include <bits/stdc++.h>
using namespace std;

#define INF 1000000007

class Graph {
    int vertices;
    vector< vector<int> > adjacencyMatrix, shortestPaths;
public:
	Graph(int);

	void addEdge(int u, int v, int w) {
        shortestPaths[u][v] = adjacencyMatrix[u][v] = w;
	}

	void FloydWarshall();
};

int main() {
	freopen("FloydWarshall.txt", "r", stdin);

	int vertices, edges, u, v, w; 
    cin >> vertices >> edges;
    
    Graph graph(vertices);

    for (int i=0; i<edges; i++) {
        cin >> u >> v >> w;
        if (u==v) {
            w = 0;
        }
        graph.addEdge(u, v, w);
    }

    graph.FloydWarshall();

    return 0;
}

// Done
Graph::Graph(int vertices) {
    this->vertices = vertices;
    adjacencyMatrix.resize(vertices);
    shortestPaths.resize(vertices);
    for (int i=0; i<vertices; i++) {
        adjacencyMatrix[i].resize(vertices);
        shortestPaths[i].resize(vertices);
        for (int j=0; j<vertices; j++) {
            shortestPaths[i][j] = adjacencyMatrix[i][j] = INF;
        }
        shortestPaths[i][i] = adjacencyMatrix[i][i] = 0;
    }
}

// Done
void Graph::FloydWarshall() {
	for (int k=0; k<vertices; k++) {
        for (int i=0; i<vertices; i++) {
            if (i==k) continue;
            for (int j=0; j<vertices; j++) {
                if (j==k) continue;
                shortestPaths[i][j] = min(shortestPaths[i][j], shortestPaths[i][k]+shortestPaths[k][j]);
            }
        }
    }

    for (int i=0; i<vertices; i++) {
        for (int j=0; j<vertices; j++) {
            cout << shortestPaths[i][j] << " ";
        }
        cout << "\n";
    }
}

//