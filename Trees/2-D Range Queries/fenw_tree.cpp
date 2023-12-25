#include <bits/stdc++.h>

using namespace std;

struct BIT_2D {
    vector<vector<int>> bit;
    int n, m;

    BIT_2D(int n, int m){
        this->n = n;
        this->m = m;
        bit.assign(n, vector<int>(m, 0));
    }

    BIT_2D(vector<vector<int>> a): BIT_2D((int) a.size(), (int) a[0].size()){
        for(int i = 0; i < (int)a.size(); i++)
            for(int j = 0; j < (int)a[0].size(); j++)
                add(i + 1, j + 1, a[i][j]);
    }

    int sum(int x, int y){
        int res = 0;
        for(; x >= 1; x -= (x & (-x)))
            for(; y >= 1; y -= (y & (-y)))
                res += bit[x][y];
        return res;
    }

    int query(int x1, int y1, int x2, int y2){
        return sum(x2, y2) - sum(x2, y1 - 1) - sum(x1 - 1, y2) + sum(x1 - 1, y1 - 1);
    }

    void add(int x, int y, int value){
        for(; x <= n; x += (x & (-x)))
            for(; y <= m; y += (y & (-y)))
                bit[x][y] += value;
    }
};

int main(){
}
