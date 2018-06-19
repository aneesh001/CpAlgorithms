#include <bits/stdc++.h>
using namespace std;

#define MAXN 100000
#define INF INT_MAX

/* SUM (max, min, gcd, lcm etc are very similar) */

int a[MAXN];
int t[4 * MAXN];

void build(int v, int tl, int tr) {
	if(tl == tr) {
		t[v] = a[tl];
	}
	else {
		int tm = (tl + tr) / 2;
		build(2 * v, tl, tm);
		build(2 * v + 1, tm + 1, tr);
		t[v] = t[2 * v] + t[2 * v + 1];
	}
}

int sum(int v, int tl, int tr, int l, int r) {
	if(l > r) {
		return 0;
	}
	else if(tl == l && tr == r) {
		return t[v];
	}
	else {
		int tm = (tl + tr) / 2;
		return sum(2 * v, tl, tm, l, min(tm, r)) + 
			sum(2 * v + 1, tm + 1, tr, max(tm + 1, l), r);
	}
}

void update(int v, int tl, int tr, int pos, int val) {
	if(tl == tr) {
		t[v] = val;
	}
	else {
		int tm = (tl + tr) / 2;
		if(pos <= tm) {
			update(2 * v, tl, tm, pos, val);
		}
		else {
			update(2 * v + 1, tm + 1, tr, pos, val);
		}
		t[v] = t[2 * v] + t[2 * v + 1];
	}
}

/* SUM */

/* MAX and its freq */

pair<int, int> t1[4 * MAXN];

pair<int, int> combine(pair<int, int> &a, pair<int, int> &b) {
	if(a.first > b.first) {
		return a;
	}
	else if(a.first < b.first) {
		return b;
	}
	else {
		return {a.first, a.second + b.second};
	}
}

void build(int v, int tl, int tr) {
	if(tl == tr) {
		t1[v] = {a[tl], 1};
	}
	else {
		int tm = (tl + tr) / 2;
		build(2 * v, tl, tm);
		build(2 * v + 1, tm + 1, tr);
		t1[v] = combine(t[2 * v], t[2 * v + 1]);
	}
}

pair<int, int> get_max(int v, int tl, int tr, int l, int r) {
	if(l > r) {
		return {-INF, 0};
	}
	else if(tl == l && tr == r) {
		return t1[v];
	}
	else {
		int tm = (tl + tr) / 2;
		return combine(get_max(2 * v, tl, tm, l, min(tm, r)),
			get_max(2 * v + 1, tm + 1, tr, max(l, tm + 1), r));
	}
}

void update(int v, int tl, int tr, int pos, int val) {
	if(tl == tr) {
		t1[v] = {val, 1};
	}
	else {
		int tm = (tl + tr) / 2;
		if(pos <= tm) {
			update(2 * v, tl, tm, pos, val);
		}
		else {
			update(2 * v + 1, tm + 1, tr, pos, val);
		}
		t1[v] = combine(t1[2 * v], t1[2 * v + 1]);
	}
}

/* MAX and its freq */

/* Searching for kth zero */
/* Build a tree that stores number of zeroes in every nod
 * very similar to SUM */

int find_kth(int v, int tl, int tr, int k) {
	if(k > t[v]) {
		return -1;
	}
	if(tl == tr) {
		return t[v];
	}
	else {
		int tm = (tl + tr) / 2;
		if(k <= t[2 * v]) {
			return find_kth(2 * v, tl, tm, k);
		}
		else {
			return find_kth(2 * v + 1, tm + 1, tr, k - t[2 * v]);
		}
	}
}

/* Searching for kth zero */

/* Sub segment with maximum sum */

struct data {
	int pref, suff, sum, ans;
};

data t2[4 * MAXN];

data combine(data &a, data &b) {
	data ret;
	ret.sum = a.sum + b.sum;
	ret.pref = max(a.sum + b.pref, a.pref);
	ret.suff = max(a.suff + b.sum, b.suff);
	ret.ans = max(max(a.ans, b.ans), a.suff + b.pref);
}

data new_data(int val) {
	data ret;
	ret.sum = val;
	ret.pref = ret.suff = ret.ans = max(0, val);
	return ret;
}

void build(int v, int tl, int tr) {
	if(tl == tr) {
		t2[v] = new_data(a[tl]);
	}
	else {
		int tm = (tl + tr) / 2;
		build(2 * v, tl, tm);
		build(2 * v + 1, tm + 1, tr);
		t2[v] = combine(t2[2 * v], t2[2 * v + 1]);
	}
}

void update(int v, int tl, int tr, int pos, int val) {
	if(tl == tr) {
		t2[v] = new_data(val);
	}
	else {
		int tm = (tl + tr) / 2;
		if(pos <= tm) {
			update(2 * v, tl, tm, pos, val);
		}
		else {
			update(2 * v + 1, tm + 1, tr, pos, val);
		}
		t2[v] = combine(t2[2 * v], t2[2 * v + 1]);
	}
}

