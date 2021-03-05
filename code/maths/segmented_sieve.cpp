/* Returns primality for each number
  in range [l, r], given a sieve
  up to sqrt(r), shifted by l 
  O(max(sqrt(r), r - l) * log(r-l)) */

vb seg_sieve(vi &sieve, int l, int r){
  vb prime(r - l + 1);
  for(int i = 2;i<sieve.size();i++){
    if(sieve[i] != i) continue;
    for(int j = i*(l/i); j<=r; j+=i){
      if(j < l) continue;
      int tmp = j;
      while(tmp && tmp % i == 0){
        tmp /= i;
        prime[j - l] = 1;
      }
    }
  }
  return prime;
}