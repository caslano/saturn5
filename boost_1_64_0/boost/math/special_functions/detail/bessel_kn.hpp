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
oPag+ETU4igB1dR00t8hZNdKljVqbkUgZKlh3jDN56Cj+UZIT62z+FQwL0hYnWk5i7SSGJnLEPsoTXu9t42ny1WZI1RmuLn/aLA8bA4OjKVvpd94ooPF+XeOSqy8XDfTol/Y1q3LxHdY0l1/LrPM3bFJFlqkJfr7sWXvS30XID1IzFcYPDvLXM8DmwuoxDbajnovsvqmaV2xiJ8OLsz8OgbUn70wVQ7bPXX7ELDGBb4mUEcGBK5W9ns/VA2PnMW5qd/KSGnGwxJxa/sGOb4kDoiOS8AaCOab4VQkABgS5wQnXpf16wMzuCrQRMTx0KJstQF+VRB4YvAx1t+ekgdp3EDKeEdUaxX9r60SVptc9jHZd4H54P5gt+kFMJxFhEoSLueTuQxZbE5RuULaj3RCn4TbltnYLK/LJajdsAe+q+EHKTQJ9pt4KUO7QofRfF5ZkennSCiRc9pstZiHlA462ZQIF4tJfoksVOhQTbLQX77GMk65mOQYlLSInjGi3KjOz3r5AK9GrQ7DxNIKRBvcGas87/VoKbL/uS5oVsMSxakF7Tu8EF++n+qmPw==
*/