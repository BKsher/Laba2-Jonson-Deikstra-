#include <bits/stdc++.h>
using namespace std;

struct edge {
	int a, b;
	double cost;
};

int n, m;
vector<edge> e;
vector < vector < pair<int, double> > > g;
vector <vector <double>> graph;
const double INF = 1000000000;

bool isDirected = true;

void add_edge(int a, int b, double cost) {
	g[a].push_back({ b, cost });
	if (!isDirected) g[b].push_back({ a, cost });
	e.push_back({ a, b, cost });
	graph[a][b] = cost;
}

vector<double> ford_belman(vector<edge> e) {
	vector<double> d(n+1, INF);
	d[n] = 0;

	for (int i = 0; i < n; i++)
		e.push_back({ n, i, 0 });

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < e.size(); j++)
			if (d[e[j].a] < INF)
				if (d[e[j].b] > d[e[j].a] + e[j].cost)
					d[e[j].b] = d[e[j].a] + e[j].cost;
	}
	for (int j = 0; j < e.size(); j++)
		if (d[e[j].b] > d[e[j].a] + e[j].cost) {
			d.clear();
			return d;
		}
	d.pop_back();
	return d;
}

vector<double> dijkstra(vector < vector < pair<int, double> > > g, vector < vector <double> > modifiedGraph, int s = 0) {
	vector<double> d(n, INF), p(n);
	d[s] = 0;
	set < pair<int, int> > q;
	q.insert(make_pair(d[s], s));
	while (!q.empty()) {
		int v = q.begin()->second;
		q.erase(q.begin());

		for (size_t j = 0; j < g[v].size(); ++j) {
			int to = g[v][j].first,
				len = modifiedGraph[v][to];
			if (d[v] + len < d[to]) {
				q.erase(make_pair(d[to], to));
				d[to] = d[v] + len;
				p[to] = v;
				q.insert(make_pair(d[to], to));
			}
		}
	}
	return d;
}

void johnson() {
	vector<double> modifyWeights = ford_belman(e);
	vector< vector <double> > modifiedGraph(n, vector<double>(n, 0));
	if (modifyWeights.empty()) {
		cout << "Graph has cycle of negative length\n";
		return;
	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) 
			if (graph[i][j] != 0)
				modifiedGraph[i][j] = (graph[i][j] + modifyWeights[i] - modifyWeights[j]);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			cout << modifiedGraph[i][j] << ' ';
		cout << '\n';
	}

	for (int s = 0; s < n; s++) {
		vector<double> d = dijkstra(g, modifiedGraph, s);

		cout << "Distanses from vertex " << s << ":\n";
		for (int i = 0; i < n; i++)
			cout << "to vertex " << i << " : " << d[i] - modifyWeights[s] + modifyWeights[i] << '\n';
		cout << '\n';
	}
}

int main()
{
	n = 4, m = 5;
	g.resize(n);
	graph.resize(n, vector<double>(n, 0));
	add_edge(0, 1, -5);
	add_edge(1, 2, 4);
	add_edge(2, 3, 1);
	add_edge(0, 3, 3);
	add_edge(0, 2, 2);
	johnson();
}
