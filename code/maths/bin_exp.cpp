// Binary exponentiation
// in case needed, add % mod whenever
// you see some computations going on
// can be modified into bin_mul easily,
// just replace * with +

ll bin_exp(ll b, ll p){
  if(p == 0) return 1;
  if(p == 1) return b;
  ll ans = 1;
  if(p % 2 == 1){
    ans *= b;
    p--;
  }
  ll x = bin_exp(b, p/2);
  return ans * x * x;
}