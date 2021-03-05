// Return the closest pair of points in O(NlogN)
using point = complex;
struct cmpx {
  bool operator ()(const point &a, const point &b) {
    return abs(real(a) - real(b)) > EPS ?
      real(a) < real(b) : imag(a) < imag(b); } };

struct cmpy {
  bool operator ()(const point &a, const point &b) {
  return abs(imag(a) - imag(b)) > EPS ?
      imag(a) < imag(b) : real(a) < real(b); } };

pair<point, point> closest_pair(vector<point> pts) {
  pair<point, point> sol;
  sort(pts.begin(), pts.end(), cmpx());
  set<point, cmpy> cur;
  set<point, cmpy>::const_iterator it, jt;
  double mn = INFINITY;
  for (int i = 0, l = 0; i < size(pts); i++) {
    while (real(pts[i]) - real(pts[l]) > mn)
      cur.erase(pts[l++]);
    it = cur.lower_bound(point(-INFINITY, imag(pts[i]) - mn));
    jt = cur.upper_bound(point(INFINITY, imag(pts[i]) + mn));
    while (it != jt) {
      double x = abs(*it - pts[i]);
      if(x < mn){
        mn = x;
        sol = {*it, pts[i]};
      }
      it++;
    cur.insert(pts[i]); }
  return sol; }