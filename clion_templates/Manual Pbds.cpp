//May not be bug free
struct SegTree {
    int size, cur;
    vector<int> cnt, sums;

    void init(int n) {
        size = 1, cur = n;
        while (size < n) size *= 2;
        cnt.assign(4 * size, 0), sums.resize(4 * size);
    }
    void build(int n, int x, int lx, int rx) {
        if (rx - lx == 1) {
            if (lx < n) {
                cnt[x] = 1;
                sums[x]++;
            }
            return;
        }
        int m = (lx + rx) / 2;
        build(n, 2 * x + 1, lx, m);
        build(n, 2 * x + 2, m, rx);
        cnt[x] = cnt[2 * x + 1] + cnt[2 * x + 2];
        sums[x] = sums[2 * x + 1] + sums[2 * x + 2];
    }
    void build(int n) {
        build(n, 0, 0, size);
    }
    void set(int i, int x, int lx, int rx) {
        if (rx - lx == 1) {
            cnt[x]--, cur--;
            sums[x]--;
            return;
        }
        int m = (lx + rx) / 2;
        if (i < m) {
            set(i, 2 * x + 1, lx, m);
        }else{
            set(i, 2 * x + 2, m, rx);
        }
        cnt[x] = cnt[2 * x + 1] + cnt[2 * x + 2];
        sums[x] = sums[2 * x + 1] + sums[2 * x + 2];
    }
    void set(int i) {
        set(i, 0, 0, size);
    }
    int find_by_order(int k, int x, int lx, int rx) {
        if (rx - lx == 1) return lx;
        int m = (lx + rx) / 2;
        int sl = cnt[2 * x + 1];
        if (k < sl) {
            return find_by_order(k, 2 * x + 1, lx, m);
        }else{
            return find_by_order(k - sl, 2 * x + 2, m, rx);
        }
    }
    int find_by_order(int k) {
        return find_by_order(k, 0, 0, size);
    }
    int begin() {
        return find_by_order(0);
    }
    int end() {
        assert(cur > 0);
        return find_by_order(cur - 1);
    }
    int order_of_key(int l, int r, int x, int lx, int rx) {
        if (lx >= r || rx <= l) return 0;
        if (lx >= l && rx <= r) return sums[x];
        int m = (lx + rx) / 2;
        return order_of_key(l, r, 2 * x + 1, lx, m) + order_of_key(l, r, 2 * x + 2, m, rx);
    }
    int order_of_key(int l, int r) {
        return order_of_key(l, r, 0, 0, size);
    }
};
