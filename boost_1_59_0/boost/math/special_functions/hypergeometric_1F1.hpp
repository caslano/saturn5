///////////////////////////////////////////////////////////////////////////////
//  Copyright 2014 Anton Bikineev
//  Copyright 2014 Christopher Kormanyos
//  Copyright 2014 John Maddock
//  Copyright 2014 Paul Bristow
//  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_HYPERGEOMETRIC_1F1_HPP
#define BOOST_MATH_HYPERGEOMETRIC_1F1_HPP

#include <boost/math/tools/config.hpp>
#include <boost/math/policies/policy.hpp>
#include <boost/math/policies/error_handling.hpp>
#include <boost/math/special_functions/detail/hypergeometric_series.hpp>
#include <boost/math/special_functions/detail/hypergeometric_asym.hpp>
#include <boost/math/special_functions/detail/hypergeometric_rational.hpp>
#include <boost/math/special_functions/detail/hypergeometric_1F1_recurrence.hpp>
#include <boost/math/special_functions/detail/hypergeometric_1F1_by_ratios.hpp>
#include <boost/math/special_functions/detail/hypergeometric_pade.hpp>
#include <boost/math/special_functions/detail/hypergeometric_1F1_bessel.hpp>
#include <boost/math/special_functions/detail/hypergeometric_1F1_scaled_series.hpp>
#include <boost/math/special_functions/detail/hypergeometric_pFq_checked_series.hpp>
#include <boost/math/special_functions/detail/hypergeometric_1F1_addition_theorems_on_z.hpp>
#include <boost/math/special_functions/detail/hypergeometric_1F1_large_abz.hpp>
#include <boost/math/special_functions/detail/hypergeometric_1F1_small_a_negative_b_by_ratio.hpp>
#include <boost/math/special_functions/detail/hypergeometric_1F1_negative_b_regions.hpp>

namespace boost { namespace math { namespace detail {

   // check when 1F1 series can't decay to polynom
   template <class T>
   inline bool check_hypergeometric_1F1_parameters(const T& a, const T& b)
   {
      BOOST_MATH_STD_USING

         if ((b <= 0) && (b == floor(b)))
         {
            if ((a >= 0) || (a < b) || (a != floor(a)))
               return false;
         }

      return true;
   }

