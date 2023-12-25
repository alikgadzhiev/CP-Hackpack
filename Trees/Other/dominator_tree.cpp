#include "bits/stdc++.h"

using namespace std;

template<typename T>
istream &operator>>(istream &is, vector<T> &v) {
    for (auto &i: v) is >> i;
    return is;
}

template<typename T>
ostream &operator<<(ostream &os, vector<T> v) {
    for (auto &i: v) os << i << ' ';
    return os;
}

struct TreeAncestor{
    vector<vector<int>> up;
    vector<int> depth;
    const int LOG = 20;
public:
    TreeAncestor(int n, vector<vector<int>> adj){
        up = vector<vector<int>> (n, vector<int>(LOG));
        depth = vector<int> (n);

        function<void(int, int)> dfs = [&](int u, int pre){
            for(int v : adj[u]){
                if(v == pre)
                    continue;
                up[v][0] = u;
                depth[v] = depth[u] + 1;
                for(int j = 1; j < LOG; j++)
                    up[v][j] = up[up[v][j - 1]][j - 1];
                dfs(v, u);
            }
        };

        dfs(0, -1);
    }

    int getKthAncestor(int node, int k){
        if(depth[node] < k){
            return -1;
        }
        for(int j = LOG - 1; j >= 0; j--){
            if(k & (1 << j))
                node = up[node][j];
        }
        return node;
    }

    int getLCA(int a, int b){
        if(depth[a] < depth[b]) {
            swap(a, b);
        }
        a = getKthAncestor(a, depth[a] - depth[b]);
        if(a == b) {
            return a;
        }
        for(int j = LOG - 1; j >= 0; j--) {
            if(up[a][j] != up[b][j]){
                a = up[a][j];
                b = up[b][j];
            }
        }
        return up[a][0];
    }
};

vector<int> topological_sort(const vector<vector<int>> &adj) {
    int n = int(adj.size());
    vector<int> in_degree(n, 0);
    vector<int> order;

    for (int i = 0; i < n; i++)
        for (int neighbor : adj[i])
            in_degree[neighbor]++;

    for (int i = 0; i < n; i++)
        if (in_degree[i] == 0)
            order.push_back(i);

    int current = 0;

    while (current < int(order.size())) {
        int node = order[current++];

        for (int neighbor : adj[node])
            if (--in_degree[neighbor] == 0)
                order.push_back(neighbor);
    }

    return order;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n);
    vector<vector<int>> in(n);
    for(int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        in[v].push_back(u);
    }

    cout << '\n';

    TreeAncestor lca(n, adj);
    vector<vector<int>> dom(n);
    vector<int> par_dom(n);
    vector<int> order = topological_sort(adj);

    for(int i = 0; i < n; i++){
        int u = order[i];
        int sz = (int) in[u].size();

        if(sz <= 1) {
            par_dom[u] = u;
            if(sz == 1){
                dom[in[u].front()].push_back(u);
            }
            continue;
        }

        int cur_lca = par_dom[in[u].front()];
        for(int j = 1; j < (int) in[u].size(); j++){
            cur_lca = lca.getLCA(cur_lca, par_dom[in[u][j]])
        }
        dom[cur_lca].push_back(u);
        par_dom[u] = cur_lca;
    }

    for(int u = 0; u < n; u++){
        for(int v : dom[u])
            cout << u + 1 << " " << v + 1 << '\n';
    }
}
