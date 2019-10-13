// in the name of Allah

#include <bits/stdc++.h>
using namespace std;

#define gcd __gcd
#define endl '\n'
#define pb push_back
#define ll long long
#define double long double
#define sz(x) ((int) (x.size()))

const int LOGN = 20;
const int N = 5e4 + 5;

class segment_tree {
private:
	int n, l, r, delta;
	vector <int> A;
	vector <int> lazy;
	vector <int> last;
	vector <int> first;
	vector <int> diff_gcd;
	void build(int node, int start, int end) {
		if(start == end) {
			first[node] = A[start];
			last[node] = A[start];
			diff_gcd[node] = 0;
		}
		else {
			int mid = (start + end) / 2;
			int nx = 2*node;
			build(nx, start, mid);
			build(nx|1, mid+1, end);
			first[node] = first[nx];
			last[node] = last[nx|1];
			diff_gcd[node] = abs(gcd(diff_gcd[nx], gcd(first[nx|1] - last[nx], diff_gcd[nx|1])));
		}
	}
	void updateRange(int node, int start, int end) {
		int nx = 2*node;
		if(lazy[node] != 0) {
			first[node] += lazy[node];
			last[node] += lazy[node];
			if(start != end) {
				lazy[nx] += lazy[node];
				lazy[nx|1] += lazy[node];
			}
			lazy[node] = 0;
		}
		if(start > end || start > r || end < l) return;
		if(start >= l && end <= r) {
			first[node] += delta;
			last[node] += delta;
			if(start != end) {
				lazy[nx] += delta;
				lazy[nx|1] += delta;
			}
			return;
		}
		int mid = (start + end) / 2;
		updateRange(nx, start, mid);
		updateRange(nx|1, mid + 1, end);
		first[node] = first[nx];
		last[node] = last[nx|1];
		diff_gcd[node] = abs(gcd(diff_gcd[nx], gcd(first[nx|1] - last[nx], diff_gcd[nx|1])));
	}
	int queryRange(int node, int start, int end) {
		if(start > end || start > r || end < l) return 0;
		int nx = 2*node;
		if(lazy[node] != 0) {
			first[node] += lazy[node];
			last[node] += lazy[node];
			if(start != end) {
				lazy[nx] += lazy[node];
				lazy[nx|1] += lazy[node];
			}
			lazy[node] = 0;
		}
		if(start >= l && end <= r) return gcd(first[node], diff_gcd[node]);
		int mid = (start + end) / 2;
		int p1 = queryRange(nx, start, mid);
		int p2 = queryRange(nx|1, mid + 1, end);
		return gcd(p1, p2);
	}
public:
	segment_tree() {}
	segment_tree(vector <int> &v) {
		A = v;
		n = sz(A);
		lazy.assign(4*n, 0);
		first.assign(4*n, 0);
		last.assign(4*n, 0);
		diff_gcd.assign(4*n, 0);
		build(1, 0, n-1);
	}
	void update(int left, int right, int D) {
		l = left;
		r = right;
		delta = D;
		updateRange(1, 0, n-1);
	}
	int query(int left, int right) {
		if(right < left) return 0;
		l = left;
		r = right;
		return queryRange(1, 0, n-1);
	}
};

int n;
int dist[N];
int dp[N][LOGN];
vector <int> g[N];

void calc() {
	dp[1][0] = 1;
	for(int j=1; j<20; j++)
		for(int i=1; i<=n; i++)
			dp[i][j] = dp[dp[i][j-1]][j-1];
}

int lca(int a, int b) {
	if(dist[a] > dist[b]) swap(a, b);
	int d = dist[b] - dist[a];
	for(int i=0; i<20; i++) if((d&(1<<i)) > 0) b = dp[b][i];
	if(a == b) return a;
	for(int i=19; i>=0; i--) {
		if(dp[a][i] != dp[b][i]) {
			a = dp[a][i];
			b = dp[b][i];
		}
	}
	return dp[a][0];
}

int sz[N];
int par[N];

void dfs1(int u, int p) {
	sz[u] = 1;
	par[u] = p;
	dp[u][0] = p;
	dist[u] = dist[p] + 1;
	for(int v : g[u]) {
		if(v == p) continue;
		dfs1(v, u);
		sz[u] += sz[v];
	}
}

int cnt;
int val[N];
int chain_idx[N];
int chain_pos[N];
int chain_head[N];
vector <int> chains[N];
vector < segment_tree > ds;

void hld(int u) {
	if(sz(chains[cnt]) == 0) chain_head[cnt] = u;
	chain_idx[u] = cnt;
	chain_pos[u] = sz(chains[cnt]);
	chains[cnt].pb(val[u]);
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

int find(int xx, int yy, int x, int y) {
	if(x == xx) return ds[xx].query(y, yy);
	else {
		int gg = ds[xx].query(0, yy);
		int u = par[chain_head[xx]];
		xx = chain_idx[u];
		yy = chain_pos[u];
		return gcd(gg, find(xx, yy, x, y));
	}
}

int find(int u, int v) {
	int w = lca(u, v);
	int x = chain_idx[w];
	int y = chain_pos[w];
	int	xu = chain_idx[u];
	int yu = chain_pos[u];
	int	xv = chain_idx[v];
	int yv = chain_pos[v];
	return gcd(find(xu, yu, x, y), find(xv, yv, x, y));
}

void change(int xx, int yy, int x, int y, int d) {
	if(x == xx) ds[xx].update(y, yy, d);
	else {
		ds[xx].update(0, yy, d);
		int u = par[chain_head[xx]];
		xx = chain_idx[u];
		yy = chain_pos[u];
		change(xx, yy, x, y, d);
	}
}

void change(int u, int v, int d) {
	int w = lca(u, v);
	int x = chain_idx[w];
	int y = chain_pos[w];
	int	xu = chain_idx[u];
	int yu = chain_pos[u];
	int	xv = chain_idx[v];
	int yv = chain_pos[v];
	change(xu, yu, x, y, d);
	change(xv, yv, x, y, d);
	change(x, y, x, y, -d);
	// take care about third one
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> n;
	int u, v;
	for(int i=1; i<n; i++) {
		cin >> u >> v;
		u++;
		v++;
		g[u].pb(v);
		g[v].pb(u);
	}
	for(int i=1; i<=n; i++) cin >> val[i];
	dist[0] = -1;
	dfs1(1, 0);
	cnt = 0;
	hld(1);
	for(int i=0; i<=cnt; i++) ds.pb(segment_tree(chains[i]));
	calc();
	char c;
	int q, d;
	cin >> q;
	while(q--) {
		cin >> c;
		cin >> u >> v;
		u++; v++;
		if(c == 'F') cout << find(u, v) << endl;
		else {
			cin >> d;
			change(u, v, d);
		}
	}
	return 0;
}


// be khoda zehnam gozid