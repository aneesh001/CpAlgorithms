#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;

vector<vector<int>> ht;
vector<vector<bool>> visited;
int n, m;
int res;

struct comp {
    bool operator()(const pair<pii,int> &a, const pair<pii,int> &b){
    	return a.second > b.second;
    }
};

bool valid(int i, int j) {
    return i >= 0 && i < n && j >= 0 && j < m;
}

vector<int> nx = {1, -1, 0, 0};
vector<int> ny = {0, 0, -1, 1};

void floodfill(){
	priority_queue<pair<pii,int> , vector<pair<pii,int>>, comp> pq;

    for(int i = 0; i < m; ++i) {
        pq.push({{0, i}, ht[0][i]});
        pq.push({{n - 1, i}, ht[n - 1][i]});
    }
    for(int i = 1; i < n - 1; ++i) {
        pq.push({{i, 0}, ht[i][0]});
        pq.push({{i, m - 1}, ht[i][m - 1]});
    }

	while(!pq.empty()){
		int cur_level = pq.top().second;

		while(!pq.empty()){
            pair<pii,int> top = pq.top();

            if(top.second > cur_level){
				break;
			}

			pq.pop();
			if(visited[top.first.first][top.first.second]){
				continue;
			}

            visited[top.first.first][top.first.second] = true;
			res += cur_level - top.second;

			for(int i = 0; i < 4; ++i){
				int cx = top.first.first + nx[i];
				int cy = top.first.second + ny[i];

				if(valid(cx, cy)){
					pq.push({{cx, cy}, ht[cx][cy]});
				}
			}
		}
	}
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

	int t;
	cin >> t;

    for(int ti = 0; ti < t; ++ti) {
        cin >> n >> m;

        ht = vector<vector<int>>(n, vector<int>(m, 0));
        visited = vector<vector<bool>>(n, vector<bool>(m, false));
        res = 0;

        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                cin >> ht[i][j];
            }
        }

        floodfill();
        cout << res << endl;
    }
	return 0;
}
