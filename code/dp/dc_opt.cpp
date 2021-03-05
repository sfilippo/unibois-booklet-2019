/*
  Divide and Conquer DP Optimization
  Sadly, no implementation examples
  Recurrence: 
   dp[i][j] = min[k < j]{dp[i-1][k] + C[k][j]}
  From O(n^2k) to O(nklogn)
  Conditions:
    opt[i][j] <= opt[i][j+1],
    where opt[i][j] is smallest optimal k for dp[i][j]
  What to do:
    we compute all dp[i] in [i][l, r] knowing that
    opt value is in k between [optL, optR]
  solve(i, l, r, optL, optR) = 
    check l == r
    m = (l+r) / 2;
    dp(i, m)
    opt(i, m)
    // costs optR - optL
    // use newly found opt to solve the problem
    solve(i, l, m-1, optL, opt[i][m])
    solve(i, m+1, r, opt[i][m], optR)
*/