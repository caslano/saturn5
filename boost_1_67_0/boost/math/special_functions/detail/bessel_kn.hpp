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
       BOOST_ASSERT(k < n);
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