//  Copyright (c) 2006 Xiaogang Zhang
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_BESSEL_JN_HPP
#define BOOST_MATH_BESSEL_JN_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/special_functions/detail/bessel_j0.hpp>
#include <boost/math/special_functions/detail/bessel_j1.hpp>
#include <boost/math/special_functions/detail/bessel_jy.hpp>
#include <boost/math/special_functions/detail/bessel_jy_asym.hpp>
#include <boost/math/special_functions/detail/bessel_jy_series.hpp>

// Bessel function of the first kind of integer order
// J_n(z) is the minimal solution
// n < abs(z), forward recurrence stable and usable
// n >= abs(z), forward recurrence unstable, use Miller's algorithm

namespace boost { namespace math { namespace detail{

template <typename T, typename Policy>
T bessel_jn(int n, T x, const Policy& pol)
{
    T value(0), factor, current, prev, next;

    BOOST_MATH_STD_USING

    //
    // Reflection has to come first:
    //
    if (n < 0)
    {
        factor = static_cast<T>((n & 0x1) ? -1 : 1);  // J_{-n}(z) = (-1)^n J_n(z)
        n = -n;
    }
    else
    {
        factor = 1;
    }
    if(x < 0)
    {
        factor *= (n & 0x1) ? -1 : 1;  // J_{n}(-z) = (-1)^n J_n(z)
        x = -x;
    }
    //
    // Special cases:
    //
    if(asymptotic_bessel_large_x_limit(T(n), x))
       return factor * asymptotic_bessel_j_large_x_2<T>(T(n), x, pol);
    if (n == 0)
    {
        return factor * bessel_j0(x);
    }
    if (n == 1)
    {
        return factor * bessel_j1(x);
    }

    if (x == 0)                             // n >= 2
    {
        return static_cast<T>(0);
    }

    BOOST_MATH_ASSERT(n > 1);
    T scale = 1;
    if (n < abs(x))                         // forward recurrence
    {
        prev = bessel_j0(x);
        current = bessel_j1(x);
        policies::check_series_iterations<T>("boost::math::bessel_j_n<%1%>(%1%,%1%)", n, pol);
        for (int k = 1; k < n; k++)
        {
            T fact = 2 * k / x;
            //
            // rescale if we would overflow or underflow:
            //
            if((fabs(fact) > 1) && ((tools::max_value<T>() - fabs(prev)) / fabs(fact) < fabs(current)))
            {
               scale /= current;
               prev /= current;
               current = 1;
            }
            value = fact * current - prev;
            prev = current;
            current = value;
        }
    }
    else if((x < 1) || (n > x * x / 4) || (x < 5))
    {
       return factor * bessel_j_small_z_series(T(n), x, pol);
    }
    else                                    // backward recurrence
    {
        T fn; int s;                        // fn = J_(n+1) / J_n
        // |x| <= n, fast convergence for continued fraction CF1
        boost::math::detail::CF1_jy(static_cast<T>(n), x, &fn, &s, pol);
        prev = fn;
        current = 1;
        // Check recursion won't go on too far:
        policies::check_series_iterations<T>("boost::math::bessel_j_n<%1%>(%1%,%1%)", n, pol);
        for (int k = n; k > 0; k--)
        {
            T fact = 2 * k / x;
            if((fabs(fact) > 1) && ((tools::max_value<T>() - fabs(prev)) / fabs(fact) < fabs(current)))
            {
               prev /= current;
               scale /= current;
               current = 1;
            }
            next = fact * current - prev;
            prev = current;
            current = next;
        }
        value = bessel_j0(x) / current;       // normalization
        scale = 1 / scale;
    }
    value *= factor;

    if(tools::max_value<T>() * scale < fabs(value))
       return policies::raise_overflow_error<T>("boost::math::bessel_jn<%1%>(%1%,%1%)", 0, pol);

    return value / scale;
}

}}} // namespaces

#endif // BOOST_MATH_BESSEL_JN_HPP


/* bessel_jn.hpp
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
*/