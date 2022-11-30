//  (C) Copyright Nick Thompson 2021.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_MATH_TOOLS_QUARTIC_ROOTS_HPP
#define BOOST_MATH_TOOLS_QUARTIC_ROOTS_HPP
#include <array>
#include <cmath>
#include <boost/math/tools/cubic_roots.hpp>

namespace boost::math::tools {

namespace detail {

// Make sure the nans are always at the back of the array:
template<typename Real>
bool comparator(Real r1, Real r2) {
   using std::isnan;
   if (isnan(r1)) { return false; }
   if (isnan(r2)) { return true; }
   return r1 < r2;
}

template<typename Real>
std::array<Real, 4> polish_and_sort(Real a, Real b, Real c, Real d, Real e, std::array<Real, 4>& roots) {
    // Polish the roots with a Halley iterate.
    using std::fma;
    using std::abs;
    for (auto &r : roots) {
        Real df = fma(4*a, r, 3*b);
        df = fma(df, r, 2*c);
        df = fma(df, r, d);
        Real d2f = fma(12*a, r, 6*b);
        d2f = fma(d2f, r, 2*c);
        Real f = fma(a, r, b);
        f = fma(f,r,c);
        f = fma(f,r,d);
        f = fma(f,r,e);
        Real denom = 2*df*df - f*d2f;
        if (abs(denom) > (std::numeric_limits<Real>::min)())
        {
            r -= 2*f*df/denom;
        }
    }
    std::sort(roots.begin(), roots.end(), detail::comparator<Real>);
    return roots;
}

}
// Solves ax^4 + bx^3 + cx^2 + dx + e = 0.
// Only returns the real roots, as these are the only roots of interest in ray intersection problems.
// Follows Graphics Gems V: https://github.com/erich666/GraphicsGems/blob/master/gems/Roots3And4.c
template<typename Real>
std::array<Real, 4> quartic_roots(Real a, Real b, Real c, Real d, Real e) {
    using std::abs;
    using std::sqrt;
    auto nan = std::numeric_limits<Real>::quiet_NaN();
    std::array<Real, 4> roots{nan, nan, nan, nan};
    if (abs(a) <= (std::numeric_limits<Real>::min)()) {
        auto cbrts = cubic_roots(b, c, d, e);
        roots[0] = cbrts[0];
        roots[1] = cbrts[1];
        roots[2] = cbrts[2];
        if (b == 0 && c == 0 && d == 0 && e == 0) {
           roots[3] = 0;
        }
        return detail::polish_and_sort(a, b, c, d, e, roots);
    }
    if (abs(e) <= (std::numeric_limits<Real>::min)()) {
        auto v = cubic_roots(a, b, c, d);
        roots[0] = v[0];
        roots[1] = v[1];
        roots[2] = v[2];
        roots[3] = 0;
        return detail::polish_and_sort(a, b, c, d, e, roots);
    }
    // Now solve x^4 + Ax^3 + Bx^2 + Cx + D = 0.
    Real A = b/a;
    Real B = c/a;
    Real C = d/a;
    Real D = e/a;
    Real Asq = A*A;
    // Let x = y - A/4:
    // Mathematica: Expand[(y - A/4)^4 + A*(y - A/4)^3 + B*(y - A/4)^2 + C*(y - A/4) + D]
    // We now solve the depressed quartic y^4 + py^2 + qy + r = 0.
    Real p = B - 3*Asq/8;
    Real q = C - A*B/2 + Asq*A/8;
    Real r = D - A*C/4 + Asq*B/16 - 3*Asq*Asq/256;
    if (abs(r) <= (std::numeric_limits<Real>::min)()) {
        auto [r1, r2, r3] = cubic_roots(Real(1), Real(0), p, q);
        r1 -= A/4;
        r2 -= A/4;
        r3 -= A/4;
        roots[0] = r1;
        roots[1] = r2;
        roots[2] = r3;
        roots[3] = -A/4;
        return detail::polish_and_sort(a, b, c, d, e, roots);
    }
    // Biquadratic case:
    if (abs(q) <= (std::numeric_limits<Real>::min)()) {
        auto [r1, r2] = quadratic_roots(Real(1), p, r);
        if (r1 >= 0) {
           Real rtr = sqrt(r1);
           roots[0] = rtr - A/4;
           roots[1] = -rtr - A/4;
        }
        if (r2 >= 0) {
           Real rtr = sqrt(r2);
           roots[2] = rtr - A/4;
           roots[3] = -rtr - A/4;
        }
        return detail::polish_and_sort(a, b, c, d, e, roots);
    }

    // Now split the depressed quartic into two quadratics:
    // y^4 + py^2 + qy + r = (y^2 + sy + u)(y^2 - sy + v) = y^4 + (v+u-s^2)y^2 + s(v - u)y + uv
    // So p = v+u-s^2, q = s(v - u), r = uv.
    // Then (v+u)^2 - (v-u)^2 = 4uv = 4r = (p+s^2)^2 - q^2/s^2.
    // Multiply through by s^2 to get s^2(p+s^2)^2 - q^2 - 4rs^2 = 0, which is a cubic in s^2.
    // Then we let z = s^2, to get
    // z^3 + 2pz^2 + (p^2 - 4r)z - q^2 = 0.
    auto z_roots = cubic_roots(Real(1), 2*p, p*p - 4*r, -q*q);
    // z = s^2, so s = sqrt(z).
    // No real roots:
    if (z_roots.back() <= 0) {
      return roots;
    }
    Real s = sqrt(z_roots.back());

    // s is nonzero, because we took care of the biquadratic case.
    Real v = (p + s*s + q/s)/2;
    Real u = v - q/s;
    // Now solve y^2 + sy + u = 0:
    auto [root0, root1] = quadratic_roots(Real(1), s, u);

    // Now solve y^2 - sy + v = 0:
    auto [root2, root3] = quadratic_roots(Real(1), -s, v);
    roots[0] = root0;
    roots[1] = root1;
    roots[2] = root2;
    roots[3] = root3;

    for (auto& r : roots) {
        r -= A/4;
    }
    return detail::polish_and_sort(a, b, c, d, e, roots);
}

}
#endif

/* quartic_roots.hpp
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
*/