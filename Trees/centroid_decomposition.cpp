struct centroid_decomp {
    int n;
    vector<vector<int>> adj;
    vector<int> sz;
    vector<int> par;
    vector<bool> vis;

    centroid_decomp(int n) {
        this->n = n;
        adj.resize(n, vector<int>());
        sz.resize(n);
        par.resize(n);
        vis.resize(n, false);
    }

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void calc_sz(int u, int p) {
        sz[u] = 1;
        for(int v : adj[u]) {
            if(vis[v] || v == p) continue;
            calc_sz(v, u);
            sz[u] += sz[v];
        }
    }

    int get_centroid(int u, int p, int cn) {
        for(int v : adj[u]) {
            if(vis[v] || v == p) continue;
            if(sz[v] > cn / 2) return get_centroid(v, u, cn);
        }
        return u;
    }

    void work(int u, int p = -1) {
        calc_sz(u, p);

        int c = get_centroid(u, p, sz[u]);
        par[c] = p;
        vis[c] = true;

        for(int v : adj[c]) {
            if(vis[v]) continue;
            work(v, c);
        }
    }
};
