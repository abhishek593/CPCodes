/* Some inequality relations:
 * Link: https://codeforces.com/blog/entry/128116?#comment-1137798
 */

struct Inequality {
    ll ceil(ll b, ll a) {
        return (a + b - 1) / a;
    }
    //Both of these inequalities assumes A != 0
    // And the solutions are including from the non - infinity side and open other side
    //This gives the range of X for the inequality AX >= B
    array<ll, 2> ineq1(ll A, ll B) {
        assert(A != 0);
        ll a = abs(A), b = abs(B);
        if (B >= 0) {
            if (A > 0) return {ceil(b, a), INF};
            return {-INF, -ceil(b, a)};
        }else{
            if (A > 0) return {-(b / a), INF};
            return {-INF, b / a};
        }
    }
    //This gives the range of X for the inequality AX <= B
    array<ll, 2> ineq2(ll A, ll B) {
    assert(A != 0);
        ll a = abs(A), b = abs(B);
        if (B >= 0) {
            if (A > 0) return {-INF, b / a};
            return {-(b / a), INF};
        }else{
            if (A > 0) return {-INF, -ceil(b, a)};
            return {ceil(b, a), INF};
        }
    }
};