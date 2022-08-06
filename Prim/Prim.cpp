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
    void Prim();
};

int main() {
	freopen("Prim.txt", "r", stdin);
	int houses, roads, u, v;
	double w; 
	cin >> houses >> roads;
	Graph graph(houses, roads);
	for (int i=0; i<roads; i++) {
		cin >> u >> v >> w;
		graph.addEdge(u, v, w);
	}

	graph.Prim();

	return 0;
}

Graph::Graph(int vertices, int edges) {
    this->vertices = vertices;
	this->edges = edges;
	adjacencyList.resize(vertices);
}	

void Graph::addEdge(int u, int v, double w) {
	adjacencyList[u].push_back(Node(v, w));
	adjacencyList[v].push_back(Node(u, w));
	
	Edges.push_back(Edge(u, v, w));
}

void Graph::Prim() {
	priority_queue<Node, vector<Node>, Comparator> pq;

    vector<double> edgeCost(vertices, INF); edgeCost[0] = 0.0;
	vector<int>parents(vertices, -1);
	vector<bool> inMST(vertices, false);
	
	Node node = Node(0, 0.0);
	pq.push(node);

	while (!pq.empty()) {
		int vertex = pq.top().vertex;
		pq.pop();
		
		if(inMST[vertex]) {
			continue;
		}
	
		inMST[vertex] = true; 

		int adjacentSize = adjacencyList[vertex].size();

		for (int i = 0; i<adjacentSize; i++) {
			int v = adjacencyList[vertex][i].vertex;
			double weight = adjacencyList[vertex][i].weight;
			if (!inMST[v] && edgeCost[v] > weight) {
				edgeCost[v] = weight;
				node.vertex = v;
				node.weight = weight;
				pq.push(node);
				parents[v] = vertex;
			}
		}
	}

	double cost=0.0;
	for (int i=1; i<vertices; i++) {
		cost += edgeCost[i];
	}
	
	printf("Cost of the minimum spanning tree : %0.3lf\n", cost);
	printf("List of edges selected by Prim: {(%d, %d)", 1, parents[1]);

	for (int i = 2; i<vertices; i++) {
		printf(", (%d, %d)", parents[i], i);
    }
	printf("}\n"); 
}

//