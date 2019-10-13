const int _N = 1e5 + 5;

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