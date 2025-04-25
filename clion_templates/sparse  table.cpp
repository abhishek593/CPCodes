template<int MAX_LOG>
struct SparseTable{
    vector<int> logs;
    vector<vector<int>> st;

    void init(int n) {
        logs.resize(n + 1);
        logs[1] = 0;
        for (int i = 2; i <= n; ++i) {
            logs[i] = logs[i / 2] + 1;
        }
        st.assign(MAX_LOG + 1, vector<int> (n));
    }
    void build() {
        int k = logs[n];
        for (int i = 0; i < n; ++i) {
            st[0][i] = i;
        }
        for (int j = 1; j <= k; ++j) {
            for (int i = 0; i + (1 << j) <= n; ++i) {
                if (a[st[j - 1][i]] < a[st[j - 1][i + (1 << (j - 1))]]) st[j][i] = st[j - 1][i];
                else st[j][i] = st[j - 1][i + (1 << (j - 1))];
            }
        }
    }
    int query(int l, int r) {
        int k = logs[r - l + 1];
        if (a[st[k][l]] < a[st[k][r - (1 << k) + 1]]) return st[k][l];
        return st[k][r - (1 << k) + 1];
    }
};