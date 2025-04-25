template <class F> using Polygon = vector<Point<F>>;
inline int prev(int i, int n) { return i == 0 ? n-1 : i-1; }
inline int next(int i, int n) { return i == n-1 ? 0 : i+1; }
template <class T> inline int sgn(const T& x) { return (T(0) < x) - (x < T(0)); }

//Returns doubled oriented area
// > 0 if vertices are in ccw order else < 0
template <class F>
F area(const Polygon<F>& poly) {
    int n = static_cast<int>(poly.size());
    F area = F(0);
    for (int i = 0; i < n; ++i)
        area += poly[i].x * (poly[next(i, n)].y - poly[prev(i, n)].y);
    return area;
}

// True if orientation of a simple polygon is counter-clockwise.
template <class F>
bool orientation(const Polygon<F>& poly) {
    int n = static_cast<int>(poly.size());
    int i = static_cast<int>(min_element(begin(poly), end(poly)) - begin(poly));
    return ccw(poly[prev(i, n)], poly[next(i, n)], poly[i]) > 0;
}
