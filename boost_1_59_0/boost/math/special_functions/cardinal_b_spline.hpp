//  (C) Copyright Nick Thompson 2019.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_SPECIAL_CARDINAL_B_SPLINE_HPP
#define BOOST_MATH_SPECIAL_CARDINAL_B_SPLINE_HPP

#include <array>
#include <cmath>
#include <limits>
#include <type_traits>

namespace boost { namespace math {

namespace detail {

  template<class Real>
  inline Real B1(Real x)
  {
    if (x < 0)
    {
      return B1(-x);
    }
    if (x < Real(1))
    {
      return 1 - x;
    }
    return Real(0);
  }
}

template<unsigned n, typename Real>
Real cardinal_b_spline(Real x) {
    static_assert(!std::is_integral<Real>::value, "Does not work with integral types.");

    if (x < 0) {
        // All B-splines are even functions:
        return cardinal_b_spline<n, Real>(-x);
    }

    if  (n==0)
    {
        if (x < Real(1)/Real(2)) {
            return Real(1);
        }
        else if (x == Real(1)/Real(2)) {
            return Real(1)/Real(2);
        }
        else {
            return Real(0);
        }
    }

    if (n==1)
    {
        return detail::B1(x);
    }

    Real supp_max = (n+1)/Real(2);
    if (x >= supp_max)
    {
        return Real(0);
    }

    // Fill v with values of B1:
    // At most two of these terms are nonzero, and at least 1.
    // There is only one non-zero term when n is odd and x = 0.
    std::array<Real, n> v;
    Real z = x + 1 - supp_max;
    for (unsigned i = 0; i < n; ++i)
    {
        v[i] = detail::B1(z);
        z += 1;
    }

    Real smx = supp_max - x;
    for (unsigned j = 2; j <= n; ++j)
    {
        Real a = (j + 1 - smx);
        Real b = smx;
        for(unsigned k = 0; k <= n - j; ++k)
        {
            v[k] = (a*v[k+1] + b*v[k])/Real(j);
            a += 1;
            b -= 1;
        }
    }

    return v[0];
}


template<unsigned n, typename Real>
Real cardinal_b_spline_prime(Real x)
{
    static_assert(!std::is_integral<Real>::value, "Cardinal B-splines do not work with integer types.");

    if (x < 0)
    {
        // All B-splines are even functions, so derivatives are odd:
        return -cardinal_b_spline_prime<n, Real>(-x);
    }


    if (n==0)
    {
        // Kinda crazy but you get what you ask for!
        if (x == Real(1)/Real(2))
        {
            return std::numeric_limits<Real>::infinity();
        }
        else
        {
            return Real(0);
        }
    }

    if (n==1)
    {
        if (x==0)
        {
            return Real(0);
        }
        if (x==1)
        {
            return -Real(1)/Real(2);
        }
        return Real(-1);
    }


    Real supp_max = (n+1)/Real(2);
    if (x >= supp_max)
    {
        return Real(0);
    }

    // Now we want to evaluate B_{n}(x), but stop at the second to last step and collect B_{n-1}(x+1/2) and B_{n-1}(x-1/2):
    std::array<Real, n> v;
    Real z = x + 1 - supp_max;
    for (unsigned i = 0; i < n; ++i)
    {
        v[i] = detail::B1(z);
        z += 1;
    }

    Real smx = supp_max - x;
    for (unsigned j = 2; j <= n - 1; ++j)
    {
        Real a = (j + 1 - smx);
        Real b = smx;
        for(unsigned k = 0; k <= n - j; ++k)
        {
            v[k] = (a*v[k+1] + b*v[k])/Real(j);
            a += 1;
            b -= 1;
        }
    }

    return v[1] - v[0];
}


template<unsigned n, typename Real>
Real cardinal_b_spline_double_prime(Real x)
{
    static_assert(!std::is_integral<Real>::value, "Cardinal B-splines do not work with integer types.");
    static_assert(n >= 3, "n>=3 for second derivatives of cardinal B-splines is required.");

    if (x < 0)
    {
        // All B-splines are even functions, so second derivatives are even:
        return cardinal_b_spline_double_prime<n, Real>(-x);
    }


    Real supp_max = (n+1)/Real(2);
    if (x >= supp_max)
    {
        return Real(0);
    }

    // Now we want to evaluate B_{n}(x), but stop at the second to last step and collect B_{n-1}(x+1/2) and B_{n-1}(x-1/2):
    std::array<Real, n> v;
    Real z = x + 1 - supp_max;
    for (unsigned i = 0; i < n; ++i)
    {
        v[i] = detail::B1(z);
        z += 1;
    }

    Real smx = supp_max - x;
    for (unsigned j = 2; j <= n - 2; ++j)
    {
        Real a = (j + 1 - smx);
        Real b = smx;
        for(unsigned k = 0; k <= n - j; ++k)
        {
            v[k] = (a*v[k+1] + b*v[k])/Real(j);
            a += 1;
            b -= 1;
        }
    }

    return v[2] - 2*v[1] + v[0];
}


template<unsigned n, class Real>
Real forward_cardinal_b_spline(Real x)
{
    static_assert(!std::is_integral<Real>::value, "Cardinal B-splines do not work with integral types.");
    return cardinal_b_spline<n>(x - (n+1)/Real(2));
}

}}
#endif

/* cardinal_b_spline.hpp
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
*/