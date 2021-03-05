vector<int> dfs_low(n),dfs_num(n);
int cnt=0;
void abdfs(int p){
    dfs_low[p]=dfs_num[p]=++cnt;
    for(auto i:g[p]){
        if(!dfs_num[i]){
            if(p==root)rootChildren++;//for if root is articulation point
            dfs_parent[i]=p;
            abdfs(i);
            if(dfs_low[i]>=dfs_num[p]){}//p is articulation point
            if(dfs_low[i]>dfs_num[p]){} //p-i is bridge
            dfs_low[p]=min(dfs_low[p],dfs_low[i]);
        } else if(i!=dfs_parent[p]) dfs_low[p]=min(dfs_low[p],dfs_num[i]);
    }
}

