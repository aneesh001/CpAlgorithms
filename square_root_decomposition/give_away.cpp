#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <assert.h>
using namespace std;

int n, q;
vector<int> arr;
vector<vector<int>> box;
int size;

int querry(int l, int r, int v) {
	int i = l;
	int j = r;
	int cnt = 0;
	while(i <= j && i % size) if(arr[i++] >= v) ++cnt;
	while(i <= j && (j + 1) % size) if(arr[j--] >= v) ++cnt;
	while(i <= j) {
		int o = i / size;
		cnt += box[o].size() - (lower_bound(box[o].begin(), box[o].end(), v) - box[o].begin());
		i += size;
	}

	return cnt;
}

void modify(int i, int v) {
	int o = i / size;
	arr[i] = v;
	for(int j = 0; j < box[o].size(); ++j) {
		box[o][j] = arr[o * size + j];
	}
	sort(box[o].begin(), box[o].end());
}

int main(void) {
	cin >> n;

	arr = vector<int>(n, 0);
	size = sqrt(n) + 1;
	for(int i = 0; i < size; ++i) {
		box.push_back(vector<int>());
	}

	for(int i = 0; i < n; ++i) {
		cin >> arr[i];
		box[i / size].push_back(arr[i]);
	}

	for(int i = 0; i < size; ++i) {
		sort(box[i].begin(), box[i].end());
	}

	cin >> q;

	for(int i = 0; i < q; ++i) {
		int type;
		cin >> type;

		if(type == 0) {
			int a, b, c;
			cin >> a >> b >> c;
			a--; b--;
			cout << querry(a, b, c) << endl;
		}
		else {
			int a, b;
			cin >> a >> b;
			a--;
			modify(a, b);
		}
	}

	return 0;
}