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
    return (Real) 0;
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
    return (Real) 0;
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
    return (Real) 0;
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

    size_t k_min = (size_t) (max)(static_cast<long>(0), boost::math::ltrunc(ceil(t - 2)));
    size_t k_max = (size_t) (max)((min)(static_cast<long>(m_beta.size() - 1), boost::math::ltrunc(floor(t + 2))), (long) 0);

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

    size_t k_min = (size_t) (max)(static_cast<long>(0), boost::math::ltrunc(ceil(t - 2)));
    size_t k_max = (size_t) (min)(static_cast<long>(m_beta.size() - 1), boost::math::ltrunc(floor(t + 2)));

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

    size_t k_min = (size_t) (max)(static_cast<long>(0), boost::math::ltrunc(ceil(t - 2)));
    size_t k_max = (size_t) (min)(static_cast<long>(m_beta.size() - 1), boost::math::ltrunc(floor(t + 2)));

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