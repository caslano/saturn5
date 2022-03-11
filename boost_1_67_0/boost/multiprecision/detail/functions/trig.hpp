
// Copyright Christopher Kormanyos 2002 - 2011.
// Copyright 2011 John Maddock. Distributed under the Boost
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469
//
// This file has no include guards or namespaces - it's expanded inline inside default_ops.hpp
//

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable : 6326) // comparison of two constants
#endif

template <class T>
void hyp0F1(T& result, const T& b, const T& x)
{
   typedef typename boost::multiprecision::detail::canonical<boost::int32_t, T>::type  si_type;
   typedef typename boost::multiprecision::detail::canonical<boost::uint32_t, T>::type ui_type;

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
      BOOST_THROW_EXCEPTION(std::runtime_error("H0F1 Failed to Converge"));
}

template <class T>
void eval_sin(T& result, const T& x)
{
   BOOST_STATIC_ASSERT_MSG(number_category<T>::value == number_kind_floating_point, "The sin function is only valid for floating point types.");
   if (&result == &x)
   {
      T temp;
      eval_sin(temp, x);
      result = temp;
      return;
   }

   typedef typename boost::multiprecision::detail::canonical<boost::int32_t, T>::type  si_type;
   typedef typename boost::multiprecision::detail::canonical<boost::uint32_t, T>::type ui_type;
   typedef typename mpl::front<typename T::float_types>::type                          fp_type;

   switch (eval_fpclassify(x))
   {
   case FP_INFINITE:
   case FP_NAN:
      if (std::numeric_limits<number<T, et_on> >::has_quiet_NaN)
      {
         result = std::numeric_limits<number<T, et_on> >::quiet_NaN().backend();
         errno  = EDOM;
      }
      else
         BOOST_THROW_EXCEPTION(std::domain_error("Result is undefined or complex and there is no NaN for this number type."));
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
   // Remove even multiples of pi.
   if (xx.compare(get_constant_pi<T>()) > 0)
   {
      eval_divide(n_pi, xx, get_constant_pi<T>());
      eval_trunc(n_pi, n_pi);
      t = ui_type(2);
      eval_fmod(t, n_pi, t);
      const bool b_n_pi_is_even = eval_get_sign(t) == 0;
      eval_multiply(n_pi, get_constant_pi<T>());
      if (n_pi.compare(get_constant_one_over_epsilon<T>()) > 0)
      {
         result = ui_type(0);
         return;
      }
      else
         eval_subtract(xx, n_pi);

      BOOST_MATH_INSTRUMENT_CODE(xx.str(0, std::ios_base::scientific));
      BOOST_MATH_INSTRUMENT_CODE(n_pi.str(0, std::ios_base::scientific));

      // Adjust signs if the multiple of pi is not even.
      if (!b_n_pi_is_even)
      {
         b_negate_sin = !b_negate_sin;
      }
   }

   // Reduce the argument to 0 <= xx <= pi/2.
   eval_ldexp(t, get_constant_pi<T>(), -1);
   if (xx.compare(t) > 0)
   {
      eval_subtract(xx, get_constant_pi<T>(), xx);
      BOOST_MATH_INSTRUMENT_CODE(xx.str(0, std::ios_base::scientific));
   }

   eval_subtract(t, xx);
   const bool b_zero    = eval_get_sign(xx) == 0;
   const bool b_pi_half = eval_get_sign(t) == 0;

   // Check if the reduced argument is very close to 0 or pi/2.
   const bool b_near_zero    = xx.compare(fp_type(1e-1)) < 0;
   const bool b_near_pi_half = t.compare(fp_type(1e-1)) < 0;
   ;

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

      static const si_type n_scale           = 9;
      static const si_type n_three_pow_scale = static_cast<si_type>(19683L);

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
      for (boost::int32_t k = static_cast<boost::int32_t>(0); k < n_scale; k++)
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
}

template <class T>
void eval_cos(T& result, const T& x)
{
   BOOST_STATIC_ASSERT_MSG(number_category<T>::value == number_kind_floating_point, "The cos function is only valid for floating point types.");
   if (&result == &x)
   {
      T temp;
      eval_cos(temp, x);
      result = temp;
      return;
   }

   typedef typename boost::multiprecision::detail::canonical<boost::int32_t, T>::type  si_type;
   typedef typename boost::multiprecision::detail::canonical<boost::uint32_t, T>::type ui_type;
   typedef typename mpl::front<typename T::float_types>::type                          fp_type;

   switch (eval_fpclassify(x))
   {
   case FP_INFINITE:
   case FP_NAN:
      if (std::numeric_limits<number<T, et_on> >::has_quiet_NaN)
      {
         result = std::numeric_limits<number<T, et_on> >::quiet_NaN().backend();
         errno  = EDOM;
      }
      else
         BOOST_THROW_EXCEPTION(std::domain_error("Result is undefined or complex and there is no NaN for this number type."));
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

   T n_pi, t;
   // Remove even multiples of pi.
   if (xx.compare(get_constant_pi<T>()) > 0)
   {
      eval_divide(t, xx, get_constant_pi<T>());
      eval_trunc(n_pi, t);
      BOOST_MATH_INSTRUMENT_CODE(n_pi.str(0, std::ios_base::scientific));
      eval_multiply(t, n_pi, get_constant_pi<T>());
      BOOST_MATH_INSTRUMENT_CODE(t.str(0, std::ios_base::scientific));
      //
      // If t is so large that all digits cancel the result of this subtraction
      // is completely meaningless, just assume the result is zero for now...
      //
      // TODO We should of course do much better, see:
      // "ARGUMENT REDUCTION FOR HUGE ARGUMENTS" K C Ng 1992
      //
      if (n_pi.compare(get_constant_one_over_epsilon<T>()) > 0)
      {
         result = ui_type(1);
         return;
      }
      else
         eval_subtract(xx, t);
      BOOST_MATH_INSTRUMENT_CODE(xx.str(0, std::ios_base::scientific));

      // Adjust signs if the multiple of pi is not even.
      t = ui_type(2);
      eval_fmod(t, n_pi, t);
      const bool b_n_pi_is_even = eval_get_sign(t) == 0;

      if (!b_n_pi_is_even)
      {
         b_negate_cos = !b_negate_cos;
      }
   }

   // Reduce the argument to 0 <= xx <= pi/2.
   eval_ldexp(t, get_constant_pi<T>(), -1);
   int com = xx.compare(t);
   if (com > 0)
   {
      eval_subtract(xx, get_constant_pi<T>(), xx);
      b_negate_cos = !b_negate_cos;
      BOOST_MATH_INSTRUMENT_CODE(xx.str(0, std::ios_base::scientific));
   }

   const bool b_zero    = eval_get_sign(xx) == 0;
   const bool b_pi_half = com == 0;

   // Check if the reduced argument is very close to 0.
   const bool b_near_zero = xx.compare(fp_type(1e-1)) < 0;

   if (b_zero)
   {
      result = si_type(1);
   }
   else if (b_pi_half)
   {
      result = si_type(0);
   }
   else if (b_near_zero)
   {
      eval_multiply(t, xx, xx);
      eval_divide(t, si_type(-4));
      n_pi = fp_type(0.5f);
      hyp0F1(result, n_pi, t);
      BOOST_MATH_INSTRUMENT_CODE(result.str(0, std::ios_base::scientific));
   }
   else
   {
      eval_subtract(t, xx);
      eval_sin(result, t);
   }
   if (b_negate_cos)
      result.negate();
}

template <class T>
void eval_tan(T& result, const T& x)
{
   BOOST_STATIC_ASSERT_MSG(number_category<T>::value == number_kind_floating_point, "The tan function is only valid for floating point types.");
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

   typedef typename boost::multiprecision::detail::canonical<boost::uint32_t, T>::type ui_type;

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
      BOOST_THROW_EXCEPTION(std::runtime_error("H2F1 failed to converge."));
}

template <class T>
void eval_asin(T& result, const T& x)
{
   BOOST_STATIC_ASSERT_MSG(number_category<T>::value == number_kind_floating_point, "The asin function is only valid for floating point types.");
   typedef typename boost::multiprecision::detail::canonical<boost::uint32_t, T>::type ui_type;
   typedef typename mpl::front<typename T::float_types>::type                          fp_type;

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
      if (std::numeric_limits<number<T, et_on> >::has_quiet_NaN)
      {
         result = std::numeric_limits<number<T, et_on> >::quiet_NaN().backend();
         errno  = EDOM;
      }
      else
         BOOST_THROW_EXCEPTION(std::domain_error("Result is undefined or complex and there is no NaN for this number type."));
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
      if (std::numeric_limits<number<T, et_on> >::has_quiet_NaN)
      {
         result = std::numeric_limits<number<T, et_on> >::quiet_NaN().backend();
         errno  = EDOM;
      }
      else
         BOOST_THROW_EXCEPTION(std::domain_error("Result is undefined or complex and there is no NaN for this number type."));
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

   if (xx.compare(fp_type(1e-4)) < 0)
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
   else if (xx.compare(fp_type(1 - 1e-4f)) > 0)
   {
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
   typedef typename boost::multiprecision::detail::canonical<long double, T>::type guess_type;
#else
   typedef fp_type guess_type;
#endif
   // Get initial estimate using standard math function asin.
   guess_type dd;
   eval_convert_to(&dd, xx);

   result = (guess_type)(std::asin(dd));

   // Newton-Raphson iteration, we should double our precision with each iteration,
   // in practice this seems to not quite work in all cases... so terminate when we
   // have at least 2/3 of the digits correct on the assumption that the correction
   // we've just added will finish the job...

   boost::intmax_t current_precision = eval_ilogb(result);
   boost::intmax_t target_precision  = current_precision - 1 - (std::numeric_limits<number<T> >::digits * 2) / 3;

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
   BOOST_STATIC_ASSERT_MSG(number_category<T>::value == number_kind_floating_point, "The acos function is only valid for floating point types.");
   typedef typename boost::multiprecision::detail::canonical<boost::uint32_t, T>::type ui_type;

   switch (eval_fpclassify(x))
   {
   case FP_NAN:
   case FP_INFINITE:
      if (std::numeric_limits<number<T, et_on> >::has_quiet_NaN)
      {
         result = std::numeric_limits<number<T, et_on> >::quiet_NaN().backend();
         errno  = EDOM;
      }
      else
         BOOST_THROW_EXCEPTION(std::domain_error("Result is undefined or complex and there is no NaN for this number type."));
      return;
   case FP_ZERO:
      result = get_constant_pi<T>();
      eval_ldexp(result, result, -1); // divide by two.
      return;
   }

   eval_abs(result, x);
   int c = result.compare(ui_type(1));

   if (c > 0)
   {
      if (std::numeric_limits<number<T, et_on> >::has_quiet_NaN)
      {
         result = std::numeric_limits<number<T, et_on> >::quiet_NaN().backend();
         errno  = EDOM;
      }
      else
         BOOST_THROW_EXCEPTION(std::domain_error("Result is undefined or complex and there is no NaN for this number type."));
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

   eval_asin(result, x);
   T t;
   eval_ldexp(t, get_constant_pi<T>(), -1);
   eval_subtract(result, t);
   result.negate();
}

template <class T>
void eval_atan(T& result, const T& x)
{
   BOOST_STATIC_ASSERT_MSG(number_category<T>::value == number_kind_floating_point, "The atan function is only valid for floating point types.");
   typedef typename boost::multiprecision::detail::canonical<boost::int32_t, T>::type  si_type;
   typedef typename boost::multiprecision::detail::canonical<boost::uint32_t, T>::type ui_type;
   typedef typename mpl::front<typename T::float_types>::type                          fp_type;

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

   boost::intmax_t current_precision = eval_ilogb(result);
   boost::intmax_t target_precision  = current_precision - 1 - (std::numeric_limits<number<T> >::digits * 2) / 3;

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
   BOOST_STATIC_ASSERT_MSG(number_category<T>::value == number_kind_floating_point, "The atan2 function is only valid for floating point types.");
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

   typedef typename boost::multiprecision::detail::canonical<boost::uint32_t, T>::type ui_type;

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
inline typename enable_if<is_arithmetic<A>, void>::type eval_atan2(T& result, const T& x, const A& a)
{
   typedef typename boost::multiprecision::detail::canonical<A, T>::type          canonical_type;
   typedef typename mpl::if_<is_same<A, canonical_type>, T, canonical_type>::type cast_type;
   cast_type                                                                      c;
   c = a;
   eval_atan2(result, x, c);
}

template <class T, class A>
inline typename enable_if<is_arithmetic<A>, void>::type eval_atan2(T& result, const A& x, const T& a)
{
   typedef typename boost::multiprecision::detail::canonical<A, T>::type          canonical_type;
   typedef typename mpl::if_<is_same<A, canonical_type>, T, canonical_type>::type cast_type;
   cast_type                                                                      c;
   c = x;
   eval_atan2(result, c, a);
}

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

/* trig.hpp
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
*/