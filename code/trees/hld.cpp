vector<int> g[MN]; //graph
vector<int> parent(n),hldpos(n),chain(n),chain_d(n),dim(n);
//computes subtree dimensions, stores parent of each node
void hlddffs0(int p){
    dim[p]=1;
    for(auto i:g[p]){
        if(i!=parent[p]){
            parent[i]=p;
            dfs1(i);
            dim[p]+=dim[i];
        }
    }
}
//heavy light decomhldposition
void hlddfs1(int p, int chain_id, int cd){
    hldpos[p]=cnt++; //hldposition in base array for rt queries
    chain[p]=chain_id; // highest node in chain
    chain_d[p]=cd; // chain depth
    int hldson=-1;
    for(auto i:g[p])if(i!=parent[p]&&(hldson==-1||dim[i]>dim[hldson]))hldson=i;
    if(hldson!=-1){ //not a leaf node
        buildhld(hldson,chain_id,cd); //heavy child
        for(auto i:G[p]){
            if(i!=parent[p] && i!=hldson[p]) //light edge
                buildhld(i,i,cd+1);
        }
    }
}
parent[0]=-1;
hlddfs0(0);
hlddfs1(0,0,0);
// build ds with new indeces (in hldpos)
int query(int x, int y){
    int ans=0;
    if(chain_d[chain[x]]>chain_d[chain[y]])
        swap(x,y);
    for(int dif = chain_d[chain[y]]-chain_d[chain[x]]; dif; --dif){
        ans=max(ans,rmq(hldpos[chain[y]],hldpos[y]);
        y=chain[y]; y=parent[y];
    }
    while(chain[x]!=chain[y]){
        ans=max(ans,rmq(hldpos[chain[y]],hldpos[y]);
        y=chain[y]; y=parent[y];
        ans=max(ans,rmq(hldpos[chain[x]],hldpos[x]);
        x=chain[x]; x=parent[x];
    }
    if(hldpos[x]<hldpos[y])
        ans=max(ans,rmq(hldpos[x],hldpos[y]);
    else
        ans=max(ans,rmq(hldpos[y],hldpos[x]);
    return ans;
}

