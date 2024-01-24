#include <bits/stdc++.h>

using namespace std;

struct segtree{
public:
    vector<int> tree;
    int n;

    segtree(int size) {
        n = (1 << (int)ceil(log2(a.size())));
        tree.resize(n * 2);
    }

    segtree(vector<int> a){
        n = (1 << (int)ceil(log2(a.size())));
        tree.resize(n * 2);
        for(int i = 0; i < (int) a.size(); i++)
            tree[n + i] = a[i];
        for(int i = n - 1; i >= 1; i--)
            tree[i] = tree[2 * i] + tree[2 * i + 1];
    }

    int query(int l, int r, int x, int lx, int rx){
        if(l <= lx && rx <= r){
            return tree[x];
        }
        if(lx > r || rx < l){
            return 0;
        }
        int mid = (lx + rx) / 2;
        return query(l, r, x * 2, lx, mid) +
               query(l, r, x * 2 + 1, mid + 1, rx);
    }

    int query(int l, int r){
        return query(l, r, 1, 0, n - 1);
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