   template <class T, class Policy>
   T hypergeometric_1F1_divergent_fallback(const T& a, const T& b, const T& z, const Policy& pol, long long& log_scaling)
   {
      BOOST_MATH_STD_USING
      const char* function = "hypergeometric_1F1_divergent_fallback<%1%>(%1%,%1%,%1%)";
      //
      // We get here if either:
      // 1) We decide up front that Tricomi's method won't work, or:
      // 2) We've called Tricomi's method and it's failed.
      //
      if (b > 0)
      {
         // Commented out since recurrence seems to always be better?
#if 0
         if ((z < b) && (a > -50))
            // Might as well use a recurrence in preference to z-recurrence:
            return hypergeometric_1F1_backward_recurrence_for_negative_a(a, b, z, pol, function, log_scaling);
         T z_limit = fabs((2 * a - b) / (sqrt(fabs(a))));
         int k = 1 + itrunc(z - z_limit);
         // If k is too large we destroy all the digits in the result:
         T convergence_at_50 = (b - a + 50) * k / (z * 50);
         if ((k > 0) && (k < 50) && (fabs(convergence_at_50) < 1) && (z > z_limit))
         {
            return boost::math::detail::hypergeometric_1f1_recurrence_on_z_minus_zero(a, b, T(z - k), k, pol, log_scaling);
         }
#endif
         if (z < b)
            return hypergeometric_1F1_backward_recurrence_for_negative_a(a, b, z, pol, function, log_scaling);
         else
            return hypergeometric_1F1_backwards_recursion_on_b_for_negative_a(a, b, z, pol, function, log_scaling);
      }
      else  // b < 0
      {
         if (a < 0)
         {
            if ((b < a) && (z < -b / 4))
               return hypergeometric_1F1_from_function_ratio_negative_ab(a, b, z, pol, log_scaling);
            else
            {
               //
               // Solve (a+n)z/((b+n)n) == 1 for n, the number of iterations till the series starts to converge.
               // If this is well away from the origin then it's probably better to use the series to evaluate this.
               // Note that if sqr is negative then we have no solution, so assign an arbitrarily large value to the
               // number of iterations.
               //
               bool can_use_recursion = (z - b + 100 < boost::math::policies::get_max_series_iterations<Policy>()) && (100 - a < boost::math::policies::get_max_series_iterations<Policy>());
               T sqr = 4 * a * z + b * b - 2 * b * z + z * z;
               T iterations_to_convergence = sqr > 0 ? T(0.5f * (-sqrt(sqr) - b + z)) : T(-a - b);
               if(can_use_recursion && ((std::max)(a, b) + iterations_to_convergence > -300))
                  return hypergeometric_1F1_backwards_recursion_on_b_for_negative_a(a, b, z, pol, function, log_scaling);
               //
               // When a < b and if we fall through to the series, then we get divergent behaviour when b crosses the origin
               // so ideally we would pick another method.  Otherwise the terms immediately after b crosses the origin may
               // suffer catastrophic cancellation....
               //
               if((a < b) && can_use_recursion)
                  return hypergeometric_1F1_backwards_recursion_on_b_for_negative_a(a, b, z, pol, function, log_scaling);
            }
         }
         else
         {
            //
            // Start by getting the domain of the recurrence relations, we get either:
            //   -1     Backwards recursion is stable and the CF will converge to double precision.
            //   +1     Forwards recursion is stable and the CF will converge to double precision.
            //    0     No man's land, we're not far enough away from the crossover point to get double precision from either CF.
            //
            // At higher than double precision we need to be further away from the crossover location to
            // get full converge, but it's not clear how much further - indeed at quad precision it's
            // basically impossible to ever get forwards iteration to work.  Backwards seems to work
            // OK as long as a > 1 whatever the precision tbough.
            //
            int domain = hypergeometric_1F1_negative_b_recurrence_region(a, b, z);
            if ((domain < 0) && ((a > 1) || (boost::math::policies::digits<T, Policy>() <= 64)))
               return hypergeometric_1F1_from_function_ratio_negative_b(a, b, z, pol, log_scaling);
            else if (domain > 0)
            {
               if (boost::math::policies::digits<T, Policy>() <= 64)
                  return hypergeometric_1F1_from_function_ratio_negative_b_forwards(a, b, z, pol, log_scaling);
               try 
               {
                  return hypergeometric_1F1_checked_series_impl(a, b, z, pol, log_scaling);
               }
               catch (const evaluation_error&)
               {
                  //
                  // The series failed, try the recursions instead and hope we get at least double precision:
                  //
                  return hypergeometric_1F1_from_function_ratio_negative_b_forwards(a, b, z, pol, log_scaling);
               }
            }
            //
            // We could fall back to Tricomi's approximation if we're in the transition zone
            // between the above two regions.  However, I've been unable to find any examples
            // where this is better than the series, and there are many cases where it leads to
            // quite grievous errors.
            /*
            else if (allow_tricomi)
            {
               T aa = a < 1 ? T(1) : a;
               if (z < fabs((2 * aa - b) / (sqrt(fabs(aa * b)))))
                  return hypergeometric_1F1_AS_13_3_7_tricomi(a, b, z, pol, log_scaling);
            }
            */
         }
      }

      // If we get here, then we've run out of methods to try, use the checked series which will
      // raise an error if the result is garbage:
      return hypergeometric_1F1_checked_series_impl(a, b, z, pol, log_scaling);
   }

