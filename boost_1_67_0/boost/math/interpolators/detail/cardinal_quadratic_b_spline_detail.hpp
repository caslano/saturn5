// Copyright Nick Thompson, 2019
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_INTERPOLATORS_CARDINAL_QUADRATIC_B_SPLINE_DETAIL_HPP
#define BOOST_MATH_INTERPOLATORS_CARDINAL_QUADRATIC_B_SPLINE_DETAIL_HPP
#include <vector>
#include <cmath>
#include <stdexcept>

namespace boost{ namespace math{ namespace interpolators{ namespace detail{

template <class Real>
Real b2_spline(Real x) {
    using std::abs;
    Real absx = abs(x);
    if (absx < 1/Real(2))
    {
        Real y = absx - 1/Real(2);
        Real z = absx + 1/Real(2);
        return (2-y*y-z*z)/2;
    }
    if (absx < Real(3)/Real(2))
    {
        Real y = absx - Real(3)/Real(2);
        return y*y/2;
    }
    return (Real) 0;
}

template <class Real>
Real b2_spline_prime(Real x) {
    if (x < 0) {
        return -b2_spline_prime(-x);
    }

    if (x < 1/Real(2))
    {
        return -2*x;
    }
    if (x < Real(3)/Real(2))
    {
        return x - Real(3)/Real(2);
    }
    return (Real) 0;
}


template <class Real>
class cardinal_quadratic_b_spline_detail
{
public:
    // If you don't know the value of the derivative at the endpoints, leave them as nans and the routine will estimate them.
    // y[0] = y(a), y[n -1] = y(b), step_size = (b - a)/(n -1).

    cardinal_quadratic_b_spline_detail(const Real* const y,
                                size_t n,
                                Real t0 /* initial time, left endpoint */,
                                Real h  /*spacing, stepsize*/,
                                Real left_endpoint_derivative = std::numeric_limits<Real>::quiet_NaN(),
                                Real right_endpoint_derivative = std::numeric_limits<Real>::quiet_NaN())
    {
        if (h <= 0) {
            throw std::logic_error("Spacing must be > 0.");
        }
        m_inv_h = 1/h;
        m_t0 = t0;

        if (n < 3) {
            throw std::logic_error("The interpolator requires at least 3 points.");
        }

        using std::isnan;
        Real a;
        if (isnan(left_endpoint_derivative)) {
            // http://web.media.mit.edu/~crtaylor/calculator.html
            a = -3*y[0] + 4*y[1] - y[2];
        }
        else {
            a = 2*h*left_endpoint_derivative;
        }

        Real b;
        if (isnan(right_endpoint_derivative)) {
            b = 3*y[n-1] - 4*y[n-2] + y[n-3];
        }
        else {
            b = 2*h*right_endpoint_derivative;
        }

        m_alpha.resize(n + 2);

        // Begin row reduction:
        std::vector<Real> rhs(n + 2, std::numeric_limits<Real>::quiet_NaN());
        std::vector<Real> super_diagonal(n + 2, std::numeric_limits<Real>::quiet_NaN());

        rhs[0] = -a;
        rhs[rhs.size() - 1] = b;

        super_diagonal[0] = 0;

        for(size_t i = 1; i < rhs.size() - 1; ++i) {
            rhs[i] = 8*y[i - 1];
            super_diagonal[i] = 1;
        }

        // Patch up 5-diagonal problem:
        rhs[1] = (rhs[1] - rhs[0])/6;
        super_diagonal[1] = Real(1)/Real(3);
        // First two rows are now:
        // 1 0 -1 | -2hy0'
        // 0 1 1/3| (8y0+2hy0')/6


        // Start traditional tridiagonal row reduction:
        for (size_t i = 2; i < rhs.size() - 1; ++i) {
            Real diagonal = 6 - super_diagonal[i - 1];
            rhs[i] = (rhs[i] - rhs[i - 1])/diagonal;
            super_diagonal[i] /= diagonal;
        }

        //  1 sd[n-1] 0     | rhs[n-1]
        //  0 1       sd[n] | rhs[n]
        // -1 0       1     | rhs[n+1]

        rhs[n+1] = rhs[n+1] + rhs[n-1];
        Real bottom_subdiagonal = super_diagonal[n-1];

        // We're here:
        //  1 sd[n-1] 0     | rhs[n-1]
        //  0 1       sd[n] | rhs[n]
        //  0 bs      1     | rhs[n+1]

        rhs[n+1] = (rhs[n+1]-bottom_subdiagonal*rhs[n])/(1-bottom_subdiagonal*super_diagonal[n]);

        m_alpha[n+1] = rhs[n+1];
        for (size_t i = n; i > 0; --i) {
            m_alpha[i] = rhs[i] - m_alpha[i+1]*super_diagonal[i];
        }
        m_alpha[0] = m_alpha[2] + rhs[0];
    }

    Real operator()(Real t) const {
        if (t < m_t0 || t > m_t0 + (m_alpha.size()-2)/m_inv_h) {
            const char* err_msg = "Tried to evaluate the cardinal quadratic b-spline outside the domain of of interpolation; extrapolation does not work.";
            throw std::domain_error(err_msg);
        }
        // Let k, gamma be defined via t = t0 + kh + gamma * h.
        // Now find all j: |k-j+1+gamma|< 3/2, or, in other words
        // j_min = ceil((t-t0)/h - 1/2)
        // j_max = floor(t-t0)/h + 5/2)
        using std::floor;
        using std::ceil;
        Real x = (t-m_t0)*m_inv_h;
        size_t j_min = ceil(x - Real(1)/Real(2));
        size_t j_max = ceil(x + Real(5)/Real(2));
        if (j_max >= m_alpha.size()) {
            j_max = m_alpha.size() - 1;
        }

        Real y = 0;
        x += 1;
        for (size_t j = j_min; j <= j_max; ++j) {
            y += m_alpha[j]*detail::b2_spline(x - j);
        }
        return y;
    }

    Real prime(Real t) const {
        if (t < m_t0 || t > m_t0 + (m_alpha.size()-2)/m_inv_h) {
            const char* err_msg = "Tried to evaluate the cardinal quadratic b-spline outside the domain of of interpolation; extrapolation does not work.";
            throw std::domain_error(err_msg);
        }
        // Let k, gamma be defined via t = t0 + kh + gamma * h.
        // Now find all j: |k-j+1+gamma|< 3/2, or, in other words
        // j_min = ceil((t-t0)/h - 1/2)
        // j_max = floor(t-t0)/h + 5/2)
        using std::floor;
        using std::ceil;
        Real x = (t-m_t0)*m_inv_h;
        size_t j_min = ceil(x - Real(1)/Real(2));
        size_t j_max = ceil(x + Real(5)/Real(2));
        if (j_max >= m_alpha.size()) {
            j_max = m_alpha.size() - 1;
        }

        Real y = 0;
        x += 1;
        for (size_t j = j_min; j <= j_max; ++j) {
            y += m_alpha[j]*detail::b2_spline_prime(x - j);
        }
        return y*m_inv_h;
    }

    Real t_max() const {
        return m_t0 + (m_alpha.size()-3)/m_inv_h;
    }

private:
    std::vector<Real> m_alpha;
    Real m_inv_h;
    Real m_t0;
};

}}}}
#endif

/* cardinal_quadratic_b_spline_detail.hpp
+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
*/