#include <bits/stdc++.h>
using namespace std;

#define INF 1000000007

struct Node {
	int vertex;
	int weight;

	Node(int vertex, int weight) {
		this->vertex = vertex;
		this->weight = weight;
	}
};

bool operator<(Node u, Node v) {
	return u.weight > v.weight;
}

class Graph {
    int vertices;
	vector< vector<Node> > adjacencyList;
public:
	Graph(int vertices) {
		this->vertices = vertices;
		adjacencyList.resize(vertices);
	}

	void addEdge(int source, int destination, int weight) {
		adjacencyList[source].push_back(Node(destination, weight));
	}

	void Dijkstra(int, int);
};

int main() {
	freopen("Dijkstra.txt", "r", stdin);

	int vertices, edges, u, v, w, source, destination; 
	cin >> vertices >> edges;

	Graph graph(vertices);

	for (int i=0; i<edges; i++) {
		cin >> u >> v >> w;
		graph.addEdge(u, v, w);
	}

	cin >> source >> destination;
	graph.Dijkstra(source, destination);
	
    return 0;
}

// Done
void Graph::Dijkstra(int source, int destination) {
	vector<int>costs(vertices, INF);
	vector<bool>inShortestPath(vertices, false);
	vector<int>parents(vertices, source);
	priority_queue<Node> pq;
	int u, v;
	int w;

	costs[source] = 0;
	pq.push(Node(source, 0));

	while(!pq.empty()) {
		u = pq.top().vertex;
		pq.pop(); 

		if (inShortestPath[u]) {
			continue;
		}
		inShortestPath[u] = true;

		int adjacenctSize = adjacencyList[u].size();

		for (int i=0; i<adjacenctSize; i++) {
			v = adjacencyList[u][i].vertex;
			w = adjacencyList[u][i].weight;
			//relaxing
			if (costs[u]+w < costs[v]) { 
				parents[v] = u;
				costs[v] = costs[u]+w;
				pq.push(adjacencyList[u][i]);
			}
		}
	}

	cout << "Shortest path cost: " << costs[destination] << "\n";

	vector<int>shortestPath;
	v = destination;

	while (v != source) {
		shortestPath.push_back(v);
		v = parents[v];
	}
	shortestPath.push_back(source);

	for (int i=shortestPath.size()-1; i>0; i--) {
		cout << shortestPath[i] << " -> ";
	}
	cout << destination << "\n";
}

//