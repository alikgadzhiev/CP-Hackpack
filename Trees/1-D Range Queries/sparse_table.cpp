#include <bits/stdc++.h>

using namespace std;


// can use to find maximum, minimum or gcd on queries
// but only if the values of array do not change
// for example, sum queries, etc.
template <typename T>
struct sparse_table{ // 0-indexation
	vector<vector<T>> ST;

	T comb(T x, T y) {
		return max(x, y);
	}

	sparse_table(vector<T> &A){
		int N = A.size();
		int LOG = 32 - __builtin_clz(N);
		ST = vector<vector<T>>(LOG, vector<T>(N));
		for (int i = 0; i < N; i++){
			ST[0][i] = A[i];
		}
		for (int i = 0; i < LOG - 1; i++){
			for (int j = 0; j < N - (1 << i); j++){
				ST[i + 1][j] = comb(ST[i][j], ST[i][j + (1 << i)]);
			}
		}
	}
	T query(int L, int R){ // [L, R)
		int d = 31 - __builtin_clz(R - L);
		return comb(ST[d][L], ST[d][R - (1 << d)]);
	}
};

int main(){
}
