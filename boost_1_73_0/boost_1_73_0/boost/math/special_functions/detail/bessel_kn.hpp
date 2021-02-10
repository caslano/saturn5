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
K33KeGLILmUbUB0iQMKENgiR1wd/36c+kMqMB/ejte9/7Q9WjcFonY65m/j21jrCfbEtzVHD9Vohk7wqI5pJj1MeZxNGsMxWrBEzbAVTscjDesVHsqycIQ+LBk9UYrPHBqj5DIGut1BIYm0G+LZaOMVqCblpsMpxA/5B65lBBDaqHNNjMKxJULfBex7ObFyrQPla2Q2nfXtY//apyd8g4vAG6/vUhtQ9epFxOxQ7qL9O32fErnp3t8BxSXg/oOD9yOzboNxjkRtCayIafjvLbrj6C3e8k0pTYQjv8ZaGnF2W+TIzuql2t+GudbUp6m0bWts5d1uWrfNWFnlVmO5Gf9zVe5Pc0R1vmetLxGDDemvcKR96FPYjt0/JNisdrlmEG4xtG9p2OFv0Fn3L0szJFjL1xvcJuM8lrra2uITtPn9zNcafe+xkx8Rme5vgHgx7XYfY2eGpi+bAE3ceT4u6WRxuyDXBqPvL+1H31/1RN2CeYN2mHUc2QVBGE6mHNRp+25NeSxfMENIwz+rjRVvVRi01TiSQuVM5Y0XntjRxyc4Oo4ALgQK7FjPs2HDYmcfhaD+RNb7a2B7L3NlpGOVCvEXKtmi6ipINhrxusL9abPYDyG4tK3KkaD2xOdOi4axu0wiEFg0voQNeK6v3
*/