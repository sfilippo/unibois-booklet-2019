// Magic formula to know point to line distance
// Very accurate :P

// s.a.x <= s.b.x
double ps_distance(point &p, segment &s){
  //magic dot product / square len ratio
  vector<double> v{p.x - s.a.x, p.y - s.a.y};
  vector<double> u{s.b.x - s.a.x, s.b.y - s.a.y};
  auto dot = v[0] * u[0] + v[1] * u[1];
  auto len = square(u[0]) + square(u[1]);
  if(len == 0) return p.distance(s.a);
  auto ratio = dot / len;
  //cout << dot << ' ' << len << " -> " << ratio << '\n';
  if(ratio <= 0) return p.distance(s.a);
  if(ratio >= 1) return p.distance(s.b);
  point proj = {s.a.x + u[0] * ratio, s.a.y + u[1] * ratio};
  return p.distance(proj);
}