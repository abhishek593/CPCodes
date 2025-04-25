template<class T, class U> struct SegTree {
    int size;
    T INITIAL = 0;
    vector<T> tree;

    void init(int n) {
        size = 1;
        while (size < n) size *= 2;
        tree.assign(2 * size, INITIAL);
    }
    
    T combine(T a, T b) {
        
    }
    
    void build(vector<T> &a, int x, int lx, int rx) {
        if (rx - lx == 1) {
            if (lx < (int) a.size()) {
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

    void update(int i, U v, int x, int lx, int rx) {
        if (rx - lx == 1) {
        
            return;
        }
        int m = (lx + rx) / 2;
        if (i < m) {
            update(i, v, 2 * x + 1, lx, m);
        } else {
            update(i, v, 2 * x + 2, m, rx);
        }
        tree[x] = combine(tree[2 * x + 1], tree[2 * x + 2]);
    }

    void update(int i, U v) {
        update(i, v, 0, 0, size);
    }

    T query(int l, int r, int x, int lx, int rx) {
        if (lx >= r || l >= rx) return 0;
        if (lx >= l && rx <= r) return tree[x];
        int m = (lx + rx) / 2;
        return combine(query(l, r, 2 * x + 1, lx, m), query(l, r, 2 * x + 2, m, rx));
    }

    T query(int l, int r) {
        return query(l, r, 0, 0, size);
    }
};