#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <algorithm>
#include <functional>
#include <utility>
#include <bitset>
#include <unordered_set>
#include <cmath>
#include <cstdlib>
#include <random>
#include <ctime>
#include <chrono>
#include <cstdio>

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
/*
  Time complexity - O(n + m)
*/
long long mod = 998244353;

vector<int> ancestor;

class dsu {
public:
    vector<int> p;
    int n;
    vector<long long> sz;

    dsu(int _n) : n(_n) {
        p.resize(n);
        iota(p.begin(), p.end(), 0);
        sz.assign(n, 1);
    }

    inline int get(int x) {
        return (x == p[x] ? x : (p[x] = get(p[x])));
    }

    inline bool unite(int x, int y) {
        int new_ancestor = x; // only for this problem
        x = get(x);
        y = get(y);
        if (x != y) {
            p[x] = y;
            ancestor[y] = new_ancestor;
            sz[y] += sz[x];
            sz[x] = 0;
            return true;
        }
        return false;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin >> n;
    
    ancestor.resize(n);
    vector<vector<int>> adj(n);
    vector<bool> vis(n);
    vector<vector<int>> q(n);
    dsu d(n);
    
    for(int i = 0; i + 1 < n; i++){
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    int m;
    cin >> m;
    for(int i = 1; i <= m; i++){
        int u, v;
        cin >> u >> v;
        u--, v--;
        q[u].push_back(v);
        q[v].push_back(u);
    }
    
    function<void(int)> dfs = [&](int u){
        vis[u] = true; ancestor[u] = u;
        d.p[u] = u;
        for(int v : adj[u]){
            if(!vis[v]){
                dfs(v);
                d.unite(u, v);
            }
        }
        for(int v : q[u]){
            if(vis[v]){
                cout << "The lowest common ancestor of " << u + 1 << " and " << v + 1 << " is "
                << ancestor[d.get(v)] + 1 << '\n';
            }
        }
    };
    
    dfs(0);
}
