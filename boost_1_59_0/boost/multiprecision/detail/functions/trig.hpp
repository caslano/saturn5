
// Copyright Christopher Kormanyos 2002 - 2011.
// Copyright 2011 John Maddock.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469
//
// This file has no include guards or namespaces - it's expanded inline inside default_ops.hpp
//

#include <boost/multiprecision/detail/standalone_config.hpp>
#include <boost/multiprecision/detail/no_exceptions_support.hpp>
#include <boost/multiprecision/detail/assert.hpp>

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable : 6326) // comparison of two constants
#pragma warning(disable : 4127) // conditional expression is constant
#endif

template <class T>
void hyp0F1(T& result, const T& b, const T& x)
{
   using si_type = typename boost::multiprecision::detail::canonical<std::int32_t, T>::type ;
   using ui_type = typename boost::multiprecision::detail::canonical<std::uint32_t, T>::type;

   // Compute the series representation of Hypergeometric0F1 taken from
   // http://functions.wolfram.com/HypergeometricFunctions/Hypergeometric0F1/06/01/01/
   // There are no checks on input range or parameter boundaries.

   T x_pow_n_div_n_fact(x);
   T pochham_b(b);
   T bp(b);

   eval_divide(result, x_pow_n_div_n_fact, pochham_b);
   eval_add(result, ui_type(1));

   si_type n;

   T tol;
   tol = ui_type(1);
   eval_ldexp(tol, tol, 1 - boost::multiprecision::detail::digits2<number<T, et_on> >::value());
   eval_multiply(tol, result);
   if (eval_get_sign(tol) < 0)
      tol.negate();
   T term;

   const int series_limit =
       boost::multiprecision::detail::digits2<number<T, et_on> >::value() < 100
           ? 100
           : boost::multiprecision::detail::digits2<number<T, et_on> >::value();
   // Series expansion of hyperg_0f1(; b; x).
   for (n = 2; n < series_limit; ++n)
   {
      eval_multiply(x_pow_n_div_n_fact, x);
      eval_divide(x_pow_n_div_n_fact, n);
      eval_increment(bp);
      eval_multiply(pochham_b, bp);

      eval_divide(term, x_pow_n_div_n_fact, pochham_b);
      eval_add(result, term);

      bool neg_term = eval_get_sign(term) < 0;
      if (neg_term)
         term.negate();
      if (term.compare(tol) <= 0)
         break;
   }

   if (n >= series_limit)
      BOOST_MP_THROW_EXCEPTION(std::runtime_error("H0F1 Failed to Converge"));
}

template <class T, unsigned N, bool b = boost::multiprecision::detail::is_variable_precision<boost::multiprecision::number<T> >::value>
struct scoped_N_precision
{
   template <class U>
   scoped_N_precision(U const&) {}
   template <class U>
   void reduce(U&) {}
};

template <class T, unsigned N>
struct scoped_N_precision<T, N, true>
{
   unsigned old_precision, old_arg_precision;
   scoped_N_precision(T& arg)
   {
      old_precision     = T::thread_default_precision();
      old_arg_precision = arg.precision();
      T::thread_default_precision(old_arg_precision * N);
      arg.precision(old_arg_precision * N);
   }
   ~scoped_N_precision()
   {
      T::thread_default_precision(old_precision);
   }
   void reduce(T& arg) 
   {
      arg.precision(old_arg_precision);
   }
};

template <class T>
void reduce_n_half_pi(T& arg, const T& n, bool go_down)
{
   //
   // We need to perform argument reduction at 3 times the precision of arg
   // in order to ensure a correct result up to arg = 1/epsilon.  Beyond that
   // the value of n will have been incorrectly calculated anyway since it will
   // have a value greater than 1/epsilon and no longer be an exact integer value.
   //
   // More information in ARGUMENT REDUCTION FOR HUGE ARGUMENTS. K C Ng.
   //
   // There are two mutually exclusive ways to achieve this, both of which are 
   // supported here:
   // 1) To define a fixed precision type with 3 times the precision for the calculation.
   // 2) To dynamically increase the precision of the variables.
   //
   using reduction_type = typename boost::multiprecision::detail::transcendental_reduction_type<T>::type;
   //
   // Make a copy of the arg at higher precision:
   //
   reduction_type big_arg(arg);
   //
   // Dynamically increase precision when supported, this increases the default
   // and ups the precision of big_arg to match:
   //
   scoped_N_precision<T, 3> scoped_precision(big_arg);
   //
   // High precision PI:
   //
   reduction_type reduction = get_constant_pi<reduction_type>();
   eval_ldexp(reduction, reduction, -1); // divide by 2
   eval_multiply(reduction, n);

   BOOST_MATH_INSTRUMENT_CODE(big_arg.str(10, std::ios_base::scientific));
   BOOST_MATH_INSTRUMENT_CODE(reduction.str(10, std::ios_base::scientific));

   if (go_down)
      eval_subtract(big_arg, reduction, big_arg);
   else
      eval_subtract(big_arg, reduction);
   arg = T(big_arg);
   //
   // If arg is a variable precision type, then we have just copied the
   // precision of big_arg s well it's value.  Reduce the precision now:
   //
   scoped_precision.reduce(arg);
   BOOST_MATH_INSTRUMENT_CODE(big_arg.str(10, std::ios_base::scientific));
   BOOST_MATH_INSTRUMENT_CODE(arg.str(10, std::ios_base::scientific));
}

