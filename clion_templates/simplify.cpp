//It simplifies the graph from parallel edges in O(V + E) time and self-loops
void simplify(vector<vector<int>> &g) {
    int n = g.size();
    vector<bool> used(n);
    vector<vector<int>> gr(n);
    for (int i = 0; i < n; ++i) {
        for (int j: g[i]) {
            if (j != i && !used[j]) {
                gr[i].push_back(j);
                used[j] = true;
            }
        }
        for (int j: g[i]) {
            used[j] = false;
        }
    }
    g = gr;
}