   template <class T>
   bool is_convergent_negative_z_series(const T& a, const T& b, const T& z, const T& b_minus_a)
   {
      BOOST_MATH_STD_USING
      //
      // Filter out some cases we don't want first:
      //
      if((b_minus_a > 0) && (b > 0))
      {
         if (a < 0)
            return false;
      }
      //
      // Generic check: we have small initial divergence and are convergent after 10 terms:
      //
      if ((fabs(z * a / b) < 2) && (fabs(z * (a + 10) / ((b + 10) * 10)) < 1))
      {
         // Double check for divergence when we cross the origin on a and b:
         if (a < 0)
         {
            T n = 300 - floor(a);
            if (fabs((a + n) * z / ((b + n) * n)) < 1)
            {
               if (b < 0)
               {
                  T m = 3 - floor(b);
                  if (fabs((a + m) * z / ((b + m) * m)) < 1)
                     return true;
               }
               else
                  return true;
            }
         }
         else if (b < 0)
         {
            T n = 3 - floor(b);
            if (fabs((a + n) * z / ((b + n) * n)) < 1)
               return true;
         }
      }
      if ((b > 0) && (a < 0))
      {
         //
         // For a and z both negative, we're OK with some initial divergence as long as
         // it occurs before we hit the origin, as to start with all the terms have the
         // same sign.
         //
         // https://www.wolframalpha.com/input/?i=solve+(a%2Bn)z+%2F+((b%2Bn)n)+%3D%3D+1+for+n
         //
         T sqr = 4 * a * z + b * b - 2 * b * z + z * z;
         T iterations_to_convergence = sqr > 0 ? T(0.5f * (-sqrt(sqr) - b + z)) : T(-a + b);
         if (iterations_to_convergence < 0)
            iterations_to_convergence = 0.5f * (sqrt(sqr) - b + z);
         if (a + iterations_to_convergence < -50)
         {
            // Need to check for divergence when we cross the origin on a:
            if (a > -1)
               return true;
            T n = 300 - floor(a);
            if(fabs((a + n) * z / ((b + n) * n)) < 1)
               return true;
         }
      }
      return false;
   }

   template <class T>
   inline T cyl_bessel_i_shrinkage_rate(const T& z)
   {
      // Approximately the ratio I_10.5(z/2) / I_9.5(z/2), this gives us an idea of how quickly
      // the Bessel terms in A&S 13.6.4 are converging:
      if (z < -160)
         return 1;
      if (z < -40)
         return 0.75f;
      if (z < -20)
         return 0.5f;
      if (z < -7)
         return 0.25f;
      if (z < -2)
         return 0.1f;
      return 0.05f;
   }

   template <class T>
   inline bool hypergeometric_1F1_is_13_3_6_region(const T& a, const T& b, const T& z)
   {
      BOOST_MATH_STD_USING
      if(fabs(a) == 0.5)
         return false;
      if ((z < 0) && (fabs(10 * a / b) < 1) && (fabs(a) < 50))
      {
         T shrinkage = cyl_bessel_i_shrinkage_rate(z);
         // We want the first term not too divergent, and convergence by term 10:
         if ((fabs((2 * a - 1) * (2 * a - b) / b) < 2) && (fabs(shrinkage * (2 * a + 9) * (2 * a - b + 10) / (10 * (b + 10))) < 0.75))
            return true;
      }
      return false;
   }