template <class T>
void eval_sin(T& result, const T& x)
{
   static_assert(number_category<T>::value == number_kind_floating_point, "The sin function is only valid for floating point types.");
   BOOST_MATH_INSTRUMENT_CODE(x.str(0, std::ios_base::scientific));
   if (&result == &x)
   {
      T temp;
      eval_sin(temp, x);
      result = temp;
      return;
   }

   using si_type = typename boost::multiprecision::detail::canonical<std::int32_t, T>::type ;
   using ui_type = typename boost::multiprecision::detail::canonical<std::uint32_t, T>::type;
   using fp_type = typename std::tuple_element<0, typename T::float_types>::type                         ;

   switch (eval_fpclassify(x))
   {
   case FP_INFINITE:
   case FP_NAN:
      BOOST_IF_CONSTEXPR(std::numeric_limits<number<T, et_on> >::has_quiet_NaN)
      {
         result = std::numeric_limits<number<T, et_on> >::quiet_NaN().backend();
         errno  = EDOM;
      }
      else
         BOOST_MP_THROW_EXCEPTION(std::domain_error("Result is undefined or complex and there is no NaN for this number type."));
      return;
   case FP_ZERO:
      result = x;
      return;
   default:;
   }

   // Local copy of the argument
   T xx = x;

   // Analyze and prepare the phase of the argument.
   // Make a local, positive copy of the argument, xx.
   // The argument xx will be reduced to 0 <= xx <= pi/2.
   bool b_negate_sin = false;

   if (eval_get_sign(x) < 0)
   {
      xx.negate();
      b_negate_sin = !b_negate_sin;
   }

   T n_pi, t;
   T half_pi = get_constant_pi<T>();
   eval_ldexp(half_pi, half_pi, -1); // divide by 2
   // Remove multiples of pi/2.
   if (xx.compare(half_pi) > 0)
   {
      eval_divide(n_pi, xx, half_pi);
      eval_trunc(n_pi, n_pi);
      t = ui_type(4);
      eval_fmod(t, n_pi, t);
      bool b_go_down = false;
      if (t.compare(ui_type(1)) == 0)
      {
         b_go_down = true;
      }
      else if (t.compare(ui_type(2)) == 0)
      {
         b_negate_sin = !b_negate_sin;
      }
      else if (t.compare(ui_type(3)) == 0)
      {
         b_negate_sin = !b_negate_sin;
         b_go_down    = true;
      }

      if (b_go_down)
         eval_increment(n_pi);
      //
      // If n_pi is > 1/epsilon, then it is no longer an exact integer value
      // but an approximation.  As a result we can no longer reliably reduce
      // xx to 0 <= xx < pi/2, nor can we tell the sign of the result as we need
      // n_pi % 4 for that, but that will always be zero in this situation.
      // We could use a higher precision type for n_pi, along with division at
      // higher precision, but that's rather expensive.  So for now we do not support
      // this, and will see if anyone complains and has a legitimate use case.
      //
      if (n_pi.compare(get_constant_one_over_epsilon<T>()) > 0)
      {
         result = ui_type(0);
         return;
      }

      reduce_n_half_pi(xx, n_pi, b_go_down);
      //
      // Post reduction we may be a few ulp below zero or above pi/2
      // given that n_pi was calculated at working precision and not
      // at the higher precision used for reduction.  Correct that now:
      //
      if (eval_get_sign(xx) < 0)
      {
         xx.negate();
         b_negate_sin = !b_negate_sin;
      }
      if (xx.compare(half_pi) > 0)
      {
         eval_ldexp(half_pi, half_pi, 1);
         eval_subtract(xx, half_pi, xx);
         eval_ldexp(half_pi, half_pi, -1);
         b_go_down = !b_go_down;
      }

      BOOST_MATH_INSTRUMENT_CODE(xx.str(0, std::ios_base::scientific));
      BOOST_MATH_INSTRUMENT_CODE(n_pi.str(0, std::ios_base::scientific));
      BOOST_MP_ASSERT(xx.compare(half_pi) <= 0);
      BOOST_MP_ASSERT(xx.compare(ui_type(0)) >= 0);
   }

   t = half_pi;
   eval_subtract(t, xx);

   const bool b_zero    = eval_get_sign(xx) == 0;
   const bool b_pi_half = eval_get_sign(t) == 0;

   BOOST_MATH_INSTRUMENT_CODE(xx.str(0, std::ios_base::scientific));
   BOOST_MATH_INSTRUMENT_CODE(t.str(0, std::ios_base::scientific));

   // Check if the reduced argument is very close to 0 or pi/2.
   const bool b_near_zero    = xx.compare(fp_type(1e-1)) < 0;
   const bool b_near_pi_half = t.compare(fp_type(1e-1)) < 0;

   if (b_zero)
   {
      result = ui_type(0);
   }
   else if (b_pi_half)
   {
      result = ui_type(1);
   }
   else if (b_near_zero)
   {
      eval_multiply(t, xx, xx);
      eval_divide(t, si_type(-4));
      T t2;
      t2 = fp_type(1.5);
      hyp0F1(result, t2, t);
      BOOST_MATH_INSTRUMENT_CODE(result.str(0, std::ios_base::scientific));
      eval_multiply(result, xx);
   }
   else if (b_near_pi_half)
   {
      eval_multiply(t, t);
      eval_divide(t, si_type(-4));
      T t2;
      t2 = fp_type(0.5);
      hyp0F1(result, t2, t);
      BOOST_MATH_INSTRUMENT_CODE(result.str(0, std::ios_base::scientific));
   }
   else
   {
      // Scale to a small argument for an efficient Taylor series,
      // implemented as a hypergeometric function. Use a standard
      // divide by three identity a certain number of times.
      // Here we use division by 3^9 --> (19683 = 3^9).

      constexpr const si_type n_scale           = 9;
      constexpr const si_type n_three_pow_scale = static_cast<si_type>(19683L);

      eval_divide(xx, n_three_pow_scale);

      // Now with small arguments, we are ready for a series expansion.
      eval_multiply(t, xx, xx);
      eval_divide(t, si_type(-4));
      T t2;
      t2 = fp_type(1.5);
      hyp0F1(result, t2, t);
      BOOST_MATH_INSTRUMENT_CODE(result.str(0, std::ios_base::scientific));
      eval_multiply(result, xx);

      // Convert back using multiple angle identity.
      for (std::int32_t k = static_cast<std::int32_t>(0); k < n_scale; k++)
      {
         // Rescale the cosine value using the multiple angle identity.
         eval_multiply(t2, result, ui_type(3));
         eval_multiply(t, result, result);
         eval_multiply(t, result);
         eval_multiply(t, ui_type(4));
         eval_subtract(result, t2, t);
      }
   }

   if (b_negate_sin)
      result.negate();
   BOOST_MATH_INSTRUMENT_CODE(result.str(0, std::ios_base::scientific));
}

