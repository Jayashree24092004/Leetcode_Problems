#define MOD 1000000007LL

long long power(long long a, long long b) {
    long long result = 1;

    while (b > 0) {
        if (b & 1)
            result = (result * a) % MOD;

        a = (a * a) % MOD;
        b >>= 1;
    }

    return result;
}

int numberOfSets(int n, int k) {
    int N = n + k - 1;
    int R = 2 * k;

    long long fact[2005];

    fact[0] = 1;

    for (int i = 1; i <= N; i++)
        fact[i] = (fact[i - 1] * i) % MOD;

    // C(N, R) = fact[N] / (fact[R] * fact[N-R])
    long long numerator = fact[N];

    long long denominator =
        (fact[R] * fact[N - R]) % MOD;

    long long inverseDenominator =
        power(denominator, MOD - 2);

    return (numerator * inverseDenominator) % MOD;
}