//
// Created by Abhishek Bansal on 5/27/2021
//
//#pragma GCC optimize ("O3")
//#pragma GCC optimize("Ofast,no-stack-protector")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,mmx,tune=native")
#include <bits/stdc++.h>
#define ll long long
#define ld long double
using namespace std;
clock_t startTime;
double getCurrentTime() {
    return (double)(clock() - startTime) / CLOCKS_PER_SEC;
}
/*------------------------------------------------IO_OPERATORS---------------------------------------------*/
template<typename T, typename U> inline ostream &operator << (ostream &_out, const pair<T, U> &_p) { _out << _p.first << " " << _p.second; return _out; }
template<typename T, typename U> inline istream &operator >> (istream &_in, pair<T, U> &_p) { _in >> _p.first >> _p.second; return _in; }
template<typename T> inline ostream &operator << (ostream &_out, const vector<T> &_v) { if (_v.empty()) return _out; _out << _v.front(); for (auto _it = ++_v.begin(); _it != _v.end(); ++_it) _out << ' ' << *_it; return _out; }
template<typename T> inline istream &operator >> (istream &_in, vector<T> &_v) { for (auto &_i : _v) _in >> _i; return _in; }
template<typename T> inline ostream &operator << (ostream &_out, const set<T> &_s) { if (_s.empty()) return _out; _out << *_s.begin(); for (auto _it = ++_s.begin(); _it != _s.end(); ++_it) _out << ' ' << *_it; return _out; }
template<typename T> inline ostream &operator << (ostream &_out, const multiset<T> &_s) { if (_s.empty()) return _out; _out << *_s.begin(); for (auto _it = ++_s.begin(); _it != _s.end(); ++_it) _out << ' ' << *_it; return _out; }
template<typename T> inline ostream &operator << (ostream &_out, const unordered_set<T> &_s) { if (_s.empty()) return _out; _out << *_s.begin(); for (auto _it = ++_s.begin(); _it != _s.end(); ++_it) _out << ' ' << *_it; return _out; }
template<typename T> inline ostream &operator << (ostream &_out, const unordered_multiset<T> &_s) { if (_s.empty()) return _out; _out << *_s.begin(); for (auto _it = ++_s.begin(); _it != _s.end(); ++_it) _out << ' ' << *_it; return _out; }
template<typename T, typename U> inline ostream &operator << (ostream &_out, const map<T, U> &_m) { if (_m.empty()) return _out; _out << "{\"" << _m.begin()->first << "\", \"" << _m.begin()->second << "\"}"; for (auto _it = ++_m.begin(); _it != _m.end(); ++_it) _out << ", { \"" << _it->first << "\", \"" << _it->second << "\"}"; return _out; }
template<typename T, typename U> inline ostream &operator << (ostream &_out, const unordered_map<T, U> &_m) { if (_m.empty()) return _out; _out << '(' << _m.begin()->first << ": " << _m.begin()->second << ')'; for (auto _it = ++_m.begin(); _it != _m.end(); ++_it) _out << ", (" << _it->first << ": " << _it->second << ')'; return _out; }
//For 1 based indexing
template<typename T>
void out(const vector<T> &a, int n) {
    for (int i = 1; i <= n; ++i) {cout << a[i] << ' ';} cout << "\n";
}
template<typename T>
void out(const vector<vector<T>> &a, int n, int m) {
    for (int i = 1; i <= n; ++i) {for (int j = 1; j <= m; ++j) {cout << a[i][j] << ' ';}cout << '\n';}
}

template<class T, class U>
struct SegTree {
    int size;
    T INITIAL = 0;
    vector<T> tree;

    void init(int n) {
        size = 1;
        while (size < n) size *= 2;
        tree.assign(2 * size, INITIAL);
    }

    T combine(T a, T b) {
        return a + b;
    }

    void build(vector<T> &a, int x, int lx, int rx) {
        if (rx - lx == 1) {
            if (lx < (int) a.size()) {
                tree[x] = a[lx];
            }
            return;
        }
        int m = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, m);
        build(a, 2 * x + 2, m, rx);
        tree[x] = combine(tree[2 * x + 1], tree[2 * x + 2]);
    }

    void build(vector<T> &a) {
        build(a, 0, 0, size);
    }

    void update(int i, U v, int x, int lx, int rx) {
        if (rx - lx == 1) {
            tree[x] = v;
            return;
        }
        int m = (lx + rx) / 2;
        if (i < m) {
            update(i, v, 2 * x + 1, lx, m);
        } else {
            update(i, v, 2 * x + 2, m, rx);
        }
        tree[x] = combine(tree[2 * x + 1], tree[2 * x + 2]);
    }

    void update(int i, U v) {
        update(i, v, 0, 0, size);
    }

    T query(int l, int r, int x, int lx, int rx) {
        if (lx >= r || l >= rx) return 0;
        if (lx >= l && rx <= r) return tree[x];
        int m = (lx + rx) / 2;
        return combine(query(l, r, 2 * x + 1, lx, m), query(l, r, 2 * x + 2, m, rx));
    }

    T query(int l, int r) {
        return query(l, r, 0, 0, size);
    }
};

vector<int> start, en;
//[st[i], en[i]) range for each
int timer;
vector<vector<int>> v;
vector<int> a;
vector<int> eulerTour;

void dfs(int i, int par = -1) {
    eulerTour.push_back(a[i]);
    start[i] = timer++;

    for (int j: v[i]) {
        if (j == par) continue;
        dfs(j, i);
    }
    en[i] = timer;
}

void solve() {
    int n;cin >> n;
    a.resize(n);//node values
    cin >> a;
    v.resize(n), start.resize(n);
    en.resize(n);
    for (int i = 0; i < n - 1; ++i) {
        int x, y;cin >> x >> y;
        --x, --y;
        v[x].push_back(y), v[y].push_back(x);
    }
    timer = 0;
    dfs(0);
    SegTree<int, int> st;
    st.init(n);
    st.build(eulerTour);
    cout << start << "\n" << en << "\n";
    int q;cin >> q;
    while (q--) {
        int op;cin >> op;
        if (op == 1) {
            int i, x;cin >> i >> x;
            --i;
            st.update(start[i], x);//assign this to node
        }else{
            //find the subtree sum of this node
            int i;cin >> i;
            --i;
            cout << st.query(start[i], en[i]) << "\n";
        }
    }
//    cout << start << "\n" << en << "\n";
}

//9
//10 5 7 6 4 1 2 3 5
//1 2
//2 3
//2 4
//1 5
//5 6
//5 9
//4 7
//4 8
//19
//2 4
//2 1
//2 5
//1 2 3
//2 2
//2 1
//1 1 0
//2 1
//1 3 20
//1 8 10
//2 1
//2 2
//2 3
//2 4
//2 5
//2 6
//2 7
//2 8
//2 9

//11
//43
//10
//21
//41
//31
//51
//41
//20
//18
//10
//1
//2
//10
//5

int main() {
    ios_base::sync_with_stdio(false);cin.tie(nullptr);

    startTime = clock();
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
//    cout << fixed << setprecision(20);
    int T = 1;
    while (T--) {
        solve();
    }
    return 0;
}