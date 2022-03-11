
// Copyright Christopher Kormanyos 2002 - 2013.
// Copyright 2011 - 2013 John Maddock. Distributed under the Boost
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

namespace detail {

template <typename T, typename U>
inline void pow_imp(T& result, const T& t, const U& p, const mpl::false_&)
{
   // Compute the pure power of typename T t^p.
   // Use the S-and-X binary method, as described in
   // D. E. Knuth, "The Art of Computer Programming", Vol. 2,
   // Section 4.6.3 . The resulting computational complexity
   // is order log2[abs(p)].

   typedef typename boost::multiprecision::detail::canonical<U, T>::type int_type;

   if (&result == &t)
   {
      T temp;
      pow_imp(temp, t, p, mpl::false_());
      result = temp;
      return;
   }

   // This will store the result.
   if (U(p % U(2)) != U(0))
   {
      result = t;
   }
   else
      result = int_type(1);

   U p2(p);

   // The variable x stores the binary powers of t.
   T x(t);

   while (U(p2 /= 2) != U(0))
   {
      // Square x for each binary power.
      eval_multiply(x, x);

      const bool has_binary_power = (U(p2 % U(2)) != U(0));

      if (has_binary_power)
      {
         // Multiply the result with each binary power contained in the exponent.
         eval_multiply(result, x);
      }
   }
}

template <typename T, typename U>
inline void pow_imp(T& result, const T& t, const U& p, const mpl::true_&)
{
   // Signed integer power, just take care of the sign then call the unsigned version:
   typedef typename boost::multiprecision::detail::canonical<U, T>::type int_type;
   typedef typename make_unsigned<U>::type                               ui_type;

   if (p < 0)
   {
      T temp;
      temp = static_cast<int_type>(1);
      T denom;
      pow_imp(denom, t, static_cast<ui_type>(-p), mpl::false_());
      eval_divide(result, temp, denom);
      return;
   }
   pow_imp(result, t, static_cast<ui_type>(p), mpl::false_());
}

} // namespace detail

template <typename T, typename U>
inline typename enable_if_c<is_integral<U>::value>::type eval_pow(T& result, const T& t, const U& p)
{
   detail::pow_imp(result, t, p, boost::is_signed<U>());
}

template <class T>
void hyp0F0(T& H0F0, const T& x)
{
   // Compute the series representation of Hypergeometric0F0 taken from
   // http://functions.wolfram.com/HypergeometricFunctions/Hypergeometric0F0/06/01/
   // There are no checks on input range or parameter boundaries.

   typedef typename mpl::front<typename T::unsigned_types>::type ui_type;

   BOOST_ASSERT(&H0F0 != &x);
   long tol = boost::multiprecision::detail::digits2<number<T, et_on> >::value();
   T    t;

   T x_pow_n_div_n_fact(x);

   eval_add(H0F0, x_pow_n_div_n_fact, ui_type(1));

   T lim;
   eval_ldexp(lim, H0F0, 1 - tol);
   if (eval_get_sign(lim) < 0)
      lim.negate();

   ui_type n;

   const unsigned series_limit =
       boost::multiprecision::detail::digits2<number<T, et_on> >::value() < 100
           ? 100
           : boost::multiprecision::detail::digits2<number<T, et_on> >::value();
   // Series expansion of hyperg_0f0(; ; x).
   for (n = 2; n < series_limit; ++n)
   {
      eval_multiply(x_pow_n_div_n_fact, x);
      eval_divide(x_pow_n_div_n_fact, n);
      eval_add(H0F0, x_pow_n_div_n_fact);
      bool neg = eval_get_sign(x_pow_n_div_n_fact) < 0;
      if (neg)
         x_pow_n_div_n_fact.negate();
      if (lim.compare(x_pow_n_div_n_fact) > 0)
         break;
      if (neg)
         x_pow_n_div_n_fact.negate();
   }
   if (n >= series_limit)
      BOOST_THROW_EXCEPTION(std::runtime_error("H0F0 failed to converge"));
}

template <class T>
void hyp1F0(T& H1F0, const T& a, const T& x)
{
   // Compute the series representation of Hypergeometric1F0 taken from
   // http://functions.wolfram.com/HypergeometricFunctions/Hypergeometric1F0/06/01/01/
   // and also see the corresponding section for the power function (i.e. x^a).
   // There are no checks on input range or parameter boundaries.

   typedef typename boost::multiprecision::detail::canonical<int, T>::type si_type;

   BOOST_ASSERT(&H1F0 != &x);
   BOOST_ASSERT(&H1F0 != &a);

   T x_pow_n_div_n_fact(x);
   T pochham_a(a);
   T ap(a);

   eval_multiply(H1F0, pochham_a, x_pow_n_div_n_fact);
   eval_add(H1F0, si_type(1));
   T lim;
   eval_ldexp(lim, H1F0, 1 - boost::multiprecision::detail::digits2<number<T, et_on> >::value());
   if (eval_get_sign(lim) < 0)
      lim.negate();

   si_type n;
   T       term, part;

   const si_type series_limit =
       boost::multiprecision::detail::digits2<number<T, et_on> >::value() < 100
           ? 100
           : boost::multiprecision::detail::digits2<number<T, et_on> >::value();
   // Series expansion of hyperg_1f0(a; ; x).
   for (n = 2; n < series_limit; n++)
   {
      eval_multiply(x_pow_n_div_n_fact, x);
      eval_divide(x_pow_n_div_n_fact, n);
      eval_increment(ap);
      eval_multiply(pochham_a, ap);
      eval_multiply(term, pochham_a, x_pow_n_div_n_fact);
      eval_add(H1F0, term);
      if (eval_get_sign(term) < 0)
         term.negate();
      if (lim.compare(term) >= 0)
         break;
   }
   if (n >= series_limit)
      BOOST_THROW_EXCEPTION(std::runtime_error("H1F0 failed to converge"));
}

