// O(N^3) Hungarian algorithm for the assignment problem
// Min Cost Bipartite Matching
// cost[i][j] = cost to match i with j
// Returns {minCost, match[]},
// where match[i] = who we matched i with

// Use 0-based, n <= m
template <typename T>
pair<T, vi> min_cost_matching(const vector<vector<T>> &cost) { 
	// internally, this will be 1-based,
	// but you must call 0-based !
	const T T_INF = numeric_limits<T>::max() / 2.0;
	int n = cost.size();
	int m = cost[0].size();
	vector<T> u(n + 1);
	vector<T> v(m + 1);
	vector<T> p(m + 1);
	vector<T> way(m + 1);
	for (int i = 1; i <= n; ++i) {
		p[0] = i;
		int j0 = 0;
		vector<T> minv (m + 1, T_INF);
		vector<bool> used (m + 1, false);
		do {
			used[j0] = true;
			int i0 = p[j0],  j1;
			T delta = T_INF;
			for (int j = 1; j <= m; ++j)
				if (!used[j]) {
					int cur = cost[i0-1][j-1] - u[i0] - v[j];
					if (cur < minv[j])
						minv[j] = cur,  way[j] = j0;
					if (minv[j] < delta)
						delta = minv[j],  j1 = j;
				}
			for (int j=0; j<=m; ++j)
				if (used[j])
					u[p[j]] += delta,  v[j] -= delta;
				else
					minv[j] -= delta;
			j0 = j1;
		} while (p[j0] != 0);
		do {
			int j1 = way[j0];
			p[j0] = p[j1];
			j0 = j1;
		} while (j0);
	}
	// returns both cost and matchings
	T sol = -v[0];
	vector<int> mates(n);
	for(int i = 1; i <= m; i++) if(p[i] != 0)
		mates[p[i]-1] = i-1;
	// build matchings
	return {sol, mates};
}