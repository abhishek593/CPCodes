
struct segtree {

    int size;
    vector<long long > ops;

    void init(int n) {
        size = 1;
        while (size < n) size *= 2;
        ops.assign(2 * size, 0LL);
    }

    void build(vector<int>& a, int x, int lx, int rx) {
        if (rx - lx == 1) {
            if (lx < (int)a.size()) {
                ops[x] = a[lx];
            }
            return;
        }
        int m = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, m);
        build(a, 2 * x + 2, m, rx);
    }

    void build(vector<int>& a) {
        build(a, 0, 0, size);
    }

    void set(int l, int r, int v, int x, int lx, int rx) {
        if (l >= rx || lx >= r) return;
        if (lx >= l && rx <= r) {
            ops[x] += v;
            return;
        }
        int m = (lx + rx) / 2;
        set(l, r, v, 2 * x + 1, lx, m);
        set(l, r, v, 2 * x + 2, m, rx);
    }

    void set(int l, int r, int v) {
        set(l, r, v, 0, 0, size);
    }

    long long get(int i, int x, int lx, int rx) {
        if (rx - lx == 1) {
            return ops[x];
        }
        int m = (lx + rx) / 2;
        long long res = ops[x];
        if (i < m) {
            res += get(i, 2 * x + 1, lx, m);
        }else{
            res += get(i, 2 * x + 2, m, rx);
        }
        return res;
    }

    long long get(int i) {
        return get(i, 0, 0, size);
    }

};