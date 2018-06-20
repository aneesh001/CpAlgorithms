#include <bits/stdc++.h>
using namespace std;

#define MAXN 1000007

int a[MAXN];
int l[MAXN];
int r[MAXN];
int st[4 * MAXN];
unordered_map<int, int> mp, mp1;

int querry(int v, int tl, int tr, int l, int r) {
	if(l > r) return 0;
	if(tl == l && tr == r) {
		return st[v];
	}
	else {
		int tm = (tl + tr) / 2;
		return querry(2 * v, tl, tm, l, min(tm, r)) + 
			querry(2 * v + 1, tm + 1, tr, max(tm + 1, l), r);
	}
}

void update(int v, int tl, int tr, int pos) {
	if(tl == tr) {
		st[v] += 1;
	}
	else {
		int tm = (tl + tr) / 2;
		if(pos <= tm) {
			update(2 * v, tl, tm, pos);
		}
		else {
			update(2 * v + 1, tm + 1, tr, pos);
		}
		st[v] = st[2 * v] + st[2 * v + 1];
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

	for(int i = 0; i < n; ++i) {
		mp[a[i]]++;
		l[i] = mp[a[i]];
	}
	mp.clear();
	for(int i = n - 1; i >= 0; --i) {
		mp1[a[i]]++;
		r[i] = mp1[a[i]];
	}

	long long ans = 0;
	for(int i = n - 1; i >= 0; --i) {
		ans = ans + querry(1, 0, n - 1, 0, l[i] - 1);
		update(1, 0, n - 1, r[i]);
	}

	cout << ans << endl;
	return 0;
}