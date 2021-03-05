// FFT, it multiplies two polynomials in O(NlogN) 
// Extremely powerful, but I've no idea how it works
// Call mul and give the polynomials as
// arrays of their coefficients :)

namespace FFT {
  struct complex {
    double a, b;
    complex() { a = b = 0; }
    complex(double _a, double _b) { a = _a; b = _b; }
    complex(double _a) { a = _a; b = 0; }
    complex operator + (complex o) { return complex(a + o.a, b + o.b); }
    complex operator - (complex o) { return complex(a - o.a, b - o.b); }
    complex operator * (complex o) {
      return complex(a * o.a - b * o.b,  a * o.b + b * o.a); }
    void operator *= (complex o) { 
      double na = a * o.a - b * o.b;
      double nb = a * o.b + b * o.a;
      a = na, b = nb;
    }
    void operator /= (double x) { a /= x, b /= x;}
    double real() { return a; }
    double imag() { return b; }
  };
  const int M = 21;
  const int N = (1 << M);
  int pre[N][M];
  int reverse(int num, int lg_n) {
    if(pre[num][lg_n]) return pre[num][lg_n] - 1;
    int res = 0;
    for (int i = 0; i < lg_n; i++) {
      if (num & (1 << i))
        res |= 1 << (lg_n - 1 - i);
    }
    pre[num][lg_n] = res + 1;
    return res;
  }
  void fft(vector<complex> & a, bool invert) {
    int n = a.size();
    int lg_n = 0;
    while ((1 << lg_n) < n) lg_n++;
    for (int i = 0; i < n; i++) {
      if (i < reverse(i, lg_n)) swap(a[i], a[reverse(i, lg_n)]);
    }
    for (int len = 2; len <= n; len <<= 1) {
      double ang = 2 * PI / len * (invert ? -1 : 1);
      complex wlen(cos(ang), sin(ang));
      for (int i = 0; i < n; i += len) {
        complex w(1);
        for (int j = 0; j < len / 2; j++) {
          complex u = a[i+j], v = a[i+j+len/2] * w;
          a[i+j] = u + v;
          a[i+j+len/2] = u - v;
          w *= wlen;
        }
      }
    }
    if (invert) {
      for (complex & x : a) x /= n;
    }
  }
  inline vi mul(vi const& a, vi const& b) {
    vector<complex> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size()) n <<= 1;
    fa.resize(n);
    fb.resize(n);
    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++) fa[i] *= fb[i];
    fft(fa, true);
    vi result(n);
    for (int i = 0; i < n; i++) {
      ll x = fa[i].real() + 0.5;
      result[i] = x;
    }
    while(result.size() && !result[result.size() - 1]) result.pop_back();
    return result;
  }
  inline vi moduloMul(vi const& a, vi const& b, ll MOD) {
    vector<complex> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size()) n <<= 1;
    fa.resize(n); fb.resize(n);
    fft(fa, false); fft(fb, false);
    for (int i = 0; i < n; i++) fa[i] *= fb[i];
    fft(fa, true);
    vi result(n);
    for (int i = 0; i < n; i++) {
      ll x = fa[i].real() + 0.5;
      if(x >= MOD) x %= MOD;
      result[i] = x;
    }
    while(result.size() && !result[result.size() - 1]) result.pop_back();
    return result;
  }
};