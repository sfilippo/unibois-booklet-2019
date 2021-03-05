// Chinese remainder theorem

/* Call gcrt(a, b) to find smallest {x, y} such
  that (x + k * y) % a[i] = b[i] for all i, k */

#define rep(i,a,b) for (__typeof(a) i=(a); i<(b); ++i)

#define iter(it,c) for (__typeof((c).begin()) \
  it = (c).begin(); it != (c).end(); ++it)

ll egcd(ll a, ll b, ll& x, ll& y) {
  if (b == 0) { x = 1; y = 0; return a; }
  ll d = egcd(b, a % b, x, y);
  x -= a / b * y; swap(x, y); return d; }

template <class T> int size(const T &x) { return x.size(); }
template <class T> T smod(T a, T b) { return (a % b + b) % b; }

ll crt(vector<ll> &as, vector<ll> &ns) {
  ll cnt = size(as), N = 1, x = 0, r, s, l;
  rep(i,0,cnt) N *= ns[i];
  rep(i,0,cnt) egcd(ns[i], l = N/ns[i], r, s), x += as[i]*s*l;
  return smod(x, N); }

pair<ll,ll> gcrt(vector<ll> &as, vector<ll> &ns) {
  map<ll,pair<ll,ll> > ms;
  rep(at,0,size(as)) {
    ll n = ns[at];
    for (ll i = 2; i*i <= n; i = i == 2 ? 3 : i + 2) {
      ll cur = 1;
      while (n % i == 0) n /= i, cur *= i;
      if (cur > 1 && cur > ms[i].first)
        ms[i] = make_pair(cur, as[at] % cur); }
    if (n > 1 && n > ms[n].first)
      ms[n] = make_pair(n, as[at] % n); }
  vector<ll> as2, ns2; ll n = 1;
  iter(it,ms) {
    as2.push_back(it->second.second);
    ns2.push_back(it->second.first);
    n *= it->second.first; }
  ll x = crt(as2,ns2);
  rep(i,0,size(as)) if (smod(x,ns[i]) != smod(as[i],ns[i]))
      return pii(0,0);
  return make_pair(x,n); }
