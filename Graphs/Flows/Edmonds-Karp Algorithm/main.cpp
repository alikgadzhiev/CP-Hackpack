#include <bits/stdc++.h>

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

long long mod = 998244353;

int edmonds_karp(vector<vector<int>> g, int s, int t){ // O(V * E^2)
    int n = (int) g.size();
    vector<int> parent(n);

    int max_flow = 0;

    auto bfs = [&](int start, int dest){
        vector<bool> vis(n, false);
        queue<int> q;
        q.push(start);
        vis[start] = true;
        parent[start] = -1;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for(int v = 0; v < n; v++){
                if(!vis[v] && g[u][v] > 0){
                    if(v == dest) {
                        parent[v] = u;
                        return true;
                    }
                    q.push(v);
                    parent[v] = u;
                    vis[v] = true;
                }
            }
        }
        return false;
    };

    while(bfs(s, t)){
        int path_flow = INT_MAX;
        for(int v = t; v != s; v = parent[v]){
            int u = parent[v];
            path_flow = min(path_flow, g[u][v]);
        }
        for(int v = t; v != s; v = parent[v]){
            int u = parent[v];
            g[u][v] -= path_flow;
            g[v][u] += path_flow;
        }
        max_flow += path_flow;
    }

    return max_flow;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n, vector<int>(n, -1));
    for(int i = 0; i < m; i++){
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        g[u][v] = w;
    }
    int s, t;
    cin >> s >> t;
    s--, t--;
    cout << edmonds_karp(g, s, t) << '\n';
}
