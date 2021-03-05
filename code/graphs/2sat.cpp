// O(N) algorithm to solve 2SAT

// 1) make a graph of size 2 * N
// 2) add all implications (c1, i1) && (c2, i2)...
// 3) run Kosaraju on the obtained graph
// 4) if label[x] = label[x^1], then we have no solution
// 5) we have a solution. (and then? :O)

// if (x = a) then (y = b) 
void add_implication(int x, bool a, int y, bool b, vvi &sat){
  x *= 2, y *= 2;
  //nego se necessario
  if(!a) x ^= 1;
  if(!b) y ^= 1;
  //aggiunge x -> y
  sat[x].push_back(y);
  //aggiunge !y -> !x
  sat[y ^ 1].push_back(x ^ 1);
}