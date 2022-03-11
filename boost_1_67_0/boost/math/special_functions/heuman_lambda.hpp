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