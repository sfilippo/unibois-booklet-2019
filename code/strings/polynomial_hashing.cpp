pair<ll,ll> diofante(ll a, ll b){
	if(!a)return {0,1};
	auto t = diofante(b%a,a);
	return {t.second-(b/a)*t.first,t.first};
}
ll modinv(ll x, ll m){
	return (diofante(x,m).first%m+m)%m;
}
template<class T, ll a, ll mod> //use int sized stuff, does not handle overflow over 64 bit
struct prefix_hash{
	int n;
	vector<ll> a_inv;
	vector<ll> psum;
	prefix_hash(T& arr, int n):n(n),a_inv(n),psum(n+1){
		a_inv[0]=1;
		a_inv[1]=modinv(a,mod);
		for(int i=2; i<n; ++i){
			a_inv[i]=(a_inv[1]*a_inv[i-1])%mod;
		}
		psum[n]=0;
		psum[n-1]=arr[n-1];
		ll powa=a;
		for(int i=n-2; i>=0; --i){
			psum[i]=(psum[i+1]+powa*arr[i]%mod)%mod;
			powa=(powa*a)%mod;
		}
	}
	ll operator()(int l, int r){ // returns hash of range [l,r]
		return (((psum[l]-psum[r+1]+mod)%mod)*a_inv[n-r-1])%mod;
	}
};

