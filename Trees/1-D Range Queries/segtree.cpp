#include <bits/stdc++.h>

using namespace std;

struct segtree{
public:
    vector<long long> tree;
    int n;

    segtree(vector<int> a){
        n = (1 << (int)ceil(log2(a.size())));
        tree.resize(n * 2);
        for(int i = 0; i < (int) a.size(); i++)
            tree[n + i] = a[i];
        for(int i = n - 1; i >= 1; i--)
            tree[i] = tree[2 * i] + tree[2 * i + 1];
    }

    long long query(int l, int r, int node = 1, int node_l = 0, int node_r = -1){
        if(node == 1)
            node_r = n - 1;
        if(l <= node_l && node_r <= r){
            return tree[node];
        }
        if(node_l > r || node_r < l){
            return 0;
        }
        int mid = (node_l + node_r) / 2;
        return query(l, r, node * 2, node_l, mid) +
               query(l, r, node * 2 + 1, mid + 1, node_r);
    }

    void update(int i, int val){
        tree[n + i] = val;
        for(int j = (n + i) / 2; j >= 1; j /= 2)
            tree[j] = tree[j * 2] + tree[j * 2 + 1];
    }
};

int main(){
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for(int &x : a)
        cin >> x;
    segtree st(a);
    for(int i = 1; i <= q; i++){
        int t;
        cin >> t;
        if(t == 1){
            int l, r, u;
            cin >> l >> r >> u;
            l--, r--;
            st.updateQuery(l, r, u);
        } else {
            int k;
            cin >> k;
            k--;
            cout << st.tree[st.n + k] << '\n';
        }
    }
}
