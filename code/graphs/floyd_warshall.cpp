// O(N^3) Floyd Warshall to find APSP
// Takes adj matrix (a[i][j] = INF means no edge!)
// Return dist matrix. careful for overflows!

vvi floyd_warshall(vvi &adj){
  vvi d(adj);
  int n = adj.size();
  for(int k = 0; k < n; k++)
    for(int i = 0; i < n; i++)
      for(int j = 0; j < n; j++)
        if(max(d[i][k], d[k][j]) != INF)
          d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
  return d;
}