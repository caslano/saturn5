// Copyright Nick Thompson, 2017
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_INTERPOLATORS_CARDINAL_CUBIC_B_SPLINE_DETAIL_HPP
#define BOOST_MATH_INTERPOLATORS_CARDINAL_CUBIC_B_SPLINE_DETAIL_HPP

#include <limits>
#include <cmath>
#include <vector>
#include <memory>
#include <boost/math/constants/constants.hpp>
#include <boost/math/special_functions/fpclassify.hpp>
#include <boost/math/special_functions/trunc.hpp>

namespace boost{ namespace math{ namespace interpolators{ namespace detail{


template <class Real>
class cardinal_cubic_b_spline_imp
{
public:
    // If you don't know the value of the derivative at the endpoints, leave them as nans and the routine will estimate them.
    // f[0] = f(a), f[length -1] = b, step_size = (b - a)/(length -1).
    template <class BidiIterator>
    cardinal_cubic_b_spline_imp(BidiIterator f, BidiIterator end_p, Real left_endpoint, Real step_size,
                       Real left_endpoint_derivative = std::numeric_limits<Real>::quiet_NaN(),
                       Real right_endpoint_derivative = std::numeric_limits<Real>::quiet_NaN());

    Real operator()(Real x) const;

    Real prime(Real x) const;

