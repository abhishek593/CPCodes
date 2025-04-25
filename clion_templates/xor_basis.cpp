struct xor_basis{
    vector<long long> basis;
    int sz = 0;
    bool inBasis(long long mask) {
        for (long long i = 60; i >= 0; --i) {
            if (!(mask & (1LL << i))) continue;
            mask ^= basis[i];
        }
        return mask == 0;
    }
    ll query(ll k) {
        ll mask = 0;

        ll tot = 1LL << sz;
        for (ll i = 60; i >= 0; i--)
            if (basis[i]) {
                ll low = tot / 2;

                if ((low < k && (mask & 1LL << i) == 0) ||
                    (low >= k && (mask & 1LL << i) > 0)) mask ^= basis[i];

                if (low < k) k -= low;

                tot /= 2;
            }

        return mask;
    }
    void init(const vector<long long> &A) {
        basis.resize(61);
        for (long long mask: A) {
            for (long long i = 60; i >= 0; --i) {
                if (!(mask & (1LL << i))) continue;
                if (!basis[i]) {
                    basis[i] = mask, sz++;
                    break;
                }
                mask ^= basis[i];
            }
        }
    }
};
