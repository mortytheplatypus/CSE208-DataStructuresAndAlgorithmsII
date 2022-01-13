#include <bits/stdc++.h>
using namespace std;

#define INF 1000000007

struct Node {
	int vertex;
	int weight;

	Node(int v, int w) {
		vertex = v;
		weight = w;
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

	void addEdge(int u, int v, int w) {
		adjacencyList[u].push_back(Node(v, w));
	}

	void Dijkstra(int, int);
};

int main() {
	freopen("in-Dijkstra.txt", "r", stdin);
	int vertices, edges, u, v, source, destination; 
	int w;
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

	cout << "Shortest path cost: " << costs[destination] << endl;

	vector<int>shortestPath;
	v = destination;

	while (v!=source) {
		shortestPath.push_back(v);
		v = parents[v];
	}
	shortestPath.push_back(source);

	for (int i=shortestPath.size()-1; i>0; i--) {
		cout << shortestPath[i] << " -> ";
	}
	cout << destination << endl;
}