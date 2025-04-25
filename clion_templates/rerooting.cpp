vector<vector<int>> v;
vector<ll> dp, c, fin;
int n;
 
void dfs(int i, int par = -1) {
    dp[i] = c[i];
    for(int j: v[i]) {
        if (j == par) continue;
        dfs(j, i);
        dp[i] += (dp[j] > 0 ? dp[j] : 0);
    }
}
 
void change_root(int i, int j) {
    dp[i] -= (dp[j] > 0 ? dp[j] : 0);
    dp[j] += (dp[i] > 0 ? dp[i] : 0);
}
 
void dfs2(int i, int par = -1) {
    fin[i] = dp[i];
    for(int j: v[i]) {
        if (j == par) continue;
        change_root(i, j);
        dfs2(j, i);
        change_root(j, i);
    }
}