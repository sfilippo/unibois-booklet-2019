// Convex Hull with Andrew Monotone chain algorithm
// Also supports queries to check if point
// is contained in convex hull

struct point {
  int x, y;
  bool operator ==(point &other){
    return x == other.x && y == other.y;
  }
  bool operator<(point &other){
    return tie(x, y) < tie(other.x, other.y);
  }
};

// -1 ccw, 0 coll, 1 cw
int orientation(point &a, point &b, point &c){
  ll val = (b.y - a.y) * (ll)(c.x - b.x) -
      (b.x - a.x) * (ll)(c.y - b.y);
  return val < 0 ? -1 : !!val;
}

struct segment {
  point a, b;
  bool contains(point &p){
    if(orientation(a, b, p) != 0)
      return 0;
    bool x = p.x >= a.x && p.x <= b.x;
    bool y = p.y >= min(a.y, b.y) && p.y <= max(a.y, b.y);
    return x && y;
  }
  bool operator& (segment &s){
    return intersect(s);
  }
  bool intersect(segment &s){
    ll o1 = orientation(a, b, s.a);
    ll o2 = orientation(a, b, s.b);
    ll o3 = orientation(s.a, s.b, a);
    ll o4 = orientation(s.a, s.b, b);
    if(o1 != o2 && o3 != o4) return 1;
    return contains(s.a) || contains(s.b) ||
      s.contains(a) || s.contains(b);
  }
  segment(point p1, point p2) : a(p1), b(p2){
    if(a.x > b.x)
      swap(a, b);
  }
};
struct convex_hull : vector<point>{
  vector<point> &h = *this;
  vector<segment> bottom, top;
  convex_hull (vector<point> &v){
    sort(v.begin(), v.end());
    for(int i = 0; i < v.size(); i++){
      while(h.size() >= 2 &&
        orientation(h[h.size()-2], h.back(), v[i]) <= 0)
        h.pop_back();
      h.push_back(v[i]);
    }
    int s = h.size() + 1, tops = h.size();
    for(int i = v.size() - 2; i >= 0; i--){
      while(h.size() >= s &&
        orientation(h[h.size()-2], h.back(), v[i]) <= 0)
        h.pop_back();
      h.push_back(v[i]);
    }
    //reminder : we have an extra point!
    // we build top/bottom segments
    top.reserve(tops - 1), bottom.reserve(h.size() - tops + 1);
    for(int i = 0; i + 1 < tops; i++)
      top.push_back(segment(h[i], h[i+1]));
    for(int i = h.size() - 1; i - 1 >= tops - 1; i--)
      bottom.push_back(segment(h[i], h[i-1]));
  }
  //we also count point on the borders
  bool contains(point &p){
    //we create a line to the sky
    segment line(p, {p.x, INF});
    //if p lays in a segment, it's in
    //if line doesn't hit top, it's out
    //if line hits bot, it's out
    //if none occurs, it's in

    //we search top hull
    //we find first segment with b.x >= p.x,
    //so that intersection is there or eventually 
    int l = 0, r = top.size();
    while(l < r){
      int m = (l + r)/2;
      if(top[m].b.x >= p.x)
        r = m;
      else
        l = m +1;
    }
    if(r == top.size()) return 0;
    segment &t = top[l];
    if(t.contains(p)) return 1;
    if(!t.intersect(line)) return 0;
    //we repeat for bottom 
    l = 0, r = bottom.size();
    while(l < r){
      int m = (l + r)/2;
      if(bottom[m].b.x >= p.x) r = m;
      else l = m+1;
    }
    //see above
    if(r == bottom.size()) return 0;
    segment &b = bottom[l];
    if(b.contains(p)) return 1;
    if(b.intersect(line)) return 0;
    //only 1 intersection so it's good
    return 1;
  }
};