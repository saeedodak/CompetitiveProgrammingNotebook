
inline ll power(ll a, ll b) {
	ll p = 1;
	while(b) {
		if(b&1) p = mul(p, a);
		a = mul(a, a);
		b /= 2;
	}
	return p;
}

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

	// largest index such that sum[idx] < val (or last)
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