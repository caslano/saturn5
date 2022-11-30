//  Copyright (c) 2006 Xiaogang Zhang
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_BESSEL_KN_HPP
#define BOOST_MATH_BESSEL_KN_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/special_functions/detail/bessel_k0.hpp>
#include <boost/math/special_functions/detail/bessel_k1.hpp>
#include <boost/math/policies/error_handling.hpp>

// Modified Bessel function of the second kind of integer order
// K_n(z) is the dominant solution, forward recurrence always OK (though unstable)

namespace boost { namespace math { namespace detail{

template <typename T, typename Policy>
T bessel_kn(int n, T x, const Policy& pol)
{
    BOOST_MATH_STD_USING
    T value, current, prev;

    using namespace boost::math::tools;

    static const char* function = "boost::math::bessel_kn<%1%>(%1%,%1%)";

    if (x < 0)
    {
       return policies::raise_domain_error<T>(function,
            "Got x = %1%, but argument x must be non-negative, complex number result not supported.", x, pol);
    }
    if (x == 0)
    {
       return policies::raise_overflow_error<T>(function, 0, pol);
    }

    if (n < 0)
    {
        n = -n;                             // K_{-n}(z) = K_n(z)
    }
    if (n == 0)
    {
        value = bessel_k0(x);
    }
    else if (n == 1)
    {
        value = bessel_k1(x);
    }
    else
    {
       prev = bessel_k0(x);
       current = bessel_k1(x);
       int k = 1;
       BOOST_MATH_ASSERT(k < n);
       T scale = 1;
       do
       {
           T fact = 2 * k / x;
           if((tools::max_value<T>() - fabs(prev)) / fact < fabs(current))
           {
              scale /= current;
              prev /= current;
              current = 1;
           }
           value = fact * current + prev;
           prev = current;
           current = value;
           ++k;
       }
       while(k < n);
       if(tools::max_value<T>() * scale < fabs(value))
          return sign(scale) * sign(value) * policies::raise_overflow_error<T>(function, 0, pol);
       value /= scale;
    }
    return value;
}

}}} // namespaces

#endif // BOOST_MATH_BESSEL_KN_HPP


/* bessel_kn.hpp
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
*/