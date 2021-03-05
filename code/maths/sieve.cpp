// Linear sieve: returns the smallest divisor
// for all numbers in [0, N]
vi divs(int n){
  vi ans(n+1), primes;
  iota(ans.begin(), ans.end(), 0);
  for(int k = 2; k <= n; k++){
    if(ans[k] == k)
      primes.push_back(k);
    for(int p : primes){
      if(p > ans[k]) break;
      if(p * k <= n) ans[p * k] = p;
      else break;
    }
  }
  return move(ans);
}