data querry(int v, int tl, int tr, int l, int r) {
	if(l > r) {
		return new_data(0);
	}
	if(tl == tr) {
		return t2[v];
	}
	else {
		int tm = (tl + tr) / 2;
		return combine(querry(2 * v, tl, tm, l, min(tm, r)), 
			querry(2 * v + 1, tm + 1, tr, max(l, tm + 1), r));
	}
}

/* Sub segment with maximum sum */

/* Smallest number greater than or equal to a specified number */

vector<int> t3[4 * MAXN];

void build(int v, int tl, int tr) {
 	if(tl == tr) {
 		t3[v] = vector<int>(1, a[tl]);
 	}
 	else {
 		int tm = (tl + tr) / 2;
 		build(2 * v, tl, tm);
 		build(2 * v + 1, tm + 1, tr);
 		merge(t3[2 * v].begin(), t3[2 * v].end(), t3[2 * v + 1].begin(), 
 			t3[2 * v + 1].end(), back_inserter(t3[v]));
 	}
 }

int querry(int v, int tl, int tr, int l, int r, int x) {
	if(l > r) {
		return INF;
	}
	if(l == tl && r == tr) {
		auto it = lower_bound(t3[v].begin(), t3[v].end(), x);
		if(it != t3[v].end()) {
			return *it;
		}
		return INF;
	}
	else {
		int tm = (tl + tr) / 2;
		return min(querry(2 * v, tl, tm, l, min(r, tm), x), 
			querry(2 * v + 1, tm + 1, tr, max(l, tm + 1), r, x));
	}
}

/* Smallest number greater than or equal to a specified number */

/* Addition on segments */

void build(int v, int tl, int tr) {
	if(tl == tr) {
		t[v] = a[tl];
	}
	else {
		int tm = (tl + tr) / 2;
		build(2 * v, tl, tm);
		build(2 * v + 1, tm + 1, tr);
		t[v] = 0;
	}
}

void update(int v, int tl, int tr, int l, int r, int add) {
	if(l > r) {
		return;
	}
	if(tl == l && tr == r) {
		t[v] += add;
	}
	else {
		int tm = (tl + tr) / 2;
		update(2 * v, tl, tm, l, min(r, tm));
		update(2 * v + 1, tm + 1, tr, max(l, tm + 1), r);
	}
}

int get(int v, int tl, int tr, int pos) {
	if(tl == tr) {
		return t[v];
	}
	else {
		int tm = (tl + tr) / 2;
		if(pos <= tm) {
			return t[v] + get(2 * v, tl, tm, pos);
		}
		else {
			return t[v] + get(2 * v + 1, tm + 1, tr, pos);
		}
	}
}

/* Addition on segments */

/* Assignment on segments */

int st[4 * MAXN];
bool marked[4 * MAXN];

void push(int v) {
	if(marked[v]) {
		st[2 * v] = st[2 * v + 1] = st[v];
		marked[2 * v] = marked[2 * v + 1] = true;
		marked[v] = false;
	}
}

void update(int v, int tl, int tr, int l, int r, int val) {
	if(l > r) {
		return;
	}
	if(tl == l && tr == r) {
		t[v] = val;
		marked[v] = true;
	}
	else {
		push(v);
		int tm = (tl + tr) / 2;
		update(2 * v, tl, tm, l, min(r, tm), val);
		update(2 * v + 1, tm + 1, tr, max(l, tm + 1), r, val);
	}
}

int get(int v, int tl, int tr, int pos) {
	if(tl == tr) {
		return t[v];
	}
	else {
		push(v);
		int tm = (tl + tr) / 2;
		if(pos <= tm) {
			return get(2 * v, tl, tm, pos);
		}
		else {
			return get(2 * v + 1, tm + 1, tr, pos);
		}
	}
}

/* Assignment on segments */

/* Addition on segments, querry for max */

int tree[4 * MAXN];
int lazy[4 * MAXN];

void push(int v) {
	lazy[2 * v] += lazy[v];
	tree[2 * v] += lazy[v];
	lazy[2 * v + 1] += lazy[v];
	tree[2 * v + 1] += lazy[v];
	lazy[v] = 0;
}

void update(int v, int tl, int tr, int l, int r, int val) {
	if(l > r) {
		return;
	}
	if(tl == l && tr == r) {
		lazy[v] += val;
		tree[v] += val;
	}
	else {
		push(v);
		int tm = (tl + tr) / 2;
		update(2 * v, tl, tm, l, min(tm, r), val);
		update(2 * v + 1, tm + 1, tr, max(tm + 1, l), r, val);
		tree[v] = max(tree[2 * v], tree[2 * v + 1]);
	}
}

int querry(int v, int tl, int tr, int l, int r) {
	if(l > r) {
		return -INF;
	}
	if(tl == l && tr == r) {
		return tree[v];
	}
	else {
		push(v);
		int tm = (tl + tr) / 2;
		return max(querry(2 * v, tl, tm, l, min(r, tm)), 
			querry(2 * v + 1, tm + 1, tr, max(l, tm + 1), r));
	}
}

/* Addition on segments, querry for max */

int main(void) {
	return 0;
}