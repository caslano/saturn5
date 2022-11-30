//  (C) Copyright Nick Thompson 2021.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_MATH_TOOLS_CUBIC_ROOTS_HPP
#define BOOST_MATH_TOOLS_CUBIC_ROOTS_HPP
#include <algorithm>
#include <array>
#include <boost/math/special_functions/sign.hpp>
#include <boost/math/tools/roots.hpp>

namespace boost::math::tools {

// Solves ax^3 + bx^2 + cx + d = 0.
// Only returns the real roots, as types get weird for real coefficients and
// complex roots. Follows Numerical Recipes, Chapter 5, section 6. NB: A better
// algorithm apparently exists: Algorithm 954: An Accurate and Efficient Cubic
// and Quartic Equation Solver for Physical Applications However, I don't have
// access to that paper!
template <typename Real>
std::array<Real, 3> cubic_roots(Real a, Real b, Real c, Real d) {
    using std::abs;
    using std::acos;
    using std::cbrt;
    using std::cos;
    using std::fma;
    using std::sqrt;
    std::array<Real, 3> roots = {std::numeric_limits<Real>::quiet_NaN(),
                                 std::numeric_limits<Real>::quiet_NaN(),
                                 std::numeric_limits<Real>::quiet_NaN()};
    if (a == 0) {
        // bx^2 + cx + d = 0:
        if (b == 0) {
            // cx + d = 0:
            if (c == 0) {
                if (d != 0) {
                    // No solutions:
                    return roots;
                }
                roots[0] = 0;
                roots[1] = 0;
                roots[2] = 0;
                return roots;
            }
            roots[0] = -d / c;
            return roots;
        }
        auto [x0, x1] = quadratic_roots(b, c, d);
        roots[0] = x0;
        roots[1] = x1;
        return roots;
    }
    if (d == 0) {
        auto [x0, x1] = quadratic_roots(a, b, c);
        roots[0] = x0;
        roots[1] = x1;
        roots[2] = 0;
        std::sort(roots.begin(), roots.end());
        return roots;
    }
    Real p = b / a;
    Real q = c / a;
    Real r = d / a;
    Real Q = (p * p - 3 * q) / 9;
    Real R = (2 * p * p * p - 9 * p * q + 27 * r) / 54;
    if (R * R < Q * Q * Q) {
        Real rtQ = sqrt(Q);
        Real theta = acos(R / (Q * rtQ)) / 3;
        Real st = sin(theta);
        Real ct = cos(theta);
        roots[0] = -2 * rtQ * ct - p / 3;
        roots[1] = -rtQ * (-ct + sqrt(Real(3)) * st) - p / 3;
        roots[2] = rtQ * (ct + sqrt(Real(3)) * st) - p / 3;
    } else {
        // In Numerical Recipes, Chapter 5, Section 6, it is claimed that we
        // only have one real root if R^2 >= Q^3. But this isn't true; we can
        // even see this from equation 5.6.18. The condition for having three
        // real roots is that A = B. It *is* the case that if we're in this
        // branch, and we have 3 real roots, two are a double root. Take
        // (x+1)^2(x-2) = x^3 - 3x -2 as an example. This clearly has a double
        // root at x = -1, and it gets sent into this branch.
        Real arg = R * R - Q * Q * Q;
        Real A = (R >= 0 ? -1 : 1) * cbrt(abs(R) + sqrt(arg));
        Real B = 0;
        if (A != 0) {
            B = Q / A;
        }
        roots[0] = A + B - p / 3;
        // Yes, we're comparing floats for equality:
        // Any perturbation pushes the roots into the complex plane; out of the
        // bailiwick of this routine.
        if (A == B || arg == 0) {
            roots[1] = -A - p / 3;
            roots[2] = -A - p / 3;
        }
    }
    // Root polishing:
    for (auto &r : roots) {
        // Horner's method.
        // Here I'll take John Gustaffson's opinion that the fma is a *distinct*
        // operation from a*x +b: Make sure to compile these fmas into a single
        // instruction and not a function call! (I'm looking at you Windows.)
        Real f = fma(a, r, b);
        f = fma(f, r, c);
        f = fma(f, r, d);
        Real df = fma(3 * a, r, 2 * b);
        df = fma(df, r, c);
        if (df != 0) {
            Real d2f = fma(6 * a, r, 2 * b);
            Real denom = 2 * df * df - f * d2f;
            if (denom != 0) {
                r -= 2 * f * df / denom;
            } else {
                r -= f / df;
            }
        }
    }
    std::sort(roots.begin(), roots.end());
    return roots;
}

// Computes the empirical residual p(r) (first element) and expected residual
// eps*|rp'(r)| (second element) for a root. Recall that for a numerically
// computed root r satisfying r = r_0(1+eps) of a function p, |p(r)| <=
// eps|rp'(r)|.
template <typename Real>
std::array<Real, 2> cubic_root_residual(Real a, Real b, Real c, Real d,
                                        Real root) {
    using std::abs;
    using std::fma;
    std::array<Real, 2> out;
    Real residual = fma(a, root, b);
    residual = fma(residual, root, c);
    residual = fma(residual, root, d);

    out[0] = residual;

    // The expected residual is:
    // eps*[4|ar^3| + 3|br^2| + 2|cr| + |d|]
    // This can be demonstrated by assuming the coefficients and the root are
    // perturbed according to the rounding model of floating point arithmetic,
    // and then working through the inequalities.
    root = abs(root);
    Real expected_residual = fma(4 * abs(a), root, 3 * abs(b));
    expected_residual = fma(expected_residual, root, 2 * abs(c));
    expected_residual = fma(expected_residual, root, abs(d));
    out[1] = expected_residual * std::numeric_limits<Real>::epsilon();
    return out;
}

// Computes the condition number of rootfinding. This is defined in Corless, A
// Graduate Introduction to Numerical Methods, Section 3.2.1.
template <typename Real>
Real cubic_root_condition_number(Real a, Real b, Real c, Real d, Real root) {
    using std::abs;
    using std::fma;
    // There are *absolute* condition numbers that can be defined when r = 0;
    // but they basically reduce to the residual computed above.
    if (root == static_cast<Real>(0)) {
        return std::numeric_limits<Real>::infinity();
    }

    Real numerator = fma(abs(a), abs(root), abs(b));
    numerator = fma(numerator, abs(root), abs(c));
    numerator = fma(numerator, abs(root), abs(d));
    Real denominator = fma(3 * a, root, 2 * b);
    denominator = fma(denominator, root, c);
    if (denominator == static_cast<Real>(0)) {
        return std::numeric_limits<Real>::infinity();
    }
    denominator *= root;
    return numerator / abs(denominator);
}

} // namespace boost::math::tools
#endif

/* cubic_roots.hpp
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
*/