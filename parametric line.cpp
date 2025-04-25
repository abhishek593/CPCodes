//Parametric equation of line
template <class F>
struct Line {
    Point<F> a, ab;
    Line() : a(), ab() {}
    Line(const Point<F>& a, const Point<F>& b, bool twoPoints = true)
            : a(a), ab(twoPoints ? b - a : b) {}
    Line(const F& xa, const F& ya, const F& xb, const F& yb)
            : a(xa, ya), ab(xb - xa, yb - ya) {}

    void swap(Line& other) { using std::swap; swap(a, other.a); swap(ab, other.ab); }
    template <class F1> explicit operator Line<F1> () const {
        return Line<F1>(Point<F1>(a), Point<F1>(ab), false); }
    template <class F1> Line& operator = (const Line<F1>& other) {
        a = other.a; ab = other.ab; return *this; }

    Point<F> b() const { return a + ab; }
    explicit operator bool () const { return ab != Point<F>(); }
};

template <class F>
inline Line<F> makeLine(const Point<F>& a, const Point<F>& b, bool twoPoints = true) {
    return Line<F>(a, b, twoPoints);
}

template <class F> void swap(Line<F>& lhs, Line<F>& rhs) { lhs.swap(rhs); }
template <class F1, class F2>
bool onLine(const Point<F1>& point, const Line<F2>& line) {
    if (!line) return point == line.a;//if line reduces to a point
    return ((point - line.a) ^ line.ab) == 0;
}

/*
 * segment is represented by two points a and b
 * If point lies on segment, cross product should be zero while dot product <= 0
 * since for a disk around a and b a point inside has angle >= 90
 */
template <class F1, class F2>
bool onSegment(const Point<F1>& point, const Line<F2>& seg) {
    if (!seg) return point == seg.a;
    auto vecta = seg.a - point, vectb = seg.b() - point;
    return (vecta ^ vectb) == 0 && (vecta * vectb) <= 0;
}

template <class F1, class F2>
bool onRay(const Point<F1>& point, const Line<F2>& ray) {
    if (!onLine(point, ray)) return false;
    return (point - ray.a) * ray.ab >= 0;
}

template <class F1, class F2> using distF = decltype(sqrt(F1() + F2()));

//Perpendicular Distance of a point from line
template <class F1, class F2>
distF<F1, F2> distLine(const Point<F1>& point, const Line<F2>& line) {
    if (!line) return dist(point, line.a);
    return abs((point - line.a) ^ line.ab) / norm(line.ab);
}

/*
 * Shortest distance of a point from segment
 * If it lies between the perpendicular lines from A and B, then this is perpendicular distane from the segment
 * Else it is the distance between a or b
 */
template <class F1, class F2>
distF<F1, F2> distSegment(const Point<F1>& point, const Line<F2>& seg) {
    if (((point - seg.a) * seg.ab) <= 0) return dist(point, seg.a);
    if (((point - seg.b()) * seg.ab) >= 0) return dist(point, seg.b());
    return distLine(point, seg);
}

//Shortest Distance of point from ray
template <class F1, class F2>
distF<F1, F2> distRay(const Point<F1>& point, const Line<F2>& ray) {
    if (((point - ray.a) * ray.ab) <= 0) return dist(point, ray.a);
    return distLine(point, ray);
}

//Projection of the point on the line stored in res
template <class F1, class F2, class F3>
void projection(const Point<F1>& point, const Line<F2>& line, Point<F3>& res) {
    res = line.a;
    if (line) res += line.ab * static_cast<F3>((point - line.a) * line.ab) / abs(line.ab);
}

//Reflection of the point about the line stored in res
template <class F1, class F2, class F3>
void reflection(const Point<F1>& point, const Line<F2>& line, Point<F3>& res) {
    projection(point, line, res);
    res = 2 * res - point;
}

//Given a segment, finds the closest point(stored in res) on this segment from point
template <class F1, class F2, class F3>
void closest(const Point<F1>& point, const Line<F2>& seg, Point<F3>& res) {
    if (((point - seg.a) * seg.ab) <= 0) res = seg.a;
    else if (((point - seg.b()) * seg.ab) >= 0) res = seg.b();
    else projection(point, seg, res);
}