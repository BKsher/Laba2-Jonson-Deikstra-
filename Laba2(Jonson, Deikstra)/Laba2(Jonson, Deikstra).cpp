#include <bits/stdc++.h>
using namespace std;

struct edge {
	int a, b;
	double cost;
};

int n, m;
vector<edge> e;
vector < vector < pair<int, double> > > g;
const double INF = 1000000000;

bool isDirected = false;

vector<double> ford_belman(vector<edge> e) {
	vector<double> d(n, INF);
	int s = 0;
	d[s] = 0;
	while (true) {
		bool any = false;
		for (int j = 0; j < e.size(); ++j)
			if (d[e[j].a] < INF)
				if (d[e[j].b] > d[e[j].a] + e[j].cost) {
					d[e[j].b] = d[e[j].a] + e[j].cost;
					any = true;
				}
		if (!any)  break;
	}
	return d;
}

vector<double> dejkstra(vector < vector < pair<int, double> > > g, int n) {
	int s = 0;
	vector<double> d(n, INF), p(n);
	d[s] = 0;
	set < pair<int, int> > q;
	q.insert(make_pair(d[s], s));
	while (!q.empty()) {
		int v = q.begin()->second;
		q.erase(q.begin());

		for (size_t j = 0; j < g[v].size(); ++j) {
			int to = g[v][j].first,
				len = g[v][j].second;
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

void add_edge(int a, int b, double cost) {
	g[a].push_back({ b, cost });
	if(!isDirected) g[b].push_back({ a, cost });
	e.push_back({ a, b, cost });
}

int main()
{
	n = 9, m = 14;
	g.resize(n);
	add_edge(0, 1, 4);
	add_edge(0, 7, 8);
	add_edge(1, 2, 8);
	add_edge(7, 8, 8);
	add_edge(1, 7, 11);
	add_edge(7, 6, 1);
	add_edge(8, 6, 6);
	add_edge(2, 8, 2);
	add_edge(2, 3, 7);
	add_edge(2, 5, 4);
	add_edge(6, 5, 2);
	add_edge(3, 5, 14);
	add_edge(3, 4, 9);
	add_edge(5, 4, 10);

	cout << (dejkstra(g, n) == ford_belman(e) ? "Same" : "Not same");

}