template <class T>
void eval_cos(T& result, const T& x)
{
   static_assert(number_category<T>::value == number_kind_floating_point, "The cos function is only valid for floating point types.");
   if (&result == &x)
   {
      T temp;
      eval_cos(temp, x);
      result = temp;
      return;
   }

   using si_type = typename boost::multiprecision::detail::canonical<std::int32_t, T>::type ;
   using ui_type = typename boost::multiprecision::detail::canonical<std::uint32_t, T>::type;

   switch (eval_fpclassify(x))
   {
   case FP_INFINITE:
   case FP_NAN:
      BOOST_IF_CONSTEXPR(std::numeric_limits<number<T, et_on> >::has_quiet_NaN)
      {
         result = std::numeric_limits<number<T, et_on> >::quiet_NaN().backend();
         errno  = EDOM;
      }
      else
         BOOST_MP_THROW_EXCEPTION(std::domain_error("Result is undefined or complex and there is no NaN for this number type."));
      return;
   case FP_ZERO:
      result = ui_type(1);
      return;
   default:;
   }

   // Local copy of the argument
   T xx = x;

   // Analyze and prepare the phase of the argument.
   // Make a local, positive copy of the argument, xx.
   // The argument xx will be reduced to 0 <= xx <= pi/2.
   bool b_negate_cos = false;

   if (eval_get_sign(x) < 0)
   {
      xx.negate();
   }
   BOOST_MATH_INSTRUMENT_CODE(xx.str(0, std::ios_base::scientific));

   T n_pi, t;
   T half_pi = get_constant_pi<T>();
   eval_ldexp(half_pi, half_pi, -1); // divide by 2
   // Remove even multiples of pi.
   if (xx.compare(half_pi) > 0)
   {
      eval_divide(t, xx, half_pi);
      eval_trunc(n_pi, t);
      //
      // If n_pi is > 1/epsilon, then it is no longer an exact integer value
      // but an approximation.  As a result we can no longer reliably reduce
      // xx to 0 <= xx < pi/2, nor can we tell the sign of the result as we need
      // n_pi % 4 for that, but that will always be zero in this situation.
      // We could use a higher precision type for n_pi, along with division at
      // higher precision, but that's rather expensive.  So for now we do not support
      // this, and will see if anyone complains and has a legitimate use case.
      //
      if (n_pi.compare(get_constant_one_over_epsilon<T>()) > 0)
      {
         result = ui_type(1);
         return;
      }
      BOOST_MATH_INSTRUMENT_CODE(n_pi.str(0, std::ios_base::scientific));
      t = ui_type(4);
      eval_fmod(t, n_pi, t);

      bool b_go_down = false;
      if (t.compare(ui_type(0)) == 0)
      {
         b_go_down = true;
      }
      else if (t.compare(ui_type(1)) == 0)
      {
         b_negate_cos = true;
      }
      else if (t.compare(ui_type(2)) == 0)
      {
         b_go_down    = true;
         b_negate_cos = true;
      }
      else
      {
         BOOST_MP_ASSERT(t.compare(ui_type(3)) == 0);
      }

      if (b_go_down)
         eval_increment(n_pi);

      reduce_n_half_pi(xx, n_pi, b_go_down);
      //
      // Post reduction we may be a few ulp below zero or above pi/2
      // given that n_pi was calculated at working precision and not
      // at the higher precision used for reduction.  Correct that now:
      //
      if (eval_get_sign(xx) < 0)
      {
         xx.negate();
         b_negate_cos = !b_negate_cos;
      }
      if (xx.compare(half_pi) > 0)
      {
         eval_ldexp(half_pi, half_pi, 1);
         eval_subtract(xx, half_pi, xx);
         eval_ldexp(half_pi, half_pi, -1);
      }
      BOOST_MP_ASSERT(xx.compare(half_pi) <= 0);
      BOOST_MP_ASSERT(xx.compare(ui_type(0)) >= 0);
   }
   else
   {
      n_pi = ui_type(1);
      reduce_n_half_pi(xx, n_pi, true);
   }

   const bool b_zero = eval_get_sign(xx) == 0;

   if (b_zero)
   {
      result = si_type(0);
   }
   else
   {
      eval_sin(result, xx);
   }
   if (b_negate_cos)
      result.negate();
   BOOST_MATH_INSTRUMENT_CODE(result.str(0, std::ios_base::scientific));
}

template <class T>
void eval_tan(T& result, const T& x)
{
   static_assert(number_category<T>::value == number_kind_floating_point, "The tan function is only valid for floating point types.");
   if (&result == &x)
   {
      T temp;
      eval_tan(temp, x);
      result = temp;
      return;
   }
   T t;
   eval_sin(result, x);
   eval_cos(t, x);
   eval_divide(result, t);
}

template <class T>
void hyp2F1(T& result, const T& a, const T& b, const T& c, const T& x)
{
   // Compute the series representation of hyperg_2f1 taken from
   // Abramowitz and Stegun 15.1.1.
   // There are no checks on input range or parameter boundaries.

   using ui_type = typename boost::multiprecision::detail::canonical<std::uint32_t, T>::type;

   T x_pow_n_div_n_fact(x);
   T pochham_a(a);
   T pochham_b(b);
   T pochham_c(c);
   T ap(a);
   T bp(b);
   T cp(c);

   eval_multiply(result, pochham_a, pochham_b);
   eval_divide(result, pochham_c);
   eval_multiply(result, x_pow_n_div_n_fact);
   eval_add(result, ui_type(1));

   T lim;
   eval_ldexp(lim, result, 1 - boost::multiprecision::detail::digits2<number<T, et_on> >::value());

   if (eval_get_sign(lim) < 0)
      lim.negate();

   ui_type n;
   T       term;

   const unsigned series_limit =
       boost::multiprecision::detail::digits2<number<T, et_on> >::value() < 100
           ? 100
           : boost::multiprecision::detail::digits2<number<T, et_on> >::value();
   // Series expansion of hyperg_2f1(a, b; c; x).
   for (n = 2; n < series_limit; ++n)
   {
      eval_multiply(x_pow_n_div_n_fact, x);
      eval_divide(x_pow_n_div_n_fact, n);

      eval_increment(ap);
      eval_multiply(pochham_a, ap);
      eval_increment(bp);
      eval_multiply(pochham_b, bp);
      eval_increment(cp);
      eval_multiply(pochham_c, cp);

      eval_multiply(term, pochham_a, pochham_b);
      eval_divide(term, pochham_c);
      eval_multiply(term, x_pow_n_div_n_fact);
      eval_add(result, term);

      if (eval_get_sign(term) < 0)
         term.negate();
      if (lim.compare(term) >= 0)
         break;
   }
   if (n > series_limit)
      BOOST_MP_THROW_EXCEPTION(std::runtime_error("H2F1 failed to converge."));
}

