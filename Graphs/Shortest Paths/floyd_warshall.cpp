#include <bits/stdc++.h>

using namespace std;

int inf = (int) (1e9) + 7;

void floyd_warshall(vector<vector<int>> &dist){
    int n = (int) dist.size();

    for(int k = 0 ; k < n; k++){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
}

int main(){
    int n, m;
    cin >> n >> m;
    vector<vector<int>> dist(n, vector<int>(n, inf));
    for(int i = 0; i < n; i++)
        dist[i][i] = 0;
    for(int i = 0; i < m; i++){
        int u, v, w;
        cin >> u >> v >> w;
        dist[u][v] = min(dist[u][v], w);
        dist[v][u] = min(dist[v][u], w);
    }

    floyd_warshall(dist);
}
