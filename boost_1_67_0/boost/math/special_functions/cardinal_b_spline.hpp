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