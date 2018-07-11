#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>
#define INF 100000007

int n, e, t;
vector<vector<pii>> graph;
vector<int> dist;

void dijkstra() {
    dist[e] = 0;
    set<pii> s;
    s.insert({0, e});

    while(!s.empty()) {
        int curr = s.begin()->second;
        s.erase(s.begin());

        for(auto p: graph[curr]) {
            int to = p.first;
            int len = p.second;

            if(dist[to] > dist[curr] + len) {
                s.erase({dist[to], to});
                dist[to] = dist[curr] + len;
                s.insert({dist[to], to});
            }
        }
    }
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> e >> t;
    e--;

    graph = vector<vector<pii>>(n, vector<pii>());
    dist = vector<int>(n, INF);

    int m;
    cin >> m;
    for(int i = 0; i < m; ++i) {
        int u, v, wt;
        cin >> u >> v >> wt;
        u--; v--;

        graph[v].push_back({u, wt});
    }

    dijkstra();

    int ans = 0;
    for(int i = 0; i < n; ++i) {
        if(dist[i] <= t) ++ans;
    }

    cout << ans << endl;

    return 0;
}
