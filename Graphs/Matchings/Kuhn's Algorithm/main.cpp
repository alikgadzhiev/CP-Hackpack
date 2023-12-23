#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> adj;
vector<int> mt;
vector<bool> used;

bool try_kuhn(int u){// O(n * m)
    if(used[u])
        return false;
    used[u] = true;
    for(int v : adj[u]){
        if(mt[v] == -1 || try_kuhn(mt[v])){
            mt[v] = u;
            return true;
        }
    }
    return false;
}

int main(){
    int n, k, m;
    cin >> n >> k >> m;
    adj.assign(n + k, vector<int>{});
    mt.assign(n + k, -1);
    used.assign(n, false);
    for(int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for(int u = 0; u < n; u++){
        fill(used.begin(), used.end(), false);
        try_kuhn(u);
    }

    for(int u = n; u < n + k; u++)
        if(mt[u] != -1)
            cout << mt[u] + 1 << " " << u + 1 << '\n';
}
