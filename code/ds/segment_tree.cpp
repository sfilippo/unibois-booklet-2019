/* SegmentTree for Range Sum Queries
  and lazy propagation
  O(N) mermory, O(logN) queries */

struct segtree {
  vector<int> v, u;
  int n;
  const int NULL_VALUE = 0;
  segtree(int num) {
    v.resize((1 << (int)(ceil(log2(num))+1))-1, NULL_VALUE);
    u.resize(v.size(), NULL_VALUE);
    n = v.size() / 2;
  }
  segtree(vector<int> &source) : segtree(source.size()) {
    for (int i = 0; i < source.size(); i++)
      v[i + n] = source[i];
    for (int i = n - 1; i >= 0; i--)
      updateNode(i);
  }
  int left(int i) { return i*2+1; }
  int right(int i) { return i*2+2; }
  int parent(int i) { return (i - 1) / 2; }

  int mergeValues(int v1, int v2) {
    return v1 + v2;
  }

  void updateNode(int i) {
    v[i] = mergeValues(v[left(i)], v[right(i)]);
  }

  void lazyUpdate(int i) {
    if (u[i] != 0) {
      v[i] += u[i];
      if (i < v.size() / 2) {
        u[left(i)] += u[i] / 2;
        u[right(i)] += u[i] / 2; }
      u[i] = 0;
    }
  }
  int rangeQuery(int i, int l, int r, int a, int b) {
    lazyUpdate(i);
    if (l >= a && r <= b)
      return v[i];
    if (r < a || l > b)
      return NULL_VALUE;
    int m = (l + r) / 2;
    return mergeValues(rangeQuery(left(i), l, m, a, b),
      rangeQuery(right(i), m + 1, r, a, b));
  }
  void updateToRoot(int i) {
    updateNode(i);
    if (i != 0) updateToRoot(parent(i)); }
  void rangeAdd(int i, int a, int b, int l, int r, int off) {
    lazyUpdate(i);
    if (l >= a && r <= b) {
      u[i] += off * (r - l + 1);
      lazyUpdate(i);
    } else if (!(r < a || l > b)) {
      int m = (l + r) / 2;
      rangeAdd(left(i), a, b, l , m, off);
      rangeAdd(right(i), a, b, m + 1, r, off);
      updateNode(i);
    }
  }
  int rangeSum(int a, int b) {
    return rangeQuery(0, 0, n, a, b); }
  void update(int index, int value) {
    int i = n + index;
    v[i] = value;
    updateToRoot(parent(i)); }
  void rangeUpdate(int a, int b, int offset) {
    rangeAdd(0, a, b, 0, n, offset); }
};