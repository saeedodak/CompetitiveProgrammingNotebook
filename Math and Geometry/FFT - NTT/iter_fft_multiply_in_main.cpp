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
	for(int i=0; ; i++) if(t < (1<<i)) return (1<<i);
}

int reverse(int num, int lg_n) {
	int res = 0;
	for(int i = 0; i < lg_n; i++) if(num & (1 << i)) res |= 1 << (lg_n - 1 - i);
	return res;
}

void fft(vector<Complex> &a, bool inv) {
	int n = a.size();
	int lg_n = 0;
	while ((1 << lg_n) < n) lg_n++;
	for (int i = 0; i < n; i++) if(i < reverse(i, lg_n)) swap(a[i], a[reverse(i, lg_n)]);
	for(int len = 2; len <= n; len <<= 1) {
		ldouble ang = 2 * PI / len * (inv ? -1 : 1);
		Complex wlen(cos(ang), sin(ang));
		for(int i = 0; i < n; i += len) {
			Complex w(1, 0);
			for(int j = 0; j < len / 2; j++) {
				Complex u = a[i+j], v = a[i+j+len/2] * w;
				a[i+j] = u + v;
				a[i+j+len/2] = u - v;
				w = w * wlen;
			}
		}
	}
	if(inv) for(Complex &x : a) x.x /= n;
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
		fft(P, 0);
		fft(Q, 0);
		for(int i=0; i<d; i++) P[i] = P[i] * Q[i];
		fft(P, 1);
		cout << ((ll) (P[0].x + 0.5));
		for(int i=1; i<=n+m; i++) cout << " " << ((ll) (P[i].x + 0.5));
		if(TC) cout << '\n';
	}
	return 0;
}