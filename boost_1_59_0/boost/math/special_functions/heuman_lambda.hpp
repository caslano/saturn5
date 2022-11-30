//  Copyright (c) 2015 John Maddock
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_ELLINT_HL_HPP
#define BOOST_MATH_ELLINT_HL_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/special_functions/ellint_rj.hpp>
#include <boost/math/special_functions/ellint_rj.hpp>
#include <boost/math/special_functions/ellint_1.hpp>
#include <boost/math/special_functions/jacobi_zeta.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/math/policies/error_handling.hpp>
#include <boost/math/tools/workaround.hpp>

// Elliptic integral the Jacobi Zeta function.

namespace boost { namespace math { 
   
namespace detail{

// Elliptic integral - Jacobi Zeta
template <typename T, typename Policy>
T heuman_lambda_imp(T phi, T k, const Policy& pol)
{
    BOOST_MATH_STD_USING
    using namespace boost::math::tools;
    using namespace boost::math::constants;

    const char* function = "boost::math::heuman_lambda<%1%>(%1%, %1%)";

    if(fabs(k) > 1)
       return policies::raise_domain_error<T>(function, "We require |k| <= 1 but got k = %1%", k, pol);

    T result;
    T sinp = sin(phi);
    T cosp = cos(phi);
    T s2 = sinp * sinp;
    T k2 = k * k;
    T kp = 1 - k2;
    T delta = sqrt(1 - (kp * s2));
    if(fabs(phi) <= constants::half_pi<T>())
    {
       result = kp * sinp * cosp / (delta * constants::half_pi<T>());
       result *= ellint_rf_imp(T(0), kp, T(1), pol) + k2 * ellint_rj(T(0), kp, T(1), T(1 - k2 / (delta * delta)), pol) / (3 * delta * delta);
    }
    else
    {
       T rkp = sqrt(kp);
       T ratio;
       if(rkp == 1)
       {
          return policies::raise_domain_error<T>(function, "When 1-k^2 == 1 then phi must be < Pi/2, but got phi = %1%", phi, pol);
       }
       else
          ratio = ellint_f_imp(phi, rkp, pol) / ellint_k_imp(rkp, pol);
       result = ratio + ellint_k_imp(k, pol) * jacobi_zeta_imp(phi, rkp, pol) / constants::half_pi<T>();
    }
    return result;
}

} // detail

template <class T1, class T2, class Policy>
inline typename tools::promote_args<T1, T2>::type heuman_lambda(T1 k, T2 phi, const Policy& pol)
{
   typedef typename tools::promote_args<T1, T2>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   return policies::checked_narrowing_cast<result_type, Policy>(detail::heuman_lambda_imp(static_cast<value_type>(phi), static_cast<value_type>(k), pol), "boost::math::heuman_lambda<%1%>(%1%,%1%)");
}

template <class T1, class T2>
inline typename tools::promote_args<T1, T2>::type heuman_lambda(T1 k, T2 phi)
{
   return boost::math::heuman_lambda(k, phi, policies::policy<>());
}

}} // namespaces

#endif // BOOST_MATH_ELLINT_D_HPP


/* heuman_lambda.hpp
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
*/