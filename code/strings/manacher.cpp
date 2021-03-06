// O(N) algorithm to find longest 
// palindromic substring with center
// in each index
// first[i] = longest ODD size pal. in i
// second[i] = longest EVEN size pal. in i
pair<vi, vi> manacher (string s) {
  vi d1(s.size()), d2(s.size());
  int n = s.size();
  int l = 0, r = -1;
  for (int i = 0; i < n; ++i) {
    int k = (i > r ? 0 : min (d1[l + r - i], r - i)) + 1;
    while (i + k < n && i - k >= 0 && s[i + k] == s[i - k]) ++k;
    d1[i] = k--;
    if (i + k > r)
      l = i - k,  r = i + k;
  }

  l = 0, r = -1;
  for (int i = 0; i < n; ++i) {
    int k = (i > r ? 0 : min (d2[l + r - i + 1 ], r - i + 1)) + 1;
    while (i + k - 1 < n && i - k >= 0 && s[i + k - 1] == s[i - k]) ++k;
    d2[i] = --k;
    if (i + k - 1 > r)
      l = i - k,  r = i + k - 1;
  }
  return {d1, d2};
}