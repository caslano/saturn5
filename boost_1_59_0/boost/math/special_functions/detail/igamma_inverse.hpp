//  (C) Copyright John Maddock 2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_SPECIAL_FUNCTIONS_IGAMMA_INVERSE_HPP
#define BOOST_MATH_SPECIAL_FUNCTIONS_IGAMMA_INVERSE_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/tools/tuple.hpp>
#include <boost/math/special_functions/gamma.hpp>
#include <boost/math/special_functions/sign.hpp>
#include <boost/math/tools/roots.hpp>
#include <boost/math/policies/error_handling.hpp>

namespace boost{ namespace math{

namespace detail{

template <class T>
T find_inverse_s(T p, T q)
{
   //
   // Computation of the Incomplete Gamma Function Ratios and their Inverse
   // ARMIDO R. DIDONATO and ALFRED H. MORRIS, JR.
   // ACM Transactions on Mathematical Software, Vol. 12, No. 4,
   // December 1986, Pages 377-393.
   //
   // See equation 32.
   //
   BOOST_MATH_STD_USING
   T t;
   if(p < 0.5)
   {
      t = sqrt(-2 * log(p));
   }
   else
   {
      t = sqrt(-2 * log(q));
   }
   static const double a[4] = { 3.31125922108741, 11.6616720288968, 4.28342155967104, 0.213623493715853 };
   static const double b[5] = { 1, 6.61053765625462, 6.40691597760039, 1.27364489782223, 0.3611708101884203e-1 };
   T s = t - tools::evaluate_polynomial(a, t) / tools::evaluate_polynomial(b, t);
   if(p < 0.5)
      s = -s;
   return s;
}

template <class T>
T didonato_SN(T a, T x, unsigned N, T tolerance = 0)
{
   //
   // Computation of the Incomplete Gamma Function Ratios and their Inverse
   // ARMIDO R. DIDONATO and ALFRED H. MORRIS, JR.
   // ACM Transactions on Mathematical Software, Vol. 12, No. 4,
   // December 1986, Pages 377-393.
   //
   // See equation 34.
   //
   T sum = 1;
   if(N >= 1)
   {
      T partial = x / (a + 1);
      sum += partial;
      for(unsigned i = 2; i <= N; ++i)
      {
         partial *= x / (a + i);
         sum += partial;
         if(partial < tolerance)
            break;
      }
   }
   return sum;
}

template <class T, class Policy>
inline T didonato_FN(T p, T a, T x, unsigned N, T tolerance, const Policy& pol)
{
   //
   // Computation of the Incomplete Gamma Function Ratios and their Inverse
   // ARMIDO R. DIDONATO and ALFRED H. MORRIS, JR.
   // ACM Transactions on Mathematical Software, Vol. 12, No. 4,
   // December 1986, Pages 377-393.
   //
   // See equation 34.
   //
   BOOST_MATH_STD_USING
   T u = log(p) + boost::math::lgamma(a + 1, pol);
   return exp((u + x - log(didonato_SN(a, x, N, tolerance))) / a);
}

template <class T, class Policy>
T find_inverse_gamma(T a, T p, T q, const Policy& pol, bool* p_has_10_digits)
{
   //
   // In order to understand what's going on here, you will
   // need to refer to:
   //
   // Computation of the Incomplete Gamma Function Ratios and their Inverse
   // ARMIDO R. DIDONATO and ALFRED H. MORRIS, JR.
   // ACM Transactions on Mathematical Software, Vol. 12, No. 4,
   // December 1986, Pages 377-393.
   //
   BOOST_MATH_STD_USING

   T result;
   *p_has_10_digits = false;

   if(a == 1)
   {
      result = -log(q);
      BOOST_MATH_INSTRUMENT_VARIABLE(result);
   }
   else if(a < 1)
   {
      T g = boost::math::tgamma(a, pol);
      T b = q * g;
      BOOST_MATH_INSTRUMENT_VARIABLE(g);
      BOOST_MATH_INSTRUMENT_VARIABLE(b);
      if((b > 0.6) || ((b >= 0.45) && (a >= 0.3)))
      {
         // DiDonato & Morris Eq 21: 
         //
         // There is a slight variation from DiDonato and Morris here:
         // the first form given here is unstable when p is close to 1,
         // making it impossible to compute the inverse of Q(a,x) for small
         // q.  Fortunately the second form works perfectly well in this case.
         //
         T u;
         if((b * q > 1e-8) && (q > 1e-5))
         {
            u = pow(p * g * a, 1 / a);
            BOOST_MATH_INSTRUMENT_VARIABLE(u);
         }
         else
         {
            u = exp((-q / a) - constants::euler<T>());
            BOOST_MATH_INSTRUMENT_VARIABLE(u);
         }
         result = u / (1 - (u / (a + 1)));
         BOOST_MATH_INSTRUMENT_VARIABLE(result);
      }
      else if((a < 0.3) && (b >= 0.35))
      {
         // DiDonato & Morris Eq 22:
         T t = exp(-constants::euler<T>() - b);
         T u = t * exp(t);
         result = t * exp(u);
         BOOST_MATH_INSTRUMENT_VARIABLE(result);
      }
      else if((b > 0.15) || (a >= 0.3))
      {
         // DiDonato & Morris Eq 23:
         T y = -log(b);
         T u = y - (1 - a) * log(y);
         result = y - (1 - a) * log(u) - log(1 + (1 - a) / (1 + u));
         BOOST_MATH_INSTRUMENT_VARIABLE(result);
      }
      else if (b > 0.1)
      {
         // DiDonato & Morris Eq 24:
         T y = -log(b);
         T u = y - (1 - a) * log(y);
         result = y - (1 - a) * log(u) - log((u * u + 2 * (3 - a) * u + (2 - a) * (3 - a)) / (u * u + (5 - a) * u + 2));
         BOOST_MATH_INSTRUMENT_VARIABLE(result);
      }
      else
      {
         // DiDonato & Morris Eq 25:
         T y = -log(b);
         T c1 = (a - 1) * log(y);
         T c1_2 = c1 * c1;
         T c1_3 = c1_2 * c1;
         T c1_4 = c1_2 * c1_2;
         T a_2 = a * a;
         T a_3 = a_2 * a;

         T c2 = (a - 1) * (1 + c1);
         T c3 = (a - 1) * (-(c1_2 / 2) + (a - 2) * c1 + (3 * a - 5) / 2);
         T c4 = (a - 1) * ((c1_3 / 3) - (3 * a - 5) * c1_2 / 2 + (a_2 - 6 * a + 7) * c1 + (11 * a_2 - 46 * a + 47) / 6);
         T c5 = (a - 1) * (-(c1_4 / 4)
                           + (11 * a - 17) * c1_3 / 6
                           + (-3 * a_2 + 13 * a -13) * c1_2
                           + (2 * a_3 - 25 * a_2 + 72 * a - 61) * c1 / 2
                           + (25 * a_3 - 195 * a_2 + 477 * a - 379) / 12);

         T y_2 = y * y;
         T y_3 = y_2 * y;
         T y_4 = y_2 * y_2;
         result = y + c1 + (c2 / y) + (c3 / y_2) + (c4 / y_3) + (c5 / y_4);
         BOOST_MATH_INSTRUMENT_VARIABLE(result);
         if(b < 1e-28f)
            *p_has_10_digits = true;
      }
   }
   else
   {
      // DiDonato and Morris Eq 31:
      T s = find_inverse_s(p, q);

      BOOST_MATH_INSTRUMENT_VARIABLE(s);

      T s_2 = s * s;
      T s_3 = s_2 * s;
      T s_4 = s_2 * s_2;
      T s_5 = s_4 * s;
      T ra = sqrt(a);

      BOOST_MATH_INSTRUMENT_VARIABLE(ra);

      T w = a + s * ra + (s * s -1) / 3;
      w += (s_3 - 7 * s) / (36 * ra);
      w -= (3 * s_4 + 7 * s_2 - 16) / (810 * a);
      w += (9 * s_5 + 256 * s_3 - 433 * s) / (38880 * a * ra);

      BOOST_MATH_INSTRUMENT_VARIABLE(w);

      if((a >= 500) && (fabs(1 - w / a) < 1e-6))
      {
         result = w;
         *p_has_10_digits = true;
         BOOST_MATH_INSTRUMENT_VARIABLE(result);
      }
      else if (p > 0.5)
      {
         if(w < 3 * a)
         {
            result = w;
            BOOST_MATH_INSTRUMENT_VARIABLE(result);
         }
         else
         {
            T D = (std::max)(T(2), T(a * (a - 1)));
            T lg = boost::math::lgamma(a, pol);
            T lb = log(q) + lg;
            if(lb < -D * 2.3)
            {
               // DiDonato and Morris Eq 25:
               T y = -lb;
               T c1 = (a - 1) * log(y);
               T c1_2 = c1 * c1;
               T c1_3 = c1_2 * c1;
               T c1_4 = c1_2 * c1_2;
               T a_2 = a * a;
               T a_3 = a_2 * a;

               T c2 = (a - 1) * (1 + c1);
               T c3 = (a - 1) * (-(c1_2 / 2) + (a - 2) * c1 + (3 * a - 5) / 2);
               T c4 = (a - 1) * ((c1_3 / 3) - (3 * a - 5) * c1_2 / 2 + (a_2 - 6 * a + 7) * c1 + (11 * a_2 - 46 * a + 47) / 6);
               T c5 = (a - 1) * (-(c1_4 / 4)
                                 + (11 * a - 17) * c1_3 / 6
                                 + (-3 * a_2 + 13 * a -13) * c1_2
                                 + (2 * a_3 - 25 * a_2 + 72 * a - 61) * c1 / 2
                                 + (25 * a_3 - 195 * a_2 + 477 * a - 379) / 12);

               T y_2 = y * y;
               T y_3 = y_2 * y;
               T y_4 = y_2 * y_2;
               result = y + c1 + (c2 / y) + (c3 / y_2) + (c4 / y_3) + (c5 / y_4);
               BOOST_MATH_INSTRUMENT_VARIABLE(result);
            }
            else
            {
               // DiDonato and Morris Eq 33:
               T u = -lb + (a - 1) * log(w) - log(1 + (1 - a) / (1 + w));
               result = -lb + (a - 1) * log(u) - log(1 + (1 - a) / (1 + u));
               BOOST_MATH_INSTRUMENT_VARIABLE(result);
            }
         }
      }
      else
      {
         T z = w;
         T ap1 = a + 1;
         T ap2 = a + 2;
         if(w < 0.15f * ap1)
         {
            // DiDonato and Morris Eq 35:
            T v = log(p) + boost::math::lgamma(ap1, pol);
            z = exp((v + w) / a);
            s = boost::math::log1p(z / ap1 * (1 + z / ap2), pol);
            z = exp((v + z - s) / a);
            s = boost::math::log1p(z / ap1 * (1 + z / ap2), pol);
            z = exp((v + z - s) / a);
            s = boost::math::log1p(z / ap1 * (1 + z / ap2 * (1 + z / (a + 3))), pol);
            z = exp((v + z - s) / a);
            BOOST_MATH_INSTRUMENT_VARIABLE(z);
         }

         if((z <= 0.01 * ap1) || (z > 0.7 * ap1))
         {
            result = z;
            if(z <= 0.002 * ap1)
               *p_has_10_digits = true;
            BOOST_MATH_INSTRUMENT_VARIABLE(result);
         }
         else
         {
            // DiDonato and Morris Eq 36:
            T ls = log(didonato_SN(a, z, 100, T(1e-4)));
            T v = log(p) + boost::math::lgamma(ap1, pol);
            z = exp((v + z - ls) / a);
            result = z * (1 - (a * log(z) - z - v + ls) / (a - z));

            BOOST_MATH_INSTRUMENT_VARIABLE(result);
         }
      }
   }
   return result;
}

template <class T, class Policy>
struct gamma_p_inverse_func
{
   gamma_p_inverse_func(T a_, T p_, bool inv) : a(a_), p(p_), invert(inv)
   {
      //
      // If p is too near 1 then P(x) - p suffers from cancellation
      // errors causing our root-finding algorithms to "thrash", better
      // to invert in this case and calculate Q(x) - (1-p) instead.
      //
      // Of course if p is *very* close to 1, then the answer we get will
      // be inaccurate anyway (because there's not enough information in p)
      // but at least we will converge on the (inaccurate) answer quickly.
      //
      if(p > 0.9)
      {
         p = 1 - p;
         invert = !invert;
      }
   }

