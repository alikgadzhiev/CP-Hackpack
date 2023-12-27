vector<int> fact, rev_fact;
 
int pow1(int x, int y, int z = C) {
    if (y == 0) {
        return 1;
    }
    if (y % 2 == 0) {
        return pow1(x*x % z, y/2, z);
    }
    return pow1(x, y-1, z)*x % z;
}
 
void make_fact(int n) {
    fact = {1};
    for (int q = 1; q <= n; q++) {
        fact.push_back(fact.back()*q % C);
    }
    rev_fact = {pow1(fact.back(), C-2, C)};
    for (int q = n; q > 0; q--) {
        rev_fact.push_back(rev_fact.back()*q % C);
    }
    reverse(rev_fact.begin(), rev_fact.end());
}
 
int C_n_k(int k, int n) {
    if (k < 0 || k > n) {
        return 0;
    }
    return fact[n]*rev_fact[k] % C*rev_fact[n-k] % C;
}

void findEulerPath(){
    ll n; // number of nodes
    ll d;
    vector<vector<pair<ll, ll>>> graph; // give him the size
    vector<int> cnt_in(szof(graph));
    for (int i = 0; i < szof(graph); ++i) {
        for (auto to : graph[i]) {
            cnt_in[to.ff]++;
        }
    }

    bool ok = true;

    int in_ind = -1, out_ind = -1;

    for (int i = 0; i < szof(graph); ++i) {
        if (cnt_in[i] != szof(graph[i])) {
            if (cnt_in[i] + 1 == szof(graph[i])) {
                if (in_ind != -1) {
                    ok = false;
                    break;
                }
                in_ind = i;
            } else if (cnt_in[i] == szof(graph[i]) + 1) {
                if (out_ind != -1) {
                    ok = false;
                    break;
                }
                out_ind = i;
            } else {
                ok = false;
                break;
            }
        }
    }

    if (!ok) {
        return;
    }

    int edges = n;

    if (in_ind != -1) {
        assert(out_ind != -1);
        graph[out_ind].push_back({in_ind, n});
        ++edges;
    }

    vector<bool> used(edges);
    vector<int> vcnt(szof(graph));
    vector<int> order;
    function<void(int)> dfs = [&](int v) {
        while (vcnt[v] < szof(graph[v])) {
            auto to = graph[v][vcnt[v]++];
            if (used[to.ss]) {
                continue;
            }
            used[to.ss] = true;
            dfs(to.ff);
            order.push_back(to.ss);
        }
    };

    dfs(0);

    if (szof(order) != edges) {
        return;
    }

    if (edges == n + 1) {
        rotate(order.begin(), find(order.begin(), order.end(), n), order.end());
        order.erase(order.begin());
    }

    cout << "Yes\n";
    reverse(order.begin(), order.end());
    for (int ind : order) {
        cout << ind + 1 << " ";
    }
    cout << "\n";
    return;
}

void binarySearch(){
    // left
    {
    	while(l < r){
		int mid = (l + r) / 2;
		....
		....
		....
		if(....)
			l = mid + 1;
		else
			r = mid;
	}
	return l;
    }

    // right
    {
    	while(l + 1 < r){
	    int mid = (l + r) / 2;
	    ....
	    ....
            ....
            if(....)
		r = mid;
	    else
		l = mid;
	}
	return r;
    }
}

long long modPow(long long x, long long y) {
    long long res = 1;
    x = x % mod;
    if (x == 0)
        return 0;

    while (y > 0) {
        if (y & 1)
            res = (res * x) % mod;
        y = y >> 1;
        x = (x * x) % mod;
    }
    return res;
}

ll computeXOR(ll n) {
    if (n % 4 == 0)
        return n;

    if (n % 4 == 1)
        return 1;

    if (n % 4 == 2)
        return n + 1;
    return 0;
}

string longDivision(string number, int divisor)
{
    // As result can be very large store it in string
    string ans;

    // Find prefix of number that is larger
    // than divisor.
    int idx = 0;
    int temp = number[idx] - '0';
    while (temp < divisor)
        temp = temp * 10 + (number[++idx] - '0');

    // Repeatedly divide divisor with temp. After
    // every division, update temp to include one
    // more digit.
    while (number.size() > idx) {
        // Store result in answer i.e. temp / divisor
        ans += (temp / divisor) + '0';

        // Take next digit of number
        temp = (temp % divisor) * 10 + number[++idx] - '0';
    }

    // If divisor is greater than number
    if (ans.length() == 0)
        return "0";

    // else return ans
    return ans;
}

std::vector<int> minp, primes, phi;
 
void sieve(int n) {
    minp.assign(n + 1, 0);
    phi.assign(n + 1, 0);
    primes.clear();
    phi[1] = 1;
    
    for (int i = 2; i <= n; i++) {
        if (minp[i] == 0) {
            minp[i] = i;
            phi[i] = i - 1;
            primes.push_back(i);
        }
        
        for (auto p : primes) {
            if (i * p > n) {
                break;
            }
            minp[i * p] = p;
            if (p == minp[i]) {
                phi[i * p] = phi[i] * p;
                break;
            }
            phi[i * p] = phi[i] * (p - 1);
        }
    }
}

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

template<typename num_t>
using ordered_set = tree<num_t, null_type, less<num_t>, rb_tree_tag, tree_order_statistics_node_update>;
