struct DSU {
    int n;
    vector<int> par, sz;

    explicit DSU(int n) : n(n) {
        par.resize(n), sz.resize(n);
        for (int i = 0; i < n; ++i) {
            par[i] = i, sz[i] = 1;
        }
    }

    int getRoot(int i) {
        if (i == par[i]) return i;
        return par[i] = getRoot(par[i]);
    }

    bool merge(int i, int j) {
        int ri = getRoot(i), rj = getRoot(j);
        if (ri == rj) return false;
        if (sz[ri] > sz[rj]) swap(ri, rj);
        sz[rj] += sz[ri];
        par[ri] = rj;
        return true;
    }

    vector<int> componentSizes() {
        vector<int> result;
        vector<int> grp_size(n);
        for (int i = 0; i < n; i++) {
            grp_size[getRoot(i)]++;
        }
        for (int i = 0; i < n; i++) {
            if (grp_size[i]) result.push_back(grp_size[i]);
        }
        result.erase(remove_if(result.begin(), result.end(), [&](int &i) { return i == 0; }), result.end());
        return result;
    }

    vector<vector<int>> getComponents() {
        vector<vector<int>> result(n);
        vector<int> grp_size(n), leader(n);
        for (int i = 0; i < n; i++) {
            leader[i] = getRoot(i);
            grp_size[leader[i]]++;
        }
        for (int i = 0; i < n; i++) result[i].reserve(grp_size[i]);
        for (int i = 0; i < n; i++) result[leader[i]].push_back(i);
        result.erase(remove_if(result.begin(), result.end(), [&](const vector<int> &v) { return v.empty(); }),
                     result.end());
        return result;
    }
};