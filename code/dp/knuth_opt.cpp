/*
  Knuth's DP Optimization
  Implementation example
  Recurrence: 
   dp[i][j] = min(i < k < j){{dp[i][k] + dp[k][j]} + C[i][j]}
  From O(n^3) to O(n^2)
  Conditions:
    opt[i][j-1] <= opt[i][j] <= opt[i+1][j],
    where opt[i][j] is smallest optimal k for dp[i][j]
  What to do:
    we solve smaller subproblems first
    then we use the fact that we don't need to try
    all k but that it's enough to try those between
    opt[i][j-1] and opt[i+1][j]
    we magically drop a N in complexity :)
*/
/* input..*/

vi sum(n);
partial_sum(v.begin(), v.end(), sum.begin());

vector<vector<ll>> dp(n, vector<ll>(n));
// smallest index of optimal solution for dp[l, r]
vvi opt(n, vi(n));
for(int s = 1; s <= n; s++){
  for(int l = 0; l + s - 1 < n; l++){
    int r = l + s - 1;
    // base cases
    if(s <= 2){
      dp[l][r] = s == 2 ? sum[r] - (l ? sum[l-1] : 0) : 0;
      opt[l][r] = l;
    } else{
      int low = opt[l][r-1];
      int hi = opt[l+1][r];
      int curr = sum[r] - (l ? sum[l-1] : 0);
      dp[l][r] = LLINF;
      // solution must be in this range as\
        opt[l-1][r] <= opt[l][r] <= opt[l][r+1] 
      for(int m = low; m <= hi; m++){
        ll tmp = curr + dp[l][m] + dp[m+1][r];
        if(tmp < dp[l][r]){
          dp[l][r] = tmp;
          opt[l][r] = m;
        }
      } // dp[l][r] is found
    }
  }
}