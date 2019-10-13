// segtree with range update for min

class segment_tree {

	private:
		int l, r, val;
		vector <int> A;
		vector <int> tree;
		vector <int> lazy;
		void build(int node, int start, int end) {
			if(start == end) tree[node] = A[start];
			else {
				int mid = (start + end) >> 1, nx = (node<<1);
				build(nx, start, mid);
				build(nx|1, mid+1, end);
				tree[node] = min(tree[nx], tree[nx|1]);
			}
		}
		void updateRange(int node, int start, int end) {
			int nx = (node<<1);
			if(lazy[node]) {
				tree[node] += lazy[node];
				if(start != end) {
					lazy[nx] += lazy[node];
					lazy[nx|1] += lazy[node];
				}
				lazy[node] = 0;
			}
			if(start > end || start > r || end < l) return;
			if(start >= l && end <= r) {
				tree[node] += val;
				if(start != end) {
					lazy[nx] += val;
					lazy[nx|1] += val;
				}
				return;
			}
			int mid = (start + end) >> 1;
			updateRange(nx, start, mid);
			updateRange(nx|1, mid + 1, end);
			tree[node] = min(tree[nx], tree[nx|1]);
		}
		int queryRange(int node, int start, int end) {
			if(start > end || start > r || end < l) return INT_MIN;
			int nx = (node<<1);
			if(lazy[node] != 0) {
				tree[node] += lazy[node];
				if(start != end) {
					lazy[nx] += lazy[node];
					lazy[nx|1] += lazy[node];
				}
				lazy[node] = 0;
			}
			if(start >= l && end <= r) return tree[node];
			int mid = (start + end) >> 1;
			int p1 = queryRange(nx, start, mid);
			int p2 = queryRange(nx|1, mid + 1, end);
			if(p1 <= p2) return p1;
			return p2;
		}

	public:

		int n;
		segment_tree() {}
		segment_tree(const vector <int> &v) {
			A = v;
			n = A.size();
			tree.assign(4*n, 0);
			lazy.assign(4*n, 0);
			build(1, 0, n-1);
		}
		int query(int left, int right) {
			l = left;
			r = right;
			return queryRange(1, 0, n-1);
		}
		void update(int left, int right, int value) {
			l = left;
			r = right;
			val = value;
			updateRange(1, 0, n-1);
		}

};