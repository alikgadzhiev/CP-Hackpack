const int BITS = 30;
const int INF = int(1e9) + 5;
 
struct binary_trie {
    static const int ALPHABET = 2;
 
    struct trie_node {
        int parent = -1;
        array<int, ALPHABET> child;
        int words_here = 0, starting_with = 0;
        int min_index = INF;
 
        trie_node() {
            memset(&child[0], -1, ALPHABET * sizeof(int));
        }
    };
 
    static const int ROOT = 0;
 
    vector<trie_node> nodes = {trie_node()};
 
    binary_trie(int total_length = -1) {
        if (total_length >= 0)
            nodes.reserve(total_length + 1);
    }
 
    int get_or_create_child(int node, int c) {
        if (nodes[node].child[c] < 0) {
            nodes[node].child[c] = int(nodes.size());
            nodes.emplace_back();
            nodes.back().parent = node;
        }
 
        return nodes[node].child[c];
    }
 
    int build(uint64_t word, int delta) {
        int node = ROOT;
 
        for (int bit = BITS - 1; bit >= 0; bit--) {
            nodes[node].starting_with += delta;
            node = get_or_create_child(node, int(word >> bit & 1));
        }
 
        nodes[node].starting_with += delta;
        return node;
    }
 
    int add(uint64_t word, int index) {
        int node = build(word, +1);
        nodes[node].words_here++;
 
        for (int x = node; x >= 0; x = nodes[x].parent)
            nodes[x].min_index = min(nodes[x].min_index, index);
 
        return node;
    }
 
    int query_min(uint64_t word, uint64_t x) {
        int node = ROOT;
        int minimum = INF;
 
        for (int bit = BITS - 1; bit >= 0; bit--) {
            int word_bit = word >> bit & 1;
            int x_bit = x >> bit & 1;
 
            if (x_bit) {
                if (nodes[node].child[word_bit] >= 0)
                    minimum = min(minimum, nodes[nodes[node].child[word_bit]].min_index);
            }
 
            node = nodes[node].child[word_bit ^ x_bit];
 
            if (node < 0)
                break;
        }
 
        return minimum;
    }
};

// link - https://codeforces.com/contest/1983/submission/269253141