   template <class T>
   inline bool hypergeometric_1F1_need_kummer_reflection(const T& a, const T& b, const T& z)
   {
      BOOST_MATH_STD_USING
      //
      // Check to see if we should apply Kummer's relation or not:
      //
      if (z > 0)
         return false;
      if (z < -1)
         return true;
      //
      // When z is small and negative, things get more complex.
      // More often than not we do not need apply Kummer's relation and the
      // series is convergent as is, but we do need to check:
      //
      if (a > 0)
      {
         if (b > 0)
         {
            return fabs((a + 10) * z / (10 * (b + 10))) < 1;  // Is the 10'th term convergent?
         }
         else
         {
            return true;  // Likely to be divergent as b crosses the origin
         }
      }
      else // a < 0
      {
         if (b > 0)
         {
            return false;  // Terms start off all positive and then by the time a crosses the origin we *must* be convergent.
         }
         else
         {
            return true;  // Likely to be divergent as b crosses the origin, but hard to rationalise about!
         }
      }
   }

      
   template <class T, class Policy>
   T hypergeometric_1F1_imp(const T& a, const T& b, const T& z, const Policy& pol, long long& log_scaling)
   {
      BOOST_MATH_STD_USING // exp, fabs, sqrt

      static const char* const function = "boost::math::hypergeometric_1F1<%1%,%1%,%1%>(%1%,%1%,%1%)";

      if ((z == 0) || (a == 0))
         return T(1);

      // undefined result:
      if (!detail::check_hypergeometric_1F1_parameters(a, b))
         return policies::raise_domain_error<T>(
            function,
            "Function is indeterminate for negative integer b = %1%.",
            b,
            pol);

      // other checks:
      if (a == -1)
         return 1 - (z / b);

      const T b_minus_a = b - a;

      // 0f0 a == b case;
      if (b_minus_a == 0)
      {
         long long scale = lltrunc(z, pol);
         log_scaling += scale;
         return exp(z - scale);
      }
      // Special case for b-a = -1, we don't use for small a as it throws the digits of a away and leads to large errors:
      if ((b_minus_a == -1) && (fabs(a) > 0.5))
      {
         // for negative small integer a it is reasonable to use truncated series - polynomial
         if ((a < 0) && (a == ceil(a)) && (a > -50))
            return detail::hypergeometric_1F1_generic_series(a, b, z, pol, log_scaling, function);

         return (b + z) * exp(z) / b;
      }

      if ((a == 1) && (b == 2))
         return boost::math::expm1(z, pol) / z;

      if ((b - a == b) && (fabs(z / b) < policies::get_epsilon<T, Policy>()))
         return 1;
      //
      // Special case for A&S 13.3.6:
      //
      if (z < 0)
      {
         if (hypergeometric_1F1_is_13_3_6_region(a, b, z))
         {
            // a is tiny compared to b, and z < 0
            // 13.3.6 appears to be the most efficient and often the most accurate method.
            T r = boost::math::detail::hypergeometric_1F1_AS_13_3_6(b_minus_a, b, T(-z), a, pol, log_scaling);
            long long scale = lltrunc(z, pol);
            log_scaling += scale;
            return r * exp(z - scale);
         }
         if ((b < 0) && (fabs(a) < 1e-2))
         {
            //
            // This is a tricky area, potentially we have no good method at all:
            //
            if (b - ceil(b) == a)
            {
               // Fractional parts of a and b are genuinely equal, we might as well
               // apply Kummer's relation and get a truncated series:
               long long scaling = lltrunc(z);
               T r = exp(z - scaling) * detail::hypergeometric_1F1_imp<T>(b_minus_a, b, -z, pol, log_scaling);
               log_scaling += scaling;
               return r;
            }
            if ((b < -1) && (max_b_for_1F1_small_a_negative_b_by_ratio(z) < b))
               return hypergeometric_1F1_small_a_negative_b_by_ratio(a, b, z, pol, log_scaling);
            if ((b > -1) && (b < -0.5f))
            {
               // Recursion is meta-stable:
               T first = hypergeometric_1F1_imp(a, T(b + 2), z, pol);
               T second = hypergeometric_1F1_imp(a, T(b + 1), z, pol);
               return tools::apply_recurrence_relation_backward(hypergeometric_1F1_recurrence_small_b_coefficients<T>(a, b, z, 1), 1, first, second);
            }
            //
            // We've got nothing left but 13.3.6, even though it may be initially divergent:
            //
            T r = boost::math::detail::hypergeometric_1F1_AS_13_3_6(b_minus_a, b, T(-z), a, pol, log_scaling);
            long long scale = lltrunc(z, pol);
            log_scaling += scale;
            return r * exp(z - scale);
         }
      }
      //
      // Asymptotic expansion for large z
      // TODO: check region for higher precision types.
      // Use recurrence relations to move to this region when a and b are also large.
      //
      if (detail::hypergeometric_1F1_asym_region(a, b, z, pol))
      {
         long long saved_scale = log_scaling;
         try
         {
            return hypergeometric_1F1_asym_large_z_series(a, b, z, pol, log_scaling);
         }
         catch (const evaluation_error&)
         {
         }
         //
         // Very occasionally our convergence criteria don't quite go to full precision
         // and we have to try another method:
         //
         log_scaling = saved_scale;
      }

      if ((fabs(a * z / b) < 3.5) && (fabs(z * 100) < fabs(b)) && ((fabs(a) > 1e-2) || (b < -5)))
         return detail::hypergeometric_1F1_rational(a, b, z, pol);

      if (hypergeometric_1F1_need_kummer_reflection(a, b, z))
      {
         if (a == 1)
            return detail::hypergeometric_1F1_pade(b, z, pol);
         if (is_convergent_negative_z_series(a, b, z, b_minus_a))
         {
            if ((boost::math::sign(b_minus_a) == boost::math::sign(b)) && ((b > 0) || (b < -200)))
            {
               // Series is close enough to convergent that we should be OK,
               // In this domain b - a ~ b and since 1F1[a, a, z] = e^z 1F1[b-a, b, -z]
               // and 1F1[a, a, -z] = e^-z the result must necessarily be somewhere near unity.
               // We have to rule out b small and negative because if b crosses the origin early
               // in the series (before we're pretty much converged) then all bets are off.
               // Note that this can go badly wrong when b and z are both large and negative,
               // in that situation the series goes in waves of large and small values which
               // may or may not cancel out.  Likewise the initial part of the series may or may
               // not converge, and even if it does may or may not give a correct answer!
               // For example 1F1[-small, -1252.5, -1043.7] can loose up to ~800 digits due to
               // cancellation and is basically incalculable via this method.
               return hypergeometric_1F1_checked_series_impl(a, b, z, pol, log_scaling);
            }
         }
         // Let's otherwise make z positive (almost always)
         // by Kummer's transformation
         // (we also don't transform if z belongs to [-1,0])
         long long scaling = lltrunc(z);
         T r = exp(z - scaling) * detail::hypergeometric_1F1_imp<T>(b_minus_a, b, -z, pol, log_scaling);
         log_scaling += scaling;
         return r;
      }
      //
      // Check for initial divergence:
      //
      bool series_is_divergent = (a + 1) * z / (b + 1) < -1;
      if (series_is_divergent && (a < 0) && (b < 0) && (a > -1))
         series_is_divergent = false;   // Best off taking the series in this situation
      //
      // If series starts off non-divergent, and becomes divergent later
      // then it's because both a and b are negative, so check for later
      // divergence as well:
      //
      if (!series_is_divergent && (a < 0) && (b < 0) && (b > a))
      {
         //
         // We need to exclude situations where we're over the initial "hump"
         // in the series terms (ie series has already converged by the time
         // b crosses the origin:
         //
         //T fa = fabs(a);
         //T fb = fabs(b);
         T convergence_point = sqrt((a - 1) * (a - b)) - a;
         if (-b < convergence_point)
         {
            T n = -floor(b);
            series_is_divergent = (a + n) * z / ((b + n) * n) < -1;
         }
      }
      else if (!series_is_divergent && (b < 0) && (a > 0))
      {
         // Series almost always become divergent as b crosses the origin:
         series_is_divergent = true;
      }
      if (series_is_divergent && (b < -1) && (b > -5) && (a > b))
         series_is_divergent = false;  // don't bother with divergence, series will be OK

      //
      // Test for alternating series due to negative a,
      // in particular, see if the series is initially divergent
      // If so use the recurrence relation on a:
      //
      if (series_is_divergent)
      {
         if((a < 0) && (floor(a) == a) && (-a < policies::get_max_series_iterations<Policy>()))
            // This works amazingly well for negative integer a:
            return hypergeometric_1F1_backward_recurrence_for_negative_a(a, b, z, pol, function, log_scaling);
         //
         // In what follows we have to set limits on how large z can be otherwise
         // the Bessel series become large and divergent and all the digits cancel out.
         // The criteria are distinctly empiracle rather than based on a firm analysis
         // of the terms in the series.
         //
         if (b > 0)
         {
            T z_limit = fabs((2 * a - b) / (sqrt(fabs(a))));
            if ((z < z_limit) && hypergeometric_1F1_is_tricomi_viable_positive_b(a, b, z))
               return detail::hypergeometric_1F1_AS_13_3_7_tricomi(a, b, z, pol, log_scaling);
         }
         else  // b < 0
         {
            if (a < 0)
            {
               T z_limit = fabs((2 * a - b) / (sqrt(fabs(a))));
               //
               // I hate these hard limits, but they're about the best we can do to try and avoid
               // Bessel function internal failures: these will be caught and handled
               // but up the expense of this function call:
               //
               if (((z < z_limit) || (a > -500)) && ((b > -500) || (b - 2 * a > 0)) && (z < -a))
               {
                  //
                  // Outside this domain we will probably get better accuracy from the recursive methods.
                  //
                  if(!(((a < b) && (z > -b)) || (z > z_limit)))
                     return detail::hypergeometric_1F1_AS_13_3_7_tricomi(a, b, z, pol, log_scaling);
                  //
                  // When b and z are both very small, we get large errors from the recurrence methods
                  // in the fallbacks.  Tricomi seems to work well here, as does direct series evaluation
                  // at least some of the time.  Picking the right method is not easy, and sometimes this
                  // is much worse than the fallback.  Overall though, it's a reasonable choice that keeps
                  // the very worst errors under control.
                  //
                  if(b > -1)
                     return detail::hypergeometric_1F1_AS_13_3_7_tricomi(a, b, z, pol, log_scaling);
               }
            }
            //
            // We previously used Tricomi here, but it appears to be worse than
            // the recurrence-based algorithms in hypergeometric_1F1_divergent_fallback.
            /*
            else
            {
               T aa = a < 1 ? T(1) : a;
               if (z < fabs((2 * aa - b) / (sqrt(fabs(aa * b)))))
                  return detail::hypergeometric_1F1_AS_13_3_7_tricomi(a, b, z, pol, log_scaling);
            }*/
         }

         return hypergeometric_1F1_divergent_fallback(a, b, z, pol, log_scaling);
      }

      if (hypergeometric_1F1_is_13_3_6_region(b_minus_a, b, T(-z)))
      {
         // b_minus_a is tiny compared to b, and -z < 0
         // 13.3.6 appears to be the most efficient and often the most accurate method.
         return boost::math::detail::hypergeometric_1F1_AS_13_3_6(a, b, z, b_minus_a, pol, log_scaling);
      }
#if 0
      if ((a > 0) && (b > 0) && (a * z / b > 2))
      {
         //
         // Series is initially divergent and slow to converge, see if applying
         // Kummer's relation can improve things:
         //
         if (is_convergent_negative_z_series(b_minus_a, b, T(-z), b_minus_a))
         {
            long long scaling = lltrunc(z);
            T r = exp(z - scaling) * detail::hypergeometric_1F1_checked_series_impl(b_minus_a, b, T(-z), pol, log_scaling);
            log_scaling += scaling;
            return r;
         }

      }
#endif
      if ((a > 0) && (b > 0) && (a * z > 50))
         return detail::hypergeometric_1F1_large_abz(a, b, z, pol, log_scaling);

      if (b < 0)
         return detail::hypergeometric_1F1_checked_series_impl(a, b, z, pol, log_scaling);
      
      return detail::hypergeometric_1F1_generic_series(a, b, z, pol, log_scaling, function);
   }

