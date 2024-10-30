struct Kuhn { // O(n*m)
    vector<vector<int>> adj;
    vector<int> mt;
    vector<bool> used;

    Kuhn(int n, int k) { // n, k - size of 1st and 2nd half respectively
        adj.resize(n, {});
        mt.resize(k, -1);
        used.resize(n, false);
    }

    void add_edge(int u, int v) {
        adj[u].push_back(v);
    }

    bool work(int u) { // is there an augmenting path
        fill(all(used), false);
        auto dfs = [&](auto &self, int u) -> bool {
            if(used[u]) return false;
            used[u] = true;
            for(int v : adj[u]) {
                if(mt[v] == -1 || self(self, mt[v])) {
                    mt[v] = u;
                    return true;
                }
            }
            return false;
        };
        return dfs(dfs, u);
    }
};
