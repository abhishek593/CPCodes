int n, m;
vector<vector<int>> g;
void readGraph(bool directed) {
    cin >> n >> m;
    g.resize(n);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        g[a].push_back(b);
        if (!directed) g[b].push_back(a);
    }
}