// in the name of Allah

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define pb push_back
#define ll long long
#define double long double
#define sz(x) ((int) (x.size()))

#define fr first
#define se second

#define INF 1e18

ll assignment(vector < vector <ll> > &a) {
	int n = sz(a)-1;
	int m = sz(a[0])-1;
	vector <ll> u(n+1), v(m+1);
	vector <int> p(m+1), way(m+1);
	for(int i=1; i<=n; i++) {
		p[0] = i;
		int j0 = 0;
		bitset <2222> used;
		vector <ll> minv(m+1, INF);
		do {
			used[j0] = 1;
			ll delta = INF;
			int i0 = p[j0], j1;
			for(int j=1; j<=m; j++) {
				if(!used[j]) {
					ll cur = a[i0][j] - u[i0] - v[j];
					if(cur < minv[j]) {
						minv[j] = cur;
						way[j] = j0;
					}
					if(minv[j] < delta) {
						delta = minv[j];
						j1 = j;
					}
				}
			}
			for(int j=0; j<=m; j++) {
				if(used[j]) {
					u[p[j]] += delta;
					v[j] -= delta;
				}
				else {
					minv[j] -= delta;
				}
			}
			j0 = j1;
		} while(p[j0] != 0);
		do {
			int j1 = way[j0];
			p[j0] = p[j1];
			j0 = j1;
		} while(j0);
	}

	vector <int> ans(n+1);
	for(int j=1; j<=m; j++) ans[p[j]] = j;

	ll res = 0;
	for(int i=1; i<=n; i++) res += a[i][ans[i]];

	// ll cost = -v[0];
	// assert(cost == res);
	return res;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	int n, m;
	cin >> n >> m;
	ll bx[n], by[n], cx[m], cy[m], x, y;
	for(int i=0; i<n; i++) cin >> bx[i] >> by[i];
	for(int i=0; i<m; i++) cin >> cx[i] >> cy[i];
	cin >> x >> y;

	ll res = 0;
	vector < vector <ll> > a(n+1, vector <ll>(m + n, 0));
	for(int i=0; i<n; i++) {
		int t = i+1;
		for(int j=0; j<m; j++) a[t][j+1] = abs(bx[i] - cx[j]) + abs(by[i] - cy[j]);
		ll dist = abs(x - bx[i]) + abs(y - by[i]);
		for(int j=m+1, k = 1; k<n; k++, j++) a[t][j] = dist;
		res += dist;
	}

	cout << assignment(a)+res << endl;

	return 0;
}