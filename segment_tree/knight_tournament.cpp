#include <bits/stdc++.h>
using namespace std;

#define MAXN 300005

int a[MAXN];
int t[4 * MAXN];

void update(int v, int tl, int tr, int l, int r, int x) {
	// invalid range.
	if(l > r) return;
	if(l > tr || r < tl) return;

	// all members already dead in this range.
	if(t[v] == tr - tl + 1) return;

	if(tl == tr) {
		t[v] = 1;
		a[tl] = x;
	}
	else {
		int tm = (tl + tr) / 2;
		update(2 * v, tl, tm, l, min(tm, r), x);
		update(2 * v + 1, tm + 1, tr, max(l, tm + 1), r, x);
		t[v] = t[2 * v] + t[2 * v + 1];
	}
}

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m;
	cin >> n >> m;
	for(int i = 0; i < m; ++i) {
		int l, r, x;
		cin >> l >> r >> x;
		l--; r--; x--;
		update(1, 0, n - 1, l, x - 1, x + 1);
		update(1, 0, n -1 , x + 1, r, x + 1);
	}

	for(int i = 0; i < n; ++i) {
		cout << a[i] << " ";
	}
	cout << endl;

	return 0;
}