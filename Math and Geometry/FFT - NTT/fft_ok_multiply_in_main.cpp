// in the name of Allah

#include <bits/stdc++.h>
 
#define endl '\n'
#define ll long long
#define PI acos(-1.0)
#define sz(x) ((ll) (x.size()))
#define ldouble long double

using namespace std;

struct Complex {
	ldouble x, y;
	Complex() {}
	Complex(ldouble x, ldouble y) : x(x), y(y) {}
	Complex(const Complex &P) : x(P.x), y(P.y) {}
	Complex operator + (const Complex &P) const {
		return Complex(x + P.x, y + P.y);
	}
	Complex operator - (const Complex &P) const {
		return Complex(x - P.x, y - P.y);
	}
	Complex operator * (Complex c) const {
		return Complex(x*c.x - y*c.y, x*c.y + y*c.x);
	}
	Complex operator / (ldouble c) const {
		return Complex(x/c, y/c);
	}
	ldouble real() {
		return x;
	}
	ldouble imag() {
		return y;
	}
};

inline int get_degree(int t) {
	for(int i=0; ; i++) {
		if(t < (1<<i)) return (1<<i);
	}
}

vector <Complex> fft(vector <Complex> v, bool INV) {
	if(v.size() == 1) return v;
	vector <Complex> P[2];
	for(int i=0; i<v.size(); i++) P[i%2].push_back(v[i]);
	vector <Complex> res(v.size());
	P[0] = fft(P[0], INV);
	P[1] = fft(P[1], INV);
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

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int TC;
	cin >> TC;
	while(TC--) {
		int n, m, t;
		cin >> n; m = n;
		int d = get_degree(n+m+1);
		vector <Complex> P(d, Complex(0, 0));
		vector <Complex> Q(d, Complex(0, 0));
		for(int i=0; i<=n; i++) { cin >> t; P[i].x = t; }
		for(int i=0; i<=n; i++) { cin >> t; Q[i].x = t; }
		P = fft(P, 0);
		Q = fft(Q, 0);
		for(int i=0; i<d; i++) P[i] = P[i] * Q[i];
		P = fft(P, 1);
		cout << ((ll) (P[0].x/d + 0.5));
		for(int i=1; i<=n+m; i++) cout << " " << ((ll) (P[i].x/d + 0.5));
		if(TC) cout << '\n';
	}
	return 0;
}