template <class T>
void eval_exp(T& result, const T& x)
{
   BOOST_STATIC_ASSERT_MSG(number_category<T>::value == number_kind_floating_point, "The exp function is only valid for floating point types.");
   if (&x == &result)
   {
      T temp;
      eval_exp(temp, x);
      result = temp;
      return;
   }
   typedef typename boost::multiprecision::detail::canonical<unsigned, T>::type ui_type;
   typedef typename boost::multiprecision::detail::canonical<int, T>::type      si_type;
   typedef typename T::exponent_type                                            exp_type;
   typedef typename boost::multiprecision::detail::canonical<exp_type, T>::type canonical_exp_type;

   // Handle special arguments.
   int  type  = eval_fpclassify(x);
   bool isneg = eval_get_sign(x) < 0;
   if (type == (int)FP_NAN)
   {
      result = x;
      errno  = EDOM;
      return;
   }
   else if (type == (int)FP_INFINITE)
   {
      if (isneg)
         result = ui_type(0u);
      else
         result = x;
      return;
   }
   else if (type == (int)FP_ZERO)
   {
      result = ui_type(1);
      return;
   }

   // Get local copy of argument and force it to be positive.
   T xx = x;
   T exp_series;
   if (isneg)
      xx.negate();

   // Check the range of the argument.
   if (xx.compare(si_type(1)) <= 0)
   {
      //
      // Use series for exp(x) - 1:
      //
      T lim;
      if (std::numeric_limits<number<T, et_on> >::is_specialized)
         lim = std::numeric_limits<number<T, et_on> >::epsilon().backend();
      else
      {
         result = ui_type(1);
         eval_ldexp(lim, result, 1 - boost::multiprecision::detail::digits2<number<T, et_on> >::value());
      }
      unsigned k = 2;
      exp_series = xx;
      result     = si_type(1);
      if (isneg)
         eval_subtract(result, exp_series);
      else
         eval_add(result, exp_series);
      eval_multiply(exp_series, xx);
      eval_divide(exp_series, ui_type(k));
      eval_add(result, exp_series);
      while (exp_series.compare(lim) > 0)
      {
         ++k;
         eval_multiply(exp_series, xx);
         eval_divide(exp_series, ui_type(k));
         if (isneg && (k & 1))
            eval_subtract(result, exp_series);
         else
            eval_add(result, exp_series);
      }
      return;
   }

   // Check for pure-integer arguments which can be either signed or unsigned.
   typename boost::multiprecision::detail::canonical<boost::intmax_t, T>::type ll;
   eval_trunc(exp_series, x);
   eval_convert_to(&ll, exp_series);
   if (x.compare(ll) == 0)
   {
      detail::pow_imp(result, get_constant_e<T>(), ll, mpl::true_());
      return;
   }
   else if (exp_series.compare(x) == 0)
   {
      // We have a value that has no fractional part, but is too large to fit
      // in a long long, in this situation the code below will fail, so
      // we're just going to assume that this will overflow:
      if (isneg)
         result = ui_type(0);
      else
         result = std::numeric_limits<number<T> >::has_infinity ? std::numeric_limits<number<T> >::infinity().backend() : (std::numeric_limits<number<T> >::max)().backend();
      return;
   }

   // The algorithm for exp has been taken from MPFUN.
   // exp(t) = [ (1 + r + r^2/2! + r^3/3! + r^4/4! ...)^p2 ] * 2^n
   // where p2 is a power of 2 such as 2048, r = t_prime / p2, and
   // t_prime = t - n*ln2, with n chosen to minimize the absolute
   // value of t_prime. In the resulting Taylor series, which is
   // implemented as a hypergeometric function, |r| is bounded by
   // ln2 / p2. For small arguments, no scaling is done.

   // Compute the exponential series of the (possibly) scaled argument.

   eval_divide(result, xx, get_constant_ln2<T>());
   exp_type n;
   eval_convert_to(&n, result);

   if (n == (std::numeric_limits<exp_type>::max)())
   {
      // Exponent is too large to fit in our exponent type:
      if (isneg)
         result = ui_type(0);
      else
         result = std::numeric_limits<number<T> >::has_infinity ? std::numeric_limits<number<T> >::infinity().backend() : (std::numeric_limits<number<T> >::max)().backend();
      return;
   }

   // The scaling is 2^11 = 2048.
   const si_type p2 = static_cast<si_type>(si_type(1) << 11);

   eval_multiply(exp_series, get_constant_ln2<T>(), static_cast<canonical_exp_type>(n));
   eval_subtract(exp_series, xx);
   eval_divide(exp_series, p2);
   exp_series.negate();
   hyp0F0(result, exp_series);

   detail::pow_imp(exp_series, result, p2, mpl::true_());
   result = ui_type(1);
   eval_ldexp(result, result, n);
   eval_multiply(exp_series, result);

   if (isneg)
      eval_divide(result, ui_type(1), exp_series);
   else
      result = exp_series;
}

template <class T>
void eval_log(T& result, const T& arg)
{
   BOOST_STATIC_ASSERT_MSG(number_category<T>::value == number_kind_floating_point, "The log function is only valid for floating point types.");
   //
   // We use a variation of http://dlmf.nist.gov/4.45#i
   // using frexp to reduce the argument to x * 2^n,
   // then let y = x - 1 and compute:
   // log(x) = log(2) * n + log1p(1 + y)
   //
   typedef typename boost::multiprecision::detail::canonical<unsigned, T>::type ui_type;
   typedef typename T::exponent_type                                            exp_type;
   typedef typename boost::multiprecision::detail::canonical<exp_type, T>::type canonical_exp_type;
   typedef typename mpl::front<typename T::float_types>::type                   fp_type;
   int                                                                          s = eval_signbit(arg);
   switch (eval_fpclassify(arg))
   {
   case FP_NAN:
      result = arg;
      errno  = EDOM;
      return;
   case FP_INFINITE:
      if (s)
         break;
      result = arg;
      return;
   case FP_ZERO:
      result = std::numeric_limits<number<T> >::has_infinity ? std::numeric_limits<number<T> >::infinity().backend() : (std::numeric_limits<number<T> >::max)().backend();
      result.negate();
      errno = ERANGE;
      return;
   }
   if (s)
   {
      result = std::numeric_limits<number<T> >::quiet_NaN().backend();
      errno  = EDOM;
      return;
   }

   exp_type e;
   T        t;
   eval_frexp(t, arg, &e);
   bool alternate = false;

   if (t.compare(fp_type(2) / fp_type(3)) <= 0)
   {
      alternate = true;
      eval_ldexp(t, t, 1);
      --e;
   }

   eval_multiply(result, get_constant_ln2<T>(), canonical_exp_type(e));
   INSTRUMENT_BACKEND(result);
   eval_subtract(t, ui_type(1)); /* -0.3 <= t <= 0.3 */
   if (!alternate)
      t.negate(); /* 0 <= t <= 0.33333 */
   T pow = t;
   T lim;
   T t2;

   if (alternate)
      eval_add(result, t);
   else
      eval_subtract(result, t);

   if (std::numeric_limits<number<T, et_on> >::is_specialized)
      eval_multiply(lim, result, std::numeric_limits<number<T, et_on> >::epsilon().backend());
   else
      eval_ldexp(lim, result, 1 - boost::multiprecision::detail::digits2<number<T, et_on> >::value());
   if (eval_get_sign(lim) < 0)
      lim.negate();
   INSTRUMENT_BACKEND(lim);

   ui_type k = 1;
   do
   {
      ++k;
      eval_multiply(pow, t);
      eval_divide(t2, pow, k);
      INSTRUMENT_BACKEND(t2);
      if (alternate && ((k & 1) != 0))
         eval_add(result, t2);
      else
         eval_subtract(result, t2);
      INSTRUMENT_BACKEND(result);
   } while (lim.compare(t2) < 0);
}