   boost::math::tuple<T, T, T> operator()(const T& x)const
   {
      BOOST_FPU_EXCEPTION_GUARD
      //
      // Calculate P(x) - p and the first two derivates, or if the invert
      // flag is set, then Q(x) - q and it's derivatives.
      //
      typedef typename policies::evaluation<T, Policy>::type value_type;
      // typedef typename lanczos::lanczos<T, Policy>::type evaluation_type;
      typedef typename policies::normalise<
         Policy, 
         policies::promote_float<false>, 
         policies::promote_double<false>, 
         policies::discrete_quantile<>,
         policies::assert_undefined<> >::type forwarding_policy;

      BOOST_MATH_STD_USING  // For ADL of std functions.

      T f, f1;
      value_type ft;
      f = static_cast<T>(boost::math::detail::gamma_incomplete_imp(
               static_cast<value_type>(a), 
               static_cast<value_type>(x), 
               true, invert,
               forwarding_policy(), &ft));
      f1 = static_cast<T>(ft);
      T f2;
      T div = (a - x - 1) / x;
      f2 = f1;
      if((fabs(div) > 1) && (tools::max_value<T>() / fabs(div) < f2))
      {
         // overflow:
         f2 = -tools::max_value<T>() / 2;
      }
      else
      {
         f2 *= div;
      }

      if(invert)
      {
         f1 = -f1;
         f2 = -f2;
      }

      return boost::math::make_tuple(static_cast<T>(f - p), f1, f2);
   }
private:
   T a, p;
   bool invert;
};

template <class T, class Policy>
T gamma_p_inv_imp(T a, T p, const Policy& pol)
{
   BOOST_MATH_STD_USING  // ADL of std functions.

   static const char* function = "boost::math::gamma_p_inv<%1%>(%1%, %1%)";

   BOOST_MATH_INSTRUMENT_VARIABLE(a);
   BOOST_MATH_INSTRUMENT_VARIABLE(p);

   if(a <= 0)
      return policies::raise_domain_error<T>(function, "Argument a in the incomplete gamma function inverse must be >= 0 (got a=%1%).", a, pol);
   if((p < 0) || (p > 1))
      return policies::raise_domain_error<T>(function, "Probability must be in the range [0,1] in the incomplete gamma function inverse (got p=%1%).", p, pol);
   if(p == 1)
      return policies::raise_overflow_error<T>(function, 0, Policy());
   if(p == 0)
      return 0;
   bool has_10_digits;
   T guess = detail::find_inverse_gamma<T>(a, p, 1 - p, pol, &has_10_digits);
   if((policies::digits<T, Policy>() <= 36) && has_10_digits)
      return guess;
   T lower = tools::min_value<T>();
   if(guess <= lower)
      guess = tools::min_value<T>();
   BOOST_MATH_INSTRUMENT_VARIABLE(guess);
   //
   // Work out how many digits to converge to, normally this is
   // 2/3 of the digits in T, but if the first derivative is very
   // large convergence is slow, so we'll bump it up to full 
   // precision to prevent premature termination of the root-finding routine.
   //
   unsigned digits = policies::digits<T, Policy>();
   if(digits < 30)
   {
      digits *= 2;
      digits /= 3;
   }
   else
   {
      digits /= 2;
      digits -= 1;
   }
   if((a < 0.125) && (fabs(gamma_p_derivative(a, guess, pol)) > 1 / sqrt(tools::epsilon<T>())))
      digits = policies::digits<T, Policy>() - 2;
   //
   // Go ahead and iterate:
   //
   std::uintmax_t max_iter = policies::get_max_root_iterations<Policy>();
   guess = tools::halley_iterate(
      detail::gamma_p_inverse_func<T, Policy>(a, p, false),
      guess,
      lower,
      tools::max_value<T>(),
      digits,
      max_iter);
   policies::check_root_iterations<T>(function, max_iter, pol);
   BOOST_MATH_INSTRUMENT_VARIABLE(guess);
   if(guess == lower)
      guess = policies::raise_underflow_error<T>(function, "Expected result known to be non-zero, but is smaller than the smallest available number.", pol);
   return guess;
}

template <class T, class Policy>
T gamma_q_inv_imp(T a, T q, const Policy& pol)
{
   BOOST_MATH_STD_USING  // ADL of std functions.

   static const char* function = "boost::math::gamma_q_inv<%1%>(%1%, %1%)";

   if(a <= 0)
      return policies::raise_domain_error<T>(function, "Argument a in the incomplete gamma function inverse must be >= 0 (got a=%1%).", a, pol);
   if((q < 0) || (q > 1))
      return policies::raise_domain_error<T>(function, "Probability must be in the range [0,1] in the incomplete gamma function inverse (got q=%1%).", q, pol);
   if(q == 0)
      return policies::raise_overflow_error<T>(function, 0, Policy());
   if(q == 1)
      return 0;
   bool has_10_digits;
   T guess = detail::find_inverse_gamma<T>(a, 1 - q, q, pol, &has_10_digits);
   if((policies::digits<T, Policy>() <= 36) && has_10_digits)
      return guess;
   T lower = tools::min_value<T>();
   if(guess <= lower)
      guess = tools::min_value<T>();
   //
   // Work out how many digits to converge to, normally this is
   // 2/3 of the digits in T, but if the first derivative is very
   // large convergence is slow, so we'll bump it up to full 
   // precision to prevent premature termination of the root-finding routine.
   //
   unsigned digits = policies::digits<T, Policy>();
   if(digits < 30)
   {
      digits *= 2;
      digits /= 3;
   }
   else
   {
      digits /= 2;
      digits -= 1;
   }
   if((a < 0.125) && (fabs(gamma_p_derivative(a, guess, pol)) > 1 / sqrt(tools::epsilon<T>())))
      digits = policies::digits<T, Policy>();
   //
   // Go ahead and iterate:
   //
   std::uintmax_t max_iter = policies::get_max_root_iterations<Policy>();
   guess = tools::halley_iterate(
      detail::gamma_p_inverse_func<T, Policy>(a, q, true),
      guess,
      lower,
      tools::max_value<T>(),
      digits,
      max_iter);
   policies::check_root_iterations<T>(function, max_iter, pol);
   if(guess == lower)
      guess = policies::raise_underflow_error<T>(function, "Expected result known to be non-zero, but is smaller than the smallest available number.", pol);
   return guess;
}

} // namespace detail

template <class T1, class T2, class Policy>
inline typename tools::promote_args<T1, T2>::type 
   gamma_p_inv(T1 a, T2 p, const Policy& pol)
{
   typedef typename tools::promote_args<T1, T2>::type result_type;
   return detail::gamma_p_inv_imp(
      static_cast<result_type>(a),
      static_cast<result_type>(p), pol);
}

template <class T1, class T2, class Policy>
inline typename tools::promote_args<T1, T2>::type 
   gamma_q_inv(T1 a, T2 p, const Policy& pol)
{
   typedef typename tools::promote_args<T1, T2>::type result_type;
   return detail::gamma_q_inv_imp(
      static_cast<result_type>(a),
      static_cast<result_type>(p), pol);
}

template <class T1, class T2>
inline typename tools::promote_args<T1, T2>::type 
   gamma_p_inv(T1 a, T2 p)
{
   return gamma_p_inv(a, p, policies::policy<>());
}

template <class T1, class T2>
inline typename tools::promote_args<T1, T2>::type 
   gamma_q_inv(T1 a, T2 p)
{
   return gamma_q_inv(a, p, policies::policy<>());
}

} // namespace math
} // namespace boost

#endif // BOOST_MATH_SPECIAL_FUNCTIONS_IGAMMA_INVERSE_HPP




/* igamma_inverse.hpp
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
*/