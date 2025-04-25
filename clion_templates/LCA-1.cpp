vector<vector<int>> g;
vector<int> euler;
vector<int> depths;
vector<int> euler_depths;
vector<int> fa;

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
    void build(const vector<int> &a) {
        int n = a.size(), k = logs[n];
        st[0][0] = 0;
        for (int i = 1; i < n; ++i) {
            st[0][i] = a[i] > a[i - 1] ? i - 1: i;
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
        if (euler_depths[st[k][l]] < euler_depths[st[k][r - (1 << k) + 1]]) return st[k][l];
        return st[k][r - (1 << k) + 1];
    }
};

void dfs(int i, int d = 0, int par = -1) {
    depths[i] = d;
    euler.push_back(i);
    fa[i] = euler.size();
    for (int j: g[i]) {
        if (j == par) continue;
        dfs(j, d + 1, i);
        euler.push_back(i);
    }
}

SparseTable<20> st;
int LCA(int u, int v) {
    if (u == v) return u;
    if (fa[u] > fa[v]) swap(u, v);
    return euler[st.query(fa[u], fa[v])];
}

for (int e: euler) euler_depths.push_back(depths[e]);
st.init((int)euler_depths.size());
st.build(euler_depths);