/* Centroid decomposition, O(NlogN) memory/time
  Given a 0-rooted tree, build a tree of height logN
  then process it in order to answer A to B (path) queries
  Can also be used in other situations
*/
struct centroid_decomposition{
  vvi &g, c;
  vi size;
  vi parent;
  int n, root;
  vvi memo;
  int height;
  vector<char> level;
  int dfs(int i){
    size[i] = 1;
    for(int x : g[i])
      dfs(x), size[i] += size[x];
    return size[i];
  }
  bool is_centroid(int i, int r){
    for(int x : g[i])
      if(size[x] > size[r]/2)
        return 0;
    return 1; }
  int prefered(int i){
    if(g[i].size() == 0)
      return i;
    int x = g[i].front();
    for(int e : g[i])
      if(size[e] > size[x])
        x = e;
    return x; }
  int centroidify(int i, int p){
    int curr = i;
    vi path;
    while(!is_centroid(curr, i)){
      path.push_back(curr);
      curr = prefered(curr);
    }
    for(int p : path)
      size[p] -= size[curr];
    size[curr] = 0;
    parent[curr] = p;
    if(i != curr)
      c[curr].push_back(centroidify(i, curr));
    for(int x : g[curr]) if(size[x])
      c[curr].push_back(centroidify(x, curr));
    return curr; }
  // i think this should be done in centroidify
  void level_dfs(int i){
    for(int x : c[i]){
      level[x] = level[i]+1;
      level_dfs(x);
    } }

  /* IMPORTANT:
    if you need to answer query,
    you can just precompute PATHS
    from/to each centroid to all his
    childs. Then you can answer A->B queries using
    LCA and this precomputed paths */

  void decompose(){
    dfs(0);
    int root = centroidify(0, -1);
    level[root] = 0;
    level_dfs(root);
    height = *max_element(level.begin(), level.end()) + 1;
    fill(size.begin(), size.end() , 1);
  }
  centroid_decomposition(vvi &source) : g(source), n(source.size()),
    c(source.size()), size(source.size()), level(source.size()),
    parent(source.size()) {
    decompose();
  }
};