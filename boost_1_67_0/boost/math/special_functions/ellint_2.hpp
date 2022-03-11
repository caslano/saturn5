//  Copyright (c) 2006 Xiaogang Zhang
//  Copyright (c) 2006 John Maddock
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  History:
//  XZ wrote the original of this file as part of the Google
//  Summer of Code 2006.  JM modified it to fit into the
//  Boost.Math conceptual framework better, and to ensure
//  that the code continues to work no matter how many digits
//  type T has.

#ifndef BOOST_MATH_ELLINT_2_HPP
#define BOOST_MATH_ELLINT_2_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/special_functions/ellint_rf.hpp>
#include <boost/math/special_functions/ellint_rd.hpp>
#include <boost/math/special_functions/ellint_rg.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/math/policies/error_handling.hpp>
#include <boost/math/tools/workaround.hpp>
#include <boost/math/special_functions/round.hpp>

// Elliptic integrals (complete and incomplete) of the second kind
// Carlson, Numerische Mathematik, vol 33, 1 (1979)

namespace boost { namespace math { 
   
template <class T1, class T2, class Policy>
typename tools::promote_args<T1, T2>::type ellint_2(T1 k, T2 phi, const Policy& pol);
   
namespace detail{

template <typename T, typename Policy>
T ellint_e_imp(T k, const Policy& pol);

// Elliptic integral (Legendre form) of the second kind
template <typename T, typename Policy>
T ellint_e_imp(T phi, T k, const Policy& pol)
{
    BOOST_MATH_STD_USING
    using namespace boost::math::tools;
    using namespace boost::math::constants;

    bool invert = false;
    if (phi == 0)
       return 0;

    if(phi < 0)
    {
       phi = fabs(phi);
       invert = true;
    }

    T result;

    if(phi >= tools::max_value<T>())
    {
       // Need to handle infinity as a special case:
       result = policies::raise_overflow_error<T>("boost::math::ellint_e<%1%>(%1%,%1%)", 0, pol);
    }
    else if(phi > 1 / tools::epsilon<T>())
    {
       // Phi is so large that phi%pi is necessarily zero (or garbage),
       // just return the second part of the duplication formula:
       result = 2 * phi * ellint_e_imp(k, pol) / constants::pi<T>();
    }
    else if(k == 0)
    {
       return invert ? T(-phi) : phi;
    }
    else if(fabs(k) == 1)
    {
       return invert ? T(-sin(phi)) : T(sin(phi));
    }
    else
    {
       // Carlson's algorithm works only for |phi| <= pi/2,
       // use the integrand's periodicity to normalize phi
       //
       // Xiaogang's original code used a cast to long long here
       // but that fails if T has more digits than a long long,
       // so rewritten to use fmod instead:
       //
       T rphi = boost::math::tools::fmod_workaround(phi, T(constants::half_pi<T>()));
       T m = boost::math::round((phi - rphi) / constants::half_pi<T>());
       int s = 1;
       if(boost::math::tools::fmod_workaround(m, T(2)) > 0.5)
       {
          m += 1;
          s = -1;
          rphi = constants::half_pi<T>() - rphi;
       }
       T k2 = k * k;
       if(boost::math::pow<3>(rphi) * k2 / 6 < tools::epsilon<T>() * fabs(rphi))
       {
          // See http://functions.wolfram.com/EllipticIntegrals/EllipticE2/06/01/03/0001/
          result = s * rphi;
       }
       else
       {
          // http://dlmf.nist.gov/19.25#E10
          T sinp = sin(rphi);
          if (k2 * sinp * sinp >= 1)
          {
             return policies::raise_domain_error<T>("boost::math::ellint_2<%1%>(%1%, %1%)", "The parameter k is out of range, got k = %1%", k, pol);
          }
          T cosp = cos(rphi);
          T c = 1 / (sinp * sinp);
          T cm1 = cosp * cosp / (sinp * sinp);  // c - 1
          result = s * ((1 - k2) * ellint_rf_imp(cm1, T(c - k2), c, pol) + k2 * (1 - k2) * ellint_rd(cm1, c, T(c - k2), pol) / 3 + k2 * sqrt(cm1 / (c * (c - k2))));
       }
       if(m != 0)
          result += m * ellint_e_imp(k, pol);
    }
    return invert ? T(-result) : result;
}

// Complete elliptic integral (Legendre form) of the second kind
template <typename T, typename Policy>
T ellint_e_imp(T k, const Policy& pol)
{
    BOOST_MATH_STD_USING
    using namespace boost::math::tools;

    if (abs(k) > 1)
    {
       return policies::raise_domain_error<T>("boost::math::ellint_e<%1%>(%1%)",
            "Got k = %1%, function requires |k| <= 1", k, pol);
    }
    if (abs(k) == 1)
    {
        return static_cast<T>(1);
    }

    T x = 0;
    T t = k * k;
    T y = 1 - t;
    T z = 1;
    T value = 2 * ellint_rg_imp(x, y, z, pol);

    return value;
}

template <typename T, typename Policy>
inline typename tools::promote_args<T>::type ellint_2(T k, const Policy& pol, const boost::true_type&)
{
   typedef typename tools::promote_args<T>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   return policies::checked_narrowing_cast<result_type, Policy>(detail::ellint_e_imp(static_cast<value_type>(k), pol), "boost::math::ellint_2<%1%>(%1%)");
}

// Elliptic integral (Legendre form) of the second kind
template <class T1, class T2>
inline typename tools::promote_args<T1, T2>::type ellint_2(T1 k, T2 phi, const boost::false_type&)
{
   return boost::math::ellint_2(k, phi, policies::policy<>());
}

} // detail

// Complete elliptic integral (Legendre form) of the second kind
template <typename T>
inline typename tools::promote_args<T>::type ellint_2(T k)
{
   return ellint_2(k, policies::policy<>());
}

// Elliptic integral (Legendre form) of the second kind
template <class T1, class T2>
inline typename tools::promote_args<T1, T2>::type ellint_2(T1 k, T2 phi)
{
   typedef typename policies::is_policy<T2>::type tag_type;
   return detail::ellint_2(k, phi, tag_type());
}

template <class T1, class T2, class Policy>
inline typename tools::promote_args<T1, T2>::type ellint_2(T1 k, T2 phi, const Policy& pol)
{
   typedef typename tools::promote_args<T1, T2>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   return policies::checked_narrowing_cast<result_type, Policy>(detail::ellint_e_imp(static_cast<value_type>(phi), static_cast<value_type>(k), pol), "boost::math::ellint_2<%1%>(%1%,%1%)");
}

}} // namespaces

#endif // BOOST_MATH_ELLINT_2_HPP


/* ellint_2.hpp
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
*/