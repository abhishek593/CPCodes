struct KMP {
    template<typename T>
    static vector<int> build(const T &s) {
        int n = s.length();
        vector<int> pi(n);
        for (int i = 1; i < n; ++i) {
            int l = pi[i - 1];
            while (l > 0 && s[i] != s[l]) {
                l = pi[l - 1];
            }
            if (s[i] == s[l]) {
                ++l;
            }
            pi[i] = l;
        }
        return pi;
    }

    template<typename T>
    vector<int> find_matches(const T &pat, const T &text, const vector<int> &pi) {
        int n = pat.size(), m = text.size();
        if (n > m)
            return {};
        vector<int> matches;
        int l = 0;
        for (int i = 0; i < m; ++i) {
            while (l > 0 && text[i] != pat[l]) {
                l = pi[l - 1];
            }
            if (text[i] == pat[l])
                l++;
            if (l == n)
                matches.push_back(i - n + 1);
        }
        return matches;
    }
};