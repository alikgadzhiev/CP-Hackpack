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

long long mod = 998244353;

vector<int> find_scc(int n, int m, vector<vector<int>> to, vector<vector<int>> from){
    vector<bool> was(n, false);
    vector<int> order;
    function<void(int)> dfs1 = [&](int u){
        was[u] = true;
        for(int v : from[u]){
            if(was[v])
                continue;
            dfs1(v);
        }
        order.push_back(u);
    };
    for(int i = 0; i < n; i++){
        if(!was[i])
            dfs1(i);
    }
    reverse(order.begin(), order.end());
    vector<int> c(n, -1);
    function<void(int)> dfs2 = [&](int u){
        for(int v : to[u]){
            if(c[v] == -1){
                c[v] = c[u];
                dfs2(v);
            }
        }
    };
    int cnt = 0;
    for(int i = 0; i < n; i++){
        int v = order[i];
        if(c[v] != -1)
            continue;
        c[v] = ++cnt;
        dfs2(v);
    }
    return c;
}

void solve(){
    int n, m;
    cin >> n >> m;
    vector<vector<int>> to(n), from(n);
    for(int i = 0; i < n; i++){
        int u, v;
        cin >> u >> v;
        u--, v--;
        to[v].push_back(u);
        from[u].push_back(v);
    }
    cout << find_scc(n, m, to, from) << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solve();
}
