#include <bits/stdc++.h>

using namespace std;

const int inf = (int) (1e9) + 7;

void dijkstra_heap(int src, vector<vector<pair<int, int>>> adj, vector<int> &dist){ // O(E * log V)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[src] = 0;
    pq.push({0, src});

    while(!pq.empty()){
        int u = pq.top().second;
        pq.pop();
        for(auto [v, w] : adj[u]){
            if(dist[v] > dist[u] + w){
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
}

int minDistance(vector<int> dist, vector<bool> vis){
    int ans = inf, min_index;

    for (int v = 0; v < (int) dist.size(); v++)
        if (!vis[v] && dist[v] <= ans)
            ans = dist[v], min_index = v;

    return min_index;
}

void dijkstra_brute(int src, vector<vector<pair<int, int>>> adj, vector<int> &dist){ // O(V^2 + E)
    int v = (int) adj.size();

    vector<bool> vis(v);
    dist[src] = 0;

    for (int phase = 0; phase < v - 1; phase++) {
        int u = minDistance(dist, vis);
        vis[u] = true;
        for(auto [v, w] : adj[u]){
            if(!vis[v] && dist[v] > dist[u] + w)
                dist[v] = dist[u] + w;
        }
    }
}

int main(){
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> adj(n);
    for(int i = 0; i < m; i++){
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    vector<int> dist(n, inf);
    dijkstra(0, adj, dist);
}
