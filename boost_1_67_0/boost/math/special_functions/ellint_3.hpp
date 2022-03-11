//  Copyright (c) 2006 Xiaogang Zhang
//  Copyright (c) 2006 John Maddock
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  History:
//  XZ wrote the original of this file as part of the Google
//  Summer of Code 2006.  JM modified it to fit into the
//  Boost.Math conceptual framework better, and to correctly
//  handle the various corner cases.
//

#ifndef BOOST_MATH_ELLINT_3_HPP
#define BOOST_MATH_ELLINT_3_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/special_functions/ellint_rf.hpp>
#include <boost/math/special_functions/ellint_rj.hpp>
#include <boost/math/special_functions/ellint_1.hpp>
#include <boost/math/special_functions/ellint_2.hpp>
#include <boost/math/special_functions/log1p.hpp>
#include <boost/math/special_functions/atanh.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/math/policies/error_handling.hpp>
#include <boost/math/tools/workaround.hpp>
#include <boost/math/special_functions/round.hpp>

// Elliptic integrals (complete and incomplete) of the third kind
// Carlson, Numerische Mathematik, vol 33, 1 (1979)

namespace boost { namespace math { 
   
namespace detail{

template <typename T, typename Policy>
T ellint_pi_imp(T v, T k, T vc, const Policy& pol);

// Elliptic integral (Legendre form) of the third kind
template <typename T, typename Policy>
T ellint_pi_imp(T v, T phi, T k, T vc, const Policy& pol)
{
   // Note vc = 1-v presumably without cancellation error.
   BOOST_MATH_STD_USING

   static const char* function = "boost::math::ellint_3<%1%>(%1%,%1%,%1%)";


   T sphi = sin(fabs(phi));
   T result = 0;

   if (k * k * sphi * sphi > 1)
   {
      return policies::raise_domain_error<T>(function,
         "Got k = %1%, function requires |k| <= 1", k, pol);
   }
   // Special cases first:
   if(v == 0)
   {
      // A&S 17.7.18 & 19
      return (k == 0) ? phi : ellint_f_imp(phi, k, pol);
   }
   if((v > 0) && (1 / v < (sphi * sphi)))
   {
      // Complex result is a domain error:
      return policies::raise_domain_error<T>(function,
         "Got v = %1%, but result is complex for v > 1 / sin^2(phi)", v, pol);
   }

   if(v == 1)
   {
      if (k == 0)
         return tan(phi);

      // http://functions.wolfram.com/08.06.03.0008.01
      T m = k * k;
      result = sqrt(1 - m * sphi * sphi) * tan(phi) - ellint_e_imp(phi, k, pol);
      result /= 1 - m;
      result += ellint_f_imp(phi, k, pol);
      return result;
   }
   if(phi == constants::half_pi<T>())
   {
      // Have to filter this case out before the next
      // special case, otherwise we might get an infinity from
      // tan(phi).
      // Also note that since we can't represent PI/2 exactly
      // in a T, this is a bit of a guess as to the users true
      // intent...
      //
      return ellint_pi_imp(v, k, vc, pol);
   }
   if((phi > constants::half_pi<T>()) || (phi < 0))
   {
      // Carlson's algorithm works only for |phi| <= pi/2,
      // use the integrand's periodicity to normalize phi
      //
      // Xiaogang's original code used a cast to long long here
      // but that fails if T has more digits than a long long,
      // so rewritten to use fmod instead:
      //
      // See http://functions.wolfram.com/08.06.16.0002.01
      //
      if(fabs(phi) > 1 / tools::epsilon<T>())
      {
         if(v > 1)
            return policies::raise_domain_error<T>(
            function,
            "Got v = %1%, but this is only supported for 0 <= phi <= pi/2", v, pol);
         //  
         // Phi is so large that phi%pi is necessarily zero (or garbage),
         // just return the second part of the duplication formula:
         //
         result = 2 * fabs(phi) * ellint_pi_imp(v, k, vc, pol) / constants::pi<T>();
      }
      else
      {
         T rphi = boost::math::tools::fmod_workaround(T(fabs(phi)), T(constants::half_pi<T>()));
         T m = boost::math::round((fabs(phi) - rphi) / constants::half_pi<T>());
         int sign = 1;
         if((m != 0) && (k >= 1))
         {
            return policies::raise_domain_error<T>(function, "Got k=1 and phi=%1% but the result is complex in that domain", phi, pol);
         }
         if(boost::math::tools::fmod_workaround(m, T(2)) > 0.5)
         {
            m += 1;
            sign = -1;
            rphi = constants::half_pi<T>() - rphi;
         }
         result = sign * ellint_pi_imp(v, rphi, k, vc, pol);
         if((m > 0) && (vc > 0))
            result += m * ellint_pi_imp(v, k, vc, pol);
      }
      return phi < 0 ? T(-result) : result;
   }
   if(k == 0)
   {
      // A&S 17.7.20:
      if(v < 1)
      {
         T vcr = sqrt(vc);
         return atan(vcr * tan(phi)) / vcr;
      }
      else
      {
         // v > 1:
         T vcr = sqrt(-vc);
         T arg = vcr * tan(phi);
         return (boost::math::log1p(arg, pol) - boost::math::log1p(-arg, pol)) / (2 * vcr);
      }
   }
   if((v < 0) && fabs(k) <= 1)
   {
      //
      // If we don't shift to 0 <= v <= 1 we get
      // cancellation errors later on.  Use
      // A&S 17.7.15/16 to shift to v > 0.
      //
      // Mathematica simplifies the expressions
      // given in A&S as follows (with thanks to
      // Rocco Romeo for figuring these out!):
      //
      // V = (k2 - n)/(1 - n)
      // Assuming[(k2 >= 0 && k2 <= 1) && n < 0, FullSimplify[Sqrt[(1 - V)*(1 - k2 / V)] / Sqrt[((1 - n)*(1 - k2 / n))]]]
      // Result: ((-1 + k2) n) / ((-1 + n) (-k2 + n))
      //
      // Assuming[(k2 >= 0 && k2 <= 1) && n < 0, FullSimplify[k2 / (Sqrt[-n*(k2 - n) / (1 - n)] * Sqrt[(1 - n)*(1 - k2 / n)])]]
      // Result : k2 / (k2 - n)
      //
      // Assuming[(k2 >= 0 && k2 <= 1) && n < 0, FullSimplify[Sqrt[1 / ((1 - n)*(1 - k2 / n))]]]
      // Result : Sqrt[n / ((k2 - n) (-1 + n))]
      //
      T k2 = k * k;
      T N = (k2 - v) / (1 - v);
      T Nm1 = (1 - k2) / (1 - v);
      T p2 = -v * N;
      T t;
      if(p2 <= tools::min_value<T>())
         p2 = sqrt(-v) * sqrt(N);
      else
         p2 = sqrt(p2);
      T delta = sqrt(1 - k2 * sphi * sphi);
      if(N > k2)
      {
         result = ellint_pi_imp(N, phi, k, Nm1, pol);
         result *= v / (v - 1);
         result *= (k2 - 1) / (v - k2);
      }

      if(k != 0)
      {
         t = ellint_f_imp(phi, k, pol);
         t *= k2 / (k2 - v);
         result += t;
      }
      t = v / ((k2 - v) * (v - 1));
      if(t > tools::min_value<T>())
      {
         result += atan((p2 / 2) * sin(2 * phi) / delta) * sqrt(t);
      }
      else
      {
         result += atan((p2 / 2) * sin(2 * phi) / delta) * sqrt(fabs(1 / (k2 - v))) * sqrt(fabs(v / (v - 1)));
      }
      return result;
   }
   if(k == 1)
   {
      // See http://functions.wolfram.com/08.06.03.0013.01
      result = sqrt(v) * atanh(sqrt(v) * sin(phi)) - log(1 / cos(phi) + tan(phi));
      result /= v - 1;
      return result;
   }
#if 0  // disabled but retained for future reference: see below.
   if(v > 1)
   {
      //
      // If v > 1 we can use the identity in A&S 17.7.7/8
      // to shift to 0 <= v <= 1.  In contrast to previous
      // revisions of this header, this identity does now work
      // but appears not to produce better error rates in 
      // practice.  Archived here for future reference...
      //
      T k2 = k * k;
      T N = k2 / v;
      T Nm1 = (v - k2) / v;
      T p1 = sqrt((-vc) * (1 - k2 / v));
      T delta = sqrt(1 - k2 * sphi * sphi);
      //
      // These next two terms have a large amount of cancellation
      // so it's not clear if this relation is useable even if
      // the issues with phi > pi/2 can be fixed:
      //
      result = -ellint_pi_imp(N, phi, k, Nm1, pol);
      result += ellint_f_imp(phi, k, pol);
      //
      // This log term gives the complex result when
      //     n > 1/sin^2(phi)
      // However that case is dealt with as an error above, 
      // so we should always get a real result here:
      //
      result += log((delta + p1 * tan(phi)) / (delta - p1 * tan(phi))) / (2 * p1);
      return result;
   }
#endif
   //
   // Carlson's algorithm works only for |phi| <= pi/2,
   // by the time we get here phi should already have been
   // normalised above.
   //
   BOOST_ASSERT(fabs(phi) < constants::half_pi<T>());
   BOOST_ASSERT(phi >= 0);
   T x, y, z, p, t;
   T cosp = cos(phi);
   x = cosp * cosp;
   t = sphi * sphi;
   y = 1 - k * k * t;
   z = 1;
   if(v * t < 0.5)
      p = 1 - v * t;
   else
      p = x + vc * t;
   result = sphi * (ellint_rf_imp(x, y, z, pol) + v * t * ellint_rj_imp(x, y, z, p, pol) / 3);

   return result;
}

// Complete elliptic integral (Legendre form) of the third kind
template <typename T, typename Policy>
T ellint_pi_imp(T v, T k, T vc, const Policy& pol)
{
    // Note arg vc = 1-v, possibly without cancellation errors
    BOOST_MATH_STD_USING
    using namespace boost::math::tools;

    static const char* function = "boost::math::ellint_pi<%1%>(%1%,%1%)";

    if (abs(k) >= 1)
    {
       return policies::raise_domain_error<T>(function,
            "Got k = %1%, function requires |k| <= 1", k, pol);
    }
    if(vc <= 0)
    {
       // Result is complex:
       return policies::raise_domain_error<T>(function,
            "Got v = %1%, function requires v < 1", v, pol);
    }

    if(v == 0)
    {
       return (k == 0) ? boost::math::constants::pi<T>() / 2 : ellint_k_imp(k, pol);
    }

    if(v < 0)
    {
       // Apply A&S 17.7.17:
       T k2 = k * k;
       T N = (k2 - v) / (1 - v);
       T Nm1 = (1 - k2) / (1 - v);
       T result = 0;
       result = boost::math::detail::ellint_pi_imp(N, k, Nm1, pol);
       // This next part is split in two to avoid spurious over/underflow:
       result *= -v / (1 - v);
       result *= (1 - k2) / (k2 - v);
       result += ellint_k_imp(k, pol) * k2 / (k2 - v);
       return result;
    }

    T x = 0;
    T y = 1 - k * k;
    T z = 1;
    T p = vc;
    T value = ellint_rf_imp(x, y, z, pol) + v * ellint_rj_imp(x, y, z, p, pol) / 3;

    return value;
}

template <class T1, class T2, class T3>
inline typename tools::promote_args<T1, T2, T3>::type ellint_3(T1 k, T2 v, T3 phi, const boost::false_type&)
{
   return boost::math::ellint_3(k, v, phi, policies::policy<>());
}

template <class T1, class T2, class Policy>
inline typename tools::promote_args<T1, T2>::type ellint_3(T1 k, T2 v, const Policy& pol, const boost::true_type&)
{
   typedef typename tools::promote_args<T1, T2>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   return policies::checked_narrowing_cast<result_type, Policy>(
      detail::ellint_pi_imp(
         static_cast<value_type>(v), 
         static_cast<value_type>(k),
         static_cast<value_type>(1-v),
         pol), "boost::math::ellint_3<%1%>(%1%,%1%)");
}

} // namespace detail

template <class T1, class T2, class T3, class Policy>
inline typename tools::promote_args<T1, T2, T3>::type ellint_3(T1 k, T2 v, T3 phi, const Policy& pol)
{
   typedef typename tools::promote_args<T1, T2, T3>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   return policies::checked_narrowing_cast<result_type, Policy>(
      detail::ellint_pi_imp(
         static_cast<value_type>(v), 
         static_cast<value_type>(phi), 
         static_cast<value_type>(k),
         static_cast<value_type>(1-v),
         pol), "boost::math::ellint_3<%1%>(%1%,%1%,%1%)");
}

template <class T1, class T2, class T3>
typename detail::ellint_3_result<T1, T2, T3>::type ellint_3(T1 k, T2 v, T3 phi)
{
   typedef typename policies::is_policy<T3>::type tag_type;
   return detail::ellint_3(k, v, phi, tag_type());
}

template <class T1, class T2>
inline typename tools::promote_args<T1, T2>::type ellint_3(T1 k, T2 v)
{
   return ellint_3(k, v, policies::policy<>());
}

}} // namespaces

#endif // BOOST_MATH_ELLINT_3_HPP


/* ellint_3.hpp
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
*/