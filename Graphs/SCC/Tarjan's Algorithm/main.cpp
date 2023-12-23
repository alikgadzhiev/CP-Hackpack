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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    for(int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
    }
    int time = 0;
    vector<int> disc(n, -1), low(n, -1), comp(n, -1);
    vector<bool> in_stack(n, false);
    stack<int> st;
    vector<vector<int>> scc;
    function<void(int)> tarjan = [&](int u){
        low[u] = time;
        disc[u] = time;
        time++;

        in_stack[u] = true;
        st.push(u);

        for(int v : adj[u]){
            if(disc[v] == -1){
                tarjan(v);
                low[u] = min(low[u], low[v]);
            } else if(in_stack[v] == true){
                low[u] = min(low[u], disc[v]);
            }
        }

        if(low[u] == disc[u]){
            scc.push_back(vector<int>());
            while(st.top() != u){
                scc[scc.size() - 1].push_back(st.top());
                in_stack[st.top()] = false;
                st.pop();
            }

            scc[scc.size() - 1].push_back(u);
            in_stack[u] = false;
            st.pop();
        }
    };

    for(int i = 0; i < n; i++){
        if(disc[i] == -1)
            tarjan(i);
    }

    int sz = (int) scc.size();
    for(int i = 0; i < sz; i++){
        for(int j = 0; j < (int) scc[i].size(); j++){
            cout << scc[i][j] + 1 << " ";
        }
        cout << '\n';
    }
}
