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

#ifndef BOOST_MATH_ELLINT_1_HPP
#define BOOST_MATH_ELLINT_1_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/special_functions/ellint_rf.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/math/policies/error_handling.hpp>
#include <boost/math/tools/workaround.hpp>
#include <boost/math/special_functions/round.hpp>

// Elliptic integrals (complete and incomplete) of the first kind
// Carlson, Numerische Mathematik, vol 33, 1 (1979)

namespace boost { namespace math {

template <class T1, class T2, class Policy>
typename tools::promote_args<T1, T2>::type ellint_1(T1 k, T2 phi, const Policy& pol);

namespace detail{

template <typename T, typename Policy>
T ellint_k_imp(T k, const Policy& pol);

// Elliptic integral (Legendre form) of the first kind
template <typename T, typename Policy>
T ellint_f_imp(T phi, T k, const Policy& pol)
{
    BOOST_MATH_STD_USING
    using namespace boost::math::tools;
    using namespace boost::math::constants;

    static const char* function = "boost::math::ellint_f<%1%>(%1%,%1%)";
    BOOST_MATH_INSTRUMENT_VARIABLE(phi);
    BOOST_MATH_INSTRUMENT_VARIABLE(k);
    BOOST_MATH_INSTRUMENT_VARIABLE(function);

    bool invert = false;
    if(phi < 0)
    {
       BOOST_MATH_INSTRUMENT_VARIABLE(phi);
       phi = fabs(phi);
       invert = true;
    }

    T result;

    if(phi >= tools::max_value<T>())
    {
       // Need to handle infinity as a special case:
       result = policies::raise_overflow_error<T>(function, 0, pol);
       BOOST_MATH_INSTRUMENT_VARIABLE(result);
    }
    else if(phi > 1 / tools::epsilon<T>())
    {
       // Phi is so large that phi%pi is necessarily zero (or garbage),
       // just return the second part of the duplication formula:
       result = 2 * phi * ellint_k_imp(k, pol) / constants::pi<T>();
       BOOST_MATH_INSTRUMENT_VARIABLE(result);
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
       BOOST_MATH_INSTRUMENT_CODE("pi/2 = " << constants::pi<T>() / 2);
       T rphi = boost::math::tools::fmod_workaround(phi, T(constants::half_pi<T>()));
       BOOST_MATH_INSTRUMENT_VARIABLE(rphi);
       T m = boost::math::round((phi - rphi) / constants::half_pi<T>());
       BOOST_MATH_INSTRUMENT_VARIABLE(m);
       int s = 1;
       if(boost::math::tools::fmod_workaround(m, T(2)) > 0.5)
       {
          m += 1;
          s = -1;
          rphi = constants::half_pi<T>() - rphi;
          BOOST_MATH_INSTRUMENT_VARIABLE(rphi);
       }
       T sinp = sin(rphi);
       sinp *= sinp;
       if (sinp * k * k >= 1)
       {
          return policies::raise_domain_error<T>(function,
             "Got k^2 * sin^2(phi) = %1%, but the function requires this < 1", sinp * k * k, pol);
       }
       T cosp = cos(rphi);
       cosp *= cosp;
       BOOST_MATH_INSTRUMENT_VARIABLE(sinp);
       BOOST_MATH_INSTRUMENT_VARIABLE(cosp);
       if(sinp > tools::min_value<T>())
       {
          BOOST_ASSERT(rphi != 0); // precondition, can't be true if sin(rphi) != 0.
          //
          // Use http://dlmf.nist.gov/19.25#E5, note that
          // c-1 simplifies to cot^2(rphi) which avoid cancellation:
          //
          T c = 1 / sinp;
          result = static_cast<T>(s * ellint_rf_imp(T(cosp / sinp), T(c - k * k), c, pol));
       }
       else
          result = s * sin(rphi);
       BOOST_MATH_INSTRUMENT_VARIABLE(result);
       if(m != 0)
       {
          result += m * ellint_k_imp(k, pol);
          BOOST_MATH_INSTRUMENT_VARIABLE(result);
       }
    }
    return invert ? T(-result) : result;
}

// Complete elliptic integral (Legendre form) of the first kind
template <typename T, typename Policy>
T ellint_k_imp(T k, const Policy& pol)
{
    BOOST_MATH_STD_USING
    using namespace boost::math::tools;

    static const char* function = "boost::math::ellint_k<%1%>(%1%)";

    if (abs(k) > 1)
    {
       return policies::raise_domain_error<T>(function,
            "Got k = %1%, function requires |k| <= 1", k, pol);
    }
    if (abs(k) == 1)
    {
       return policies::raise_overflow_error<T>(function, 0, pol);
    }

    T x = 0;
    T y = 1 - k * k;
    T z = 1;
    T value = ellint_rf_imp(x, y, z, pol);

    return value;
}

template <typename T, typename Policy>
inline typename tools::promote_args<T>::type ellint_1(T k, const Policy& pol, const boost::true_type&)
{
   typedef typename tools::promote_args<T>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   return policies::checked_narrowing_cast<result_type, Policy>(detail::ellint_k_imp(static_cast<value_type>(k), pol), "boost::math::ellint_1<%1%>(%1%)");
}

template <class T1, class T2>
inline typename tools::promote_args<T1, T2>::type ellint_1(T1 k, T2 phi, const boost::false_type&)
{
   return boost::math::ellint_1(k, phi, policies::policy<>());
}

}

// Complete elliptic integral (Legendre form) of the first kind
template <typename T>
inline typename tools::promote_args<T>::type ellint_1(T k)
{
   return ellint_1(k, policies::policy<>());
}

// Elliptic integral (Legendre form) of the first kind
template <class T1, class T2, class Policy>
inline typename tools::promote_args<T1, T2>::type ellint_1(T1 k, T2 phi, const Policy& pol)
{
   typedef typename tools::promote_args<T1, T2>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   return policies::checked_narrowing_cast<result_type, Policy>(detail::ellint_f_imp(static_cast<value_type>(phi), static_cast<value_type>(k), pol), "boost::math::ellint_1<%1%>(%1%,%1%)");
}

template <class T1, class T2>
inline typename tools::promote_args<T1, T2>::type ellint_1(T1 k, T2 phi)
{
   typedef typename policies::is_policy<T2>::type tag_type;
   return detail::ellint_1(k, phi, tag_type());
}

}} // namespaces

#endif // BOOST_MATH_ELLINT_1_HPP


/* ellint_1.hpp
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
*/