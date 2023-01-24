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
GX7r/P5gtMFnefzeei5o0cylJf89sC+pfKgpC9HspZLz1mqYo4HS/gvYn/ER0UqUWj7scx13T7Du8vLO7hHz+nJXYohTjI8uINzoMoLm8ZHZb5lRPNwKVboLr/ewkwXjO43Rj6wY1ftaAsa95OvPBfUU1tKpAq+Tv7NwEWfs3kgW6jrt7cb7C+yhgpZm5JtZlCBH5a/xd/J5+yJv9HPxczVYPnC6EfgJiDD6C1hE66Ptk+BvopVuZ1U5j73XSBXYvY8lRNGLZl5xgXifKClMFfE1/+QPxgkUlvw4+3aWedb7a5QdSbHNV2zw26/4Y4FT5AnWcmsYOZ6FEUeT0TI+eG6c5+UUwkpWTAqECT4YFUYlSVCLDrn0isST/rnXcd07q9J1pkZGhI4RAsOh9x2/GWqjScHn2bv2DUCedMOiOO0FtHWl+HkKjK+k5EV/icmPHhP7xOUxJrNNzDK9uS8JVMWQp5M/YFU4YEpEjHX2J/CKXG1Ns3SE8x8Xu3746E4LeAdGNip42xG6ntqcRzFr8ASmCmOO83t9/67P5+A3fzych/MwEBjSftItKfugZ1Pg7iZxXrK1X65tU44n9mkUjJJb5sor+SWFIfxFo7qgxY3yvGD0V2YwVNBdnZC8tPz4m7AinFduMKUUJz52sryyFMA7dzdfPCRbp5SeYGurGkEYdXXG8MytPOcLFftKflc1H+GFrlZlzxLI9zZj
*/