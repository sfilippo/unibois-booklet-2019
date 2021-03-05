// O(|S| + |T|) string matchin with KMP
// Computes occurences of S in T

// Amortized O(|S|) prefix function
vi pref_func(const string &s){
  vi p(s.size());
  for(int i = 1, match = 0; i < s.size(); i++){
    while(match && s[i] != s[match])
      match = p[match - 1];
    match += s[i] == s[match];
    p[i] = match;
  }
  return move(p);
}
int count_matches(string &s, string &t){
  vi p = pref_func(s);
  int ans = 0, match = 0;
  for(char c : t){
    while(match && c != s[match])
      match = p[match - 1];
    match += c == s[match];
    if(match == s.size()){
      ans++;
      match = p.back();}
  }
  return ans;
}