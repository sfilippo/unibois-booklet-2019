// O(N) Topological sort for DAG
// Returns array v, indexes in topo-sorted order
// (for i < j, v[i] it NOT reachable by v[j])
// Can be used (often reversed) instead of DP
// for DAG problems

vi toposort(vvi &g){
  const int n = g.size();
  vector<bool> vis(n);
  vi topo; topo.reserve(n);
  function<void(int)> dfs = [](int i){
    vis[i] = 1;
    for(int e : g[i]) if(!vis[e]) dfs(e);
      topo.push_back(i);
  };
  for(int i = 0; i < n; i++)
    if(!vis[i])
      dfs(i);
  reverse(topo.begin(), topo.end());
  return topo;
}