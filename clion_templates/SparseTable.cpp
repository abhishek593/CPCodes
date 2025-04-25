template<class T, int MAX_LOG>
struct SparseTable{
    vector<int> logs;
    vector<vector<T>> st;

    void init(int n) {
        logs.resize(n + 1);
        logs[1] = 0;
        for (int i = 2; i <= n; ++i) {
            logs[i] = logs[i / 2] + 1;
        }
        st.assign(MAX_LOG + 1, vector<T> (n));
    }

    void build(const vector<T> &a) {
        int n = a.size(), k = logs[n];
        for (int i = 0; i < n; ++i) {
            st[0][i] = a[i];
        }
        for (int j = 1; j <= k; ++j) {
            for (int i = 0; i + (1 << j) <= n; ++i) {
                st[j][i] = function(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
            }
        }
    }

    T function(T a, T b) {
        return min(a, b);
    }

    //0 based indexing [l, r]
    T query(int l, int r) {
        int k = logs[r - l + 1];
        return function(st[k][l], st[k][r - (1 << k) + 1]);
    }

};