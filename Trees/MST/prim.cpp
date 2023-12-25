#include <bits/stdc++.h>

using namespace std;

int main(){
    int n, m;
    cin >> n >> m;

    vector<vector<vector<int>>> adj(n + 1);
    for(int i = 1; i <= m; i++){
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, 1});

    vector<bool> visited(n + 1, false);

    int sum = 0;
    while(!pq.empty()){
        pair<int, int> best = pq.top();
        pq.pop();

        int w = best.first;
        int u = best.second;

        if(visited[u])
            continue;

        sum += w;
        visited[u] = true;

        for(auto v : adj[u]){
            if(visited[v[0]])
                continue;
            pq.push({v[1], v[0]});
        }
    }

    cout << sum << '\n';

    // Time complexity - O(n*logn + e)
}
