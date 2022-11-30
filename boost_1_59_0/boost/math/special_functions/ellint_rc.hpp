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
          result = (boost::math::log1p(arg, pol) - boost::math::log1p(-arg, pol)) / (2 * sqrt(x - y));
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