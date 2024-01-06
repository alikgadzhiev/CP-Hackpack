// constrained_bipartite_matching solves the following problem:
// You are given a bipartite graph with edges going from the left side to the right side (there can be multi-edges).
// For each node, you are given constraints in the form of low[node] and high[node], meaning that the number of matches
// at this node must end up between low[node] and high[node].
// Find a subset of the edges to match that satisfies all the low/high constraints, or determine that it's impossible.
// When a solution exists, this can also find the minimum number of matched edges needed in order to solve the
// constraints. Note that this adds an additional log factor to the time complexity due to binary search.
// See also https://cp-algorithms.com/graph/flow_with_demands.html and https://codeforces.com/contest/1240/submission/62062679
struct constrained_bipartite_matching {
    int N, M;
    int source, sink, dummy_source, dummy_sink;
    vector<pair<int, int>> edges;
    dinic<int> graph;
 
    constrained_bipartite_matching(int n = 0, int m = 0) {
        init(n, m);
    }
 
    void init(int n, int m) {
        N = n;
        M = m;
        edges = {};
        source = N + M;
        sink = N + M + 1;
        dummy_source = N + M + 2;
        dummy_sink = N + M + 3;
    }
 
    void add_edge(int a, int b) {
        assert(0 <= a && a < N);
        assert(0 <= b && b < M);
        edges.emplace_back(a, N + b);
    }
 
    pair<int, int> build_graph(const vector<int> &low, const vector<int> &high, int dummy_cap = INF) {
        assert(int(low.size()) == N + M && int(high.size()) == N + M);
        graph.init(N + M + 4);
        int left_sum = 0, right_sum = 0;
 
        for (int i = 0; i < int(edges.size()); i++)
            graph.add_directional_edge(edges[i].first, edges[i].second, 1, i);
 
        for (int i = 0; i < N + M; i++)
            if (i < N) {
                graph.add_directional_edge(source, i, low[i]);
                graph.add_directional_edge(dummy_source, i, high[i] - low[i]);
                left_sum += low[i];
            } else {
                graph.add_directional_edge(i, sink, low[i]);
                graph.add_directional_edge(i, dummy_sink, high[i] - low[i]);
                right_sum += low[i];
            }
 
        graph.add_directional_edge(source, dummy_sink, right_sum);
        graph.add_directional_edge(dummy_sink, dummy_source, dummy_cap);
        graph.add_directional_edge(dummy_source, sink, left_sum);
 
        // Flow paths can move as follows:
        // 1) source -> left -> right -> sink. This helps directly satisfy two low constraints.
        // 2) source -> left -> right -> dummy_sink -> dummy_source -> sink. This satisfies a low constraint on the left
        //      with the help of a high constraint on the right. dummy_source -> sink is limited by left_sum in order to
        //      prevent using more of this than necessary to satisfy left low constraints.
        // 3) source -> dummy_sink -> dummy_source -> left -> right -> sink. This satisfies a low constraint on the
        //      right with the help of a high constraint on the left. dummy_source -> sink is limited by right_sum in
        //      order to prevent using more of this than necessary to satisfy right low constraints.
        // 4) source -> dummy_sink -> dummy_source -> sink. This is a direct path that helps ensure that the total flow
        //      reaches exactly left_sum + right_sum when completed.
        return {left_sum, right_sum};
    }
 
    int& get_capacity(int from, int to) {
        for (auto &e : graph.adj[from])
            if (e.node == to)
                return e.capacity;
 
        assert(false);
    }
 
    void add_to_dummy_edge(int change) {
        get_capacity(dummy_sink, dummy_source) += change;
    }
 
    // Returns {success, edge assignment (true for matched edges)}.
    pair<bool, vector<bool>> solve(const vector<int> &low, const vector<int> &high, bool require_minimum = false) {
        assert(int(low.size()) == N + M && int(high.size()) == N + M);
 
        for (int i = 0; i < N + M; i++)
            if (low[i] > high[i])
                return {false, {}};
 
        pair<int, int> sums = build_graph(low, high);
        int left_sum = sums.first, right_sum = sums.second;
        int total_flow = graph.flow(source, sink);
 
        if (total_flow != left_sum + right_sum)
            return {false, {}};
 
        if (require_minimum) {
            // Find the amount of flow sent through the edge dummy_sink -> dummy_source to use as an upper bound.
            int upper = get_capacity(dummy_source, dummy_sink);
 
            // We can use max(left_sum, right_sum) as a lower bound, since min(left_sum, right_sum) is an upper bound
            // for the amount of flow that went through without the dummy vertices.
            int lower = max(left_sum, right_sum);
            assert(lower <= upper);
 
            // Due to the way the graph is constructed, if we find the lowest capacity of the dummy_sink -> dummy_source
            // edge that still results in a total flow of left_sum + right_sum, we then guarantee that we've used the
            // minimum possible number of edges.
            if (lower < upper) {
                cerr << "Searching between " << lower << " and " << upper << endl;
 
                build_graph(low, high, lower);
                total_flow = graph.flow(source, sink);
 
                if (total_flow != left_sum + right_sum) {
                    // Binary search to find the highest dummy edge capacity that doesn't get enough flow.
                    while (lower < upper) {
                        int mid = (lower + upper + 1) / 2;
 
                        dinic<int> graph_copy = graph;
                        int total_flow_copy = total_flow;
 
                        add_to_dummy_edge(mid - lower);
                        total_flow += graph.flow(source, sink);
 
                        if (total_flow == left_sum + right_sum) {
                            upper = mid - 1;
                            graph = graph_copy;
                            total_flow = total_flow_copy;
                        } else {
                            lower = mid;
                        }
                    }
 
                    assert(total_flow != left_sum + right_sum);
                    lower++;
                    add_to_dummy_edge(1);
                    total_flow += graph.flow(source, sink);
                }
 
                cerr << "Result: " << lower << endl;
                assert(total_flow == left_sum + right_sum);
            }
        }
 
        vector<bool> matched(edges.size(), false);
 
        for (auto &e_list : graph.adj)
            for (auto &e : e_list)
                if (e.id >= 0)
                    matched[e.id] = e.capacity == 0;
 
        return {true, matched};
    }
};
// https://codeforces.com/contest/1416/problem/F - link
