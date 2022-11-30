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

    size_t k_min = static_cast<size_t>((max)(static_cast<long>(0), boost::math::ltrunc(ceil(t - 2))));
    size_t k_max = static_cast<size_t>((max)((min)(static_cast<long>(m_beta.size() - 1), boost::math::ltrunc(floor(t + 2))), 0l));
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

    size_t k_min = static_cast<size_t>((max)(static_cast<long>(0), boost::math::ltrunc(ceil(t - 2))));
    size_t k_max = static_cast<size_t>((min)(static_cast<long>(m_beta.size() - 1), boost::math::ltrunc(floor(t + 2))));

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

    size_t k_min = static_cast<size_t>((max)(static_cast<long>(0), boost::math::ltrunc(ceil(t - 2))));
    size_t k_max = static_cast<size_t>((min)(static_cast<long>(m_beta.size() - 1), boost::math::ltrunc(floor(t + 2))));

    for (size_t k = k_min; k <= k_max; ++k)
    {
        z += m_beta[k]*b3_spline_double_prime(t - k);
    }
    return z*m_h_inv*m_h_inv;
}


}}}
#endif

/* cubic_b_spline_detail.hpp
+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
*/