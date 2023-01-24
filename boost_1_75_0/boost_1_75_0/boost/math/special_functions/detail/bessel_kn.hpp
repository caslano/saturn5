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
TVr1snlG0Gh+hNc9NWbys3h66lngilsmq2xL7vwPV0LKFk4G1ABSEJWyhTPxiA/uyNNBQ0vptxMH72A+9w7JUpd2cbGsmS0mbGiDWNbJFsti2naQWNYFa6J6ylH3GqeB3zXrd12D81HnBpybZsSE12kPzJwYVnbR88n0maMnnbFGjAV+5TP7ieUBc/9J0kMqYj2zWy/ple8NM9+APssXHA95fUZUVuf3HAMFyq4+5q0T57KrMm9fZdHWIvx0SKR4brR6JDANFGSoZGJ827M6vP1kJNm2j7PFKw9cwgE+qHUxMxTLODnimd/cLCHjL+3tD0q/k4Y9vBRxvPLTrLxY+uVUbYzsN28zAeoQ5QW3LIRJGxAYC045hkhrgRRUrMcFo6cjJ1T+sFytB3Us2uCfCj7qMmkNbJgTYRNhGY49/A9850lr8R/Nec63Gd+/5seB2ByqiOwW2PBCqO0wGIaSjYM0f1ywfWdYNhxmHBJok5rGR2mwaGvdp6Td6pG/fsaayqmD5D0gABQ7IrhMRtb7tSKf6WDdiOxGmFuGNwZSTGKBgZRsV1v3WaeCazGecX4/+fpGRLgA+PGL0YyThVSLcDPce2e0WtMeI7U3HCpkQxQ5ChB8I9SuWDfZMo8dBViVpGF9/oAU7Wj2cFbCU67G7hzF2Sv8GgSOibtJJYKvQ/PLfCsv+DNLG13+v9sESbnPh5210Mr1KJSc2vOh
*/