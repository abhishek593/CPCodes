template<const int &MOD>
struct Modular {
    int val;
    explicit Modular(int64_t v = 0) {if (v < 0) v = v % MOD + MOD;if (v >= MOD) v %= MOD;val = int(v);}
    Modular(int v) : Modular(int64_t(v)) {}
    explicit Modular(unsigned v) : Modular(uint64_t(v)) {}

    explicit operator int() const { return val; }
    explicit operator unsigned() const { return val; }
    explicit operator int64_t() const { return val; }
    explicit operator uint64_t() const { return val; }
    explicit operator double() const { return val; }
    explicit operator long double() const { return val; }
    Modular& operator+=(const Modular& other) { if ((val += other.val) >= MOD) val -= MOD; return *this; }
    Modular& operator-=(const Modular& other) { if ((val -= other.val) < 0) val += MOD; return *this; }

    static unsigned fast_mod(uint64_t x, unsigned m = MOD) {
#if !defined(_WIN32) || defined(_WIN64)
        return unsigned(x % m);
#endif
        auto x_high = unsigned(x >> 32), x_low = unsigned(x);
        unsigned quot, rem;
        asm("divl %4\n"
            : "=a" (quot), "=d" (rem)
            : "d" (x_high), "a" (x_low), "r" (m));
        return rem;
    }
    Modular& operator*=(const Modular &other) {val = fast_mod(uint64_t(val) * other.val);return *this;}
    Modular& operator/=(const Modular &other) {return *this *= other.inv();}
    friend Modular operator+(const Modular &lhs, const Modular &rhs) { return Modular(lhs) += rhs; }
    friend Modular operator-(const Modular &lhs, const Modular &rhs) { return Modular(lhs) -= rhs; }
    friend Modular operator*(const Modular &lhs, const Modular &rhs) { return Modular(lhs) *= rhs; }
    friend Modular operator/(const Modular &lhs, const Modular &rhs) { return Modular(lhs) /= rhs; }

    Modular& operator++() {val = val == MOD - 1 ? 0 : val + 1;return *this;}
    Modular& operator--() {val = val == 0 ? MOD - 1 : val - 1;return *this;}
    Modular operator++(int) { Modular result = *this; ++*this; return result; }
    Modular operator--(int) { Modular result = *this; --*this; return result; }
    Modular operator-() const {return val == 0 ? 0 : MOD - val;}
    friend bool operator==(const Modular &lhs, const Modular &rhs) { return lhs.val == rhs.val; }
    friend bool operator!=(const Modular &lhs, const Modular &rhs) { return lhs.val != rhs.val; }
    friend bool operator<(const Modular &lhs, const Modular &rhs) { return lhs.val < rhs.val; }
    friend bool operator>(const Modular &lhs, const Modular &rhs) { return lhs.val > rhs.val; }
    friend bool operator<=(const Modular &lhs, const Modular &rhs) { return lhs.val <= rhs.val; }
    friend bool operator>=(const Modular &lhs, const Modular &rhs) { return lhs.val >= rhs.val; }

    static const int SAVE_INV = int(1e6) + 5;
    static Modular save_inv[SAVE_INV];
    static void prepare_inv() {
        for (int64_t p = 2; p * p <= MOD; p += p % 2 + 1)
            assert(MOD % p != 0);
        save_inv[0] = 0;
        save_inv[1] = 1;
        for (int i = 2; i < SAVE_INV; i++)
            save_inv[i] = save_inv[MOD % i] * (MOD - MOD / i);
    }
    Modular inv() const {
        if (save_inv[1] == 0)
            prepare_inv();
        if (val < SAVE_INV)
            return save_inv[val];
        Modular product = 1;
        int v = val;
        while (v >= SAVE_INV) {
            product *= MOD - MOD / v;
            v = MOD % v;
        }
        return product * save_inv[v];
    }
    Modular pow(int64_t p) const {
        if (p < 0)
            return inv().pow(-p);
        Modular a = *this, result = 1;
        while (p > 0) {
            if (p & 1)
                result *= a;
            p >>= 1;
            if (p > 0)
                a *= a;
        }
        return result;
    }
    friend ostream& operator<<(ostream &os, const Modular &m) {
        return os << m.val;
    }
};

template<const int &MOD> Modular<MOD> Modular<MOD>::save_inv[Modular<MOD>::SAVE_INV];

extern const int MOD = int(1e9) + 7;
using Mint = Modular<MOD>;

struct Combinatorics{
    vector<Mint> _factorial = {1, 1}, _inv_factorial = {1, 1};

    void compute_factorials(int64_t maximum) {
        static int prepared_maximum = 1;
        if (maximum <= prepared_maximum)
            return;
        maximum += maximum / 16;
        _factorial.resize(maximum + 1);
        _inv_factorial.resize(maximum + 1);
        for (int i = prepared_maximum + 1; i <= maximum; i++) {
            _factorial[i] = i * _factorial[i - 1];
            _inv_factorial[i] = _inv_factorial[i - 1] / i;
        }
        prepared_maximum = int(maximum);
    }

    Mint factorial(int n) {
        compute_factorials(n);
        return _factorial[n];
    }

    Mint inv_factorial(int n) {
        compute_factorials(n);
        return _inv_factorial[n];
    }

    Mint choose(int64_t n, int64_t r) {
        if (r < 0 || r > n) return 0;
        compute_factorials(n);
        return _factorial[n] * _inv_factorial[r] * _inv_factorial[n - r];
    }

    Mint permute(int64_t n, int64_t r) {
        if (r < 0 || r > n) return 0;
        compute_factorials(n);
        return _factorial[n] * _inv_factorial[n - r];
    }

    Mint inv_choose(int64_t n, int64_t r) {
        assert(0 <= r && r <= n);
        compute_factorials(n);
        return _inv_factorial[n] * _factorial[r] * _factorial[n - r];
    }

    Mint inv_permute(int64_t n, int64_t r) {
        assert(0 <= r && r <= n);
        compute_factorials(n);
        return _inv_factorial[n] * _factorial[n - r];
    }
};