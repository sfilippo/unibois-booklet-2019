// Queue with get_max() in O(1)

struct maxqueue{
  deque<pair<ll,int>> q;
  int l = 0, r = 0;
  int size(){ return r - l; }
  void push(ll val){
    while(q.size() && q.back().first <= val)
      q.pop_back();
    q.push_back({val, r++}); }
  void pop(){
    if(q.front().second == l)
      q.pop_front();
    l++; }
  ll get_max(){
    if(!size()) return -1;
    return q.front().first;}
};