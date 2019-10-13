class BIT {
	public :
	int tree[max_n];
	BIT() { memset(tree, 0, sizeof tree); }
	int query(int idx) {
		int sum = 0;
		while (idx > 0){
			sum += tree[idx];
			idx -= (idx & -idx);
		}
		return sum;
	}
	int query(int i, int j) {
		return query(j) - query(i-1);
	}
	void update(int idx, int val) {
		while (idx <= max_n) {
			tree[idx] += val;
			idx += (idx & -idx);
		}
	}
}