// adj[u][j] - (v, i) where {u, v} is the edge and i is the index of the edge
vector<int> euler(const vector<vector<pair<int, int>>> &adj, int m) {
    int n = (int) adj.size();
    vector<int> deg(n);
    for(int i = 0; i < n; i++)
        deg[i] = (int) adj[i].size();
 
    int src = 0;
    while(src < n && deg[src] % 2 == 0) src++;
    if(src == n) {
        src = 0;
        while(src < n && !deg[src]) src++;
        if(src == n) return {};
    }
 
    int odd = 0;
    for(int i = 0; i < n; i++) odd += (deg[i] & 1);
    if(odd > 2) return {};
 
    vector<int> cur(n), ans;
    vector<bool> vis(m, false);
    auto dfs = [&](this auto &&self, int x) -> void {
        for (int &j = cur[x]; j < adj[x].size(); j++) {
            auto [y, i] = adj[x][j];
            if (!vis[i]) {
                vis[i] = true;
                self(y);
                ans.push_back(i);
            }
        }
    };
    dfs(src);
 
    return ans;
}
