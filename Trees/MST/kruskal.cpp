#include <bits/stdc++.h>

using namespace std;

class dsu {
public:
    vector<int> p;
    int n;
    vector<int> sz;

    dsu(int _n) : n(_n) {
        p.resize(n);
        iota(p.begin(), p.end(), 0);
        sz.assign(n, 1);
    }

    inline int get(int x) {
        return (x == p[x] ? x : (p[x] = get(p[x])));
    }

    inline bool unite(int x, int y) {
        x = get(x);
        y = get(y);
        if (x != y) {
            p[x] = y;
            sz[y] += sz[x];
            sz[x] = 0;
            return true;
        }
        return false;
    }
};

int main(){
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj;
    for(int i = 0; i < m; i++){
        int u, v, w;
        cin >> u >> v >> w;
        adj.push_back({w, u, v});
    }

    sort(adj.begin(), adj.end());

    dsu dsu(n + 1);
    int sum = 0;
    for(int i = 0; i < m; i++){
        if(dsu.unite(adj[i][1], adj[i][2])){
            sum += adj[i][0];
        }
    }

    cout << sum << '\n';

//  Time complexity - O(m*logm)
//  Because of sorting, it's slower than Prim's algorithm
}