   template <class T, class Policy>
   inline T hypergeometric_1F1_imp(const T& a, const T& b, const T& z, const Policy& pol)
   {
      BOOST_MATH_STD_USING // exp, fabs, sqrt
      long long log_scaling = 0;
      T result = hypergeometric_1F1_imp(a, b, z, pol, log_scaling);
      //
      // Actual result will be result * e^log_scaling.
      //
      static const thread_local long long max_scaling = lltrunc(boost::math::tools::log_max_value<T>()) - 2;
      static const thread_local T max_scale_factor = exp(T(max_scaling));

      while (log_scaling > max_scaling)
      {
         result *= max_scale_factor;
         log_scaling -= max_scaling;
      }
      while (log_scaling < -max_scaling)
      {
         result /= max_scale_factor;
         log_scaling += max_scaling;
      }
      if (log_scaling)
         result *= exp(T(log_scaling));
      return result;
   }

   template <class T, class Policy>
   inline T log_hypergeometric_1F1_imp(const T& a, const T& b, const T& z, int* sign, const Policy& pol)
   {
      BOOST_MATH_STD_USING // exp, fabs, sqrt
      long long log_scaling = 0;
      T result = hypergeometric_1F1_imp(a, b, z, pol, log_scaling);
      if (sign)
      *sign = result < 0 ? -1 : 1;
     result = log(fabs(result)) + log_scaling;
      return result;
   }

