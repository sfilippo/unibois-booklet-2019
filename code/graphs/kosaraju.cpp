// O(N) algo to find SCC

void dfs_order(vvi &g, int i, vec<bool> &vis, vi &dfso){
  vis[i] = 1;
  for(int &p : g[i])
    if(!vis[p])
      dfs_order(g, p, vis, dfso);
  dfso.push_back(i);
}

void l_dfs(vvi &g, int i, vec<bool> &vis, vi &labels, int &l){
  if(!vis[i]){
    vis[i] = 1;
    ++l;
  }
  labels[i] = l;
  for(int &x : g[i])
    if(!vis[x]){
      vis[x] = 1;
    l_dfs(g, x, vis, labels, l);
  }
}

// Returns a graph (DAG) of SCC
// g is the graph to build on
// labels[i] = SCC to which g[i] belongs
// dfs = order in which nodes were visited in the first

vvi kosaraju(vvi &g, vi &labels, vi &dfso){
  //we make a stack based on dfs order (in a way that no node is\
    before someone reachable by him - except for SCC case!
  dfso.reserve(g.size());
  vec<bool> vis(g.size());
  for(int i = 0; i < g.size(); i++)
    if(!vis[i])
      dfs_order(g, i, vis, dfso);
  //we need the reverse graph
  vvi rg(g.size());
  for(int i = 0; i < g.size(); i++)
    for(int &p : g[i])
      rg[p].push_back(i);
  //now, we just go backwards from last node visited and build the scc
  fill(vis.begin(), vis.end(), 0);
  int l = -1;
  for(int i = g.size() - 1; i >= 0; i--)
    if(!vis[dfso[i]])
      l_dfs(rg, dfso[i], vis, labels, l);
  //labels are set, we construct the graph
  vvi scc(l+1);//l started as -1, so we add 1
  set<pii> edges;
  for(int i = 0; i < g.size(); i++){
    for(int &p : g[i])
      if(labels[i] != labels[p]){
        if(edges.count({labels[i], labels[p]}) == 0){
          scc[labels[i]].push_back(labels[p]);
          edges.insert({labels[i], labels[p]});
        }
      }
  }
  return scc;
}