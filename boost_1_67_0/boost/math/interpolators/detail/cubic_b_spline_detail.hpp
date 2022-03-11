// Copyright Nick Thompson, 2017
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef CUBIC_B_SPLINE_DETAIL_HPP
#define CUBIC_B_SPLINE_DETAIL_HPP

#include <limits>
#include <cmath>
#include <vector>
#include <memory>
#include <boost/math/constants/constants.hpp>
#include <boost/math/special_functions/fpclassify.hpp>

namespace boost{ namespace math{ namespace detail{


template <class Real>
class cubic_b_spline_imp
{
public:
    // If you don't know the value of the derivative at the endpoints, leave them as nans and the routine will estimate them.
    // f[0] = f(a), f[length -1] = b, step_size = (b - a)/(length -1).
    template <class BidiIterator>
    cubic_b_spline_imp(BidiIterator f, BidiIterator end_p, Real left_endpoint, Real step_size,
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
cubic_b_spline_imp<Real>::cubic_b_spline_imp(BidiIterator f, BidiIterator end_p, Real left_endpoint, Real step_size,
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
Real cubic_b_spline_imp<Real>::operator()(Real x) const
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
Real cubic_b_spline_imp<Real>::prime(Real x) const
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
Real cubic_b_spline_imp<Real>::double_prime(Real x) const
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


}}}
#endif

/* cubic_b_spline_detail.hpp
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
*/