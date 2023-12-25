#include <bits/stdc++.h>

using namespace std;

struct BIT {
    vector<int> bit;
    int n;

    BIT(int n){
        this->n = n;
        bit.assign(n + 1, 0);
    }

    BIT(vector<int> a) : BIT((int)a.size()){
        for(int i = 0; i < (int)a.size(); i++)
            add(i + 1, a[i]);
    }

    int sum(int r){
        int res = 0;
        for(; r >= 1; r -= (r & (-r)))
            res += bit[r];
        return res;
    }

    int query(int l, int r){
        return sum(r) - sum(l - 1);
    }

    void add(int idx, int value){
        for(; idx <= n; idx += (idx & (-idx)))
            bit[idx] += value;
    }
};

int main(){
}
