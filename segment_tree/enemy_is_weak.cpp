#include <bits/stdc++.h>
using namespace std;

#define MAXN 1000007

int a[MAXN];
vector<int> st[4 * MAXN];

void build(int v, int tl, int tr) {
	if(tl == tr) {
		st[v].push_back(a[tl]);
	}
	else {
		int tm = (tl + tr) / 2;
		build(2 * v, tl, tm);
		build(2 * v + 1, tm + 1, tr);
		merge(st[2 * v].begin(), st[2 * v].end(), 
			st[2 * v + 1].begin(), st[2 * v + 1].end(), back_inserter(st[v]));
	}
}

int querry1(int v, int tl, int tr, int l, int r, int val) {
	if(l > r) {
		return 0;
	}
	if(tl == l && tr == r) {
		return st[v].end() - upper_bound(st[v].begin(), st[v].end(), val);
	}
	else {
		int tm = (tl + tr) / 2;
		return querry1(2*v, tl, tm, l, min(r, tm), val) +
			querry1(2*v + 1, tm + 1, tr, max(tm + 1, l), r, val);
	}
}

int querry2(int v, int tl, int tr, int l, int r, int val) {
	if(l > r) {
		return 0;
	}
	if(tl == l && tr == r) {
		return lower_bound(st[v].begin(), st[v].end(), val) - st[v].begin();
	}
	else {
		int tm = (tl + tr) / 2;
		return querry2(2*v, tl, tm, l, min(r, tm), val) +
			querry2(2*v + 1, tm + 1, tr, max(l, tm + 1), r, val);
	}
}

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;
	cin >> n;
	for(int i = 0; i < n; ++i) {
		cin >> a[i];
	}

	build(1, 0, n - 1);

	long long ans = 0;
	for(int i = 0; i < n; ++i) {
		long long left = querry1(1, 0, n - 1, 0, i - 1, a[i]);
		long long right = querry2(1, 0, n - 1, i + 1, n - 1, a[i]);

		ans += left * right;
	}

	cout << ans << endl;
	return 0;
}