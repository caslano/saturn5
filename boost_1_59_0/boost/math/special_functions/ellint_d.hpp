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

#ifndef BOOST_MATH_ELLINT_D_HPP
#define BOOST_MATH_ELLINT_D_HPP

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
typename tools::promote_args<T1, T2>::type ellint_d(T1 k, T2 phi, const Policy& pol);
   
namespace detail{

template <typename T, typename Policy>
T ellint_d_imp(T k, const Policy& pol);

// Elliptic integral (Legendre form) of the second kind
template <typename T, typename Policy>
T ellint_d_imp(T phi, T k, const Policy& pol)
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

    if(phi >= tools::max_value<T>())
    {
       // Need to handle infinity as a special case:
       result = policies::raise_overflow_error<T>("boost::math::ellint_d<%1%>(%1%,%1%)", 0, pol);
    }
    else if(phi > 1 / tools::epsilon<T>())
    {
       // Phi is so large that phi%pi is necessarily zero (or garbage),
       // just return the second part of the duplication formula:
       result = 2 * phi * ellint_d_imp(k, pol) / constants::pi<T>();
    }
    else
    {
       // Carlson's algorithm works only for |phi| <= pi/2,
       // use the integrand's periodicity to normalize phi
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
       BOOST_MATH_INSTRUMENT_VARIABLE(rphi);
       BOOST_MATH_INSTRUMENT_VARIABLE(m);
       T sinp = sin(rphi);
       T cosp = cos(rphi);
       BOOST_MATH_INSTRUMENT_VARIABLE(sinp);
       BOOST_MATH_INSTRUMENT_VARIABLE(cosp);
       T c = 1 / (sinp * sinp);
       T cm1 = cosp * cosp / (sinp * sinp);  // c - 1
       T k2 = k * k;
       if(k2 * sinp * sinp > 1)
       {
          return policies::raise_domain_error<T>("boost::math::ellint_d<%1%>(%1%, %1%)", "The parameter k is out of range, got k = %1%", k, pol);
       }
       else if(rphi == 0)
       {
          result = 0;
       }
       else
       {
          // http://dlmf.nist.gov/19.25#E10
          result = s * ellint_rd_imp(cm1, T(c - k2), c, pol) / 3;
          BOOST_MATH_INSTRUMENT_VARIABLE(result);
       }
       if(m != 0)
          result += m * ellint_d_imp(k, pol);
    }
    return invert ? T(-result) : result;
}

// Complete elliptic integral (Legendre form) of the second kind
template <typename T, typename Policy>
T ellint_d_imp(T k, const Policy& pol)
{
    BOOST_MATH_STD_USING
    using namespace boost::math::tools;

    if (abs(k) >= 1)
    {
       return policies::raise_domain_error<T>("boost::math::ellint_d<%1%>(%1%)",
            "Got k = %1%, function requires |k| <= 1", k, pol);
    }
    if(fabs(k) <= tools::root_epsilon<T>())
       return constants::pi<T>() / 4;

    T x = 0;
    T t = k * k;
    T y = 1 - t;
    T z = 1;
    T value = ellint_rd_imp(x, y, z, pol) / 3;

    return value;
}

template <typename T, typename Policy>
inline typename tools::promote_args<T>::type ellint_d(T k, const Policy& pol, const std::true_type&)
{
   typedef typename tools::promote_args<T>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   return policies::checked_narrowing_cast<result_type, Policy>(detail::ellint_d_imp(static_cast<value_type>(k), pol), "boost::math::ellint_d<%1%>(%1%)");
}

// Elliptic integral (Legendre form) of the second kind
template <class T1, class T2>
inline typename tools::promote_args<T1, T2>::type ellint_d(T1 k, T2 phi, const std::false_type&)
{
   return boost::math::ellint_d(k, phi, policies::policy<>());
}

} // detail

// Complete elliptic integral (Legendre form) of the second kind
template <typename T>
inline typename tools::promote_args<T>::type ellint_d(T k)
{
   return ellint_d(k, policies::policy<>());
}

// Elliptic integral (Legendre form) of the second kind
template <class T1, class T2>
inline typename tools::promote_args<T1, T2>::type ellint_d(T1 k, T2 phi)
{
   typedef typename policies::is_policy<T2>::type tag_type;
   return detail::ellint_d(k, phi, tag_type());
}

template <class T1, class T2, class Policy>
inline typename tools::promote_args<T1, T2>::type ellint_d(T1 k, T2 phi, const Policy& pol)
{
   typedef typename tools::promote_args<T1, T2>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   return policies::checked_narrowing_cast<result_type, Policy>(detail::ellint_d_imp(static_cast<value_type>(phi), static_cast<value_type>(k), pol), "boost::math::ellint_2<%1%>(%1%,%1%)");
}

}} // namespaces

#endif // BOOST_MATH_ELLINT_D_HPP


/* ellint_d.hpp
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
*/