template<class F>
Polygon<F> convexHull(Polygon<F>& points) {
    if (points.size() == 1) return points;
    sort(points.begin(), points.end(), [](const Point<F>& a, const Point<F>&b) {
        return a.x < b.x || (a.x == b.x && a.y < b.y);
    });
    Polygon<F> upHull = {points[0]}, downHull = {points[0]};
    Point<F> p1 = points[0], p2 = points.back();
    int n = points.size(), sign;
    for (int i = 1; i < n; ++i) {
        sign = sgn(ccw(points[i] - p1, p2 - points[i]));
        if (i == n - 1 || sign > 0) {
            while (upHull.size() > 1 && ccw(upHull.back() - upHull[upHull.size() - 2], points[i] - upHull.back()) <= 0)
                upHull.pop_back();
            upHull.push_back(points[i]);
        }
        if (i == n - 1 || sign < 0) {
            while (downHull.size() > 1 && ccw(downHull.back() - downHull[downHull.size() - 2], points[i] - downHull.back()) >= 0)
                downHull.pop_back();
            downHull.push_back(points[i]);
        }
    }
    Polygon<F> hull = downHull;
    for (int i = (int)upHull.size() - 2; i > 0; --i) {
        hull.push_back(upHull[i]);
    }
    return hull;
}
