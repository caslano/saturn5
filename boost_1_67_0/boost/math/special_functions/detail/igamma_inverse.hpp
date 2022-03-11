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
   boost::uintmax_t max_iter = policies::get_max_root_iterations<Policy>();
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
   boost::uintmax_t max_iter = policies::get_max_root_iterations<Policy>();
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