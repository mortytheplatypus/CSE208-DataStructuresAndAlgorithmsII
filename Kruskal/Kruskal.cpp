#include<bits/stdc++.h>
using namespace std;

#define INF 1000000007

struct Node {
	int vertex;
	double weight;

	Node(int vertex, int weight) {
		this->vertex = vertex;
		this->weight = weight;
	}
};

struct Comparator {
	bool operator()(Node const& first, Node const& second) {
		return first.weight > second.weight;
	}
};

struct Edge {
	int source, destination;
	double weight;

	bool operator<(Edge const& edge) {
		return this->weight < edge.weight;
	}

	Edge(int source, int destination, double weight) {
		this->source = source;
		this->destination = destination;
		this->weight = weight;
	}
};

class Graph {
	int vertices;
	int edges;
	vector<vector<Node> > adjacencyList;
	vector<Edge> Edges;

public:
	Graph(int, int);
    void addEdge(int, int, double);
	void Kruskal();
};

int main() {
	freopen("Kruskal.txt", "r", stdin);

	int houses, roads, u, v;
	double w; 
	cin >> houses >> roads;

	Graph graph(houses, roads);

	for (int i=0; i<roads; i++) {
		cin >> u >> v >> w;
		graph.addEdge(u, v, w);
	}

	graph.Kruskal();

	return 0;
}

// Done
Graph::Graph(int vertices, int edges) {
    this->vertices = vertices;
	this->edges = edges;
	adjacencyList.resize(vertices);
}	

// Done
void Graph::addEdge(int u, int v, double w) {
	adjacencyList[u].push_back(Node(v, w));
	adjacencyList[v].push_back(Node(u, w));
	
	Edges.push_back(Edge(u, v, w));
}

// Done
int Parent(int vertex, vector<int>&parents)  {
	if (vertex == parents[vertex]) {
		return vertex;
	}

	return parents[vertex] = Parent(parents[vertex], parents);
}

// Done
void Union(int a, int b, vector<int>&parents, vector<int>&ranks) {
	a = Parent(a, parents);
	b = Parent(b, parents);

	if (ranks[a] > ranks[b]) {
		parents[a] = b;
	} else if (ranks[a] < ranks[b]) {
		parents[b] = a;
	} else {
		parents[a] = b;
		ranks[b]++;
	}
}

// Done
void Graph::Kruskal() {
	vector<int>parents(vertices), ranks(vertices, 0);
	for (int i=0; i<vertices; i++) {
		parents[i] = i;
		ranks[i] = 0;
	}
	vector<Edge> result;
	sort(Edges.begin(), Edges.end());

	for (int i=0; i<edges; i++) { 
		if (Parent(Edges[i].source, parents) != Parent(Edges[i].destination, parents)) {
			result.push_back(Edges[i]);
			Union(Edges[i].source, Edges[i].destination, parents, ranks);
		}
	}

	double cost = 0.0;
	for (int i=0; i<vertices-1; i++) {
		cost += result[i].weight;
	}
	printf("Cost of the minimum spanning tree : %0.3lf\n", cost);

	printf("List of edges selected by Kruskal: {(%d, %d)", result[0].source, result[0].destination);

	for (int i = 1; i<result.size(); i++) {
		printf(", (%d, %d)", result[i].source, result[i].destination);
    }
	printf("}\n");	
}

//