
class fen {

public:

	ll add_tree[N];
	ll mul_tree[N];

	fen() {
		memset(add_tree, 0, sizeof add_tree);
		memset(mul_tree, 0, sizeof mul_tree);
	}

	void internalUpdate(ll idx, ll mul, ll add) {
		while(idx <= N) {
			mul_tree[idx] += mul;
			add_tree[idx] += add;
			idx += (idx & -idx);
		}
	}

	void update(ll l, ll r, ll val) {
		internalUpdate(l, val, -val * (l - 1));
		internalUpdate(r+1, -val, val * r);
	}

	ll query(ll idx) {
		ll mul = 0;
		ll add = 0;
		ll start = idx;
		while(idx > 0) {
			mul += mul_tree[idx];
			add += add_tree[idx];
			idx -= (idx & -idx);
		}
		return mul * start + add;
	}
	
}