// in the name of Allah

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define pb push_back
#define ll long long
#define double long double
#define sz(x) ((int) (x.size()))

// #define fr first
// #define se second

/*

const ll mod = 998244353;

ll add(ll a, ll b) {
	a += b;
	if(a >= mod) return a - mod;
	return a;
}

ll mul(ll a, ll b) {
	a *= b;
	if(a >= mod) return a % mod;
	return a;
}

ll power(ll a, ll b) {
	ll p = 1;
	while(b) {
		if(b&1) p = mul(p, a);
		a = mul(a, a);
		b /= 2;
	}
	return p;
}

/**/

/*

// a bit of NT

const int _N = 1234567;

ll F[_N];
ll IF[_N];

void init() {
	F[0] = 1;
	for(int i=1; i<_N; i++) F[i] = mul(F[i-1], i);
	IF[_N-1] = power(F[_N-1], mod-2);
	for(int i=_N-2; i>=0; i--) IF[i] = mul(IF[i+1], i+1);
}

ll ncr(ll x, ll y) {
	if(y > x || y < 0) return 0;
	return mul(F[x], mul(IF[x-y], IF[y]));
}

ll euler(ll m) {
	ll res = 1;
	for(ll i = 2; i*i <= m; i++) {
		if(m%i == 0) {
			m /= i;
			res *= (i - 1);
			while(m % i == 0) {
				m /= i;
				res *= i;
			}
		}
	}
	if(m > 1) res *= (m-1);
	return res;
}

/**/

/*

// fenwick

struct FenwickTree {

	int n;
	vector <ll> t;

	FenwickTree(int nn) {
		n = nn;
		t.resize(n + 1);
	}

	void update(int idx, ll delta) {
		while(idx <= n) {
			t[idx] += delta;
			idx += (idx & -idx);
		}
	}

	ll sum(int idx) {
		ll res = 0;
		while(idx > 0) {
			res += t[idx];
			idx -= (idx & -idx);
		}
		return res;
	}

	// largest index has sum[idx] < val (or last)
	int firstIndexOfGE(ll val) {
		int step = (1 << 30);
		int i = 0;
		ll now = 0;
		while (step > 0) {
			if (i + step <= n && now + t[i + step] < val) {
				now += t[i + step];
				i += step;
			}
			step /= 2;
		}
		return i;
	}

	void debug() {
		for(int i = 1; i <= n; i++) {
			cerr << sum(i) - sum(i - 1) << " ";
		}
		cerr << endl;
	}

};

/**/

const int N = 1e5 + 10;

int n;
vector <int> g[N];

int sz[N];
int par[N];

void dfs1(int u, int p) {
	sz[u] = 1;
	par[u] = p;
	for(int v : g[u]) {
		if(v == p) continue;
		dfs1(v, u);
		sz[u] += sz[v];
	}
}

int cnt;
int chain_idx[N];
int chain_pos[N];
int chain_head[N];
int chain_size[N];

void hld(int u) {
	if(chain_size[cnt] == 0) chain_head[cnt] = u;
	chain_idx[u] = cnt;
	chain_pos[u] = chain_size[cnt];
	chain_size[cnt]++;
	int nx = 0, mx = 0;
	for(int v : g[u]) {
		if(v == par[u]) continue;
		if(mx < sz[v]) {
			mx = sz[v];
			nx = v;
		}
	}
	if(nx > 0) {
		hld(nx);
		for(int v : g[u]) {
			if(v == par[u] || v == nx) continue;
			cnt++;
			hld(v);
		}
	}
}

int main() {
	// ll start = clock();
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	cin >> n;
	int u, v;
	for(int i=1; i<n; i++) {
		cin >> u >> v;
		g[u].pb(v);
		g[v].pb(u);
	}
	dfs1(1, 0);
	cnt = 0;
	memset(chain_size, 0, sizeof chain_size);
	hld(1);

	// cerr << (clock() - start) / (CLOCKS_PER_SEC*1.0) << endl;
	return 0;
}