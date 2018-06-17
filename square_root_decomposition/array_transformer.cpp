#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 10;
const int B = 1024;

int arr[N];
int n, m, u;
vector<int> box[505];

void update(int l, int r, int v, int p) {
	int i = l;
	int j = r;
	int cnt = 0;
	while(i <= j && i % B) if(arr[i++] < v) ++cnt;
	while(i <= j && (j + 1) % B) if(arr[j--] < v) ++cnt;
	while(i <= j) {
		cnt += lower_bound(box[i / B].begin(), box[i / B].end(), v) - box[i / B].begin();
		i += B;
	}

	arr[p] = 1LL * u * cnt / (r - l + 1);
	for(int k = 0; k < box[p / B].size(); ++k) {
		box[p / B][k] = arr[(p / B) * B + k];
	}
	sort(box[p / B].begin(), box[p / B].end());
}

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m >> u;
	for(int i = 0; i < n; ++i) {
		cin >> arr[i];
		box[i / B].push_back(arr[i]);
	}
	for(int i = 0; i <= n / B; ++i) {
		sort(box[i].begin(), box[i].end());
	}

	for(int i = 0; i < m; ++i) {
		int l, r, v, p;
		cin >> l >> r >> v >> p;
		--l; --r; --p;
		update(l, r, v, p);
	}

	for(int i = 0; i < n; ++i) {
		cout << arr[i] << endl;
	}

	return 0;
}