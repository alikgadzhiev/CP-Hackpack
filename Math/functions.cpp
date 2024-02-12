vector<int> fact, rev_fact;

int modPow(int x, int y) {
    int res = 1;
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

void make_fact(int n) {
    fact = {1};
    for (int q = 1; q <= n; q++) {
        fact.push_back(fact.back() * q % mod);
    }
    rev_fact = {modPow(fact.back(), mod - 2, mod)};
    for (int q = n; q > 0; q--) {
        rev_fact.push_back(rev_fact.back() * q % mod);
    }
    reverse(rev_fact.begin(), rev_fact.end());
}
 
int C(int k, int n) {
    if (k < 0 || k > n) {
        return 0;
    }
    return fact[n] * rev_fact[k] % mod * rev_fact[n - k] % mod;
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

