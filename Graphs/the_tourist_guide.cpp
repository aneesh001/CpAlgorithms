#include <bits/stdc++.h>
using namespace std;

#define INF 1000000007

int main(void) {
	int n, m;
	int count = 0;

	while(cin >> n >> m && !(n == 0 && m == 0)) {
		count += 1;
		vector<vector<pair<int, int>>> graph(n, vector<pair<int, int>>());
		for(int i = 0; i < m; ++i) {
			int u, v, w;
			cin >> u >> v >> w;
			u--; v--;

			graph[u].push_back({v, w});
			graph[v].push_back({u, w});
		}

		int s, d, t;
		cin >> s >> d >> t;
		s--;
		d--;

		vector<int> maximin(n, 0);
		maximin[s] = INF;

		for(int i = 0; i < n - 1; ++i) {
			for(int u = 0; u < n; ++u) {
				for(auto &p: graph[u]) {
					int v = p.first;
					int wt = p.second;

					maximin[v] = max(maximin[v], min(maximin[u], wt));
				}
			}
		}

		double ans = maximin[d] - 1;
		cout << "Scenario #" << count << endl;
		cout << "Minimum Number of Trips = " << static_cast<int>(ceil(t / ans)) << endl;
		cout << endl;
	}

	return 0;
}