    Real double_prime(Real x) const;

private:
    std::vector<Real> m_beta;
    Real m_h_inv;
    Real m_a;
    Real m_avg;
};



template <class Real>
Real b3_spline(Real x)
{
    using std::abs;
    Real absx = abs(x);
    if (absx < 1)
    {
        Real y = 2 - absx;
        Real z = 1 - absx;
        return boost::math::constants::sixth<Real>()*(y*y*y - 4*z*z*z);
    }
    if (absx < 2)
    {
        Real y = 2 - absx;
        return boost::math::constants::sixth<Real>()*y*y*y;
    }
    return static_cast<Real>(0);
}

template<class Real>
Real b3_spline_prime(Real x)
{
    if (x < 0)
    {
        return -b3_spline_prime(-x);
    }

    if (x < 1)
    {
        return x*(3*boost::math::constants::half<Real>()*x - 2);
    }
    if (x < 2)
    {
        return -boost::math::constants::half<Real>()*(2 - x)*(2 - x);
    }
    return static_cast<Real>(0);
}

template<class Real>
Real b3_spline_double_prime(Real x)
{
    if (x < 0)
    {
        return b3_spline_double_prime(-x);
    }

    if (x < 1)
    {
        return 3*x - 2;
    }
    if (x < 2)
    {
        return (2 - x);
    }
    return static_cast<Real>(0);
}


template <class Real>
template <class BidiIterator>
cardinal_cubic_b_spline_imp<Real>::cardinal_cubic_b_spline_imp(BidiIterator f, BidiIterator end_p, Real left_endpoint, Real step_size,
                                             Real left_endpoint_derivative, Real right_endpoint_derivative) : m_a(left_endpoint), m_avg(0)
{
    using boost::math::constants::third;

    std::size_t length = end_p - f;

    if (length < 5)
    {
        if (boost::math::isnan(left_endpoint_derivative) || boost::math::isnan(right_endpoint_derivative))
        {
            throw std::logic_error("Interpolation using a cubic b spline with derivatives estimated at the endpoints requires at least 5 points.\n");
        }
        if (length < 3)
        {
            throw std::logic_error("Interpolation using a cubic b spline requires at least 3 points.\n");
        }
    }

    if (boost::math::isnan(left_endpoint))
    {
        throw std::logic_error("Left endpoint is NAN; this is disallowed.\n");
    }
    if (left_endpoint + length*step_size >= (std::numeric_limits<Real>::max)())
    {
        throw std::logic_error("Right endpoint overflows the maximum representable number of the specified precision.\n");
    }
    if (step_size <= 0)
    {
        throw std::logic_error("The step size must be strictly > 0.\n");
    }
    // Storing the inverse of the stepsize does provide a measurable speedup.
    // It's not huge, but nonetheless worthwhile.
    m_h_inv = 1/step_size;

    // Following Kress's notation, s'(a) = a1, s'(b) = b1
    Real a1 = left_endpoint_derivative;
    // See the finite-difference table on Wikipedia for reference on how
    // to construct high-order estimates for one-sided derivatives:
    // https://en.wikipedia.org/wiki/Finite_difference_coefficient#Forward_and_backward_finite_difference
    // Here, we estimate then to O(h^4), as that is the maximum accuracy we could obtain from this method.
    if (boost::math::isnan(a1))
    {
        // For simple functions (linear, quadratic, so on)
        // almost all the error comes from derivative estimation.
        // This does pairwise summation which gives us another digit of accuracy over naive summation.
        Real t0 = 4*(f[1] + third<Real>()*f[3]);
        Real t1 = -(25*third<Real>()*f[0] + f[4])/4  - 3*f[2];
        a1 = m_h_inv*(t0 + t1);
    }

    Real b1 = right_endpoint_derivative;
    if (boost::math::isnan(b1))
    {
        size_t n = length - 1;
        Real t0 = 4*(f[n-3] + third<Real>()*f[n - 1]);
        Real t1 = -(25*third<Real>()*f[n - 4] + f[n])/4  - 3*f[n - 2];

        b1 = m_h_inv*(t0 + t1);
    }

    // s(x) = \sum \alpha_i B_{3}( (x- x_i - a)/h )
    // Of course we must reindex from Kress's notation, since he uses negative indices which make C++ unhappy.
    m_beta.resize(length + 2, std::numeric_limits<Real>::quiet_NaN());

    // Since the splines have compact support, they decay to zero very fast outside the endpoints.
    // This is often very annoying; we'd like to evaluate the interpolant a little bit outside the
    // boundary [a,b] without massive error.
    // A simple way to deal with this is just to subtract the DC component off the signal, so we need the average.
    // This algorithm for computing the average is recommended in
    // http://www.heikohoffmann.de/htmlthesis/node134.html
    Real t = 1;
    for (size_t i = 0; i < length; ++i)
    {
        if (boost::math::isnan(f[i]))
        {
            std::string err = "This function you are trying to interpolate is a nan at index " + std::to_string(i) + "\n";
            throw std::logic_error(err);
        }
        m_avg += (f[i] - m_avg) / t;
        t += 1;
    }


    // Now we must solve an almost-tridiagonal system, which requires O(N) operations.
    // There are, in fact 5 diagonals, but they only differ from zero on the first and last row,
    // so we can patch up the tridiagonal row reduction algorithm to deal with two special rows.
    // See Kress, equations 8.41
    // The the "tridiagonal" matrix is:
    // 1  0 -1
    // 1  4  1
    //    1  4  1
    //       1  4  1
    //          ....
    //          1  4  1
    //          1  0 -1
    // Numerical estimate indicate that as N->Infinity, cond(A) -> 6.9, so this matrix is good.
    std::vector<Real> rhs(length + 2, std::numeric_limits<Real>::quiet_NaN());
    std::vector<Real> super_diagonal(length + 2, std::numeric_limits<Real>::quiet_NaN());

    rhs[0] = -2*step_size*a1;
    rhs[rhs.size() - 1] = -2*step_size*b1;

    super_diagonal[0] = 0;

    for(size_t i = 1; i < rhs.size() - 1; ++i)
    {
        rhs[i] = 6*(f[i - 1] - m_avg);
        super_diagonal[i] = 1;
    }


    // One step of row reduction on the first row to patch up the 5-diagonal problem:
    // 1 0 -1 | r0
    // 1 4 1  | r1
    // mapsto:
    // 1 0 -1 | r0
    // 0 4 2  | r1 - r0
    // mapsto
    // 1 0 -1 | r0
    // 0 1 1/2| (r1 - r0)/4
    super_diagonal[1] = 0.5;
    rhs[1] = (rhs[1] - rhs[0])/4;

    // Now do a tridiagonal row reduction the standard way, until just before the last row:
    for (size_t i = 2; i < rhs.size() - 1; ++i)
    {
        Real diagonal = 4 - super_diagonal[i - 1];
        rhs[i] = (rhs[i] - rhs[i - 1])/diagonal;
        super_diagonal[i] /= diagonal;
    }

    // Now the last row, which is in the form
    // 1 sd[n-3] 0      | rhs[n-3]
    // 0  1     sd[n-2] | rhs[n-2]
    // 1  0     -1      | rhs[n-1]
    Real final_subdiag = -super_diagonal[rhs.size() - 3];
    rhs[rhs.size() - 1] = (rhs[rhs.size() - 1] - rhs[rhs.size() - 3])/final_subdiag;
    Real final_diag = -1/final_subdiag;
    // Now we're here:
    // 1 sd[n-3] 0         | rhs[n-3]
    // 0  1     sd[n-2]    | rhs[n-2]
    // 0  1     final_diag | (rhs[n-1] - rhs[n-3])/diag

    final_diag = final_diag - super_diagonal[rhs.size() - 2];
    rhs[rhs.size() - 1] = rhs[rhs.size() - 1] - rhs[rhs.size() - 2];


    // Back substitutions:
    m_beta[rhs.size() - 1] = rhs[rhs.size() - 1]/final_diag;
    for(size_t i = rhs.size() - 2; i > 0; --i)
    {
        m_beta[i] = rhs[i] - super_diagonal[i]*m_beta[i + 1];
    }
    m_beta[0] = m_beta[2] + rhs[0];
}

template<class Real>
Real cardinal_cubic_b_spline_imp<Real>::operator()(Real x) const
{
    // See Kress, 8.40: Since B3 has compact support, we don't have to sum over all terms,
    // just the (at most 5) whose support overlaps the argument.
    Real z = m_avg;
    Real t = m_h_inv*(x - m_a) + 1;

    using std::max;
    using std::min;
    using std::ceil;
    using std::floor;

    size_t k_min = static_cast<size_t>((max)(static_cast<long>(0), boost::math::ltrunc(ceil(t - 2))));
    size_t k_max = static_cast<size_t>((max)((min)(static_cast<long>(m_beta.size() - 1), boost::math::ltrunc(floor(t + 2))), 0l));

    for (size_t k = k_min; k <= k_max; ++k)
    {
        z += m_beta[k]*b3_spline(t - k);
    }

    return z;
}

template<class Real>
Real cardinal_cubic_b_spline_imp<Real>::prime(Real x) const
{
    Real z = 0;
    Real t = m_h_inv*(x - m_a) + 1;

    using std::max;
    using std::min;
    using std::ceil;
    using std::floor;

    size_t k_min = static_cast<size_t>((max)(static_cast<long>(0), boost::math::ltrunc(ceil(t - 2))));
    size_t k_max = static_cast<size_t>((min)(static_cast<long>(m_beta.size() - 1), boost::math::ltrunc(floor(t + 2))));

    for (size_t k = k_min; k <= k_max; ++k)
    {
        z += m_beta[k]*b3_spline_prime(t - k);
    }
    return z*m_h_inv;
}

template<class Real>
Real cardinal_cubic_b_spline_imp<Real>::double_prime(Real x) const
{
    Real z = 0;
    Real t = m_h_inv*(x - m_a) + 1;

    using std::max;
    using std::min;
    using std::ceil;
    using std::floor;

    size_t k_min = static_cast<size_t>((max)(static_cast<long>(0), boost::math::ltrunc(ceil(t - 2))));
    size_t k_max = static_cast<size_t>((min)(static_cast<long>(m_beta.size() - 1), boost::math::ltrunc(floor(t + 2))));

    for (size_t k = k_min; k <= k_max; ++k)
    {
        z += m_beta[k]*b3_spline_double_prime(t - k);
    }
    return z*m_h_inv*m_h_inv;
}

}}}}
#endif

/* cardinal_cubic_b_spline_detail.hpp
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
*/