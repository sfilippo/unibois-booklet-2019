// (untested) O(ElogV) Dijkstra with priority queue
// takes a vector<vector<pii>> and return vector of
// distances. watchout for int overflow
vi dijkstra(graph &g, int source){
  vi dist(g.size(), INF);
  priority_queue<pii, vector<pii>, greater<pii>> pq;
  dist[source] = 0;
  pq.push({0, source});
  while(!pq.empty()){
    pii curr = pq.top(); pq.pop();
    if(dist[curr].second < curr.first)
      continue;
    for(pii &e : g[curr.second])
      if(curr.first + e.second < dist[e.first]){
        dist[e.first] = curr.first + e.second;
        pq.push({dist[e.first], e.first});
      }
  }
  return dist;
}