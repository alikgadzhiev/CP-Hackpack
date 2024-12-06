struct edge {
    int v = -1, w = 0;
    edge(int v, int w): v(v), w(w) {}
};

struct lca_lift {
  const int lg = 24;
  int n;
  vector<int> depth;
  vector<int> depthw;
  vector<vector<edge> > edges;
  vector<vector<int> > lift;

  lca_lift(int sz) {
    n = sz;
    depth = vector<int>(n);
    depthw = vector<int>(n);
    edges = vector<vector<edge> >(n, vector<edge>());
    lift = vector<vector<int> >(n, vector<int>(lg, -1));
  }

  void add_edge(int a, int b, int w = 0) {
    edges[a].push_back(edge(b, w));
    edges[b].push_back(edge(a, w));
  }

  void attach(int node_to_attach, int node_to_attach_to, int weight = 0) {
    int a = node_to_attach, b = node_to_attach_to;
    add_edge(a, b, weight);

    lift[a][0] = b;

    for (int i = 1; i < lg; i++) {
      if (lift[a][i - 1] == -1) lift[a][i] = -1;
      else lift[a][i] = lift[lift[a][i - 1]][i - 1];
    }

    depth[a] = depth[b] + 1;
    depthw[a] = depthw[b] + weight;
  }

  void work(int u = 0) {
    depth[u] = depthw[u] = 0;
    dfs(u);
  }

  void dfs(int u, int par = -1) {
    lift[u][0] = par;

    for (int i = 1; i < lg; i++) {
      if (lift[u][i - 1] == -1) lift[u][i] = -1;
      else lift[u][i] = lift[lift[u][i - 1]][i - 1];
    }

    for (edge e : edges[u]) {
      if (e.v != par) {
        depth[e.v] = depth[u] + 1;
        depthw[e.v] = depthw[u] + e.w;
        dfs(e.v, u);
      }
    }
  }

  int get(int u, int k) {
    for (int i = lg - 1; i >= 0; i--) {
	  if (u == -1) return u;
      if ((1 << i) <= k) {
        u = lift[u][i];
        k -= (1 << i);
      }
    }
    return u;
  }

  int get_lca(int a, int b) {
    if (depth[a] < depth[b]) swap(a, b);
    int d = depth[a] - depth[b];
    int u = get(a, d);
    if (u == b) {
      return u;
    } else {
      for (int i = lg - 1; i >= 0; i--) {
        if (lift[u][i] != lift[b][i]) {
          u = lift[u][i];
          b = lift[b][i];
        }
      }
      return lift[b][0];
    }
  }

  int get_dist(int a, int b) {
    int v = get_lca(a, b);
    return depth[a] + depth[b] - 2 * depth[v];
  }

  int get_distw(int a, int b) {
    int v = get_lca(a, b);
    return depthw[a] + depthw[b] - 2 * depthw[v];
  }
};
