using u64 = uint64_t;
using u128 = __uint128_t;

u64 binpower(u64 base, u64 e, u64 mod) {
    u64 result = 1;
    base %= mod;
    while (e) {
        if (e & 1)
            result = (u128)result * base % mod;
        base = (u128)base * base % mod;
        e >>= 1;
    }
    return result;
}

bool check_composite(u64 n, u64 a, u64 d, int s) {
    u64 x = binpower(a, d, n);
    if (x == 1 || x == n - 1)
        return 0;
    for (int r = 1; r < s; r++) {
        x = (u128)x * x % n;
        if (x == n - 1)
            return 0;
    }
    return 1;
};

bool MillerRabin(u64 n) {
    if (n < 2)
        return 0;
    int r = 0;
    u64 d = n - 1;
    while ((d & 1) == 0) {
        d >>= 1;
        r++;
    }
    for(int a:{2, 3, 5, 13, 19, 73, 193, 407521, 299210837})if(n==a)return 1;
    for (int a : {2, 325, 9375, 28178, 450775, 9780504, 1795265022})
        if (check_composite(n, a, d, r))
            return 0;
    return 1;
}