template <class T>
const T& get_constant_log10()
{
   static BOOST_MP_THREAD_LOCAL T    result;
   static BOOST_MP_THREAD_LOCAL long digits = 0;
#ifndef BOOST_MP_USING_THREAD_LOCAL
   static BOOST_MP_THREAD_LOCAL bool b = false;
   constant_initializer<T, &get_constant_log10<T> >::do_nothing();

   if (!b || (digits != boost::multiprecision::detail::digits2<number<T> >::value()))
   {
      b = true;
#else
   if ((digits != boost::multiprecision::detail::digits2<number<T> >::value()))
   {
#endif
      typedef typename boost::multiprecision::detail::canonical<unsigned, T>::type ui_type;
      T                                                                            ten;
      ten = ui_type(10u);
      eval_log(result, ten);
      digits = boost::multiprecision::detail::digits2<number<T> >::value();
   }

   return result;
}

template <class T>
void eval_log10(T& result, const T& arg)
{
   BOOST_STATIC_ASSERT_MSG(number_category<T>::value == number_kind_floating_point, "The log10 function is only valid for floating point types.");
   eval_log(result, arg);
   eval_divide(result, get_constant_log10<T>());
}

template <class R, class T>
inline void eval_log2(R& result, const T& a)
{
   eval_log(result, a);
   eval_divide(result, get_constant_ln2<R>());
}

template <typename T>
inline void eval_pow(T& result, const T& x, const T& a)
{
   BOOST_STATIC_ASSERT_MSG(number_category<T>::value == number_kind_floating_point, "The pow function is only valid for floating point types.");
   typedef typename boost::multiprecision::detail::canonical<int, T>::type si_type;
   typedef typename mpl::front<typename T::float_types>::type              fp_type;

   if ((&result == &x) || (&result == &a))
   {
      T t;
      eval_pow(t, x, a);
      result = t;
      return;
   }

   if ((a.compare(si_type(1)) == 0) || (x.compare(si_type(1)) == 0))
   {
      result = x;
      return;
   }
   if (a.compare(si_type(0)) == 0)
   {
      result = si_type(1);
      return;
   }

   int type = eval_fpclassify(x);

   switch (type)
   {
   case FP_ZERO:
      switch (eval_fpclassify(a))
      {
      case FP_ZERO:
         result = si_type(1);
         break;
      case FP_NAN:
         result = a;
         break;
      case FP_NORMAL:
      {
         // Need to check for a an odd integer as a special case:
         try
         {
            typename boost::multiprecision::detail::canonical<boost::intmax_t, T>::type i;
            eval_convert_to(&i, a);
            if (a.compare(i) == 0)
            {
               if (eval_signbit(a))
               {
                  if (i & 1)
                  {
                     result = std::numeric_limits<number<T> >::infinity().backend();
                     if (eval_signbit(x))
                        result.negate();
                     errno = ERANGE;
                  }
                  else
                  {
                     result = std::numeric_limits<number<T> >::infinity().backend();
                     errno  = ERANGE;
                  }
               }
               else if (i & 1)
               {
                  result = x;
               }
               else
                  result = si_type(0);
               return;
            }
         }
         catch (const std::exception&)
         {
            // fallthrough..
         }
         BOOST_FALLTHROUGH;
      }
      default:
         if (eval_signbit(a))
         {
            result = std::numeric_limits<number<T> >::infinity().backend();
            errno  = ERANGE;
         }
         else
            result = x;
         break;
      }
      return;
   case FP_NAN:
      result = x;
      errno  = ERANGE;
      return;
   default:;
   }

   int s = eval_get_sign(a);
   if (s == 0)
   {
      result = si_type(1);
      return;
   }

   if (s < 0)
   {
      T t, da;
      t = a;
      t.negate();
      eval_pow(da, x, t);
      eval_divide(result, si_type(1), da);
      return;
   }

   typename boost::multiprecision::detail::canonical<boost::intmax_t, T>::type an;
   typename boost::multiprecision::detail::canonical<boost::intmax_t, T>::type max_an =
       std::numeric_limits<typename boost::multiprecision::detail::canonical<boost::intmax_t, T>::type>::is_specialized ? (std::numeric_limits<typename boost::multiprecision::detail::canonical<boost::intmax_t, T>::type>::max)() : static_cast<typename boost::multiprecision::detail::canonical<boost::intmax_t, T>::type>(1) << (sizeof(typename boost::multiprecision::detail::canonical<boost::intmax_t, T>::type) * CHAR_BIT - 2);
   typename boost::multiprecision::detail::canonical<boost::intmax_t, T>::type min_an =
       std::numeric_limits<typename boost::multiprecision::detail::canonical<boost::intmax_t, T>::type>::is_specialized ? (std::numeric_limits<typename boost::multiprecision::detail::canonical<boost::intmax_t, T>::type>::min)() : -min_an;

   T fa;
#ifndef BOOST_NO_EXCEPTIONS
   try
   {
#endif
      eval_convert_to(&an, a);
      if (a.compare(an) == 0)
      {
         detail::pow_imp(result, x, an, mpl::true_());
         return;
      }
#ifndef BOOST_NO_EXCEPTIONS
   }
   catch (const std::exception&)
   {
      // conversion failed, just fall through, value is not an integer.
      an = (std::numeric_limits<boost::intmax_t>::max)();
   }
#endif
   if ((eval_get_sign(x) < 0))
   {
      typename boost::multiprecision::detail::canonical<boost::uintmax_t, T>::type aun;
#ifndef BOOST_NO_EXCEPTIONS
      try
      {
#endif
         eval_convert_to(&aun, a);
         if (a.compare(aun) == 0)
         {
            fa = x;
            fa.negate();
            eval_pow(result, fa, a);
            if (aun & 1u)
               result.negate();
            return;
         }
#ifndef BOOST_NO_EXCEPTIONS
      }
      catch (const std::exception&)
      {
         // conversion failed, just fall through, value is not an integer.
      }
#endif
      eval_floor(result, a);
      // -1^INF is a special case in C99:
      if ((x.compare(si_type(-1)) == 0) && (eval_fpclassify(a) == FP_INFINITE))
      {
         result = si_type(1);
      }
      else if (a.compare(result) == 0)
      {
         // exponent is so large we have no fractional part:
         if (x.compare(si_type(-1)) < 0)
         {
            result = std::numeric_limits<number<T, et_on> >::infinity().backend();
         }
         else
         {
            result = si_type(0);
         }
      }
      else if (type == FP_INFINITE)
      {
         result = std::numeric_limits<number<T, et_on> >::infinity().backend();
      }
      else if (std::numeric_limits<number<T, et_on> >::has_quiet_NaN)
      {
         result = std::numeric_limits<number<T, et_on> >::quiet_NaN().backend();
         errno  = EDOM;
      }
      else
      {
         BOOST_THROW_EXCEPTION(std::domain_error("Result of pow is undefined or non-real and there is no NaN for this number type."));
      }
      return;
   }

   T t, da;

   eval_subtract(da, a, an);

   if ((x.compare(fp_type(0.5)) >= 0) && (x.compare(fp_type(0.9)) < 0) && (an < max_an) && (an > min_an))
   {
      if (a.compare(fp_type(1e-5f)) <= 0)
      {
         // Series expansion for small a.
         eval_log(t, x);
         eval_multiply(t, a);
         hyp0F0(result, t);
         return;
      }
      else
      {
         // Series expansion for moderately sized x. Note that for large power of a,
         // the power of the integer part of a is calculated using the pown function.
         if (an)
         {
            da.negate();
            t = si_type(1);
            eval_subtract(t, x);
            hyp1F0(result, da, t);
            detail::pow_imp(t, x, an, mpl::true_());
            eval_multiply(result, t);
         }
         else
         {
            da = a;
            da.negate();
            t = si_type(1);
            eval_subtract(t, x);
            hyp1F0(result, da, t);
         }
      }
   }
   else
   {
      // Series expansion for pow(x, a). Note that for large power of a, the power
      // of the integer part of a is calculated using the pown function.
      if (an)
      {
         eval_log(t, x);
         eval_multiply(t, da);
         eval_exp(result, t);
         detail::pow_imp(t, x, an, mpl::true_());
         eval_multiply(result, t);
      }
      else
      {
         eval_log(t, x);
         eval_multiply(t, a);
         eval_exp(result, t);
      }
   }
}

template <class T, class A>
#if BOOST_WORKAROUND(BOOST_MSVC, < 1800)
inline typename enable_if_c<!is_integral<A>::value, void>::type
#else
inline typename enable_if_c<is_compatible_arithmetic_type<A, number<T> >::value && !is_integral<A>::value, void>::type
#endif
eval_pow(T& result, const T& x, const A& a)
{
   // Note this one is restricted to float arguments since pow.hpp already has a version for
   // integer powers....
   typedef typename boost::multiprecision::detail::canonical<A, T>::type          canonical_type;
   typedef typename mpl::if_<is_same<A, canonical_type>, T, canonical_type>::type cast_type;
   cast_type                                                                      c;
   c = a;
   eval_pow(result, x, c);
}

template <class T, class A>
#if BOOST_WORKAROUND(BOOST_MSVC, < 1800)
inline void
#else
inline typename enable_if_c<is_compatible_arithmetic_type<A, number<T> >::value, void>::type
#endif
eval_pow(T& result, const A& x, const T& a)
{
   typedef typename boost::multiprecision::detail::canonical<A, T>::type          canonical_type;
   typedef typename mpl::if_<is_same<A, canonical_type>, T, canonical_type>::type cast_type;
   cast_type                                                                      c;
   c = x;
   eval_pow(result, c, a);
}

template <class T>
void eval_exp2(T& result, const T& arg)
{
   BOOST_STATIC_ASSERT_MSG(number_category<T>::value == number_kind_floating_point, "The log function is only valid for floating point types.");

   // Check for pure-integer arguments which can be either signed or unsigned.
   typename boost::multiprecision::detail::canonical<typename T::exponent_type, T>::type i;
   T                                                                                     temp;
   try
   {
      eval_trunc(temp, arg);
      eval_convert_to(&i, temp);
      if (arg.compare(i) == 0)
      {
         temp = static_cast<typename mpl::front<typename T::unsigned_types>::type>(1u);
         eval_ldexp(result, temp, i);
         return;
      }
   }
   catch (const boost::math::rounding_error&)
   { /* Fallthrough */
   }
   catch (const std::runtime_error&)
   { /* Fallthrough */
   }

   temp = static_cast<typename mpl::front<typename T::unsigned_types>::type>(2u);
   eval_pow(result, temp, arg);
}

namespace detail {

template <class T>
void small_sinh_series(T x, T& result)
{
   typedef typename boost::multiprecision::detail::canonical<unsigned, T>::type ui_type;
   bool                                                                         neg = eval_get_sign(x) < 0;
   if (neg)
      x.negate();
   T p(x);
   T mult(x);
   eval_multiply(mult, x);
   result    = x;
   ui_type k = 1;

   T lim(x);
   eval_ldexp(lim, lim, 1 - boost::multiprecision::detail::digits2<number<T, et_on> >::value());

   do
   {
      eval_multiply(p, mult);
      eval_divide(p, ++k);
      eval_divide(p, ++k);
      eval_add(result, p);
   } while (p.compare(lim) >= 0);
   if (neg)
      result.negate();
}

template <class T>
void sinhcosh(const T& x, T* p_sinh, T* p_cosh)
{
   typedef typename boost::multiprecision::detail::canonical<unsigned, T>::type ui_type;
   typedef typename mpl::front<typename T::float_types>::type                   fp_type;

   switch (eval_fpclassify(x))
   {
   case FP_NAN:
      errno = EDOM;
      // fallthrough...
   case FP_INFINITE:
      if (p_sinh)
         *p_sinh = x;
      if (p_cosh)
      {
         *p_cosh = x;
         if (eval_get_sign(x) < 0)
            p_cosh->negate();
      }
      return;
   case FP_ZERO:
      if (p_sinh)
         *p_sinh = x;
      if (p_cosh)
         *p_cosh = ui_type(1);
      return;
   default:;
   }

   bool small_sinh = eval_get_sign(x) < 0 ? x.compare(fp_type(-0.5)) > 0 : x.compare(fp_type(0.5)) < 0;

   if (p_cosh || !small_sinh)
   {
      T e_px, e_mx;
      eval_exp(e_px, x);
      eval_divide(e_mx, ui_type(1), e_px);
      if (eval_signbit(e_mx) != eval_signbit(e_px))
         e_mx.negate(); // Handles lack of signed zero in some types

      if (p_sinh)
      {
         if (small_sinh)
         {
            small_sinh_series(x, *p_sinh);
         }
         else
         {
            eval_subtract(*p_sinh, e_px, e_mx);
            eval_ldexp(*p_sinh, *p_sinh, -1);
         }
      }
      if (p_cosh)
      {
         eval_add(*p_cosh, e_px, e_mx);
         eval_ldexp(*p_cosh, *p_cosh, -1);
      }
   }
   else
   {
      small_sinh_series(x, *p_sinh);
   }
}

} // namespace detail

template <class T>
inline void eval_sinh(T& result, const T& x)
{
   BOOST_STATIC_ASSERT_MSG(number_category<T>::value == number_kind_floating_point, "The sinh function is only valid for floating point types.");
   detail::sinhcosh(x, &result, static_cast<T*>(0));
}

template <class T>
inline void eval_cosh(T& result, const T& x)
{
   BOOST_STATIC_ASSERT_MSG(number_category<T>::value == number_kind_floating_point, "The cosh function is only valid for floating point types.");
   detail::sinhcosh(x, static_cast<T*>(0), &result);
}

template <class T>
inline void eval_tanh(T& result, const T& x)
{
   BOOST_STATIC_ASSERT_MSG(number_category<T>::value == number_kind_floating_point, "The tanh function is only valid for floating point types.");
   T c;
   detail::sinhcosh(x, &result, &c);
   if ((eval_fpclassify(result) == FP_INFINITE) && (eval_fpclassify(c) == FP_INFINITE))
   {
      bool s = eval_signbit(result) != eval_signbit(c);
      result = static_cast<typename mpl::front<typename T::unsigned_types>::type>(1u);
      if (s)
         result.negate();
      return;
   }
   eval_divide(result, c);
}

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

/* pow.hpp
57Sxwfy42LQMaOUUo3DpcU5Mmbp/w2uidvBIm9CKHo21UUoWWujhmCfrW84nE5L2kgjSxQjDdVI4L3o5dVDLjD2NfVTb0AXIJoi7IyH4jt0Pe7a2jxPdDTMBieDxNrsOmU19HjxZVRxoQpbe/3qR2IqJWL/9IWRRQFbfzZGTXnF10ArVvugRzVGltk7Hacu4el7EttbuYi0X4a7s7wiyIeyo9pL0bhtuQ5Bvn/zYRWB331npVoaofZpW/YbP43vdabZfBuBtiGbcYPuP+NHcEPu0BfaieVvxxdxNwHPIkF34l97EzgIeyLy1ouyY0U7sNCvxr0be6jmfO/6I/RZmkUdRSOOnu1Sl+vmi8SR+veR+K6NvBEEPyc9nqq3o1N2vDKM3+IVbtR8hnTF628N/qTXaR8cfEOcOuWBJpsZ4SXknsPvmYy5zEWqSoR1Myl5IyV4sjArIVscuKuqjfGGCobIQdXoTN09BCg4jxdHQ5zZ6LVL5zhYb2bUJtcX/2/mUW9aV3Oa0VI8yErhJ0NbC+bRvXrCklnRPPiEO2Xrz+PgJRbG34TEey/bE+oKnb5PsMMNgW5tNlQ6WspX8LsUfoggZx/vINRT5E3gFizgVhn+Qwe9JqDmPC0qXyrgDfe8bOCn6K9SJ/yxW7jxQUUkO8DuQbOdcUZQ0+XW4uCRGIdPQNR5GwQKG+sC3dWesqbXCiu8knApjrzhvhcERAlc8bfz4JcJq09qFdaWWmezYRuANYA5Dpbd2Id0bwP5uP13sqsU8dElsMPSfi79GgXLUNAhGViFYQNYJGBh3I2sA1PlCnU4uH9l8XGt8rIo7yBirDIuKoNEPzxAt0adEDy8qsKJWlYtvvBANeJ7s6qZ63oJMeqS9zLf3Tkkkmq3XskWu/G3kge3S9vIL1o5Bu7EXlU6SDnn2Q9wrjomIH94AftCVdzqGX6TDdGwdBhesbuBrYU1RjbFHiScSVpFGT7AxQhXv3Jkex2ChRIVWI2PnUJTrvZscjHQ0wffizjnq65W7c/B52i6PMjxe+ZXCwJtHGIf2gLJzu72PF5fm4mFxA790vVPPlqrZqCyyBko+pupLPs0QTULlhVJ3p9RYnhmpJotQZVyVN8JKJuPyYCHIOVdPMMVJ5RTzoWzT8kK11AzT32VvqwLO0w00ifs5AsamYpYSJuBFhaXT4scu/N1Xsey/8aySCxdWIKL4bP8Oysxz+XdPSkXqgKcFC2zKwk/vCyRr/bRWkJlvXqt9npDUlF/yCSBxTFNQQrCv7l9oXAvrXvLESjiwUB8Zh/NEPmSQ83CVIfA+Ea4R8FP80qxPFEyyZ2H0ji1WLvtuRqYJTUEpqBt2kamwZ1dXjL2WPj6ZCC0HcZ78++bT+cZnCmt5wIpel8XyH0/zGGahhToAEvYoVRMRZcpCn1LOOWfs7HskqTw0TRpSts4+B62c0J0VEnzEfd6llo07YgQy+PTepVSdR+roIuXK3iWRCBfSl5qVYaP1d1ZmHDlPirdN2fNNnLQN1mZicxEKrmd6PKCAMSK5xFEizYqubXI+PvttbBjZuEqlNeN1deedt0NA8BiRfD8OtojR1F3/iA2TrBkVeyrfc4t7klqnG3rNNLKmDQIYCxQbdYgtqzrn4V9MHjaa2OG7Icnqb7pxZ3BF5JW3/jXOjALb/wOBCKQuC5tj4DOxGFRri3iySOdPMuFqOx5lt75Iv1I8dLOTfqTNtHaZ1dW5cgslKEAI8ImdMxt0unQ/4bP7klAVN4XIr6frovsA0x4XlccyGn4GH3rHMTezJ1hVaE5C/0lvIDh+EbYnm1c7OMgko34coxn2iMLfLJKn7sFLpAsNw3jrTptBvDd34T4tcIIpVsoP3uF34TMJDVwNJHdSJrf0UG62lOgMsNY9d+8+3JCaJTEkYWC45kBy9wTxpdC0MjE8EGGuMdBAjeOeod3r13Nx2KTjjB/Ev3M8YODomnomMc1jLmRC6xmWIiI79xJcDlzUEWxn4MpuA6zRqjhiI5ZrJ1G4IriXQr/iaZbS2rWwotQNMaPKpe599r5AVBZFfuawYdetiy/FLsGfr3fH8ITT9YfZikzWi1HGXGJhiQyggjToADqvQ9u6hYzhrxsZHEh4zdj5gpN+TdxZAesL8FFRCnxqznp0CGe1YHoYYPOM9aQ0k2VXGBGoqMPfRkir1sl7osTb7LLj/Q/S73lzxfhSroK7k9xWQRhRxj0NR/IXybDsZNVm3+xJZhzFVdXtcMk2iNg/Ww75QeMZElrqdpt7wtrpR6NnvP4bDJO8NCGgsHaHJj6geM5JZt/fZRD71cBhSzzeTSlNY1nlJOEgBP5ZQfTSo2LRZGy0kuUBRC1Gko3r3EB3DPP9bfIFhO7pOvm14kqRFeVBye9tG894MqS6ry+Vbe2Y6+dUONtor7Sw1U95knQObbvi78djEYFR8tbrVuXjxEo3HryaF/I/tDBXr9ItHLlmSJymz9G+MWwPtRXgX1Mf1np8c3eqn07ynM++VrnZT10zXkeTqtP/ET/NN19HPd43MUbsra7xkuJEVUWCdgNZgXcQXv3nXsi++ZxvlHMBlQFWhysSZ1dJwZbPZPswbhJBuFiqRohF+p9WtXByCTIfYbcJgUMQ66wnihaampIT4nfY4lgrYrvA2LGDAeddGppRWLqyaBX5GnxPP90ygg7chz4zrGsLiTl+ZQPhGdYwxYIwl9DAvQ8cVJGo8Rd+vQDUGONwKzF+ffSJfgOAy7uLWbbGl4hIiHm7a363hUcX3N8u8WzKvZN/8cwb5Tbbtc+qyz0uLO+tM4EK/3oS3jU9j1/vZMk8NRb1UAdbx+X99TAkP8A44G7rzQqGQpHa57Qti+3Dkj0Al7rIGqx/e2O+iOquwVw+TIiMM6Ty5MQrLOz6+Pt8xYI7khm29S8LtM0ZCygvgQsiTiLL26V7asRhztpqZHaXzM/fE1f9qihIP49szQSwT5yuuLm2T78sF2Hgo6YkAjSARUUYF9b+pWYLY1QtQmxqB5UwGVzjwTpRwHlOmqqiTt7lqmgtU5DSN5nmlhGgHw83EnZb5I69CF4NQd/eXBkN9opxP6FFd5/CxZew11HUNqoxQ2eTtZflWRmjj1YpmZfKKaTKd/R0byBkBdWEHm+jL8aZORBqp2nI2eXhUGsEQQVEXQaJtTE48kpHnypwwb4l/VWmIXMATkZIFi5TtuX7e8tZR/14CA5WrkyJUynotQ9eDgP2bwZgu7dyAAQs+9OZmeYfDV3dmvEiyLyLQ89iHd6cf349BdWntR6+4YPLVYOOmzBrOQzlDmwkK99JAR/4L8MmJiYOeWTrfofNeDkQCU0jyKGrCWfJuOexhVgbifysc7lb+0MSDNKYKR0DBIjxJ5uLQfMpCM3WudIDVxF1CudGVbsf/V8Lb1kP/vcwJSCpT+uuyjmx+rWGG3wduq+5Wbw4jJjecyUjk1nlAMG1/zBs/dxpeJIJ6bpX66occHPDfBN37R41T+FhuPIK05XZ1dNJQaCWI/qFS1PhmWUhGJnh60U8x/D2POtjbECXb34nMynSTYrWHji5K+qQ6YgF42buHTj+p3KxaOuDmN2GvyJqZb20b7geaBOTgEBcEOcIVjNmBXf75W//4NOp8wJgVFrtzwhIBuNupltqWEcO1CZpt7VKIaRR2wLJyAOC8YiPPwA0FtJzTI866bA3JlveffbBA3tHo9QG0MrilUpK5Q7Mbh3o/vGiPqKfldm7ynokoVo3lwo/bg6jRz3MZcuTR0Y2hAe1i/SVYdWb74VLqGcnuj/bfVWlAmfvO/DZHV/zO1avSogl82yiYk9m1AI8hXHSCe5ARCRbLu8oVM3YnVPPbA+BasPxJOqATky3nLJs+n3nVmCX4W7TdtE15r0g51Gk99z1qlmDXbXM5mdCKz9cUFT7pPjkT1yHd8B1Unkizxdbl33PIsjTrncOk+KsYrL75MZgdPbiV9xpPUjoy0FsUc1FPEAdIG/lbeXECezUdD9ZXtPcvzjMIFdGKKr5Hqn5aEaTR+fBnsoAXt+37WKT07uB/GXneqPc3N9ETU5sIfWU1qznyr1gnEtyeUzNsNKqCMZIpSDceOBMIZ1FxDyBE54/FCNcLtxpKdr8O7+JAneQSQXD+PYa9hA8BRk0lGs6DsiPHncHuIvcjpvYirqtbVV4UlmAoneejm1I5WPcBYmhXhIzIIU7bVef2MD779m/nGPQi8VcCIVA4+0qbyxYzD95WSz7GgWuIz3M9BW9E0wPtBK/kymlPD36Cc3uld33H/sLtp5hZmgtx03TbVwpweYSauRKCkcrbRzssMyIIWq/4TADAnMO9yTnJnZCGDBvS2PHkxI1LBX0zVybV/hFaxkiNyLuJCoNbwmKJA/rt3g/DkqOZcfzqnadu5KR/MXc3meb1rIF1UJ8BqAJyKrxnX7qPuuPjsJUDNUWtXdeOjTcDOeMf7e/R455EU4iBCnG4xny+PyGKl254TsZuPYECPwQER0EjdxIYZhiConJzJggBOlF2DjD8TY9qSqIBIdDR6tvwEAqemT05YsOZCohJBrSc5UyonZkH/pK7pyx7cnrv5urfUcv4z8HKVFJdvc8Syxu4gYrZMcPNmSkEgmt90m94v/4vpMg9QNlaYMzG8F1dFYcjBSnEANEA2nQ/xhUy9FutFwQxjWpYrx9Jn6eNI6rRLi9pFsBcx6WQn3bFh7ijZIOTSsvc/Bty99Gw7BiUrq0ehcwTpy/vBpSnywzUOdIRdtEuqprKwmr1haxLmhL983SWnl7r6//bLuonoaPxfNv3Gak8h85WOf1UmFWeB+FsNffUJ+JJDdxMLzk4oJyQcpvyuUGTs71C1NTEBTEmDB14tPgdVm3PpFCaTnDeBsfly67PD/rF6cOE7yk4y1X8T4k3S4dkXAjhK/EmBj1zRYp4bgIrS8eEdN6hNZ9RWLzj1r2/pkyuy60oMHxwiISNEG97ljI+fTLyqSKODKk401WBSjy1CIC1ax/cbEKnyWLmmPtgpziNF7Nt1CZsshz8UfuSFM+YxBPun6JhS68eanv8n8HBy33ciJC6yt6S3J2/wjugd7uSP53stiGAJRy4e5gw1SV3QRgWdWXafg+9KlBduHol3DNy390H8zL5RxqbQPL/SmX/pIket7LgJSEgJdaH9m0xepeU/n4MbPxojUJhqd7OvSnBZ5ggKSoBGtOnm5Wg5CC6Sh1SY6CU31tvRAZ9fyGaJv4+gSn6E69PuwCrtf0gTXWt74xEzqZb1zWVhy4T6RBkRwQiyixD/vBmDk5hq1a2E+j06WrEIBP0Wt1/CzB2TZjO2c/Rog+Qq+f9TlAa1rF+cXX18n4xOemFcYdHy7kEzok6rswdti3roZlQX7dgFoyY/5AmpQyTvvQHXlntDtcNyxGae2v8GeiZgqkm1teCi+P9vl5ivZ8xEwB2pR4hc2PFi2j0Reap+sb8lPHrb0XxRmqCqY5PyYav16Rpoae+Bni2bXKvDAmpDgCJKR+CqhQuyCkebg2sVHKNHdPmufx5OZLwsPjJuMHuJZstWiN5fbDl48Vn1x53ken9354GEuMKdzN3xIVAF15+gkVcPueLwESW5uPOwzKHhdv1wG/W/DYEfGeG4mE8W2uVZTD5ovg92NQBW45jpB986IXqJL6vJU33Qwwvk4Q3RUBCfFQZicjgt7FSEQlWr6yUw8zAgGSVG3FeUs5/BvvB7a0zkMDriVw1Cm+zrmukzthqwvNdvnxHmhRT0jlvb9le4Vkqm7jZLFbzJlSae9UK7wmvmyc+C+HIj3H0G76yIsULb3h8MGTGpAe1fi+Lqrgk6PPkp1/RxnlAzezwnyY7ntz4tWeI0mIYScyGNCnohluEjRrm24DeP9F5D0FdjoSN9H8THteGkfIX+J8bq0qyGAZAk2KnlL7RD6PdmAsNHuB79Wjt2gPshUlsw0fd15rJxuvdhf6W0c0OPzBQR/hjq91OJj01SBVsRGXmBCg7ZqMkMiqstZrSdFbp2gd31YVbWzmFGO2vQcFG3mjwykKzpmY/maKwSKx1cNEjTPtTlxsRlgG5V/CvwfE2vKVOKep5jynX3q6n2x3TuDuOffNceNa8Pje/7qtJVr5PK18RadMuLAAvBEqD5kvhBDR1ZhaLwih907uz0/txBs1Fs36W745W/oqDmU8XKC/r/YgFS+6tJLoWV7IhIXKzNMqosz9MOtI/hGIYTqEnvF6Gyx+Sf++Rhx7ynCorWs92EhCf3juEDFVtlhr3CqsK1MQlqFCdZCVHn6I1sk9Ld9tOy+7dNlzbJFx04WPs6lEslJnQIuWjk+YVUA5cLpiyJDuQ5k2bFjcPf315RfhA5a2Old4/Q8d5CfgvFE6qyXTVI6rBAXP2IE6yHCfRf+bH0OWyevE4uUBwN3kgsEcloarlsu3DvkPI64lacg6Igmz3rCTYCA4KcXYl80mJmn5KuSQ/ITVO/PPB98LmWbp4/b0SJWnLvZUjJ9hwaQyrUY0dXj99rnbsXO621MLQeA9qTYmSGw6RHdIn9Erfzr+fYJx/LfHjWFBtHoKjNV85moto38VKPnn1c1x/z73d1EVRbq+zPoOVxHM46ZsqT4k7nMnElMA7jVZQHBDt+viadx3gevbLOjFtDorlrmkjfo6n5lifmm5GSspS9gbCTlALlKnBGutpa6IxZi6wh0xxaVOVGDE0aO1VONPmT0qmvitjGdkhv9a9HWKr03+GU9QHXA8tyyiBWd03JiKTHIHs+X1tFsONuGdUkSHua7QbqhC4+uoRBOYmNX3FY4Et8jYVES/QILG35OSLUhlUJliVKkapmgNuE44TP0AS+tMGa6pDhRcZf0vDOTEki0TTQphGtctVm9PW6fmB3D1JQoOy7SgqzmoSX5CCUqcAMqy9HKwPVyuV0Ev83lZZ3Twp788XWeMdUeqo+fmaIGXHuszWZ6l69fUvJMb5HiaKrIeVTW3LuN/2Wu9q/gtdw4cE3qLP/bpdpYdBlrqqoYbp7sGaXdCU7iuoI0b3quaFyzBmRTysViPP5CktAOhbqJSFth7VZijyFtgv9ugE+5VHA3jQ/u6CaYFJZs6+k88Hm9zlh9CCPjg5Lc7EyzZh7GD9CYwD3EzvHNWubNOQyM/5XtaWxfRG23Q0h512yovIjtjXZLsBegYQE85KtB5bwAjg9hYqkN8Lu/oVNkM59kBPNJLoMgGLimw+S4MBEKAFHLQc23pzDgi6iqJfaeGOWxhLaFyHQl7orQCQSdOxto9KlTjjUiFnlmkVWlCk+EXgV9uWY8JgNhdx7wUDVyTp2aO3brIe8ALoQbaAsyCWB00C+/XdenQourBcSLPvIqPqoGy6y840AYlOfeO/riPXNi7FghNr37kDgfaTOH+G0lI+0LkB9TCJ9sSosWTFogL6rkuoVe8MRpt0DYOCBpuTzGu26oqaw+K9WlSKmhq6KLwaAFFZLwqR8mBSKP8rPf/PiywTScRG4tRz31nSIPPiPeSbW4vrxJcXTMKamoHbn75o6CPu9kwdTSnDys8YcfYau0Wg9MSncTPb471/AxS5f3uYj65x5jN8jgVqU/aaNn4dAgOaNeDv7FCcimWjc+pUcsRiTxWXgN06bfB1eEwOPnd6Lx7zGNPESCwbUnRSLYZ+se6RxJYSgqGKrKg/RhbjIVLWyWZCdvchKFtbK2BSRsKf4EAYOZhWnpiVSZKnkVjlV5A+SjlZcT4MJsMq5nraV71Ss8/uoEeTEPT4Zys8CK+SJL3Pc+fevhaSs8WB8wPl+fSfyTaGNtBkrlPN/gLV2itAKVelCM7Z1Q/B/LRYu12ztfbvWkJtZ1T6HGXdnXEXgbnVevbQBSOaUO8NqRru5x3py3+OSFoYqDjx01fFlifZ9vzhY3HnZ2gI19KaoNT9fxKLsYhQK0+o+cxBaHnYmwEvmGf6AM72afb6ezLQS3c82O65DN+hAjveSqYN2EBrKFIaHCHhdtI8nUhQxqVDISDQoN6QeKnwd2L1fIU6ehQ1D5MPudGS8xi+1Og9k7U+ScMiXfdjY6twMg14aFwdtCBc1nuRo/yRhbFdxV2LfSeQyUAUr9qbR9inezJUnFshEzUiYLRMeEwgbHttiCunuZpTftY4sIaij4uuozo48BXZlIEDpJkTr2su0FKMad2GondUh48Hp8DR4UtImI4UsYB+lFKG64Z45KGnty0O82t7l9Lk57d+1GyQpcZnMsMoIuodOOlXOKH2CFEXzATd2xudKyXbg/MRWzaTa32wE+teYsHL77HfDFNdVgVdUmlxfHFqMEO/XmAg7oR6XY7Cw2hl8Ga+qnGYT5PnOncH6B9Ns6D1tevYEFbrGP8yl31CR2/TG9E4z7OwCIQvyQ86M15G5Kvkh/VveZee2vYlWO7/x3XPS45dC8/Vv4VC6MDBmKgx4afU/laN8Iku+5AQFbhRmNaZoMUfb5jjV3f3GDdVmSdj6Q3ASIIDfc9w720ZJKptnwfIPK+bL2PcpHpwAOjjS+nKykoE71N/ZnmTvtnt5hMVIw1O0uNuZSqM+KcV7A9xxnOPbD6gfbT3dEbY+QwfFgouVmX6iLUOwcnP2+agpu4bNMbbLYHndEPLP9f+anaHgb+jG3hZoAHuwRDLkfiNeXyTUEsRIKv4GoodHtrjQqg6QkS8OAuw5q5+edwbhHh6nPhyRR4wSJB9M/0rh33YMEHxz6SR1StxmU/z8XRAbVPuwWS1pIog+pOnIm5MzyRqXUed1LFHa+jP2Vz72oVqnfvzB69jt7H4QXrCOBLRdGPJY3FCvT2823mXgQRCdC7JZhQAYdk6Rz6y0htUu+iwxtmuBwtb+YK9OoOlzdi2lJ6cibkVAim2aMQiQ2ZyQfm2qn3JIbmq1LTK9T8+LEujo3VOdzuB8DDSzhZPO16hZYPoluZXJKo3n8+oIlTjwZh5gglP+T8Y4RDFwyKdwPWAiBYWaf7wW+fy4YK+8Qj88K+eqQN97/L+8+I5h7lz/Yf2YPmWyn1hDL5FvFwHQifOesGkejjHmKftvQkRw8rwrk+DOipwGW2Ej823d58A4sYcJxcZMQTTDAnYbLRhiWxS+zn5tYLD1h2O2UpdnuiscjeiSx4/ifrLqCwU0jVlNhGHa2pfyeqIsdiBCRN2ll+V/jir2ZJTEDTRLHkeeC7RUr03Rs=
*/