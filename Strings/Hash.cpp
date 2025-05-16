const int NP = 1;
int pr[NP];
bool is_prime(int n) {
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (int d = 3; (int)(d) * d <= n; d += 2) if (n % d == 0) return false;
    return true;
}
void gen_primes() {
    const int L = 100'000'000;
    const int R = 1'000'000'000;
    for (int i = 0; i < NP; ++i) {
        pr[i] = L + rd() % (R - L);
        while (!is_prime(pr[i])) ++pr[i];
    }
}
 
using Hash = array<int, NP>;
 
Hash operator+(const Hash &a, const Hash &b) {
    Hash res;
    for (int i = 0; i < NP; ++i) res[i] = (a[i] + b[i]) % pr[i];
    return res;
}
Hash operator+(const Hash &a, int b) {
    Hash res;
    for (int i = 0; i < NP; ++i) res[i] = (a[i] + b) % pr[i];
    return res;
}
Hash operator-(const Hash &a, const Hash &b) {
    Hash res;
    for (int i = 0; i < NP; ++i) res[i] = (a[i] - b[i] + pr[i]) % pr[i];
    return res;
}
Hash operator*(const Hash &a, const Hash &b) {
    Hash res;
    for (int i = 0; i < NP; ++i) res[i] = ((int)(a[i]) * b[i]) % pr[i];
    return res;
}
Hash operator*(const Hash &a, int b) {
    Hash res;
    for (int i = 0; i < NP; ++i) res[i] = ((int)(a[i]) * b) % pr[i];
    return res;
}
 
const int N = 2'001;
const int X = 257;
 
Hash xpow[N + 1];

void fillX() {
    gen_primes();
    fill(all(xpow[0]), 1);
    for(int i = 1; i <= N; i++)
        xpow[i] = xpow[i - 1] * X;
}

auto get_h = [&](int pos, int len, const vector<Hash> &h) -> Hash {
    return h[pos + len] - h[pos] * xpow[len];
};

// https://codeforces.com/group/9Ro0ZujTIb/contest/609412/submission/319237484
