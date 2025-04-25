struct SlidingWindowMinimum{
    deque<int> dq;
    void add(int e) {
        while (!dq.empty() && e < dq.back()) {
            dq.pop_back();
        }
        dq.push_back(e);
    }
    void remove(int e) {
        assert(e >= dq.front());
        if (e == dq.front()) {
            dq.pop_front();
        }
    }
    int getMin() {
        return dq.front();
    }
};

struct SlidingWindowMaximum{
    deque<int> dq;
    void add(int e) {
        while (!dq.empty() && e > dq.back()) {
            dq.pop_back();
        }
        dq.push_back(e);
    }
    void remove(int e) {
        assert(e <= dq.front());
        if (e == dq.front()) {
            dq.pop_front();
        }
    }
    int getMax() {
        return dq.front();
    }
};