template <class T>
void eval_asin(T& result, const T& x)
{
   static_assert(number_category<T>::value == number_kind_floating_point, "The asin function is only valid for floating point types.");
   using ui_type = typename boost::multiprecision::detail::canonical<std::uint32_t, T>::type;
   using fp_type = typename std::tuple_element<0, typename T::float_types>::type                         ;

   if (&result == &x)
   {
      T t(x);
      eval_asin(result, t);
      return;
   }

   switch (eval_fpclassify(x))
   {
   case FP_NAN:
   case FP_INFINITE:
      BOOST_IF_CONSTEXPR(std::numeric_limits<number<T, et_on> >::has_quiet_NaN)
      {
         result = std::numeric_limits<number<T, et_on> >::quiet_NaN().backend();
         errno  = EDOM;
      }
      else
         BOOST_MP_THROW_EXCEPTION(std::domain_error("Result is undefined or complex and there is no NaN for this number type."));
      return;
   case FP_ZERO:
      result = x;
      return;
   default:;
   }

   const bool b_neg = eval_get_sign(x) < 0;

   T xx(x);
   if (b_neg)
      xx.negate();

   int c = xx.compare(ui_type(1));
   if (c > 0)
   {
      BOOST_IF_CONSTEXPR(std::numeric_limits<number<T, et_on> >::has_quiet_NaN)
      {
         result = std::numeric_limits<number<T, et_on> >::quiet_NaN().backend();
         errno  = EDOM;
      }
      else
         BOOST_MP_THROW_EXCEPTION(std::domain_error("Result is undefined or complex and there is no NaN for this number type."));
      return;
   }
   else if (c == 0)
   {
      result = get_constant_pi<T>();
      eval_ldexp(result, result, -1);
      if (b_neg)
         result.negate();
      return;
   }

   if (xx.compare(fp_type(1e-3)) < 0)
   {
      // http://functions.wolfram.com/ElementaryFunctions/ArcSin/26/01/01/
      eval_multiply(xx, xx);
      T t1, t2;
      t1 = fp_type(0.5f);
      t2 = fp_type(1.5f);
      hyp2F1(result, t1, t1, t2, xx);
      eval_multiply(result, x);
      return;
   }
   else if (xx.compare(fp_type(1 - 5e-2f)) > 0)
   {
      // http://functions.wolfram.com/ElementaryFunctions/ArcSin/26/01/01/
      // This branch is simlilar in complexity to Newton iterations down to
      // the above limit.  It is *much* more accurate.
      T dx1;
      T t1, t2;
      eval_subtract(dx1, ui_type(1), xx);
      t1 = fp_type(0.5f);
      t2 = fp_type(1.5f);
      eval_ldexp(dx1, dx1, -1);
      hyp2F1(result, t1, t1, t2, dx1);
      eval_ldexp(dx1, dx1, 2);
      eval_sqrt(t1, dx1);
      eval_multiply(result, t1);
      eval_ldexp(t1, get_constant_pi<T>(), -1);
      result.negate();
      eval_add(result, t1);
      if (b_neg)
         result.negate();
      return;
   }
#ifndef BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS
   using guess_type = typename boost::multiprecision::detail::canonical<long double, T>::type;
#else
   using guess_type = fp_type;
#endif
   // Get initial estimate using standard math function asin.
   guess_type dd;
   eval_convert_to(&dd, xx);

   result = (guess_type)(std::asin(dd));

   // Newton-Raphson iteration, we should double our precision with each iteration,
   // in practice this seems to not quite work in all cases... so terminate when we
   // have at least 2/3 of the digits correct on the assumption that the correction
   // we've just added will finish the job...

   std::intmax_t current_precision = eval_ilogb(result);
   std::intmax_t target_precision  = std::numeric_limits<number<T> >::is_specialized ? 
      current_precision - 1 - (std::numeric_limits<number<T> >::digits * 2) / 3
      : current_precision - 1 - (boost::multiprecision::detail::digits2<number<T> >::value() * 2) / 3;

   // Newton-Raphson iteration
   while (current_precision > target_precision)
   {
      T sine, cosine;
      eval_sin(sine, result);
      eval_cos(cosine, result);
      eval_subtract(sine, xx);
      eval_divide(sine, cosine);
      eval_subtract(result, sine);
      current_precision = eval_ilogb(sine);
      if (current_precision <= (std::numeric_limits<typename T::exponent_type>::min)() + 1)
         break;
   }
   if (b_neg)
      result.negate();
}

template <class T>
inline void eval_acos(T& result, const T& x)
{
   static_assert(number_category<T>::value == number_kind_floating_point, "The acos function is only valid for floating point types.");
   using ui_type = typename boost::multiprecision::detail::canonical<std::uint32_t, T>::type;

   switch (eval_fpclassify(x))
   {
   case FP_NAN:
   case FP_INFINITE:
      BOOST_IF_CONSTEXPR(std::numeric_limits<number<T, et_on> >::has_quiet_NaN)
      {
         result = std::numeric_limits<number<T, et_on> >::quiet_NaN().backend();
         errno  = EDOM;
      }
      else
         BOOST_MP_THROW_EXCEPTION(std::domain_error("Result is undefined or complex and there is no NaN for this number type."));
      return;
   case FP_ZERO:
      result = get_constant_pi<T>();
      eval_ldexp(result, result, -1); // divide by two.
      return;
   }

   T xx;
   eval_abs(xx, x);
   int c = xx.compare(ui_type(1));

   if (c > 0)
   {
      BOOST_IF_CONSTEXPR(std::numeric_limits<number<T, et_on> >::has_quiet_NaN)
      {
         result = std::numeric_limits<number<T, et_on> >::quiet_NaN().backend();
         errno  = EDOM;
      }
      else
         BOOST_MP_THROW_EXCEPTION(std::domain_error("Result is undefined or complex and there is no NaN for this number type."));
      return;
   }
   else if (c == 0)
   {
      if (eval_get_sign(x) < 0)
         result = get_constant_pi<T>();
      else
         result = ui_type(0);
      return;
   }

   using fp_type = typename std::tuple_element<0, typename T::float_types>::type;

   if (xx.compare(fp_type(1e-3)) < 0)
   {
      // https://functions.wolfram.com/ElementaryFunctions/ArcCos/26/01/01/
      eval_multiply(xx, xx);
      T t1, t2;
      t1 = fp_type(0.5f);
      t2 = fp_type(1.5f);
      hyp2F1(result, t1, t1, t2, xx);
      eval_multiply(result, x);
      eval_ldexp(t1, get_constant_pi<T>(), -1);
      result.negate();
      eval_add(result, t1);
      return;
   }
   if (eval_get_sign(x) < 0)
   {
      eval_acos(result, xx);
      result.negate();
      eval_add(result, get_constant_pi<T>());
      return;
   }
   else if (xx.compare(fp_type(0.85)) > 0)
   {
      // https://functions.wolfram.com/ElementaryFunctions/ArcCos/26/01/01/
      // This branch is simlilar in complexity to Newton iterations down to
      // the above limit.  It is *much* more accurate.
      T dx1;
      T t1, t2;
      eval_subtract(dx1, ui_type(1), xx);
      t1 = fp_type(0.5f);
      t2 = fp_type(1.5f);
      eval_ldexp(dx1, dx1, -1);
      hyp2F1(result, t1, t1, t2, dx1);
      eval_ldexp(dx1, dx1, 2);
      eval_sqrt(t1, dx1);
      eval_multiply(result, t1);
      return;
   }

#ifndef BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS
   using guess_type = typename boost::multiprecision::detail::canonical<long double, T>::type;
#else
   using guess_type = fp_type;
#endif
   // Get initial estimate using standard math function asin.
   guess_type dd;
   eval_convert_to(&dd, xx);

   result = (guess_type)(std::acos(dd));

   // Newton-Raphson iteration, we should double our precision with each iteration,
   // in practice this seems to not quite work in all cases... so terminate when we
   // have at least 2/3 of the digits correct on the assumption that the correction
   // we've just added will finish the job...

   std::intmax_t current_precision = eval_ilogb(result);
   std::intmax_t target_precision = std::numeric_limits<number<T> >::is_specialized ?
      current_precision - 1 - (std::numeric_limits<number<T> >::digits * 2) / 3
      : current_precision - 1 - (boost::multiprecision::detail::digits2<number<T> >::value() * 2) / 3;

   // Newton-Raphson iteration
   while (current_precision > target_precision)
   {
      T sine, cosine;
      eval_sin(sine, result);
      eval_cos(cosine, result);
      eval_subtract(cosine, xx);
      cosine.negate();
      eval_divide(cosine, sine);
      eval_subtract(result, cosine);
      current_precision = eval_ilogb(cosine);
      if (current_precision <= (std::numeric_limits<typename T::exponent_type>::min)() + 1)
         break;
   }
}

