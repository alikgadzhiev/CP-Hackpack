template<typename flow_t>
struct dinic {
    struct edge {
        int node, rev;
        flow_t capacity;
        int id = -1;
 
        edge() {}
 
        edge(int _node, int _rev, flow_t _capacity, int _id = -1)
            : node(_node), rev(_rev), capacity(_capacity), id(_id) {}
    };
 
    int V = -1;
    vector<vector<edge>> adj;
    vector<int> dist;
    vector<int> q;
    int q_start, q_end;
    vector<int> edge_index;
    bool flow_called;
 
    dinic(int vertices = -1) {
        if (vertices >= 0)
            init(vertices);
    }
 
    void init(int vertices) {
        V = vertices;
        adj.assign(V, {});
        dist.resize(V);
        q.resize(V);
        edge_index.resize(V);
        flow_called = false;
    }
 
    void _add_edge(int u, int v, flow_t capacity1, flow_t capacity2, int id1, int id2) {
        assert(0 <= u && u < V && 0 <= v && v < V);
        edge uv_edge(v, int(adj[v].size()) + (u == v ? 1 : 0), capacity1, id1);
        edge vu_edge(u, int(adj[u].size()), capacity2, id2);
        adj[u].push_back(uv_edge);
        adj[v].push_back(vu_edge);
    }
 
    void add_directional_edge(int u, int v, flow_t capacity, int id = -1) {
        _add_edge(u, v, capacity, 0, id, -1);
    }
 
    void add_bidirectional_edge(int u, int v, flow_t capacity, int id = -1) {
        _add_edge(u, v, capacity, capacity, id, id);
    }
 
    edge &reverse_edge(const edge &e) {
        return adj[e.node][e.rev];
    }
 
    void bfs_check(int node, int potential_dist) {
        if (potential_dist < dist[node]) {
            dist[node] = potential_dist;
            q[q_end++] = node;
        }
    }
 
    bool bfs(int source, int sink) {
        fill(dist.begin(), dist.end(), INF);
        q_start = q_end = 0;
        bfs_check(source, 0);
 
        while (q_start < q_end) {
            int node = q[q_start++];
 
            for (edge &e : adj[node])
                if (e.capacity > 0)
                    bfs_check(e.node, dist[node] + 1);
        }
 
        return dist[sink] < INF;
    }
 
    flow_t dfs(int node, flow_t path_cap, int sink) {
        if (node == sink)
            return path_cap;
 
        if (dist[node] >= dist[sink])
            return 0;
 
        flow_t total_flow = 0;
 
        // Because we are only performing DFS in increasing order of dist, we don't have to revisit fully searched edges
        // again later.
        while (edge_index[node] < int(adj[node].size())) {
            edge &e = adj[node][edge_index[node]];
 
            if (e.capacity > 0 && dist[node] + 1 == dist[e.node]) {
                flow_t path = dfs(e.node, min(path_cap, e.capacity), sink);
                path_cap -= path;
                e.capacity -= path;
                reverse_edge(e).capacity += path;
                total_flow += path;
            }
 
            // If path_cap is 0, we don't want to increment edge_index[node] as this edge may not be fully searched yet.
            if (path_cap == 0)
                break;
 
            edge_index[node]++;
        }
 
        return total_flow;
    }
 
    flow_t flow(int source, int sink) {
        assert(V >= 0);
        flow_t total_flow = 0;
 
        while (bfs(source, sink)) {
            for (int i = 0; i < V; i++)
                edge_index[i] = 0;
 
            total_flow += dfs(source, numeric_limits<flow_t>::max(), sink);
        }
 
        flow_called = true;
        return total_flow;
    }
};
// https://codeforces.com/contest/1416/problem/F - link
