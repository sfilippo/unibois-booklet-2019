long long cross(P a, P b, P c){
	return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x);
}
long long dist2(P a, P b){
	return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}
vector<P> graham_scan(vector<P>& a){
	sort(a.begin()+1,a.end(),
	[&](P b, P c){
		if(cross(a[0],b,c)==0)
			return dist2(a[0],b)<dist2(a[0],c);
		return cross(a[0],b,c)>0;	
	});
	vector<P> ch;
	ch.push_back(a[0]);
	ch.push_back(a[1]);
	for(auto &p:a){
		while(ch.size()>=2 && cross(ch[ch.size()-2],ch.back(),p)<=0)
			ch.pop_back();
		ch.push_back(p);
	}
	return ch;
}

