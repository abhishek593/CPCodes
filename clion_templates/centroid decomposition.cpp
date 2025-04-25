int OneCentroid(int root, const vector<vector<int>> &g, const vector<bool> &dead) {
    static vector<int> sz(g.size());
    function<void (int, int)> get_sz = [&](int i, int par) {
        sz[i] = 1;
        for (auto j : g[i]) {
            if (j != par && !dead[j]) {
                get_sz(j, i);
                sz[i] += sz[j];
            }
        }
    };
    get_sz(root, -1);
    int n = sz[root];
    function<int (int, int)> dfs = [&](int i, int par) {
        for (auto j : g[i]) {
            if (j != par && !dead[j]) {
                if (sz[j] > n / 2) {
                    return dfs(j, i);
                }
            }
        }
        return i;
    };
    return dfs(root, -1);
}

vector<int> CentroidDecomposition(const vector<vector<int>> &g, const vector<vector<pair<int, int>>> &l, int q) {
    int n = g.size();
    vector<int> ans(q, 0);
    vector<bool> dead(n, false);
    function<void (int)> rec = [&](int start) {
        int c = OneCentroid(start, g, dead);
        dead[c] = true;
        for (auto i : g[c]) {
            if (!dead[i]) {
                rec(i);
            }
        }

//        map<int, int> cnt;
//        function<void (int, int, int, bool)> add_cnt = [&](int u, int prev, int d, bool add) {
//            cnt[d] += (add ? 1 : -1);
//            for (auto v : g[u])
//                if (v != prev && !dead[v]) {
//                    add_cnt(v, u, d + 1, add);
//                }
//        };
//        function<void (int, int, int)> calc = [&](int u, int prev, int d) {
//            for (auto it : l[u]) {
//                int dd, idx;
//                tie(dd, idx) = it;
//                if (dd - d >= 0 && cnt.count(dd - d)) {
//                    ans[idx] += cnt[dd - d];
//                }
//            }
//            for (auto v : g[u])
//                if (v != prev && !dead[v]) {
//                    calc(v, u, d + 1);
//                }
//        };
//        add_cnt(c, -1, 0, true);//accumulate for everything in all subtrees
//        for (auto it : l[c]) {
//            int dd, idx;
//            tie(dd, idx) = it;
//            ans[idx] += cnt[dd];
//        }
//        for (auto u : g[c]) if (!dead[u]) {
//                add_cnt(u, c, 1, false);//remove current subtree
//                calc(u, c, 1);//calc
//                add_cnt(u, c, 1, true);// add back current subtree
//            }

        dead[c] = false;
    };
    rec(0);
    return ans;
}
