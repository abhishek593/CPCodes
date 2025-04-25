/*
 * Problem Link : https://codeforces.com/contest/600/problem/E
 */

int n;
vector<vector<int>> v;
vector<ll> c, ans, mx;//mx[i] stores the maximum frequency in the subtree
vector<map<int, int>> mp;//mp[i] stores the frequency of each color in subtree

void merge(int a, int b) {
    if (mp[a].size() < mp[b].size()) {
        swap(mp[a], mp[b]);
        ans[a] = ans[b];
        mx[a] = mx[b];
    }
    for (auto &p: mp[b]) {
        int col = p.first, cnt = p.second;
        mp[a][col] += cnt;
        if (mp[a][col] > mx[a]) {
            ans[a] = 0;
            mx[a] = mp[a][col];
        }
        if (mp[a][col] == mx[a]) {
            ans[a] += col;
        }
    }
}

void dfs(int i, int par = -1) {
    mx[i] = 1;
    mp[i][c[i]] = 1;
    ans[i] = c[i];
    for (int j: v[i]) {
        if (j == par) continue;
        dfs(j, i);
        merge(i, j);
    }
}

void solve() {
    cin >> n;
    v.resize(n), c.resize(n), ans.resize(n), mx.resize(n), mp.resize(n);
    cin >> c;
    for (int i = 0; i < n - 1; ++i) {
        int a, b;cin >> a >> b;
        --a, --b;
        v[a].push_back(b), v[b].push_back(a);
    }
    dfs(0);
    cout << ans;
}