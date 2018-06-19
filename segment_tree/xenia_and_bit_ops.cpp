#include <iostream>
#include <vector>
#include <utility>
#include <assert.h>
#include <cmath>

using namespace std;

#define MAXN 1500000

int arr[MAXN];
pair<int, int> st[4 * MAXN];

pair<int, int> combine(pair<int, int> &a, pair<int, int> &b) {
	assert(a.second == b.second);

	if(a.second == 0) {
		return make_pair(a.first | b.first, 1);
	}
	else {
		return make_pair(a.first ^ b.first, 0);
	}
}

void build(int v, int l, int r) {
	if(l == r) {
		st[v] = make_pair(arr[l], 0);
	}
	else {
		int m = (l + r) / 2;
		build(2 * v, l, m);
		build(2 * v + 1, m + 1, r);
		st[v] = combine(st[2 * v], st[2 * v + 1]);
	}
}

void update(int v, int l, int r, int p, int b) {
	if(l == r) {
		st[v] = make_pair(b, 0);
	}
	else {
		int m = (l + r) / 2;
		if(p <= m) {
			update(2 * v, l, m, p, b);
		}
		else {
			update(2 * v + 1, m + 1, r, p, b);
		}
		st[v] = combine(st[2 * v], st[2 * v + 1]);
	}
}

int main(void) {
	int s, m;
	cin >> s >> m;
	int n = (int) pow(2, s);
	for(int i = 0; i < n; ++i) {
		cin >> arr[i];
	}
	build(1, 0, n - 1);
	for(int i = 0; i < m; ++i) {
		int p, b;
		cin >> p >> b;
		update(1, 0, n - 1, p - 1, b);
		cout << st[1].first << endl;
	}
	return 0;
}