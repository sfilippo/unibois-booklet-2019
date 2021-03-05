/* Implicit Treap (BBST)
  can be augmented or used as map/set
  O(logN) expected queries */

// srand(time(0));
struct treap{
private:
  struct node{
    int val;
    int p = rand();
    // int h = 1;
    int size = 1;
    node *l = nullptr;
    node *r = nullptr;
    node (int a){
      val = a;
    }
    void update(){
      // int lh = l != nullptr ? l->h : 0;
      // int rh = r != nullptr ? r->h : 0;
      // h = 1 + max(lh, rh);
      int ls = l != nullptr ? l->size : 0;
      int rs = r != nullptr ? r->size : 0;
      size = 1 + ls + rs;
    }
  };
  node *merge(node *a, node *b){
    if(a == nullptr) return b;
    if(b == nullptr) return a;
    if(a->p < b->p){
      a->r = merge(a->r, b);
      a->update();
      return a;
    } else{
      b->l = merge(a, b->l);
      b->update();
      return b;
    }
  }
  int pos(node *a){
    if(a->l == nullptr) return 0;
    return a->l->size;
  }
  pair<node*, node*> split(node *a, int k){
    if(a == nullptr) return {nullptr, nullptr};
    int p = pos(a);
    // if a->key < k
    if(p < k){
      auto x = split(a->r, k - (p + 1));
      a->r = x.first;
      a->update();
      return {a, x.second};
    } else{
      auto x = split(a->l, k);
      a->l = x.second;
      a->update();
      return {x.first, a};
    }
  }
  node *insert(node* a, int index, int val){
    auto x = split(a, index);
    return merge(x.first, merge(new node(val), x.second));
  }
  node *erase(node *a, int k){
    if(a == nullptr) return nullptr;
    int p = pos(a);
    // if a->key == k
    if(p == k){
      node* ans = merge(a->l, a->r);
      free(a);
      return ans;
    }
    if(k < p)
      a->l = erase(a->l, k);
    else
      a->r = erase(a->r, k - (p + 1));
    a->update();
    return a;
  }
  //0-based
  int get_kth(node *a, int k){
    int p = pos(a);
    if(p == k)
      return a->val;
    if(k < p)
      return get_kth(a->l, k);
    else
      return get_kth(a->r, k - (p + 1));
  }
  node *root = nullptr;
public:
  void insert(int i, int val){
    root = insert(root, i, val);
  }
  void erase(int k){
    root = erase(root, k);
  }
  // int height(){
  //  return root != nullptr ? root->h : 0;
  // }
  int operator[](int i){
    return get_kth(root, i);
  }
};