template <class T>
void eval_atan(T& result, const T& x)
{
   static_assert(number_category<T>::value == number_kind_floating_point, "The atan function is only valid for floating point types.");
   using si_type = typename boost::multiprecision::detail::canonical<std::int32_t, T>::type ;
   using ui_type = typename boost::multiprecision::detail::canonical<std::uint32_t, T>::type;
   using fp_type = typename std::tuple_element<0, typename T::float_types>::type                         ;

   switch (eval_fpclassify(x))
   {
   case FP_NAN:
      result = x;
      errno  = EDOM;
      return;
   case FP_ZERO:
      result = x;
      return;
   case FP_INFINITE:
      if (eval_get_sign(x) < 0)
      {
         eval_ldexp(result, get_constant_pi<T>(), -1);
         result.negate();
      }
      else
         eval_ldexp(result, get_constant_pi<T>(), -1);
      return;
   default:;
   }

   const bool b_neg = eval_get_sign(x) < 0;

   T xx(x);
   if (b_neg)
      xx.negate();

   if (xx.compare(fp_type(0.1)) < 0)
   {
      T t1, t2, t3;
      t1 = ui_type(1);
      t2 = fp_type(0.5f);
      t3 = fp_type(1.5f);
      eval_multiply(xx, xx);
      xx.negate();
      hyp2F1(result, t1, t2, t3, xx);
      eval_multiply(result, x);
      return;
   }

   if (xx.compare(fp_type(10)) > 0)
   {
      T t1, t2, t3;
      t1 = fp_type(0.5f);
      t2 = ui_type(1u);
      t3 = fp_type(1.5f);
      eval_multiply(xx, xx);
      eval_divide(xx, si_type(-1), xx);
      hyp2F1(result, t1, t2, t3, xx);
      eval_divide(result, x);
      if (!b_neg)
         result.negate();
      eval_ldexp(t1, get_constant_pi<T>(), -1);
      eval_add(result, t1);
      if (b_neg)
         result.negate();
      return;
   }

   // Get initial estimate using standard math function atan.
   fp_type d;
   eval_convert_to(&d, xx);
   result = fp_type(std::atan(d));

   // Newton-Raphson iteration, we should double our precision with each iteration,
   // in practice this seems to not quite work in all cases... so terminate when we
   // have at least 2/3 of the digits correct on the assumption that the correction
   // we've just added will finish the job...

   std::intmax_t current_precision = eval_ilogb(result);
   std::intmax_t target_precision  = std::numeric_limits<number<T> >::is_specialized ?
      current_precision - 1 - (std::numeric_limits<number<T> >::digits * 2) / 3
      : current_precision - 1 - (boost::multiprecision::detail::digits2<number<T> >::value() * 2) / 3;

   T s, c, t;
   while (current_precision > target_precision)
   {
      eval_sin(s, result);
      eval_cos(c, result);
      eval_multiply(t, xx, c);
      eval_subtract(t, s);
      eval_multiply(s, t, c);
      eval_add(result, s);
      current_precision = eval_ilogb(s);
      if (current_precision <= (std::numeric_limits<typename T::exponent_type>::min)() + 1)
         break;
   }
   if (b_neg)
      result.negate();
}

template <class T>
void eval_atan2(T& result, const T& y, const T& x)
{
   static_assert(number_category<T>::value == number_kind_floating_point, "The atan2 function is only valid for floating point types.");
   if (&result == &y)
   {
      T temp(y);
      eval_atan2(result, temp, x);
      return;
   }
   else if (&result == &x)
   {
      T temp(x);
      eval_atan2(result, y, temp);
      return;
   }

   using ui_type = typename boost::multiprecision::detail::canonical<std::uint32_t, T>::type;

   switch (eval_fpclassify(y))
   {
   case FP_NAN:
      result = y;
      errno  = EDOM;
      return;
   case FP_ZERO:
   {
      if (eval_signbit(x))
      {
         result = get_constant_pi<T>();
         if (eval_signbit(y))
            result.negate();
      }
      else
      {
         result = y; // Note we allow atan2(0,0) to be +-zero, even though it's mathematically undefined
      }
      return;
   }
   case FP_INFINITE:
   {
      if (eval_fpclassify(x) == FP_INFINITE)
      {
         if (eval_signbit(x))
         {
            // 3Pi/4
            eval_ldexp(result, get_constant_pi<T>(), -2);
            eval_subtract(result, get_constant_pi<T>());
            if (eval_get_sign(y) >= 0)
               result.negate();
         }
         else
         {
            // Pi/4
            eval_ldexp(result, get_constant_pi<T>(), -2);
            if (eval_get_sign(y) < 0)
               result.negate();
         }
      }
      else
      {
         eval_ldexp(result, get_constant_pi<T>(), -1);
         if (eval_get_sign(y) < 0)
            result.negate();
      }
      return;
   }
   }

   switch (eval_fpclassify(x))
   {
   case FP_NAN:
      result = x;
      errno  = EDOM;
      return;
   case FP_ZERO:
   {
      eval_ldexp(result, get_constant_pi<T>(), -1);
      if (eval_get_sign(y) < 0)
         result.negate();
      return;
   }
   case FP_INFINITE:
      if (eval_get_sign(x) > 0)
         result = ui_type(0);
      else
         result = get_constant_pi<T>();
      if (eval_get_sign(y) < 0)
         result.negate();
      return;
   }

   T xx;
   eval_divide(xx, y, x);
   if (eval_get_sign(xx) < 0)
      xx.negate();

   eval_atan(result, xx);

   // Determine quadrant (sign) based on signs of x, y
   const bool y_neg = eval_get_sign(y) < 0;
   const bool x_neg = eval_get_sign(x) < 0;

   if (y_neg != x_neg)
      result.negate();

   if (x_neg)
   {
      if (y_neg)
         eval_subtract(result, get_constant_pi<T>());
      else
         eval_add(result, get_constant_pi<T>());
   }
}
template <class T, class A>
inline typename std::enable_if<boost::multiprecision::detail::is_arithmetic<A>::value, void>::type eval_atan2(T& result, const T& x, const A& a)
{
   using canonical_type = typename boost::multiprecision::detail::canonical<A, T>::type         ;
   using cast_type = typename std::conditional<std::is_same<A, canonical_type>::value, T, canonical_type>::type;
   cast_type                                                                      c;
   c = a;
   eval_atan2(result, x, c);
}

