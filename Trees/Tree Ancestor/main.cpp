#include <bits/stdc++.h>

using namespace std;

struct TreeAncestor{
    vector<vector<int>> up;
    vector<int> depth;
    const int LOG = 20;
public:
    TreeAncestor(int n, vector<vector<int>> adj){
        up = vector<vector<int>> (n, vector<int>(LOG));
        depth = vector<int> (n);

        function<void(int, int)> dfs = [&](int u, int pre){
            for(int v : adj[u]){
                if(v == pre)
                    continue;
                up[v][0] = u;
                depth[v] = depth[u] + 1;
                for(int j = 1; j < LOG; j++)
                    up[v][j] = up[up[v][j - 1]][j - 1];
                dfs(v, u);
            }
        };

        dfs(0, -1);
    }

    int getKthAncestor(int node, int k){
        if(depth[node] < k){
            return -1;
        }
        for(int j = LOG - 1; j >= 0; j--){
            if(k & (1 << j))
                node = up[node][j];
        }
        return node;
    }

    int getLCA(int a, int b){
        if(depth[a] < depth[b]) {
            swap(a, b);
        }
        a = getKthAncestor(a, depth[a] - depth[b]);
        if(a == b) {
            return a;
        }
        for(int j = LOG - 1; j >= 0; j--) {
            if(up[a][j] != up[b][j]){
                a = up[a][j];
                b = up[b][j];
            }
        }
        return up[a][0];
    }
};

int main(){
}
