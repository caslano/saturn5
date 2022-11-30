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
    return static_cast<Real>(0);
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
    return static_cast<Real>(0);
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
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
*/