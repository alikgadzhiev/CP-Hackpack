#include <iostream>

using namespace std;

int inf = (int) (1e9) + 7;

void ford_bellman(int src, vector<vector<pair<int, int>>> adj, vector<int> &dist, vector<int> &path){ // O(E * V)
    dist[src] = 0;
    for(;;){
        bool any = false;
        for(int u = 0; u < (int) adj.size(); u++){
            if(adj.empty() || dist[u] == inf)
                continue;
            for(auto [v, w] : adj[u]){
                if(dist[v] > dist[u] + w){
                    dist[v] = dist[u] + w;
                    path[v] = u;
                    any = true;
                }
            }
        }
        if(!any)
            break;
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
    vector<int> path(n, -1);
    ford_bellman(0, adj, dist, path);
}