   template <class T, class Policy>
   inline T hypergeometric_1F1_regularized_imp(const T& a, const T& b, const T& z, const Policy& pol)
   {
      BOOST_MATH_STD_USING // exp, fabs, sqrt
      long long log_scaling = 0;
      T result = hypergeometric_1F1_imp(a, b, z, pol, log_scaling);
      //
      // Actual result will be result * e^log_scaling / tgamma(b).
      //
      int result_sign = 1;
      T scale = log_scaling - boost::math::lgamma(b, &result_sign, pol);

      static const thread_local T max_scaling = boost::math::tools::log_max_value<T>() - 2;
      static const thread_local T max_scale_factor = exp(max_scaling);

      while (scale > max_scaling)
      {
         result *= max_scale_factor;
         scale -= max_scaling;
      }
      while (scale < -max_scaling)
      {
         result /= max_scale_factor;
     scale += max_scaling;
      }
      if (scale != 0)
         result *= exp(scale);
      return result * result_sign;
   }

} // namespace detail

template <class T1, class T2, class T3, class Policy>
inline typename tools::promote_args<T1, T2, T3>::type hypergeometric_1F1(T1 a, T2 b, T3 z, const Policy& /* pol */)
{
   BOOST_FPU_EXCEPTION_GUARD
      typedef typename tools::promote_args<T1, T2, T3>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   typedef typename policies::normalise<
      Policy,
      policies::promote_float<false>,
      policies::promote_double<false>,
      policies::discrete_quantile<>,
      policies::assert_undefined<> >::type forwarding_policy;
   return policies::checked_narrowing_cast<result_type, Policy>(
      detail::hypergeometric_1F1_imp<value_type>(
         static_cast<value_type>(a),
         static_cast<value_type>(b),
         static_cast<value_type>(z),
         forwarding_policy()),
      "boost::math::hypergeometric_1F1<%1%>(%1%,%1%,%1%)");
}

template <class T1, class T2, class T3>
inline typename tools::promote_args<T1, T2, T3>::type hypergeometric_1F1(T1 a, T2 b, T3 z)
{
   return hypergeometric_1F1(a, b, z, policies::policy<>());
}

template <class T1, class T2, class T3, class Policy>
inline typename tools::promote_args<T1, T2, T3>::type hypergeometric_1F1_regularized(T1 a, T2 b, T3 z, const Policy& /* pol */)
{
   BOOST_FPU_EXCEPTION_GUARD
      typedef typename tools::promote_args<T1, T2, T3>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   typedef typename policies::normalise<
      Policy,
      policies::promote_float<false>,
      policies::promote_double<false>,
      policies::discrete_quantile<>,
      policies::assert_undefined<> >::type forwarding_policy;
   return policies::checked_narrowing_cast<result_type, Policy>(
      detail::hypergeometric_1F1_regularized_imp<value_type>(
         static_cast<value_type>(a),
         static_cast<value_type>(b),
         static_cast<value_type>(z),
         forwarding_policy()),
      "boost::math::hypergeometric_1F1<%1%>(%1%,%1%,%1%)");
}

template <class T1, class T2, class T3>
inline typename tools::promote_args<T1, T2, T3>::type hypergeometric_1F1_regularized(T1 a, T2 b, T3 z)
{
   return hypergeometric_1F1_regularized(a, b, z, policies::policy<>());
}

template <class T1, class T2, class T3, class Policy>
inline typename tools::promote_args<T1, T2, T3>::type log_hypergeometric_1F1(T1 a, T2 b, T3 z, const Policy& /* pol */)
{
  BOOST_FPU_EXCEPTION_GUARD
    typedef typename tools::promote_args<T1, T2, T3>::type result_type;
  typedef typename policies::evaluation<result_type, Policy>::type value_type;
  typedef typename policies::normalise<
    Policy,
    policies::promote_float<false>,
    policies::promote_double<false>,
    policies::discrete_quantile<>,
    policies::assert_undefined<> >::type forwarding_policy;
  return policies::checked_narrowing_cast<result_type, Policy>(
    detail::log_hypergeometric_1F1_imp<value_type>(
      static_cast<value_type>(a),
      static_cast<value_type>(b),
      static_cast<value_type>(z),
      0,
      forwarding_policy()),
    "boost::math::hypergeometric_1F1<%1%>(%1%,%1%,%1%)");
}

template <class T1, class T2, class T3>
inline typename tools::promote_args<T1, T2, T3>::type log_hypergeometric_1F1(T1 a, T2 b, T3 z)
{
  return log_hypergeometric_1F1(a, b, z, policies::policy<>());
}

template <class T1, class T2, class T3, class Policy>
inline typename tools::promote_args<T1, T2, T3>::type log_hypergeometric_1F1(T1 a, T2 b, T3 z, int* sign, const Policy& /* pol */)
{
  BOOST_FPU_EXCEPTION_GUARD
    typedef typename tools::promote_args<T1, T2, T3>::type result_type;
  typedef typename policies::evaluation<result_type, Policy>::type value_type;
  typedef typename policies::normalise<
    Policy,
    policies::promote_float<false>,
    policies::promote_double<false>,
    policies::discrete_quantile<>,
    policies::assert_undefined<> >::type forwarding_policy;
  return policies::checked_narrowing_cast<result_type, Policy>(
    detail::log_hypergeometric_1F1_imp<value_type>(
      static_cast<value_type>(a),
      static_cast<value_type>(b),
      static_cast<value_type>(z),
      sign,
      forwarding_policy()),
    "boost::math::hypergeometric_1F1<%1%>(%1%,%1%,%1%)");
}

template <class T1, class T2, class T3>
inline typename tools::promote_args<T1, T2, T3>::type log_hypergeometric_1F1(T1 a, T2 b, T3 z, int* sign)
{
  return log_hypergeometric_1F1(a, b, z, sign, policies::policy<>());
}


  } } // namespace boost::math

#endif // BOOST_MATH_HYPERGEOMETRIC_HPP

/* hypergeometric_1F1.hpp
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
*/