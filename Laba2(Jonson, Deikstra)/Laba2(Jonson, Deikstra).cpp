#include <bits/stdc++.h>
using namespace std;

struct edge {
	int a, b, cost;
};

int n, m, v;
vector<edge> e;
const int INF = 1000000000;

void ford_belman(vector<edge> e) {
	vector<int> d(n, INF);
	d[v] = 0;
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
}

int main()
{
    
}
