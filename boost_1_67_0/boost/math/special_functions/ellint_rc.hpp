//  Copyright (c) 2006 Xiaogang Zhang, 2015 John Maddock
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  History:
//  XZ wrote the original of this file as part of the Google
//  Summer of Code 2006.  JM modified it to fit into the
//  Boost.Math conceptual framework better, and to correctly
//  handle the y < 0 case.
//  Updated 2015 to use Carlson's latest methods.
//

#ifndef BOOST_MATH_ELLINT_RC_HPP
#define BOOST_MATH_ELLINT_RC_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/policies/error_handling.hpp>
#include <boost/math/tools/config.hpp>
#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/special_functions/log1p.hpp>
#include <boost/math/constants/constants.hpp>
#include <iostream>

// Carlson's degenerate elliptic integral
// R_C(x, y) = R_F(x, y, y) = 0.5 * \int_{0}^{\infty} (t+x)^{-1/2} (t+y)^{-1} dt
// Carlson, Numerische Mathematik, vol 33, 1 (1979)

namespace boost { namespace math { namespace detail{

template <typename T, typename Policy>
T ellint_rc_imp(T x, T y, const Policy& pol)
{
    BOOST_MATH_STD_USING

    static const char* function = "boost::math::ellint_rc<%1%>(%1%,%1%)";

    if(x < 0)
    {
       return policies::raise_domain_error<T>(function,
            "Argument x must be non-negative but got %1%", x, pol);
    }
    if(y == 0)
    {
       return policies::raise_domain_error<T>(function,
            "Argument y must not be zero but got %1%", y, pol);
    }

    // for y < 0, the integral is singular, return Cauchy principal value
    T prefix, result;
    if(y < 0)
    {
        prefix = sqrt(x / (x - y));
        x = x - y;
        y = -y;
    }
    else
       prefix = 1;

    if(x == 0)
    {
       result = constants::half_pi<T>() / sqrt(y);
    }
    else if(x == y)
    {
       result = 1 / sqrt(x);
    }
    else if(y > x)
    {
       result = atan(sqrt((y - x) / x)) / sqrt(y - x);
    }
    else
    {
       if(y / x > 0.5)
       {
          T arg = sqrt((x - y) / x);
          result = (boost::math::log1p(arg) - boost::math::log1p(-arg)) / (2 * sqrt(x - y));
       }
       else
       {
          result = log((sqrt(x) + sqrt(x - y)) / sqrt(y)) / sqrt(x - y);
       }
    }
    return prefix * result;
}

} // namespace detail

template <class T1, class T2, class Policy>
inline typename tools::promote_args<T1, T2>::type 
   ellint_rc(T1 x, T2 y, const Policy& pol)
{
   typedef typename tools::promote_args<T1, T2>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   return policies::checked_narrowing_cast<result_type, Policy>(
      detail::ellint_rc_imp(
         static_cast<value_type>(x),
         static_cast<value_type>(y), pol), "boost::math::ellint_rc<%1%>(%1%,%1%)");
}

template <class T1, class T2>
inline typename tools::promote_args<T1, T2>::type 
   ellint_rc(T1 x, T2 y)
{
   return ellint_rc(x, y, policies::policy<>());
}

}} // namespaces

#endif // BOOST_MATH_ELLINT_RC_HPP


/* ellint_rc.hpp
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
*/