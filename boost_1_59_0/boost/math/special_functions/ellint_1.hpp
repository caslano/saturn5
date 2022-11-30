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
          BOOST_MATH_ASSERT(rphi != 0); // precondition, can't be true if sin(rphi) != 0.
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
inline typename tools::promote_args<T>::type ellint_1(T k, const Policy& pol, const std::true_type&)
{
   typedef typename tools::promote_args<T>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   return policies::checked_narrowing_cast<result_type, Policy>(detail::ellint_k_imp(static_cast<value_type>(k), pol), "boost::math::ellint_1<%1%>(%1%)");
}

template <class T1, class T2>
inline typename tools::promote_args<T1, T2>::type ellint_1(T1 k, T2 phi, const std::false_type&)
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