// FastStack
// random access: O(1)
// push/pop: O(1)
template <typename T, int MaxSize>
class FastStack {
private:
    // T data_[MaxSize];
    vector<T> data_;
    int top_;

public:
#ifdef PRINT_MAX_STACK_SIZE
    int max_size = 0;
#endif
    // FastStack() : top_(0) {}
    FastStack() : top_(0) { data_.resize(MaxSize); }
    FastStack(const vector<T>& vec) : top_(0) {
        assert(vec.size() <= MaxSize);
        copy(vec.begin(), vec.end(), data_);
        top_ = (int)vec.size();
    }
    template <class... Args>
    void emplace(Args&&... args) {
        assert(top_ < MaxSize);
        data_[top_++] = T(std::forward<Args>(args)...);
    }
    void push(const T& x) {
        check_size();
        data_[top_++] = x;
    }
    void push(T&& x) {
        check_size();
        data_[top_++] = x;
    }
    T* push_null() {
        check_size();
        return &data_[top_++];
    }
    void pop() { --top_; }
    T pop_val() { return data_[--top_]; }
    T* pop_pointer() { return &data_[--top_]; }
    int size() const { return top_; }
    void clear() { top_ = 0; }
    T& operator[](const int& i) { return data_[i]; }
    const T& operator[](const int& i) const { return data_[i]; }
    T* top_pointer() {
        assert(top_ > 0);
        return &data_[top_ - 1];
    }
    T* get_pointer(const int& i) { return &data_[i]; }
    T& top() {
        assert(top_ > 0);
        return data_[top_ - 1];
    }
    const T& top() const {
        assert(top_ > 0);
        return data_[top_ - 1];
    }
    vector<T>& data() { return data_; }
    bool empty() const { return top_ == 0; }
    vector<T> to_vector() const {
        vector<T> res;
        res.reserve(top_);
        for (int i = 0; i < top_; i++) {
            res.emplace_back(data_[i]);
        }
        return res;
    }
    void resize(const int& n) {
        assert(n <= MaxSize);
        top_ = n;
    }

private:
    void check_size() {
#ifdef PRINT_MAX_STACK_SIZE
        chmax(max_size, top_ + 1);
#endif
    }
};