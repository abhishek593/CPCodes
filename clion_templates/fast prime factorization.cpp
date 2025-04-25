namespace internal {
 
    using i64 = int64_t;
    using u32 = uint32_t;
    using u64 = uint64_t;
    using u128 = __uint128_t;
    #define rep(i, n) for (int i = 0; i < (int)(n); i++)
 
 
    mt19937_64 mt{random_device{}()};
    u64 rnd(u64 n) { return uniform_int_distribution<u64>(0, n-1)(mt); }
 
// >>> montgomery (64bit)
    struct m64 {
        using i64 = int64_t;
        using u64 = uint64_t;
        using u128 = __uint128_t;
 
        inline static u64 m, r, n2; // r * m = -1 (mod 1<<64), n2 = 1<<128 (mod m)
        static void set_mod(u64 m) {
            assert(m < (1ull << 62));
            assert((m & 1) == 1);
            m64::m = m;
            n2 = -u128(m) % m;
            r = m;
            rep (_, 5) r *= 2 - m*r;
            r = -r;
            assert(r * m == -1ull);
        }
        static u64 reduce(u128 b) { return (b + u128(u64(b) * r) * m) >> 64; }
 
        u64 x;
        m64() : x(0) {}
        m64(u64 x) : x(reduce(u128(x) * n2)){};
        u64 val() const { u64 y = reduce(x); return y >= m ? y-m : y; }
        m64 &operator+=(m64 y) {
            x += y.x - (m << 1);
            x = (i64(x) < 0 ? x + (m << 1) : x);
            return *this;
        }
        m64 &operator-=(m64 y) {
            x -= y.x;
            x = (i64(x) < 0 ? x + (m << 1) : x);
            return *this;
        }
        m64 &operator*=(m64 y) { x = reduce(u128(x) * y.x); return *this; }
        m64 operator+(m64 y) const { return m64(*this) += y; }
        m64 operator-(m64 y) const { return m64(*this) -= y; }
        m64 operator*(m64 y) const { return m64(*this) *= y; }
        bool operator==(m64 y) const { return (x >= m ? x-m : x) == (y.x >= m ? y.x-m : y.x); }
        bool operator!=(m64 y) const { return not operator==(y); }
        m64 pow(u64 n) const {
            m64 y = 1, z = *this;
            for ( ; n; n >>= 1, z *= z) if (n & 1) y *= z;
            return y;
        }
    };
// <<<
 
// >>> is_prime (Miller-Rabin)
    bool is_prime(const uint64_t x) {
        if (x == 2 or x == 3 or x == 5 or x == 7) return true;
        if (x % 2 == 0 or x % 3 == 0 or x % 5 == 0 or x % 7 == 0) return false;
        if (x < 121) return x > 1;
        const u64 d = (x-1) >> __builtin_ctzll(x-1);
        m64::set_mod(x);
        const m64 one(1), minus_one(x-1);
        auto ok = [&](u64 a) {
            auto y = m64(a).pow(d);
            u64 t = d;
            while (y != one and y != minus_one and t != x-1) y *= y, t <<= 1;
            if (y != minus_one and t % 2 == 0) return false;
            return true;
        };
        if (x < (1ull << 32)) {
            for (u64 a : { 2, 7, 61 }) if (not ok(a)) return false;
        } else {
            for (u64 a : { 2, 325, 9375, 28178, 450775, 9780504, 1795265022 }) {
                if (x <= a) return true;
                if (not ok(a)) return false;
            }
        }
        return true;
    }
// <<<
 
// >>> factor (Pollard rho)
    u64 rho(u64 n, u64 c) {
        m64::set_mod(n);
        assert(n > 1);
        const m64 cc(c);
        auto f = [&](m64 x) { return x*x + cc; };
        m64 x = 1, y = 2, z = 1, q = 1;
        u64 g = 1;
        const u64 m = 1LL<<(__lg(n)/5); // ?
        for (u64 r = 1; g == 1; r <<= 1) {
            x = y;
            rep (_, r) y = f(y);
            for (u64 k = 0; k < r and g == 1; k += m) {
                z = y;
                rep (_, min(m, r-k)) y = f(y), q *= x-y;
                g = gcd(q.val(), n);
            }
        }
        if (g == n) do { z = f(z); g = gcd((x-z).val(), n); } while (g == 1);
        return g;
    }
 
    u64 find_prime_factor(u64 n) {
        assert(n > 1);
        if (is_prime(n)) return n;
        rep (_, 100) {
            u64 m = rho(n, rnd(n));
            if (is_prime(m)) return m;
            n = m;
        }
        cerr << "failed" << endl;
        assert(false);
        return -1;
    }
 
    vector<pair<u64, u32>> factor(u64 n) {
        static vector<pair<u64, u32>> v;
        v.clear();
        for (u64 i = 2; i <= 100 and i*i <= n; ++i) {
            if (n % i == 0) {
                u32 cnt = 0;
                do ++cnt, n /= i; while (n % i == 0);
                v.emplace_back(i, cnt);
            }
        }
        while (n > 1) {
            auto p = find_prime_factor(n);
            u32 cnt = 0;
            do ++cnt, n /= p; while (n % p == 0);
            v.emplace_back(p, cnt);
        }
        sort(v.begin(), v.end());
        return v;
    }
// <<<
 
}
using internal::is_prime;
using internal::factor;