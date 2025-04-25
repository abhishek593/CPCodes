template< typename T = int >
struct HeavyLightDecomposition {
    vector< vector< int > > g;
    vector< int > sz, startTime, endTime, head, rev, par, depths;
    HeavyLightDecomposition() { }
    explicit HeavyLightDecomposition(const vector< vector< int > > &_g) : g(_g) {}

    void build() {
        sz.assign(g.size(), 0);
        startTime.assign(g.size(), 0);
        endTime.assign(g.size(), 0);
        head.assign(g.size(), 0);
        rev.assign(g.size(), 0);
        par.assign(g.size(), 0);
        depths.assign(g.size(), 0);
        dfs_sz(0, -1, 0);
        int t = 0;
        dfs_hld(0, -1, t);
    }

    /* k: 0-indexed */
    int la(int v, int k) {
        while(true) {
            int u = head[v];
            if(startTime[v] - k >= startTime[u]) return rev[startTime[v] - k];
            k -= startTime[v] - startTime[u] + 1;
            v = par[u];
        }
    }

    int lca(int u, int v) const {
        for(;; v = par[head[v]]) {
            if(startTime[u] > startTime[v]) swap(u, v);
            if(head[u] == head[v]) return u;
        }
    }

    int dist(int u, int v) const {
        return depths[u] + depths[v] - 2 * depths[lca(u, v)];
    }

    template< typename E, typename Q, typename F, typename S >
    E query(int u, int v, const E &ti, const Q &q, const F &f, const S &s, bool edge = false) {
        E l = ti, r = ti;
        for(;; v = par[head[v]]) {
            if(startTime[u] > startTime[v]) swap(u, v), swap(l, r);
            if(head[u] == head[v]) break;
            l = f(q(startTime[head[v]], startTime[v] + 1), l);
        }
        return s(f(q(startTime[u] + edge, startTime[v] + 1), l), r);
    }

    template< typename E, typename Q, typename F >
    E query(int u, int v, const E &ti, const Q &q, const F &f, bool edge = false) {
        return query(u, v, ti, q, f, f, edge);
    }

    template< typename Q >
    void update(int u, int v, const Q &q, bool edge = false) {
        for(;; v = par[head[v]]) {
            if(startTime[u] > startTime[v]) swap(u, v);
            if(head[u] == head[v]) break;
            q(startTime[head[v]], startTime[v] + 1);
        }
        q(startTime[u] + edge, startTime[v] + 1);
    }

    /* {parent, child} */
    vector< pair< int, int > > compress(vector< int > &remark) {
        auto cmp = [&](int a, int b) { return startTime[a] < startTime[b]; };
        sort(begin(remark), end(remark), cmp);
        remark.erase(unique(begin(remark), end(remark)), end(remark));
        int K = (int) remark.size();
        for(int k = 1; k < K; k++) remark.emplace_back(lca(remark[k - 1], remark[k]));
        sort(begin(remark), end(remark), cmp);
        remark.erase(unique(begin(remark), end(remark)), end(remark));
        vector< pair< int, int > > es;
        stack< int > st;
        for(auto &k : remark) {
            while(!st.empty() && endTime[st.top()] <= startTime[k]) st.pop();
            if(!st.empty()) es.emplace_back(st.top(), k);
            st.emplace(k);
        }
        return es;
    }

    void dfs_sz(int idx, int p, int d) {
        depths[idx] = d;
        par[idx] = p;
        sz[idx] = 1;
        if(!g[idx].empty() && g[idx][0] == p) swap(g[idx][0], g[idx].back());
        for(auto &to : g[idx]) {
            if(to == p) continue;
            dfs_sz(to, idx, d + 1);
            sz[idx] += sz[to];
            if(sz[g[idx][0]] < sz[to]) swap(g[idx][0], to);
        }
    }

    void dfs_hld(int idx, int p, int ×) {
        startTime[idx] = times++;
        rev[startTime[idx]] = idx;
        for(auto &to : g[idx]) {
            if(to == p) continue;
            head[to] = (g[idx][0] == to ? head[idx] : to);
            dfs_hld(to, idx, times);
        }
        endTime[idx] = times;
    }
};