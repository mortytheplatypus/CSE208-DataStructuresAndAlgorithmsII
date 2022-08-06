#include <bits/stdc++.h>
using namespace std;

#define INF 1000000007

struct Edge {
	int source;
	int destination;
	int weight;

	Edge(int source, int destination, int weight) {
		this->source = source;
		this->destination = destination;
		this->weight = weight;
	}
};

class Graph {
    int vertices, edges;
	vector<Edge> Edges;
public:
	Graph(int vertices, int edges) {
		this->vertices = vertices;
		this->edges = edges;
	}

	void addEdge(int u, int v, int w) {
		Edges.push_back(Edge(u, v, w));
	}

	void BellmanFord(int, int);
};

int main() {
	freopen("BellmanFord.txt", "r", stdin);

	int vertices, edges, u, v, w, source, destination; 
	cin >> vertices >> edges;

	Graph graph(vertices, edges);

	for (int i=0; i<edges; i++) {
		cin >> u >> v >> w;
		graph.addEdge(u, v, w);
	}

	cin >> source >> destination;
	graph.BellmanFord(source, destination);
	
    return 0;
}

// Done
void Graph::BellmanFord(int source, int destination) {
	vector<int>costs(vertices, INF);
	vector<int>parents(vertices, -1);
	int u, v;
	int w;
	costs[source] = 0;

	for (int i=0; i<edges; i++) {
		if (Edges[i].source==source) {
			swap(Edges[i], Edges[0]);
			break;
		}
	}
    
	for (int j=1; j<vertices; j++) {
		for (int i=0; i<edges; i++) {
			//relaxing
			if (costs[Edges[i].source]+Edges[i].weight < costs[Edges[i].destination]) {
				costs[Edges[i].destination] = costs[Edges[i].source]+Edges[i].weight;
				parents[Edges[i].destination] = Edges[i].source;
			}
		}
	}

	bool negativeCycle = false;
	for (int i=0; i<edges; i++) {
		if (costs[Edges[i].source]+Edges[i].weight < costs[Edges[i].destination]) {
			negativeCycle = true;
			break;
		}
	}


	if (negativeCycle) {
		cout << "The graph contains a negative cycle\n";
	} else {
		cout << "Shortest path cost: " << costs[destination] << "\n";
		vector<int> shortestPath;
		int v = destination;

		while (v != source) {
			shortestPath.push_back(v);
			v = parents[v];
		}
		shortestPath.push_back(source);

		for (int i=shortestPath.size()-1; i>0; i--) {
			cout << shortestPath[i] << " -> ";
		}
		cout << shortestPath[0] << "\n";
	}
}

//