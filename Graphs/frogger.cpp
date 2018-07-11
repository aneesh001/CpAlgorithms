#include <bits/stdc++.h>
using namespace std;

#define INF 1000000007

double dist(const pair<int, int> &p1, const pair<int, int> &p2) {
	double a = pow(p1.first - p2.first, 2);
	double b = pow(p1.second - p2.second, 2);
	return sqrt(a + b);
}

int main(void) {
	int n;
	int count = 0;
	cout << fixed;
	cout << setprecision(3);

	while(cin >> n && n != 0) {
		count += 1;
		vector<pair<int, int>> points;
		for(int i = 0; i < n; ++i) {
			int u, v;
			cin >> u >> v;
			points.push_back({u, v});
		}

		vector<double> minimax(n, INF);
		minimax[0] = 0;
		for(int iter = 0; iter < n - 1; ++iter) {
			for(int i = 0; i < n; ++i) {
				for(int j = 0; j < n; ++j) {
					if(i != j) {
						minimax[j] = min(minimax[j], max(minimax[i], dist(points[i], points[j])));
					}
				}
			}
		}

		cout << "Scenario #" << count << endl;
		cout <<  "Frog Distance = " << minimax[1] << endl;
		cout << endl;
	}

	return 0;
}