// Sparse Table
// O(NlogN) memory, O(1) RMQ

struct sparse_table { vvi m;
  sparse_table(vi arr) {
    m.push_back(arr);
    for (int k = 0; (1<<(++k)) <= arr.size(); ) {
      m.push_back(vi(arr.size()-(1<<k)+1));
      for(int i = 0; i < arr.size() - (1<<k) + 1; i++)
        m[k][i] = min(m[k-1][i], m[k-1][i+(1<<(k-1))]); } }
  int query(int l, int r) {
    int k = 0; while (1<<(k+1) <= r-l+1) k++;
    return min(m[k][l], m[k][r-(1<<k)+1]); } };