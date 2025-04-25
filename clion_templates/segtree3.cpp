template<class T, class U> struct SegtreeLazy {
    int size;
    const T NO_OPERATION = 0;
    vector<T> ops;

    void init(int n) {
        size = 1;
        while (size < n) size *= 2;
        ops.assign(2 * size, NO_OPERATION);
    }

    void applyLazyOnNode(T &a, T &b) {
        if (b == NO_OPERATION) return;
        
    }

    void propagate(int x, int lx, int rx) {
        if (rx - lx == 1) return;
        applyLazyOnNode(ops[2 * x + 1], ops[x]);
        applyLazyOnNode(ops[2 * x + 2], ops[x]);
        ops[x] = NO_OPERATION;
    }

    void build(vector<T> &a, int x, int lx, int rx) {
        if (rx - lx == 1) {
            if (lx < (int)a.size()) {
                
            }
            return;
        }
        int m = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, m);
        build(a, 2 * x + 2, m, rx);
    }

    void build(vector<T> &a) {
        build(a, 0, 0, size);
    }

    void update(int l, int r, U v, int x, int lx, int rx) {
        propagate(x, lx, rx);
        if (l >= rx || lx >= r) return;
        if (lx >= l && rx <= r) {
            
            return;
        }
        int m = (lx + rx) / 2;
        update(l, r, v, 2 * x + 1, lx, m);
        update(l, r, v, 2 * x + 2, m, rx);
    }

    void update(int l, int r, U v) {
        update(l, r, v, 0, 0, size);
    }

    T query(int i, int x, int lx, int rx) {
        propagate(x, lx, rx);
        if (rx - lx == 1) {
            return ops[x];
        }
        int m = (lx + rx) / 2;
        if (i < m) {
            return query(i, 2 * x + 1, lx, m);
        }
        return query(i, 2 * x + 2, m, rx);
    }

    T query(int i) {
        return query(i, 0, 0, size);
    }
};