#include "bits/stdc++.h"

using namespace std;

void addEdge(int u, int v, vector<set<int>> &adj, vector<int> &deg){
    adj[u].insert(v);
    adj[v].insert(u);
    deg[u]++;
    deg[v]++;
}

void deleteEdge(int u, int v, vector<set<int>> &adj, vector<int> &deg){
    adj[u].erase(v);
    adj[v].erase(u);
    deg[u]--;
    deg[v]--;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<set<int>> adj(n);
    vector<int> deg(n);
    for(int i = 0; i < m; i++){ // O(m*log m)
        int u, v;
        cin >> u >> v;
        u--, v--;
        addEdge(u, v, adj, deg);
    }

    int v1 = -1, v2 = -1;
    int odd = 0;
    for(int i = 0; i < n; i++){ // O(n)
        if(deg[i] % 2 == 0)
            continue;
        odd++;
        if(v1 == -1)
            v1 = i;
        else
            v2 = i;
    }

    if(odd > 2){
        cout << -1 << '\n';
        return 0;
    } else if(v1 != -1){
        addEdge(v1, v2, adj, deg);
    }

    stack<int> st;
    st.push(0);
    vector<int> res;
    while (!st.empty()) { // O(n*log n + m)
        int v = st.top();
        if (!deg[v]) {
            res.push_back(v);
            st.pop();
        } else {
            int u = *adj[v].begin();
            deleteEdge(u, v, adj, deg);
            st.push(u);
        }
    }

    if (v1 != -1) {
        for (int i = 0; i + 1 < (int)res.size(); i++) {
            if ((res[i] == v1 && res[i + 1] == v2) ||
                (res[i] == v2 && res[i + 1] == v1)) {
                vector<int> res2;
                for (int j = i + 1; j < (int)res.size(); ++j)
                    res2.push_back(res[j]);
                for (int j = 1; j <= i; ++j)
                    res2.push_back(res[j]);
                res = res2;
                break;
            }
        }
    }

    if (count(deg.begin(), deg.end(), 0) != n) {
        cout << -1 << '\n';
    } else {
        for (int x : res)
            cout << x << " ";
    }
}
