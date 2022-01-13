#include<bits/stdc++.h>
using namespace std;

#define INF 1000000007

struct Node {
	int vertex;
	double weight;
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
};

class Graph {
	int vertices;
	int edges;
	vector<vector<Node> > adjacencyList;
	vector<Edge> Edges;

public:
	Graph(int, int);
    void addEdge(int, int, double);
    void PrimMST();
	void KruskalMST();
};

int main() {
	freopen("in-mst.txt", "r", stdin);
	int houses, roads, u, v;
	double w; 
	cin >> houses >> roads;
	Graph graph(houses, roads);
	for (int i=0; i<roads; i++) {
		cin >> u >> v >> w;
		graph.addEdge(u, v, w);
	}

	graph.PrimMST();
	graph.KruskalMST();

	return 0;
}

Graph::Graph(int vertices, int edges) {
    this->vertices = vertices;
	this->edges = edges;
	adjacencyList.resize(vertices);
}	

void Graph::addEdge(int u, int v, double weight) {
	Node node;
	node.weight = weight;
	node.vertex = v;
	adjacencyList[u].push_back(node);
	node.vertex = u;
	adjacencyList[v].push_back(node);

	Edge edge;
	edge.source = u;
	edge.destination = v;
	edge.weight = weight;
	Edges.push_back(edge);
}

void Graph::PrimMST() {
	priority_queue<Node, vector<Node>, Comparator> pq;

    vector<double> edgeCost(vertices, INF); edgeCost[0] = 0.0;
	vector<int>parents(vertices, -1);
	vector<bool> inMST(vertices, false);
	
	Node node;
	node.vertex = 0;
	node.weight = 0.0;
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

int Parent(int vertex, vector<int>&parents)  {
	if (vertex == parents[vertex]) {
		return vertex;
	}

	return parents[vertex] = Parent(parents[vertex], parents);
}

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

void Graph::KruskalMST() {
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

	// double cost = 0.0;
	// for (int i=0; i<vertices-1; i++) {
	// 	cost += result[i].weight;
	// }
	// printf("Cost of the minimum spanning tree : %0.3lf\n", cost);

	printf("List of edges selected by Kruskal: {(%d, %d)", result[0].source, result[0].destination);

	for (int i = 1; i<result.size(); i++) {
		printf(", (%d, %d)", result[i].source, result[i].destination);
    }
	printf("}\n");	
}

