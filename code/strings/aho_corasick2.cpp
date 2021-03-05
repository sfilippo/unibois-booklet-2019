// Aho corasick for
// "Count pattern occurencies" queries
// O(N) time/memory complexity
struct node{
  node *parent, *fall, *output;
  char c = '$';
  int ending = -1, taken = 0;
  unordered_map<char, node*> f;
  node(node *p, char c) : parent(p), c(c){}
  node(){}
  vector<node*> rev_out;
};
struct aho_trie{
  node *root = new node();
  int l = 0; 
  void insert(string s){
    node *curr = root;
    for(char c : s)
      curr = curr->f.count(c) ? curr->f[c] : (curr->f[c] = new node(curr, c));
    curr->ending = l++;
  }
  void set_falls(){
    queue<node*> q;
    q.push(root);
    while(!q.empty()){
      node *curr = q.front(); q.pop();
      for(auto &x : curr->f)
        q.push(x.second);
      if(curr == root) continue;
      // compute suffix link
      curr->fall = curr->parent->fall;
      while(curr->fall->f.count(curr->c) == 0 && curr->fall != root)
        curr->fall = curr->fall->fall;
      if(curr->fall != curr->parent && curr->fall->f.count(curr->c))
        curr->fall = curr->fall->f[curr->c];
      curr->output = curr->fall->ending != -1 ? curr->fall : curr->fall->output;
      curr->output->rev_out.push_back(curr);
    }
  }
  vi query(string s){
    node *stato = root;
    for(char c : s){
      while(stato != root && stato->f.count(c) == 0)
        stato = stato->fall;
      if(stato->f.count(c))
        stato = stato->f[c];
      stato->taken++;
    }
    vi ans(l);
    function<int(node*)> dfs = [&](node *i){
      int taken = 0;
      for(auto x : i->rev_out)
        taken += dfs(x);
      taken += i->taken;
      if(i->ending != -1) ans[i->ending] = taken;
      i->taken = 0;
      return taken;
    };
    dfs(root);
    return ans;
  }
  aho_trie(){
    root->parent = root->fall = root->output = root;
  }
};