// LCA with binary lifting
// just add node with pointer to father
// be careful as memory is MAXN * MAXJ
// MAXJ should be >= log2(N)
const int MAXN = 1e5;
const int MAXJ = 20;
struct node {
  node *p, *jmp[MAXJ];
  int depth;
  node(node *_p = NULL) : p(_p) {
    depth = p ? 1 + p->depth : 0;
    memset(jmp, 0, sizeof(jmp));
    jmp[0] = p;
    for (int i = 1; (1<<i) <= depth; i++)
      jmp[i] = jmp[i-1]->jmp[i-1]; } };
node* st[MAXN];
node* lca(node *a, node *b) {
  if (!a || !b) return NULL;
  if (a->depth < b->depth) swap(a,b);
  for (int j = 19; j >= 0; j--)
    while (a->depth - (1<<j) >= b->depth) a = a->jmp[j];
  if (a == b) return a;
  for (int j = 19; j >= 0; j--)
    while (a->depth >= (1<<j) && a->jmp[j] != b->jmp[j])
      a = a->jmp[j], b = b->jmp[j];
  return a->p; }