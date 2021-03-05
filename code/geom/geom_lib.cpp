//Blaise1 geometry lib, in its shrinked version

using T = long double; T EPS = 1e-12; T INF = 1e18;
struct point {
  T x, y;
  point(T x, T y) : x(x), y(y) { }
  bool operator==(point &o) { return (fabs(x-o.x)<=EPS) ? 
    ((fabs(y-o.y)<=EPS) ? true : false) : false; }
  bool operator!=(point &o) { return !(*this == o); }
  point operator+(point &o) { return {x+o.x,y+o.y}; }
  point operator-() { return {-x,-y}; }
  point operator-(point &o) { return *this+(-o); }
  point operator*(T &d) { return {x*d,y*d}; }
  point operator*(point &o) { return {x*o.x,y*o.y}; }
  T operator%(point &o) { return (*this*o).magnitude(); }
  T operator^(point &o) { return x*o.y-y*o.x; }
  T distance(point &o) {
    return hypotl(fabs(x - o.x), fabs(y - o.y)); }
  T sq_distance(point &o) {
    return fabs(x-o.x)*fabs(x-o.x) +fabs(y-o.y)*fabs(y-o.y); }
  point normalized() {
    point tmp(x, y); tmp.normalize(); return tmp; }
  void normalize(){ T hy = hypotl(x, y); x /= hy; y /= hy; }
  T magnitude() { return x + y; }
  point rotated_rad(T rad) {
    point tmp(x, y); tmp.rotate_rad(rad); return tmp; }
  void rotate_rad(T rad){
    T cos = cosl(rad); T sin = sinl(rad);
    cos = fabs(cos) < EPS ? 0 : cos;
    sin = fabs(sin) < EPS ? 0 : sin;
    x = x * cos - y * sin; y = x * sin + y * cos; }
  T angle(point& o) {
    point self = this->normalized();
    point oth = o.normalized();
    if(self == oth) return 0;
    return fabs(acosl(self % oth)); } };

struct line {
  point dir, perp;
  T a,b,c;
  line(T a, T b, T c) : perp(a,b), dir(0,0) {
    assert(!(a == 0 && b == 0));
    perp.normalize(); dir = perp.rotated_rad(-M_PI/2);
    this->c = c / hypotl(a,b);
    this->a = perp.x; this->b = perp.y; }
  line(point p1, point p2) : perp(0,0), dir(p2-p1) {
    assert(p1 != p2);
    dir.normalize(); perp = dir.rotated_rad(M_PI/2);
    a = perp.x; b = perp.y; c = -(perp % p1); }
  bool inLine(point &p) {
    return fabs(dir.x * p.x + dir.y * p.y + c) <= EPS; }
  bool operator==(line &o) {
    if(fabs(a - o.a) > EPS) return false;
    line inv(-o.a,-o.b,-o.c);
    return fabs(a-inv.a)<=EPS && fabs(b-inv.b)<=EPS &&
      fabs(c-inv.c)<=EPS; }
  T signed_distance(point &p) { return perp % p + c; }
  point project(point &p) {
    return p - (perp * signed_distance(p)); }
  line parallel(point &p) {
    line res = *this; res.c -= signed_distance(p);
    return res; }
  point intersect(line &s) {
    line l = *this; T d = l.a * s.b - s.a * l.b;
    if(fabs(d) <= EPS) return {-INF, -INF};
    return { (s.c*l.b-l.c*s.b)/d,(s.c*l.a-l.c*s.a)/(-d)}; } };
struct segment {
  point start, end;
  segment(point p1, point p2) : start(p1), end(p2) { }
  bool lies(point &a) {
    point b = start; point c = end; line l(b,c);
    T dist = l.signed_distance(a);
    if(!(fabs(dist) <= EPS)) return false;
    point ba = a-b; point bc = c-b;
    point ca = a-c; point cb = b-c;
    return !(ba % bc < 0 || ca % cb < 0); }
  point intersect(segment &s2) {
    segment s1 = *this; line l1(s1.start, s1.end);
    line l2(s2.start, s2.end);
    point inter = l1.intersect(l2); point inf(-INF, -INF);
    if(inter == inf){
      if(l1 == l2){
        if(s1.lies(s2.start)) return s2.start;
        if(s1.lies(s2.end)) return s2.end;
        if(s2.lies(s1.start)) return s1.start;
        if(s2.lies(s1.end)) return s1.end; }
      return inf; }
    if(s1.lies(inter) && s2.lies(inter)) return inter;
    return inf; }
  T sq_distance(point &p) {
    point v(p.x - start.x, p.y - start.y);
    point u(end.x - start.x, end.y - start.y);
    T dot = v % u; T len = (u * u).magnitude();
    if(fabs(len) <= EPS) return p.sq_distance(start);
    T ratio = dot / len;
    if(ratio <= EPS) return p.sq_distance(start);
    if(ratio >= 1 - EPS) return p.sq_distance(end);
    point proj = (u * ratio) + start;
    return p.sq_distance(proj); }
  T distance(point &p) { return sqrtl(sq_distance(p)); } };