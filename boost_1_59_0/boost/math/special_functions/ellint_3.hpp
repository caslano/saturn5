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
      result = sqrt(v) * atanh(sqrt(v) * sin(phi), pol) - log(1 / cos(phi) + tan(phi));
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
   BOOST_MATH_ASSERT(fabs(phi) < constants::half_pi<T>());
   BOOST_MATH_ASSERT(phi >= 0);
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
inline typename tools::promote_args<T1, T2, T3>::type ellint_3(T1 k, T2 v, T3 phi, const std::false_type&)
{
   return boost::math::ellint_3(k, v, phi, policies::policy<>());
}

template <class T1, class T2, class Policy>
inline typename tools::promote_args<T1, T2>::type ellint_3(T1 k, T2 v, const Policy& pol, const std::true_type&)
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