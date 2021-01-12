//  Copyright (c) 2015 John Maddock
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_MATH_ELLINT_JZ_HPP
#define BOOST_MATH_ELLINT_JZ_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/special_functions/ellint_1.hpp>
#include <boost/math/special_functions/ellint_rj.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/math/policies/error_handling.hpp>
#include <boost/math/tools/workaround.hpp>

// Elliptic integral the Jacobi Zeta function.

namespace boost { namespace math { 
   
namespace detail{

// Elliptic integral - Jacobi Zeta
template <typename T, typename Policy>
T jacobi_zeta_imp(T phi, T k, const Policy& pol)
{
    BOOST_MATH_STD_USING
    using namespace boost::math::tools;
    using namespace boost::math::constants;

    bool invert = false;
    if(phi < 0)
    {
       phi = fabs(phi);
       invert = true;
    }

    T result;
    T sinp = sin(phi);
    T cosp = cos(phi);
    T s2 = sinp * sinp;
    T k2 = k * k;
    T kp = 1 - k2;
    if(k == 1)
       result = sinp * (boost::math::sign)(cosp);  // We get here by simplifying JacobiZeta[w, 1] in Mathematica, and the fact that 0 <= phi.
    else
       result = k2 * sinp * cosp * sqrt(1 - k2 * s2) * ellint_rj_imp(T(0), kp, T(1), T(1 - k2 * s2), pol) / (3 * ellint_k_imp(k, pol));
    return invert ? T(-result) : result;
}

} // detail

template <class T1, class T2, class Policy>
inline typename tools::promote_args<T1, T2>::type jacobi_zeta(T1 k, T2 phi, const Policy& pol)
{
   typedef typename tools::promote_args<T1, T2>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   return policies::checked_narrowing_cast<result_type, Policy>(detail::jacobi_zeta_imp(static_cast<value_type>(phi), static_cast<value_type>(k), pol), "boost::math::jacobi_zeta<%1%>(%1%,%1%)");
}

template <class T1, class T2>
inline typename tools::promote_args<T1, T2>::type jacobi_zeta(T1 k, T2 phi)
{
   return boost::math::jacobi_zeta(k, phi, policies::policy<>());
}

}} // namespaces

#endif // BOOST_MATH_ELLINT_D_HPP


/* jacobi_zeta.hpp
wy34XERdVx3znEyfe52q516Vbur85/jnJn/3GzN9yHgyncwl55CF5BpyK7mLND5bG5+lfcj2ZDAZQcaRZnISmU/K51v57ZLqz7OVpPG5VT6vko7PoFYyj3T1mfMAWUnKZ0zH50sdOnTo0KFDhw4dOnTo+N/DkxxXn+f/nPzX1bn/IX3ur8/99bm/Dh06dOjQoUOHDh06dPyjqPfr/xkWG78hkzm+Dn7/X7UBHNRtALoNQLcB
*/