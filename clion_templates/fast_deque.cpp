// FastDeque
// random access: O(1)
// push/pop front/back: O(1)
// rotate forward/backward: O(1)
template <typename T, int MaxSize>
class FastDeque {
    T data_[MaxSize];
    int head_;
    int tail_;

public:
    FastDeque() : head_(0), tail_(0) {}
    FastDeque(const vector<T>& vec) : head_(0), tail_(0) {
        assert(vec.size() < MaxSize);
        copy(vec.begin(), vec.end(), data_);
        tail_ = (int)vec.size();
    }
    template <class... Args>
    void emplace_back(Args&&... args) {
        data_[tail_] = T(std::forward<Args>(args)...);
        increment(tail_);
        assert(head_ != tail_);
    }
    void push_back(const T& x) {
        data_[tail_] = x;
        increment(tail_);
        assert(head_ != tail_);
    }
    void push_back(T&& x) {
        data_[tail_] = x;
        increment(tail_);
        assert(head_ != tail_);
    }
    template <class... Args>
    void emplace_front(Args&&... args) {
        decrement(head_);
        data_[head_] = T(std::forward<Args>(args)...);
        assert(head_ != tail_);
    }
    void push_front(const T& x) {
        decrement(head_);
        data_[head_] = x;
        assert(head_ != tail_);
    }
    void push_front(T&& x) {
        decrement(head_);
        data_[head_] = x;
        assert(head_ != tail_);
    }
    void pop_back() {
        assert(head_ != tail_);
        decrement(tail_);
    }
    void pop_front() {
        assert(head_ != tail_);
        increment(head_);
    }
    T pop_back_val() {
        assert(head_ != tail_);
        decrement(tail_);
        return data_[tail_];
    }
    T pop_front_val() {
        assert(head_ != tail_);
        T res = move(data_[head_]);
        increment(head_);
        return res;
    }
    int size() const {
        int sz = (tail_ >= head_ ? tail_ - head_ : MaxSize - head_ + tail_);
        return sz;
    }
    void clear() { head_ = tail_ = 0; }
    T& operator[](const int& i) { return data_[head_ + i < MaxSize ? head_ + i : head_ + i - MaxSize]; }
    const T& operator[](const int& i) const { return data_[head_ + i < MaxSize ? head_ + i : head_ + i - MaxSize]; }
    T& front() { return data_[head_]; }
    const T& front() const { return data_[head_]; }
    T& back() { return data_[tail_ == 0 ? MaxSize - 1 : tail_ - 1]; }
    const T& back() const { return data_[tail_ == 0 ? MaxSize - 1 : tail_ - 1]; }
    void rotate_forward() {
        if (head_ == tail_)
            return;
        data_[tail_] = move(data_[head_]);
        increment(head_);
        increment(tail_);
    }
    void rotate_backward() {
        if (head_ == tail_)
            return;
        decrement(head_);
        decrement(tail_);
        data_[head_] = move(data_[tail_]);
    }
    bool empty() const { return head_ == tail_; }
    vector<T> to_vector() const {
        int sz = size();
        vector<T> res;
        res.reserve(sz);
        for (int i = head_; i != tail_; increment(i)) {
            res.emplace_back(data_[i]);
        }
        return res;
    }

private:
    inline void increment(int& x) const {
        if (++x == MaxSize)
            x = 0;
    }
    inline void decrement(int& x) const {
        if (--x == -1)
            x = MaxSize - 1;
    }
};