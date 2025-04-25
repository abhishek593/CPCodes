template<class T, class U> struct SegtreeLazy {
    int size;
    const U NO_OPERATION = 0;
    const T INITIAL = 0;
    const T NEUTRAL_ELEMENT = 0;
    vector<T> tree;
    vector<U> changes;

    void init(int n) {
        size = 1;
        while (size < n) size *= 2;
        changes.assign(2 * size, NO_OPERATION);
        tree.assign(2 * size, INITIAL);
    }

    T combine(T a, T b) {
        
    }

    void applyLazyOnChange(U &a, U &b) {
        
    }

    void applyLazyOnNode(T &a, U &b) {
        
    }

    void propagate(int x, int lx, int rx) {
        if (rx - lx == 1 || changes[x] == NO_OPERATION) return;
        applyLazyOnNode(tree[2 * x + 1], changes[x]);
        applyLazyOnNode(tree[2 * x + 2], changes[x]);
        applyLazyOnChange(changes[2 * x + 1], changes[x]);
        applyLazyOnChange(changes[2 * x + 2], changes[x]);
        changes[x] = NO_OPERATION;
    }

    void build(vector<T> &a, int x, int lx, int rx) {
        if (rx - lx == 1) {
            if (lx < (int)a.size()) {
                tree[x] = a[lx];
            }
            return;
        }
        int m = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, m);
        build(a, 2 * x + 2, m, rx);
        tree[x] = combine(tree[2 * x + 1], tree[2 * x + 2]);
    }

    void build(vector<T> &a) {
        build(a, 0, 0, size);
    }

    void update(int l, int r, U v, int x, int lx, int rx) {
        propagate(x, lx, rx);
        if (l >= rx || lx >= r) return;
        if (lx >= l && rx <= r) {
            applyLazyOnNode(tree[x], v);
            applyLazyOnChange(changes[x], v);
            return;
        }
        int m = (lx + rx) / 2;
        update(l, r, v, 2 * x + 1, lx, m);
        update(l, r, v, 2 * x + 2, m, rx);
        tree[x] = combine(tree[2 * x + 1], tree[2 * x + 2]);
    }

    void update(int l, int r, U v) {
        update(l, r, v, 0, 0, size);
    }

    T query(int l, int r, int x, int lx, int rx) {
        propagate(x, lx, rx);
        if (l >= rx || lx >= r) return NEUTRAL_ELEMENT;
        if (lx >= l && rx <= r) {
            return tree[x];
        }
        int m = (lx + rx) / 2;
        return combine(query(l, r, 2 * x + 1, lx, m), query(l, r, 2 * x + 2, m, rx));
    }

    T query(int l, int r) {
        return query(l, r, 0, 0, size);
    }
};