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
       return factor * asymptotic_bessel_j_large_x_2<T>(T(n), x);
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

    BOOST_ASSERT(n > 1);
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