// in the name of Allah

#include <bits/stdc++.h>
 
#define endl '\n'
#define ll long long
#define PI acos(-1.0)
#define ldouble long double
#define sz(x) ((ll) (x.size()))

using namespace std;

struct Complex {
	ldouble x, y;
	Complex() {}
	Complex(ldouble x, ldouble y) : x(x), y(y) {}
	Complex(const Complex &p) : x(p.x), y(p.y) {}
	Complex operator + (const Complex &p) const {
		return Complex(x + p.x, y + p.y);
	}
	Complex operator - (const Complex &p) const {
		return Complex(x - p.x, y - p.y);
	}
	Complex operator * (Complex c) const {
		return Complex(x*c.x - y*c.y, x*c.y + y*c.x);
	}
	Complex operator / (ldouble c) const {
		return Complex(x/c, y/c);
	}
};

inline int get_degree(int t) {
	for(int i=0; ; i++) {
		if(t < (1<<i)) return (1<<i);
	}
}

inline vector <Complex> fft(vector <Complex> v, bool INV) {
	if(v.size() == 1) return v;
	vector <Complex> p[2];
	for(int i=0; i<v.size(); i++) p[i%2].push_back(v[i]);
	vector <Complex> P[2], res(v.size());
	P[0] = fft(p[0], INV);
	P[1] = fft(p[1], INV);
	Complex w = Complex(1, 0);
	Complex step = Complex(cos(2*PI/v.size()), sin(2*PI/v.size()));
	if(INV) step = Complex(cos(2*PI/v.size()), -sin(2*PI/v.size()));
	for(int i=0; i<v.size()/2; i++) {
		res[i] = P[0][i] + (w * P[1][i]);
		res[i+v.size()/2] = P[0][i] - (w * P[1][i]);
		w = w * step;
	}
	return res;
}

inline void multiply(vector <ll> &a, vector <ll> &b) {
	int n = sz(a)-1;
	int m = sz(b)-1;
	int d = get_degree(n+m+1);
	vector <Complex> P(d, Complex(0, 0));
	vector <Complex> Q(d, Complex(0, 0));
	for(int i=0; i<=n; i++) P[i].x = a[i];
	for(int i=0; i<=m; i++) Q[i].x = b[i];
	P = fft(P, 0);
	Q = fft(Q, 0);
	for(int i=0; i<d; i++) P[i] = P[i] * Q[i];
	P = fft(P, 1);
	a.resize(n+m+1);
	for(int i=0; i<=n+m; i++) a[i] = ((ll) (P[i].x/d + 0.5));
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int TC;
	cin >> TC;
	while(TC--) {
		int n;
		cin >> n;
		vector <ll> a(n+1), b(n+1);
		for(int i=0; i<=n; i++) cin >> a[i];
		for(int i=0; i<=n; i++) cin >> b[i];
		multiply(a, b);
		cout << a[0];
		for(int i=1; i<sz(a); i++) cout << " " << a[i];
		if(TC) cout << '\n';
	}
	return 0;
}