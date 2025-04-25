template<class T>
struct Manacher{
    /*
     * Computes the radius of the longest palindrome centered at each element in O(n) time.
     * Actual palindrome length is `2 * radius[i] + 1`.
     */
    vector<int> odd_manacher(const T &s) {
        int n = s.length();
        vector<int> odd(n);
        for (int i = 0, l = 0, r = -1; i < n; ++i) {
            int k = i > r ? 1: min(r - i + 1, odd[l + r - i]);
            while (i - k >= 0 && i + k < n && s[i - k] == s[i + k]) {
                ++k;
            }
            odd[i] = --k;
            if (i + k > r) {
                r = i + k;
                l = i - k;
            }
        }
        return odd;
    }
    /*
     * Computes the radius of the longest palindrome centered at gap between i and i + 1 in O(n) time.
     * Actual palindrome length is `2 * radius[i] + 1`.
     */
    vector<int> even_manacher(const T &s) {
        int n = s.length();
        vector<int> even(n + 1);
        for (int i = 0, l = 0, r = -1; i < n; ++i) {
            int k = i > r ? 0: min(r - i + 1, even[l + r - i + 1]);
            while (i - k - 1 >= 0 && i + k < n && s[i - k - 1] == s[i + k]) {
                ++k;
            }
            even[i] = k--;
            if (i + k > r) {
                r = i + k;
                l = i - k - 1;
            }
        }
        return even;
    }
    /*
     * Returns a vector `lengths` of size `2 * n + 1` where `lengths[i]` indicates a palindrome starting at
     * `(i - lengths[i]) / 2` and ending at `(i + lengths[i]) / 2` (exact division).
     */
    vector<int> combined_manacher(const T &s) {
        int n = s.length();
        T extended(2 * n + 1, 0);
        for (int i = 0; i < n; i++)
            extended[2 * i + 1] = s[i];
        return odd_manacher(extended);
    }
};