/*
 * Use on static arrays
 * Space Complexity: O(N log N)
 * Time Complexity: O(log^2 N)
 * For arrays with updates use Persistent Segment Tree because updates here are O(N)
 */

template<typename T>
struct MergeSortTree{
    int size;
    const int INF = 0;
    vector<vector<T>> tree;

    void init(int n) {
        size = 1;
        while (size < n) size *= 2;
        tree.resize(2 * size);
    }

    void build(const vector<T> &a, int x, int lx, int rx) {
        tree[x].resize(rx - lx);
        if (rx - lx == 1) {
            if (lx < (int)a.size()) {
                tree[x][0] = a[lx];
            }else tree[x][0] = INF;
            return;
        }
        int m = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, m);
        build(a, 2 * x + 2, m, rx);
        int i = 0, j = 0, k = 0, n1 = m - lx, n2 = rx - m;
        while (i < n1 && j < n2) {
            if (tree[2 * x + 1][i] < tree[2 * x + 2][j]) {
                tree[x][k++] = tree[2 * x + 1][i++];
            }else{
                tree[x][k++] = tree[2 * x + 2][j++];
            }
        }
        while (i < n1) {
            tree[x][k++] = tree[2 * x + 1][i++];
        }
        while (j < n2) {
            tree[x][k++] = tree[2 * x + 2][j++];
        }
    }

    void build(const vector<T> &a) {
        build(a, 0, 0, size);
    }

    T query(int l, int r, T k, int x, int lx, int rx) {
        if (lx >= r || l >= rx) return 0;
        if (lx >= l && rx <= r) return less_than(k, tree[x]) + 1;
        int m = (lx + rx) / 2;
        return query(l, r, k, 2 * x + 1, lx, m) + query(l, r, k, 2 * x + 2, m, rx);
    }

    T query(int l, int r, T k) {
        return query(l, r, k, 0, 0, size);
    }
};