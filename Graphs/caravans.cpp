#include <bits/stdc++.h>
using namespace std;

int n, m;
int s, f, r;
vector<vector<int>> graph;
vector<int> d_s;
vector<int> d_r;

vector<int> bfs(int src) {
    vector<int> vis(n, false);
    vector<int> dist(n, -1);
    dist[src] = 0;

    queue<int> q;
    q.push(src);
    vis[src] = true;

    while(!q.empty()) {
        int curr = q.front();
        q.pop();

        for(int i: graph[curr]) {
            if(!vis[i]) {
                q.push(i);
                vis[i] = true;
                dist[i] = dist[curr] + 1;
            }
        }
    }

    return dist;
}

int main(void) {
    cin >> n >> m;
    graph = vector<vector<int>>(n, vector<int>());
    for(int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    cin >> s >> f >> r;
    s--; f--; r--;

    d_s = bfs(s);
    d_r = bfs(r);

    

    return 0;
}
