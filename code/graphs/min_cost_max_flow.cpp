// O(V^3M) (estimated) algorithm for MCMF
// Uses an implementation of Pape-Levit
// for shortest path (better in practice,
// but not as good as Dijkstra asymptotically)
// Hope it's good enough :P

struct edge {
  int b, u;
  ll c, f;
  size_t back;
};

using graph = vector<vector<edge>>;

// a to b, capacity u, cost c
void add_edge (graph &g, int a, int b, ll u, ll c) {
  edge r1 = {b, u, c, 0, g[b].size ()};
  edge r2 = {a, 0, -c, 0, g[a].size ()};
  g[a].push_back (r1);
  g[b].push_back (r2);
}

// graph, source, sink
// returns {flow, cost}
pair<ll, ll> mcmf(graph &g, int s, int t){
  ll flow = 0, cost = 0;
  ll k = MAX_FLOW; // use Dinic :)
  while(flow < k){
    vi id(n), d(n, INF), q(n), p(n);
    vector<size_t> p_edge(n);
    int qh = 0, qt = 0;
    q[qt++] = s;
    d[s] = 0;
    while (qh != qt) {
      int v = q[qh++];
      id[v] = 2;
      if (qh == n) qh = 0;
      for (size_t i = 0; i < g[v].size(); ++i) {
        edge & r = g[v][i];
        if (rf <ru && d[v] + rc < d[rb]) {
          d[rb] = d[v] + rc;
          if (id[rb] == 0) {
            q[qt++] = rb;
            if (qt == n) qt = 0;
          }
          else if (id[rb] == 2) {
            if (--qh == -1) qh = n-1;
            q[qh] = rb;
          }
          id[rb] = 1;
          p[rb] = v;
          p_edge[rb] = i;
        }
      }
    }
    if (d[t] == INF) break;
    ll addflow = k - flow;
    for (int v = t; v! = s; v = p[v]) {
      int pv = p [v]; size_t pr = p_edge[v];
      addflow = min(addflow, g[pv][pr].u - g[pv][pr].f);
    }
    for (int v = t; v! = s; v = p [v]) {
      int pv = p [v];
      size_t pr = p_edge[v], r = g[pv][pr].back;
      g[pv][pr].f += addflow;
      g[v][r].f -= addflow;
      cost += g[pv][pr].c * addflow;
    }
    flow += addflow;
  }
  return {flow, cost};
}