template <class T, class A>
inline typename std::enable_if<boost::multiprecision::detail::is_arithmetic<A>::value, void>::type eval_atan2(T& result, const A& x, const T& a)
{
   using canonical_type = typename boost::multiprecision::detail::canonical<A, T>::type         ;
   using cast_type = typename std::conditional<std::is_same<A, canonical_type>::value, T, canonical_type>::type;
   cast_type                                                                      c;
   c = x;
   eval_atan2(result, c, a);
}

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

/* trig.hpp
YL/Af0H8gvwF9Qv6F8wv2F9wv+B/IfxC/IX0C/kXyi/UX2i/0H9h/ML8hfUL+xfOL9xfeL/wfxH8IvxF9Iv4F8kv0l9kv8h//flF8YvyF9Uv6l80v2h/0f2i/8Xwi/EX0y/mXyy/WH+x/WL/xfGL8xfXL+5fPL94f/H94v8l8Evwl9Av4V8iv0R/if0S/yXxS/KX1C/pXzK/ZH/J/fr7S/6Xwi/FX0q/lH+p/FL9pfZL/ZfGL81fWr+0f+n80v2l90v/l8Evw19Gv4x/mfwy/WX2y/yXxS/LX1a/rH/Z/LL9ZffL/pfDL8dfTr+cf7n8cv3l9sv9l8cvz19ev7x/+fzy+/Xfvg/XoKMLS6iaTi6HsXC8f0Uu3Djj0JEVMdN7g1K0t8Byp6ouFBtzDOTYd23KtXEnCvtU3L5mpew0f7P8M9yZuqNOaw809E3bm321gXJr45HNISSYIhB5b+WM7fvmELBoiJoYubXikYVNCg5AVG6KJATf7fInPHyVPhk+NQLxeU44pKCmhZZT+2zo5AnMTWZDk1cgwBFEI9Lw4xy0w6x3ZRm9QMBcTnw1LWO4F+2+VvnTMpKZmUwUIXJok/DeWqf9YvF8mo45bnSpa0f7khm1axPJAYsvDC2cmxRE0dWoO0+bAV3mE9nMXnYIK+AWdvqAx1+x4hiZ9i+UdRPtIZSiHYFqAnX/EpGG1Br8AmdcFqLCHc+1lNRja6rL/bWIDORtqVWXpC5xzffHZgaPtv23xDPb/EYwucjzammerKF66egOrqWc/A3lUpp2jpt0Pl3CxE72pjhyTBKrQFyn2b3Sv61hlKoCrCFwOhz5sJdCB1W6e8vTYCSNUbKlU/+eW6p0xSBw7PZK7vSFonrTzAQGFyVqaXPZEY3Auhkx08uNH8JDtNPBmAxSCiJerZ2NYl1b/WhRxyi+oDhvKsk/7iX4eBjs/ZoHiyuDPnh9iH8NS9h1+4rcvtXidqqOu5eYpG42RAltDaF/VLlGN9Vmf+Cn54a+dWqaXQLwJ2iaYvv0lUz+yXoExn+VEcpzsRgrHgtOUfkyUvMexJOyXSBwbNIv1/nbfJvsQg+9u0PKvnuekU9yK67ddBjVS2Xs+nlJbl1IpzCIv7z30xJ72prBSfGM14aY9ClWccaihWSLCuh7jgc5Ht6S7kDi31idH2QPMsQ0Q1ox305qo31fqeCTCUzBT51UkNfjyXikLYXKLg8gn3Fd9N7VA/YWh/mDVsCXqte3zHPVeCNXSNKAySe7od5LQ4sf2VPs5XVviA8ExomnMHCqHQJ0Q4EheRA9dZNxKOyqF3K0+MyhmESqq2vKbQbkDlM5RCqbC8M/WTH59BNF14upj8jKf8xAu5moPBCSl4zC0448vuI++eDp+V/fX9QuXhkEl8goPXYVZnWEk1VtoJET1xLXy2g1ordT6VZoE98yLrDewJo0CPSdPkGpi1bKoAZQLZ5/DYhQzDqz2RK44txkwevmy/6QlL1ddb4t7Ukn1z+vVPbab373KDrAczfqnvqzM+9r6tBHBO/Fz7FBNCDw7dFg2FlMVkzXXSFKW2cLjACBPwA1M423jYhPvTtiUUPatAviu6L93fZk3N3Jds0+TSmFwPaRcm0w0LEf6/H0Dw51149nC3xR71VgwPjTJvCg6gx3XEi+I1cXIeAZV/kF/922Lr7jHEuRAAAs/9O2wZsdU1Z/AIjeHadhEicvKKegTt+cDu459FBUrcI8tZYwwooldHLMpu+bQeWUSd/IKMEz2pi3KTK8iD/iz94wq2tVATFTSmxf/5EZ5INda/JpLZRr676vfN96qwac617K49zVWEefGs962ikdsSj8rZtlctLwR5a2lVKWyrGYYob5RFI16/yTtITdeiq5nJ0pnapSyd7EXXt9J3vd2P3nOn0K7+9KnYxo8dKZ87Gb64nwZBqVrv1JY3TMtWR+IaPDjsqG58fD+AaRewMSzM79y0jVmMGg2kevpL3aG13mqMZr9MtXwezHZ9uj8o5Kru9m6PxpNJYPuunPmqmUraFvmOsHqEqp5zkx4ofamjgZNRUoWYtddcXjnlBGpGzDx/kft/Qr0P09lPWINLAPAaM2Ffcd2CicigzqZwYyt9xQ1ANHyWBlnkVK6SVwpNAHnRQgh9DXZ8Ju0lZL07qoO0ADRFqzLVz2atr+ONpqd4hQRlAjalugmICXCik26dQkoMu/Cnl9WAv7Os8QNGmpgzlL3pBH+gJljOco0kson6oCOKCTxFArcQE0GUCRsgIJJXvo9yhVYX9eOcll4aqatmFEcz2WsWr8nuBJ1/j4FTxJzjFzlCSgr57NRlOXRAudqH7PqfMfm9pLTyn4nRH8R/QJRWJ/kgq0DEukllFDCPXsN9m1i6mcvzbDhmuhXJjND4L0wThIC9/9vN6Pxng0ULirBxB5G8jk8kFFePnCVAbI19GJfwQV8EuFn9eE4UclUAjL4e/M+rlT5rTsBjvhn7MiQ93VvoyRcYAwmL09Ba+Fv5IlsigfbwonqnuaLvLvCjvpR+jXXbZjuBl8CkQnaS1Nrm+JA4W9tHSVre12xWCfcXx3H6EU1a5kHHqRELms8hNLCCclUreohOKDWV1Rc2eCpw21DXiL0EAyZMB25Tjkk8xNZLFxyTxRXKJo5+E9MW8KHb6EFsAZkfYBGTv24X1FJykuHlGVom5yoPBy0nPKeBTol2ZTiW9UUV6Os4Svx8PbdiPadBW3bv/M4IVzkR7MyG9h4o0eYbOXmZXJCIKFnEwUQnJL87EwK+LJHOkr8DCr47GsyIZQPlFejyC1vGrLvpQa+eXOM3lJlRTWgj2BO8NRGEXw7bxi3Qy61SfMs7usUw0mtH7QUY53D5DK09O+fMXuNdSXciuxX2VhaY002q4HSeGFWyX0UiA5ok6y3EMRfsOGy9BqJazRDtmaSV4J4hgGyJryWUAL6QqYBgiBFZnVoZ8LMD/IfJTLPfHKXfZmLl0R6VTY9UfVTt1oJw6WeNxVu1tGjVO0ZCqkutd7Vd0clHd3Xt6FIwXA14IH/qOAInOv8t9+bIpiT5JwNsGzqpf3MEWXCV0OFNm1eyaILgbujA+LUViRhbvCW2rYCmxM7RSJOXfNuoD/yTp1o3O4ipiod5FO6FZsT451QBP9XEZNkwqqp9voNUQa1Rk/QJ80y4tfBOXFPPGtLEdc9tE13aimbnAUxWjfQLGQua3zmbbLXkxxOMiqqQ8zpR/BUD1DvAtFbpE/gVr/UzgWp16HJO9KW+myj1kgrJQxedE19wRlz0PsZI2+Gn6Q8bmdnHKuUfo+SKpUXUH69CLHWYB1rBtC5EEhuEoELYT4I4zYcdLGjFKfKzaXIinDKzUGe0ErmfdxbYumKHPKEllNViiuTyxBW81g1iQVcLKkKd9RNDt/GbAXhpClATwPMRvs8+eC3InjHqG/CO0nG3hbbCBOM9dfAbFTKVLm36JKSz7QF90a6DBOSV/MPy1vWpoAhyfIUKUwYDZg3cntcKh3arLQC1Cqeg428ydBuNVIW7GLYMWlyGsoAyr8GA9z6B/spdNP9rPy5NwWiZxRqTXQ5uhe/SFLAgU23JYEDGAP9CWsGcU5LBGZbc6RLB12qfup8/AKrOYcxHOuFhPhF1yejmexdTRDqfsFXC0O1t7g/U8LKGGo5V5GztkxB/MiFGL1HYRSFERNzAbBsJujFZmkZ6aHncJ7Gqdj1GQSBUe0aFwSM/lG96ROJP3rk4SDOFABXJ2x8c2no11aHCk0kCfd8C4huW8RnAaCMj51DKzSs1y5Pv7D+MoXiYQdH289IlGKly2fpDDyURfMa/wj7+PxmWpmHnd0KpZ66Km41UEmRCM4RR25a/R/5odCzULGiNhnyaLP2pUK5iqUNP1LhZG6e/AFCxrtzWKPclcUiVyHTIEguzwyjTpxeJctZFILhrc9XSpEijOR72vp+NJp/DvuavUiDGu73d9F4VseamuJRpvWrEw3p/B2nJlJmmY1LCc1B+r2cfKpiJ4vLhYMDN/Ju7Tv69UnkaAmV4S4iDpaFyon1c28zQHWTfRU3re020U2dmQhMt6oUXtcJ2kURRQ3YC1++we5Nia3kQY2bPzwGKy+Do2PKExwnvqoqvhfLqJO7kmxhny3Q+9yRM8VvN+zoK4Gu5Za3/oxMcKPtvbb8b5pVfbXYiEnvp8mWRy9xL7coGgO8hp6Lv2YEy+RTEQpezE+9xEnSaN2VHKMGrDG0UNR3LotqS5R92A9YaA+Hl/QLatCnuVj2xIf6aEnT8dfJ+Xjz7qLy+fRDx7J3UdrzmNTnszvDS2ZNWOfYnuFb0vE7HRT6Lz4Qcq5gNtf3s57K99nr9XrgcYzF3rpk91PNo90VN+m/iC7kYG6vUQUpWYHudDIZTnSF4xivYTngPvg4zh+uKpe77llffwX09uz6SPv6FiqX0VeQdflsDG9PiEqemMHUvewH73lul46JMExeA0juL4wYIUbma32fpdlbR0ufwDPcynoWdie5RCpOmeZdXKQGnUiXyc1uk52vUt3dN5kbse4z5UhheBzWPYjpaeYAstFfnwnV+Wfb74pMWyVr0ougVPx8XN/ugse7992uR5mO6ZDzkkNnQxoJMsxamShUWBUlLsoKDBZcAZPNc+GpFdBJDzmZewX9D8dMZp/yFiDgdLmWWqbG5Q6LHRSJXVwU5wTPpYRi/XYr/yTwRxsTEtnaKhoGOYTGhojfTStX3ThF4I0uSjMYLiI/UrBrpfyNmmYQ5cX1HVcpaI2SBws95AsVkUrszF0rU2jNBwUL/HC5LnGJUaxgzf4ssMULCNqVx41mjQ06h1Ne9GqWdVVIXrMmhMPK2ki5KVy9beeGCxKz6AI+TSqOXo2YjCaFSWsdaM2ULQJvT49kjbK75d1IuUt++OrVwuXZRdRB3bMmlNeLXBrxSqzZS1cR8qy86mCkuctSkdVNxEKU9BwtsUMl0ouoPT3mv80r7xazP5GSFiIGSzNLKAGIFW7nMhQroWbNRt9jGc7EmlcW2kTVoWpZLokQqEVPtMqbKIUusTUIPCeRSl4rspQqkVtODU1YDRjdgiaRahk+iQK3olVdmcu1fz7HYmpQkQWLu/g6lq7R2lga6hHbdieQ+1/HcpbWN8vtwyXZUtZeBouzfymvDhvcTqifElecVNM0NOLVklra9+r0I/cNAXFhQyB8ujJ+8FB6upaxUvr3vpoqyDnrcE8oqt2q3qI9/M1Hajuyvttid/7Xf2yG+/je4t/6FXrTv00d/2ZrpRWAXuVxcnta+NWRvHyAN7rPk21oH8q5cNrgvFm7zomktw6Y1cRB70MTDOOlKkwFGg1GYZOgXLYiCHZ5R6sC5JA+50PvGsB9A+gt4QDsmdhLPBzwsAt+SdKku8B8mjEj3uq1iou9u4va3DRI2St5PNst8Modw0DQ6iRxCQZQqjTCbHwuyxZ8GO2WJhTNEmw0/YeYanDJ9bx/WtZ9FW7LP2B8dZyz5fIOHymSRV9ZAEb8KS/rB6iHXZ+FzH05C0yqgrouWweuBqwE/BlXw36FUkwC/8GkBUoK3Cmn7VeK3TLefRVAXoxrRfoA67gJ6Lgiv+d/B6DHvnCm0iHRMQtSdG2Xq5IG7ob3hr4s0iM11Hp6zth1+/GDATyo7LD/Av7m131WiPACfUMG1TsCRnNj5xv1YNu1XjQyG9BamQOUQps3Sdd1wjiGXEwGeKEucYBUQt0AoyrV4t+VR5Ri7BAVJcNYQuWAtzq3y1Up4iii1pkU2eJsAP5CPBftlaRB5Z+TZBXJkGaftV9rHWbHKzoD0DcAPuEcbEEW4DcUNxgDqV/ebTv3wh5IF3YBkz9u/se9F4gn2GGXREXfOpqCbgBcEAq9OChW5JX7fEY500+D1fjDFCqsPnNCfF+U9UIQymPmIUpD45TR5QFLgG21jOFepYeTgU1Z12bRJgBrAE6CbxGuFIHdOeBx5Sp/ZcmWPQHaBJyC4ZaLMKaSESDf6df6FxcPhjFps7Cj8sfr6gMmcKEqsdDHLvPRrANc+23oTtl6m4VvK7j8AA+EAbE/HD7CvXwka84ImqRFfjWyBFvwHJAnwO8deoWUXXxi9D7b8ReoewA2CFaKNcwI2wxFhDragm5oboAk9AQN9sgrjpRc8NrYjMh00H1qehh0+BafmuX90qPM/HPjr5j1IOzQ117C7BW9IITXw3UDrNDnPvN1aVdz1fq3jrQCXxNGaLTn6UvW88TxLPmoDKwCe8KLCjTb7oPrU4T1FOH3+YwnzgF3V2aSwEH4BLhDqIOmCImAiXd9uiv8j2ukBJ5wisiL+QVWI5Igk68Uc8BF7w5/ho64g24DiCcH8+fNd9nUUQffpEl+oQoAi9YdqgufxIF1gTqv14jVk5BQVNRdaBmoCWIE+cB2cWvVnEmAdnBdqx2mPTgV8oB3rUHk6FLgM8eQdD+Ivzka5mgnvr8tKf5lE0l1mGuwJV+XCCW8qo8iGqwQVz+T32ceWJzDcAOwPDNAurIBhr+NH0m/RpT+ITwuKCVuAxifqF+4CCW4b3+0vdjuAh4oO/+2X2GAS1K8XIHHdi/hzI0NxXGpBtf+GVkH+Aeql6vHvVpLNIq5R2WHQg7NQaVG374JfZBOY0oPmQSWqD+aS2TlqbfeR9znjK9A1BDdChUZvnutPAUox4rvVTdzSVnZMKMvx2qHc8c4BR604c78ZAzYh1OG+YZSlSytmqeGXYQlx8LP1ud5JwKhRV5DU8fmB5PnSy9A7ADMrz24KGFqDR2HeoakRr8HTpuDTwAl99v/iDEsa3iWvjAOSC/uQfE145tt/FCXwHngD9DjVjQWWoWNEI0j0x2vDVf1raTfet6N5H7D8GneHhfIL1XfC68CyOxV8DqrLdE9Wy0QI5r6JhNMgAA3ACoAG73Ye3tAS1B79HbobgB/9HXMwTRCRwKqsM0A9TwN+9z0iObA5sCMgHGZXZLWF0MkdFhIZgAxENghx+etp3kQ01aIWV+vNEqwMXn8nGA3Enow1XCwsb/ZlS7wEtfJ21v/N5LlZxcGuWlPVgEuox0WtKq3nk3/psNH2OuEqSYZ58R3ujveLWtI8rEZVt5K1/zAVnIOE2YyzpemHkZ6h6M4oqPRwl+JPTATH6Krbsn5CPWkTp/xrl6JGFexiQZMZ4Icqnd7yoE7cJj+IKg3430HR0b5Qgcb4J/dL+5cepXntKtPmJmqGKuVdXyYmQRmdnULKj8ajzkpqxjM1It7RK2y/c8b/3cyWP8LwdhEVda9nmOO4yMxj88reQKUk7xOaiUwnNgMYln33wiZ445+NSWZoVCigi+o0jJ+hUCnsEViOdcI7Kj5GoyL8F/9Jvne0iKSC4rUUrwyEQgB6zB7Rs+kTBT+iVTYad94+rCmiFlZeX4KU4kVwg7kXS6akNjpdJvtsTdHlq2hZZqrbSGl+RigFce3QI5qWkrUOmDh2mN14K47gLtPWnsmSPIbKUicImAm2L/zzGBSL33UkoF7ABRzLSorLqFaaP3UkkhMwW4BErJKsLX4k/xlUZfZkXDkwSEtVkkrC0+ihSFAkhSPcESo4a/nUB4SbV1u48IDrhpDAxvqfxb0RqSJEymUEXXhXIU/Z89ERFjG0TMP7GxSf7+cGi2
*/