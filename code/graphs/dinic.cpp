// O(VE^2) Dinic algorithm for MaxFlow
// Diff with Scaling Dinic (asyntotically faster)
// commented above Dinic's code

// We represent the graph as an adiacency list
// of edge list indexes !!!

struct edge{
  int from, to; // the connected nodes
  int f; // the flow we can still push
};

using graph = vvi;
using edge_list = vector<edge>;

// Also, we use i^1 to get back-edge of i-th edge
constexpr int back_edge(int i){ return i ^ 1;}

// Assumes directed edges
const bool IS_DIRECTED = 1;

void add_edge(graph &g, edge_list &e, int a,
    int b, int c, bool directed = IS_DIRECTED){
  int index = e.size();
  g[a].push_back(index);
  g[b].push_back(back_edge(index));
  e.push_back({a, b, c});
  e.push_back({b, a, directed ? 0 : c});
}

// int level_dfs(graph &g, edge_list &el, vi &level,
//   vi &pointer, int source, int sink, int lim){
int level_dfs(graph &g, edge_list &el, vi &level,
    vi &pointer, int source, int sink, int flow = INF){
  // if(source == sink) return lim;
  if(source == sink) return flow;
  for(int &idx = pointer[source]; idx < g[source].size();
      idx++){
    int i = g[source][idx];
    edge &e = el[i];
    // if(level[e.to] == level[source] + 1 && e.f >= lim){
    if(level[e.to] == level[source] + 1 && e.f > 0){
      // int pushed = level_dfs(g, el, level, pointer,
      //   e.to, sink, lim);
      int pushed = level_dfs(g, el, level, pointer,
          e.to, sink, min(flow, e.f));
      if(pushed > 0){
        el[i].f -= pushed;
        el[back_edge(i)].f += pushed;
        return pushed;
      }
    }
  }
  return 0; // couldn't push flow
}

// bool level_bfs(graph &g, edge_list &el, vi &level,
//   int source, int sink, int lim){
bool level_bfs(graph &g, edge_list &el, vi &level,
    int source, int sink){
  fill(level.begin(), level.end(), INF);
  level[source] = 0;
  queue<int> q;
  q.push(source);
  while(!q.empty() && level[sink] == INF){
    int curr = q.front(); q.pop();
    for(int &i : g[curr]){
      edge &e = el[i];
      // if(e.f >= lim && level[e.to] == INF){
      if(e.f > 0 && level[e.to] == INF){
        level[e.to] = level[curr] + 1;
        q.push(e.to);
      }
    }
  }
  return level[sink] != INF;
}

ll dinic(graph &g, edge_list &el, int source, int sink){
  vi level(g.size());
  ll flow = 0;
  // TODO: check for long long
  // int lim = 1<<30;
  // while(lim > 0){
  while(level_bfs(g, el, level, source, sink)){
    // core optimization trick, for chained DFSs
    vi pointer(g.size());
    // if we can't send enough flow
    // if(!level_bfs(g, el, level, source, sink, lim)){
    //   lim /= 2;
    //   continue;
    // }
    // while(level_dfs(g, el, level, pointer, source, sink, lim)){
    //    flow += lim;
    // }
    int tmp;
    while((tmp = level_dfs(g, el, level, pointer, source, sink))){
      flow += tmp;
    }
  }
  return flow;
}