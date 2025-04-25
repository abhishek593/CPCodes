template<class F>
struct Line{
    F a, b, c;
    Line(): a(), b(), c() {}
    Line(const F& _a, const F& _b, const F& _c) {a = _a, b = _b, c = _c;}
    Line(const F& xa, const F& ya, const F& xb, const F& yb) {
        a = ya - yb, b = xb - xa, c = -a * xa - b * ya;
    }
};

template <class F> istream& operator >> (istream& is, Line<F>& line) {
    return is >> line.a >> line.b >> line.c; }
template <class F> ostream& operator << (ostream& os, const Line<F>& line) {
    return os << line.a << ' ' << line.b << ' ' << line.c; }

//Perpendicular Distance of a point from line
template <class F1, class F2>
long double distLine(const Point<F1>& point, const Line<F2>& line) {
    return (ld)abs(line.a * point.x + line.b * point.y + line.c) / (ld)sqrt(line.a * line.a + line.b * line.b);
}

template<class F1, class F2>
Point<long double> intersection(const Line<F1>& l1, const Line<F2>& l2) {
    return Point<long double>((ld)(l2.c * l1.b - l1.c * l2.b) / (ld)(l1.a * l2.b - l2.a * l1.b),
                              (ld)(l2.a * l1.c - l1.a * l2.c) / (ld)(l1.a * l2.b - l2.a * l1.b));
}

template<class F1, class F2>
bool onLine(const Line<F1>& l, const Point<F2> &p) {
    return l.a * p.x + l.b * p.y + l.c == 0;
}