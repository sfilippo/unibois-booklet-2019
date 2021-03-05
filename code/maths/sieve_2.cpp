// Linear sieve variant:\
  also computes euler totient (coprimes <= i),\
  number of distinct divisors,\
  sum of divisors,\
  for all i in [1, N]

struct sieve{
  vi d, s0, fi; // smallest div, number of divs, euler fi
  vector<ll> s1; // sum of divisors
  sieve(int n) : d(n+1), s0(n+1), s1(n+1), fi(n+1){
    // just standard linear sieve
    vi primes;
    fi[1] = 1;
    d[1] = 0; iota(d.begin() + 2, d.end(), 2);
    s0[1] = 1;
    s1[1] = 1;
    for(int k = 2; k <= n; k++){
      if(d[k] == k) primes.push_back(k);
      for(int p : primes){
        if(p > d[k]) break;
        if(p * (ll)k <= n) d[p * k] = p;
        else break;
      }
      // smallest div
      ll p1 = d[k];
      // fi function
      if(d[k/p1] != p1) fi[k] = fi[k/p1] * (p1-1);
      else fi[k] = fi[k/p1] * p1;
      // distinct divisors
      int times = 0;
      for(int i = k / p1; d[i] == p1; i /= p1, times++);
      s0[k] = s0[k / p1] / (times+1) * (times+2);
      // sum of divisors
      ll sum_prev = s1[k / bin_exp(p1, times + 1)];
      s1[k] = s1[k/p1] + sum_prev * bin_exp(p1, times+1);
    }
  }
};