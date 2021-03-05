// Aho corasick which allows
// to get full automata (go)
// O(N*alfa) memory/time complexity
struct aho{
  const int root = 0;
  vvi go;
  vi parent, ch, suff, super, end;
  int label = 0;
  int size = 1;
  int new_node(char c, int p){
    ch[size] = c;
    parent[size] = p;
    return size++;
  }
  aho(int total) : go(total + 5, vi(26, -1)),
    parent(total + 5, 0), ch(total + 5, -1),
    suff(total + 5, 0), super(total + 5, 0),
    end(total + 5, -1) {}

  void insert(string &s){
    int i = root;
    for(char c : s){
      c -= 'A';
      if(go[i][c] == -1)
        go[i][c] = new_node(c, i);
      i = go[i][c];
    }
    end[i] = label++;
  }
  void build(){
    queue<int> q; q.push(root);
    while(!q.empty()){
      int i = q.front(); q.pop();
      if(i != root){
        if(parent[i] == root)
          suff[i] = root;
        else
          suff[i] = go[suff[parent[i]]][ch[i]];
      }
      for(int c = 0; c < 26; c++){
        if(go[i][c] == -1){
          go[i][c] = i == root ? root : go[suff[i]][c];
        }else q.push(go[i][c]);
      }
      if(i != root) {
        super[i] = end[suff[i]] != -1 ? suff[i] : super[suff[i]];
      }
    }
  }
};