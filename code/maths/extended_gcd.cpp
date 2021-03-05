// Extended GCD

/* Solves diophantine equation
   a*x + b*y = gcd(a, b)
   and return {x, y, gcd(a, b)}
   if ll, might require __i128 */
vector<ll> exgcd (ll a, ll b){
	if(!b) return {1, 0, a};
	auto x = exgcd(b, a % b);
	return {x[1], x[0] - x[1] * (a/b), x[2]};
}
