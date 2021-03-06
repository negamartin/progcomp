#include "common.h"

// search x in a[i]
//
// first a[i] >  x:   upper_bound(a, x)
// first a[i] >= x:   lower_bound(a, x)
//  last a[i] <  x: --lower_bound(a, x)
//  last a[i] <= x: --upper_bound(a, x)

// note: searching for the largest [l, r] such that f(l) > a & f(r) < b where
// [a, b] is a range in f() space may result in negative [l, r] ranges.

// searches for a value in an [l, r] range (both inclusive).
//
// the `isleft(m)` function evaluates whether `m` is strictly to the left of the
// target value.
int binsearch_left(int l, int r, bool isleft(int)) {
    while (l != r) {
        int m = (l + r) / 2;
        if (isleft(m)) {
            l = m + 1;
        } else {
            r = m;
        }
    }
    return l;
}

// searches for a value in an [l, r] range (both inclusive).
//
// the `isright(m)` function evaluates whether `m` is strictly to the right of
// the target value.
//
// note the `+1` when computing `m`, which avoids infinite loops.
// the only difference with `binsearch_left` is how the evaluation function is
// specified. both are functionally identical.
int binsearch_right(int l, int r, bool isright(int)) {
    while (l != r) {
        int m = (l + r + 1) / 2;
        if (isright(m)) {
            r = m - 1;
        } else {
            l = m;
        }
    }
    return l;
}

// continuous ternary (golden section) search.
//
// searches for a minimum value of the given unimodal function (monotonic
// positive derivative).
template <typename T, typename U>
pair<T, U> ctersearch(int iter, T a, T b, U f(T)) {
    const T INVG = 0.61803398874989484820;

    U av = f(a);
    U bv = f(b);

    T mid = a + (b - a) * INVG;
    U midv = f(mid);

    for (int i = 0; i < iter; i++) {
        T new_mid = a + (mid - a) * INVG;
        U new_midv = f(new_mid);
        if (new_midv > midv) {
            // Search the right interval
            a = b;
            av = bv;
            b = new_mid;
            bv = new_midv;
        } else {
            // Search the left interval
            b = mid;
            bv = midv;
            mid = new_mid;
            midv = new_midv;
        }
    }
    return {mid, midv};
}

int main() {
    vector<int> ints = {4, 8, 9, 9, 11, 20};

    // lower_bound
    assert(lower_bound(ints.begin(), ints.end(), 3) - ints.begin() == 0);
    assert(lower_bound(ints.begin(), ints.end(), 9) - ints.begin() == 2);
    assert(lower_bound(ints.begin(), ints.end(), 10) - ints.begin() == 4);
    assert(lower_bound(ints.begin(), ints.end(), 25) - ints.begin() == 6);

    // upper_bound
    assert(upper_bound(ints.begin(), ints.end(), 3) - ints.begin() == 0);
    assert(upper_bound(ints.begin(), ints.end(), 9) - ints.begin() == 4);
    assert(upper_bound(ints.begin(), ints.end(), 10) - ints.begin() == 4);
    assert(upper_bound(ints.begin(), ints.end(), 25) - ints.begin() == 6);
}