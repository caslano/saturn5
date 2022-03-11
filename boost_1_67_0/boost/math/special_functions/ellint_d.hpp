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
inline typename tools::promote_args<T>::type ellint_d(T k, const Policy& pol, const boost::true_type&)
{
   typedef typename tools::promote_args<T>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   return policies::checked_narrowing_cast<result_type, Policy>(detail::ellint_d_imp(static_cast<value_type>(k), pol), "boost::math::ellint_d<%1%>(%1%)");
}

// Elliptic integral (Legendre form) of the second kind
template <class T1, class T2>
inline typename tools::promote_args<T1, T2>::type ellint_d(T1 k, T2 phi, const boost::false_type&)
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