template<typename T>
vector<T> slidingWindowMinimum(const vector<T> &a, int k) {
    int n = a.size();
    vector<T> ans(n - k + 1);
    deque<T> dq;
    int cnt = k - 1, tail = 0;
    for (int i = 0; i < n; ++i) {
        while (!dq.empty() && a[i] < dq.back()) {
            dq.pop_back();
        }
        dq.push_back(a[i]);
        if (cnt > 0) cnt--;
        else{
            ans[i - k + 1] = dq.front();
            if (a[tail] == dq.front()) {
                dq.pop_front();
            }
            ++tail;
        }
    }
    return ans;
}

template<typename T>
vector<T> slidingWindowMaximum(const vector<T> &a, int k) {
    int n = a.size();
    vector<T> ans(n - k + 1);
    deque<T> dq;
    int cnt = k - 1, tail = 0;
    for (int i = 0; i < n; ++i) {
        while (!dq.empty() && a[i] > dq.back()) {
            dq.pop_back();
        }
        dq.push_back(a[i]);
        if (cnt > 0) cnt--;
        else{
            ans[i - k + 1] = dq.front();
            if (a[tail] == dq.front()) {
                dq.pop_front();
            }
            ++tail;
        }
    }
    return ans;
}