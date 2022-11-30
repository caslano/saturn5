//  Copyright (c) 2006 Xiaogang Zhang
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_BESSEL_YN_HPP
#define BOOST_MATH_BESSEL_YN_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/special_functions/detail/bessel_y0.hpp>
#include <boost/math/special_functions/detail/bessel_y1.hpp>
#include <boost/math/special_functions/detail/bessel_jy_series.hpp>
#include <boost/math/policies/error_handling.hpp>

// Bessel function of the second kind of integer order
// Y_n(z) is the dominant solution, forward recurrence always OK (though unstable)

namespace boost { namespace math { namespace detail{

template <typename T, typename Policy>
T bessel_yn(int n, T x, const Policy& pol)
{
    BOOST_MATH_STD_USING
    T value, factor, current, prev;

    using namespace boost::math::tools;

    static const char* function = "boost::math::bessel_yn<%1%>(%1%,%1%)";

    if ((x == 0) && (n == 0))
    {
       return -policies::raise_overflow_error<T>(function, 0, pol);
    }
    if (x <= 0)
    {
       return policies::raise_domain_error<T>(function,
            "Got x = %1%, but x must be > 0, complex result not supported.", x, pol);
    }

    //
    // Reflection comes first:
    //
    if (n < 0)
    {
        factor = static_cast<T>((n & 0x1) ? -1 : 1);  // Y_{-n}(z) = (-1)^n Y_n(z)
        n = -n;
    }
    else
    {
        factor = 1;
    }
    if(x < policies::get_epsilon<T, Policy>())
    {
       T scale = 1;
       value = bessel_yn_small_z(n, x, &scale, pol);
       if(tools::max_value<T>() * fabs(scale) < fabs(value))
          return boost::math::sign(scale) * boost::math::sign(value) * policies::raise_overflow_error<T>(function, 0, pol);
       value /= scale;
    }
    else if(asymptotic_bessel_large_x_limit(n, x))
    {
       value = factor * asymptotic_bessel_y_large_x_2(static_cast<T>(abs(n)), x, pol);
    }
    else if (n == 0)
    {
        value = bessel_y0(x, pol);
    }
    else if (n == 1)
    {
        value = factor * bessel_y1(x, pol);
    }
    else
    {
       prev = bessel_y0(x, pol);
       current = bessel_y1(x, pol);
       int k = 1;
       BOOST_MATH_ASSERT(k < n);
       policies::check_series_iterations<T>("boost::math::bessel_y_n<%1%>(%1%,%1%)", n, pol);
       T mult = 2 * k / x;
       value = mult * current - prev;
       prev = current;
       current = value;
       ++k;
       if((mult > 1) && (fabs(current) > 1))
       {
          prev /= current;
          factor /= current;
          value /= current;
          current = 1;
       }
       while(k < n)
       {
           mult = 2 * k / x;
           value = mult * current - prev;
           prev = current;
           current = value;
           ++k;
       }
       if(fabs(tools::max_value<T>() * factor) < fabs(value))
          return sign(value) * sign(factor) * policies::raise_overflow_error<T>(function, 0, pol);
       value /= factor;
    }
    return value;
}

}}} // namespaces

#endif // BOOST_MATH_BESSEL_YN_HPP


/* bessel_yn.hpp
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
*/