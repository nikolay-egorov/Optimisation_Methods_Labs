#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <list> 
using namespace std;

struct edge {
	int a, b, cost;
};

class listNode{
	int v;
	int weight;
public:
	listNode(int _v, int _w) { v = _v; weight = _w; }
	int getV() { return v; }
	int getWeight() { return weight; }
};
 

class linearGraph {
	int V_number;
	list<listNode> *graph;
	void topSort(int start, vector<bool> &visited, stack<int> &Order);
public:
	linearGraph(int V) {
		this->V_number = V;
		graph = new list<listNode>[V];
	}

	void addEdge(int u, int v, int weight);

	void newShortPath(int start );

};

 

int main() {

	int  numb_e=0, was,n, m, v;
	vector<edge> e;
	stack<int> Order;
	const int INF = 1000000000;

	freopen("in.txt", "r",stdin);
	cin >> n >> m >> v;
	was = n; 
	e.emplace_back(edge{ n, m, v });
	++numb_e;
	do {
		cin >> n >> m >> v;
		if (n != was) {
			++numb_e;
			was = n;
		}
		e.emplace_back(edge{ n, m, v });
	} while (cin);


	vector<int> d(numb_e+2, INF);
	 

	//new way O(V+E)
	linearGraph gr(numb_e+2);

	
	for (int i = 0; i < e.size()-1; i++) {
		gr.addEdge(e[i].a, e[i].b, e[i].cost);
	}

	cout << "Topological order solution\nShortest path costs: ";
	gr.newShortPath(1);
	d[1] = 0;
	

	cout << "\n\nBellman-Ford way\nShortest path costs: ";
	 


	for (int i = 0; i<numb_e -1 ; ++i)
		for (int j = 0; j < e.size() ; ++j) {
			if (d[e[j].a] < INF)
				d[e[j].b] = min(d[e[j].b], d[e[j].a] + e[j].cost);

		}


	cout << d[numb_e+1]<<endl;
	/*
	for (auto i : d) {
		 
		cout << i << " \n";
	}


	*/

	
}




void linearGraph::topSort(int start, vector<bool> &visited, stack<int> &Order) {
	visited[start] = true;
	list<listNode>::iterator i;
	for (i = graph[start].begin(); i != graph[start].end(); ++i)
	{
		listNode node = *i;
		if (!visited[node.getV()])
			topSort(node.getV(), visited, Order);
	}

	Order.push(start);

}

void linearGraph::addEdge(int u, int v, int weight)
{
	listNode node(v, weight);
	graph[u].push_back(node);  
}

void linearGraph::newShortPath(int start)
{
	const int INF = INT_MAX;
	stack<int> Order;
	vector<bool> visited(V_number +1, false);
	vector<int> dist(V_number + 1, INF);

	dist[start] = 0;

	for (int i = 0; i < V_number; i++)
		if (!visited[i]) {
			topSort(i, visited, Order);
		}

	while (Order.empty() == false)
	{
		 
		int u = Order.top();
		Order.pop();

		  
		list<listNode>::iterator i;
		if (dist[u] != INF)
		{
			for (i = graph[u].begin(); i != graph[u].end(); ++i)
				if (dist[i->getV()] > dist[u] + i->getWeight())
					dist[i->getV()] = dist[u] + i->getWeight();
		}

	}

	cout << dist[V_number-1] << " ";
/*	for (auto i:dist) {
		if (i < INF)
			cout << i << " \n";
 
	}
	*/
}




