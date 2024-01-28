#include "bits/stdc++.h"

#define int long long
using namespace std;

template<typename T>
istream &operator>>(istream &is, vector<T> &v) {
    for (auto &i: v) is >> i;
    return is;
}

template<typename T>
ostream &operator<<(ostream &os, vector<T> v) {
    for (auto &i: v) os << i << ' ';
    return os;
}

int mod = 998244353;

void heapify(vector<int> &a, int n, int idx){

    int root = idx;
    int l = idx * 2 + 1, r = idx * 2 + 2;

    if(l < n && a[l] > a[root])
        root = l;

    if(r < n && a[r] > a[root])
        root = r;

    if(root != idx){
        swap(a[root], a[idx]);
        heapify(a, n, root);
    }
}

void heap_sort(vector<int> &a){
    int n = (int) a.size();

    for(int i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i);

    for(int i = n - 1; i >= 0; i--){
        swap(a[i], a[0]);
        heapify(a, i, 0);
    }
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    cin >> a;

    heap_sort(a);
    cout << a << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
//    cin >> t;
    while(t--)
        solve();
}
