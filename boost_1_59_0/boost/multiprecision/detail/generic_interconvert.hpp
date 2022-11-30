///////////////////////////////////////////////////////////////////////////////
//  Copyright 2011 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MP_GENERIC_INTERCONVERT_HPP
#define BOOST_MP_GENERIC_INTERCONVERT_HPP

#include <cmath>
#include <limits>
#include <boost/multiprecision/detail/standalone_config.hpp>
#include <boost/multiprecision/detail/default_ops.hpp>
#include <boost/multiprecision/detail/no_exceptions_support.hpp>
#include <boost/multiprecision/detail/assert.hpp>
#include <boost/multiprecision/detail/functions/trunc.hpp>

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable : 4127 6326)
#endif

namespace boost { namespace multiprecision { namespace detail {

template <class To, class From>
inline To do_cast(const From& from)
{
   return static_cast<To>(from);
}
template <class To, class B, ::boost::multiprecision::expression_template_option et>
inline To do_cast(const number<B, et>& from)
{
   return from.template convert_to<To>();
}

template <class To, class From>
void generic_interconvert(To& to, const From& from, const std::integral_constant<int, number_kind_floating_point>& /*to_type*/, const std::integral_constant<int, number_kind_integer>& /*from_type*/)
{
   using default_ops::eval_add;
   using default_ops::eval_bitwise_and;
   using default_ops::eval_convert_to;
   using default_ops::eval_get_sign;
   using default_ops::eval_is_zero;
   using default_ops::eval_ldexp;
   using default_ops::eval_right_shift;
   // smallest unsigned type handled natively by "From" is likely to be it's limb_type:
   using l_limb_type = typename canonical<unsigned char, From>::type;
   // get the corresponding type that we can assign to "To":
   using to_type = typename canonical<l_limb_type, To>::type;
   From                                              t(from);
   bool                                              is_neg = eval_get_sign(t) < 0;
   if (is_neg)
      t.negate();
   // Pick off the first limb:
   l_limb_type limb;
   l_limb_type mask = static_cast<l_limb_type>(~static_cast<l_limb_type>(0));
   From        fl;
   eval_bitwise_and(fl, t, mask);
   eval_convert_to(&limb, fl);
   to = static_cast<to_type>(limb);
   eval_right_shift(t, std::numeric_limits<l_limb_type>::digits);
   //
   // Then keep picking off more limbs until "t" is zero:
   //
   To       l;
   unsigned shift = std::numeric_limits<l_limb_type>::digits;
   while (!eval_is_zero(t))
   {
      eval_bitwise_and(fl, t, mask);
      eval_convert_to(&limb, fl);
      l = static_cast<to_type>(limb);
      eval_right_shift(t, std::numeric_limits<l_limb_type>::digits);
      eval_ldexp(l, l, shift);
      eval_add(to, l);
      shift += std::numeric_limits<l_limb_type>::digits;
   }
   //
   // Finish off by setting the sign:
   //
   if (is_neg)
      to.negate();
}

template <class To, class From>
void generic_interconvert(To& to, const From& from, const std::integral_constant<int, number_kind_integer>& /*to_type*/, const std::integral_constant<int, number_kind_integer>& /*from_type*/)
{
   using default_ops::eval_bitwise_and;
   using default_ops::eval_bitwise_or;
   using default_ops::eval_convert_to;
   using default_ops::eval_get_sign;
   using default_ops::eval_is_zero;
   using default_ops::eval_left_shift;
   using default_ops::eval_right_shift;
   // smallest unsigned type handled natively by "From" is likely to be it's limb_type:
   using limb_type = typename canonical<unsigned char, From>::type;
   // get the corresponding type that we can assign to "To":
   using to_type = typename canonical<limb_type, To>::type;
   From                                            t(from);
   bool                                            is_neg = eval_get_sign(t) < 0;
   if (is_neg)
      t.negate();
   // Pick off the first limb:
   limb_type limb;
   limb_type mask = static_cast<limb_type>(~static_cast<limb_type>(0));
   From      fl;
   eval_bitwise_and(fl, t, mask);
   eval_convert_to(&limb, fl);
   to = static_cast<to_type>(limb);
   eval_right_shift(t, std::numeric_limits<limb_type>::digits);
   //
   // Then keep picking off more limbs until "t" is zero:
   //
   To       l;
   unsigned shift = std::numeric_limits<limb_type>::digits;
   while (!eval_is_zero(t))
   {
      eval_bitwise_and(fl, t, mask);
      eval_convert_to(&limb, fl);
      l = static_cast<to_type>(limb);
      eval_right_shift(t, std::numeric_limits<limb_type>::digits);
      eval_left_shift(l, shift);
      eval_bitwise_or(to, l);
      shift += std::numeric_limits<limb_type>::digits;
   }
   //
   // Finish off by setting the sign:
   //
   if (is_neg)
      to.negate();
}

template <class To, class From>
void generic_interconvert(To& to, const From& from, const std::integral_constant<int, number_kind_floating_point>& /*to_type*/, const std::integral_constant<int, number_kind_floating_point>& /*from_type*/)
{
#ifdef BOOST_MSVC
#pragma warning(push)
//#pragma warning(disable : 4127)
#endif
   //
   // The code here only works when the radix of "From" is 2, we could try shifting by other
   // radixes but it would complicate things.... use a string conversion when the radix is other
   // than 2:
   //
   BOOST_IF_CONSTEXPR(std::numeric_limits<number<From> >::radix != 2)
   {
      to = from.str(0, std::ios_base::fmtflags()).c_str();
      return;
   }
   else
   {
      using ui_type = typename canonical<unsigned char, To>::type;

      using default_ops::eval_add;
      using default_ops::eval_convert_to;
      using default_ops::eval_fpclassify;
      using default_ops::eval_get_sign;
      using default_ops::eval_is_zero;
      using default_ops::eval_subtract;

      //
      // First classify the input, then handle the special cases:
      //
      int c = eval_fpclassify(from);

      if (c == static_cast<int>(FP_ZERO))
      {
         to = ui_type(0);
         return;
      }
      else if (c == static_cast<int>(FP_NAN))
      {
         to = static_cast<const char*>("nan");
         return;
      }
      else if (c == static_cast<int>(FP_INFINITE))
      {
         to = static_cast<const char*>("inf");
         if (eval_get_sign(from) < 0)
            to.negate();
         return;
      }

      typename From::exponent_type e;
      From                         f, term;
      to = ui_type(0);

      eval_frexp(f, from, &e);

      constexpr const int shift = std::numeric_limits<std::intmax_t>::digits - 1;

      while (!eval_is_zero(f))
      {
         // extract int sized bits from f:
         eval_ldexp(f, f, shift);
         eval_floor(term, f);
         e -= shift;
         eval_ldexp(to, to, shift);
         typename boost::multiprecision::detail::canonical<std::intmax_t, To>::type ll;
         eval_convert_to(&ll, term);
         eval_add(to, ll);
         eval_subtract(f, term);
      }
      using to_exponent = typename To::exponent_type;
      if (e > (std::numeric_limits<to_exponent>::max)())
      {
         to = static_cast<const char*>("inf");
         if (eval_get_sign(from) < 0)
            to.negate();
         return;
      }
      if (e < (std::numeric_limits<to_exponent>::min)())
      {
         to = ui_type(0);
         if (eval_get_sign(from) < 0)
            to.negate();
         return;
      }
      eval_ldexp(to, to, static_cast<to_exponent>(e));
   }
#ifdef BOOST_MSVC
#pragma warning(pop)
#endif
}

template <class To, class From>
void generic_interconvert(To& to, const From& from, const std::integral_constant<int, number_kind_rational>& /*to_type*/, const std::integral_constant<int, number_kind_rational>& /*from_type*/)
{
   using to_component_type = typename component_type<number<To> >::type;

   number<From>      t(from);
   to_component_type n(numerator(t)), d(denominator(t));
   using default_ops::assign_components;
   assign_components(to, n.backend(), d.backend());
}

template <class To, class From>
void generic_interconvert(To& to, const From& from, const std::integral_constant<int, number_kind_rational>& /*to_type*/, const std::integral_constant<int, number_kind_integer>& /*from_type*/)
{
   using to_component_type = typename component_type<number<To> >::type;

   number<From>      t(from);
   to_component_type n(t), d(1);
   using default_ops::assign_components;
   assign_components(to, n.backend(), d.backend());
}

template <class LargeInteger>
inline typename std::enable_if<is_signed_number<LargeInteger>::value>::type make_positive(LargeInteger& val)
{
   if (val.sign() < 0)
      val = -val;
}
template <class LargeInteger>
inline typename std::enable_if<!is_signed_number<LargeInteger>::value>::type make_positive(LargeInteger&){}

template <class R, class LargeInteger>
R safe_convert_to_float(const LargeInteger& i)
{
   using std::ldexp;
   if (!i)
      return R(0);
   BOOST_IF_CONSTEXPR(std::numeric_limits<R>::is_specialized && std::numeric_limits<R>::max_exponent)
   {
      LargeInteger val(i);
      make_positive(val);
      std::size_t mb = msb(val);
      if (mb >= std::numeric_limits<R>::max_exponent)
      {
         int scale_factor = static_cast<int>(mb) + 1 - std::numeric_limits<R>::max_exponent;
         BOOST_MP_ASSERT(scale_factor >= 1);
         val >>= scale_factor;
         R result = val.template convert_to<R>();
         BOOST_IF_CONSTEXPR(std::numeric_limits<R>::digits == 0 || std::numeric_limits<R>::digits >= std::numeric_limits<R>::max_exponent)
         {
            //
            // Calculate and add on the remainder, only if there are more
            // digits in the mantissa that the size of the exponent, in
            // other words if we are dropping digits in the conversion
            // otherwise:
            //
            LargeInteger remainder(i);
            remainder &= (LargeInteger(1) << scale_factor) - 1;
            result += ldexp(safe_convert_to_float<R>(remainder), -scale_factor);
         }
         return i.sign() < 0 ? static_cast<R>(-result) : result;
      }
   }
   return i.template convert_to<R>();
}

template <class To, class Integer>
inline typename std::enable_if<!(is_number<To>::value || std::is_floating_point<To>::value)>::type
generic_convert_rational_to_float_imp(To& result, const Integer& n, const Integer& d, const std::integral_constant<bool, true>&)
{
   //
   // If we get here, then there's something about one type or the other
   // that prevents an exactly rounded result from being calculated
   // (or at least it's not clear how to implement such a thing).
   //
   using default_ops::eval_divide;
   number<To> fn(safe_convert_to_float<number<To> >(n)), fd(safe_convert_to_float<number<To> >(d));
   eval_divide(result, fn.backend(), fd.backend());
}
template <class To, class Integer>
inline typename std::enable_if<is_number<To>::value || std::is_floating_point<To>::value>::type
generic_convert_rational_to_float_imp(To& result, const Integer& n, const Integer& d, const std::integral_constant<bool, true>&)
{
   //
   // If we get here, then there's something about one type or the other
   // that prevents an exactly rounded result from being calculated
   // (or at least it's not clear how to implement such a thing).
   //
   To fd(safe_convert_to_float<To>(d));
   result = safe_convert_to_float<To>(n);
   result /= fd;
}

template <class To, class Integer>
typename std::enable_if<is_number<To>::value || std::is_floating_point<To>::value>::type
generic_convert_rational_to_float_imp(To& result, Integer& num, Integer& denom, const std::integral_constant<bool, false>&)
{
   //
   // If we get here, then the precision of type To is known, and the integer type is unbounded
   // so we can use integer division plus manipulation of the remainder to get an exactly
   // rounded result.
   //
   if (num == 0)
   {
      result = 0;
      return;
   }
   bool s = false;
   if (num < 0)
   {
      s   = true;
      num = -num;
   }
   std::ptrdiff_t denom_bits = msb(denom);
   std::ptrdiff_t shift      = std::numeric_limits<To>::digits + denom_bits - msb(num);
   if (shift > 0)
      num <<= shift;
   else if (shift < 0)
      denom <<= boost::multiprecision::detail::unsigned_abs(shift);
   Integer q, r;
   divide_qr(num, denom, q, r);
   std::ptrdiff_t q_bits = msb(q);
   if (q_bits == std::numeric_limits<To>::digits - 1)
   {
      //
      // Round up if 2 * r > denom:
      //
      r <<= 1;
      int c = r.compare(denom);
      if (c > 0)
         ++q;
      else if ((c == 0) && (q & 1u))
      {
         ++q;
      }
   }
   else
   {
      BOOST_MP_ASSERT(q_bits == std::numeric_limits<To>::digits);
      //
      // We basically already have the rounding info:
      //
      if (q & 1u)
      {
         if (r || (q & 2u))
            ++q;
      }
   }
   using std::ldexp;
   result = do_cast<To>(q);
   result = ldexp(result, static_cast<int>(-shift));
   if (s)
      result = -result;
}
template <class To, class Integer>
inline typename std::enable_if<!(is_number<To>::value || std::is_floating_point<To>::value)>::type
generic_convert_rational_to_float_imp(To& result, Integer& num, Integer& denom, const std::integral_constant<bool, false>& tag)
{
   number<To> t;
   generic_convert_rational_to_float_imp(t, num, denom, tag);
   result = t.backend();
}

template <class To, class From>
inline void generic_convert_rational_to_float(To& result, const From& f)
{
   //
   // Type From is always a Backend to number<>, or an
   // instance of number<>, but we allow
   // To to be either a Backend type, or a real number type,
   // that way we can call this from generic conversions, and
   // from specific conversions to built in types.
   //
   using actual_from_type = typename std::conditional<is_number<From>::value, From, number<From> >::type                                                                                                                                                                                                           ;
   using actual_to_type = typename std::conditional<is_number<To>::value || std::is_floating_point<To>::value, To, number<To> >::type                                                                                                                                                                            ;
   using integer_type = typename component_type<actual_from_type>::type                                                                                                                                                                                                                                 ;
   using dispatch_tag = std::integral_constant<bool, !std::numeric_limits<integer_type>::is_specialized || std::numeric_limits<integer_type>::is_bounded || !std::numeric_limits<actual_to_type>::is_specialized || !std::numeric_limits<actual_to_type>::is_bounded || (std::numeric_limits<actual_to_type>::radix != 2)>;

   integer_type n(numerator(static_cast<actual_from_type>(f))), d(denominator(static_cast<actual_from_type>(f)));
   generic_convert_rational_to_float_imp(result, n, d, dispatch_tag());
}

template <class To, class From>
inline void generic_interconvert(To& to, const From& from, const std::integral_constant<int, number_kind_floating_point>& /*to_type*/, const std::integral_constant<int, number_kind_rational>& /*from_type*/)
{
   generic_convert_rational_to_float(to, from);
}

template <class To, class From>
void generic_interconvert_float2rational(To& to, const From& from, const std::integral_constant<int, 2>& /*radix*/)
{
   using std::ldexp;
   using std::frexp;
   using ui_type = typename std::tuple_element<0, typename To::unsigned_types>::type;
   constexpr const int shift = std::numeric_limits<long long>::digits;
   typename From::exponent_type e;
   typename component_type<number<To>>::type num, denom;
   number<From> val(from);
   val = frexp(val, &e);
   while (val)
   {
      val = ldexp(val, shift);
      e -= shift;
      long long ll = boost::multiprecision::detail::lltrunc(val);
      val -= ll;
      num <<= shift;
      num += ll;
   }
   denom = ui_type(1u);
   if (e < 0)
      denom <<= -e;
   else if (e > 0)
      num <<= e;
   assign_components(to, num.backend(), denom.backend());
}

template <class To, class From, int Radix>
void generic_interconvert_float2rational(To& to, const From& from, const std::integral_constant<int, Radix>& /*radix*/)
{
   using std::ilogb;
   using std::scalbn;
   using std::pow;
   using std::abs;
   //
   // This is almost the same as the binary case above, but we have to use
   // scalbn and ilogb rather than ldexp and frexp, we also only extract
   // one Radix digit at a time which is terribly inefficient!
   //
   using ui_type = typename std::tuple_element<0, typename To::unsigned_types>::type;
   typename From::exponent_type e;
   typename component_type<number<To>>::type num, denom;
   number<From> val(from);

   if (!val)
   {
      to = ui_type(0u);
      return;
   }

   e   = ilogb(val);
   val = scalbn(val, -e);
   while (val)
   {
      long long ll = boost::multiprecision::detail::lltrunc(val);
      val -= ll;
      val = scalbn(val, 1);
      num *= Radix;
      num += ll;
      --e;
   }
   ++e;
   denom = ui_type(Radix);
   denom = pow(denom, abs(e));
   if (e > 0)
   {
      num *= denom;
      denom = 1;
   }
   assign_components(to, num.backend(), denom.backend());
}

template <class To, class From>
void generic_interconvert(To& to, const From& from, const std::integral_constant<int, number_kind_rational>& /*to_type*/, const std::integral_constant<int, number_kind_floating_point>& /*from_type*/)
{
   generic_interconvert_float2rational(to, from, std::integral_constant<int, std::numeric_limits<number<From> >::is_specialized ? std::numeric_limits<number<From> >::radix : 2>());
}

template <class To, class From>
void generic_interconvert(To& to, const From& from, const std::integral_constant<int, number_kind_integer>& /*to_type*/, const std::integral_constant<int, number_kind_rational>& /*from_type*/)
{
   number<From> t(from);
   number<To>   result(numerator(t) / denominator(t));
   to = result.backend();
}

template <class To, class From>
void generic_interconvert_float2int(To& to, const From& from, const std::integral_constant<int, 2>& /*radix*/)
{
   using std::frexp;
   using std::ldexp;
   
   using exponent_type = typename From::exponent_type;
   constexpr const exponent_type        shift = std::numeric_limits<long long>::digits;
   exponent_type                        e;
   number<To>                           num(0u);
   number<From>                         val(from);
   val      = frexp(val, &e);
   bool neg = false;
   if (val.sign() < 0)
   {
      val.backend().negate();
      neg = true;
   }
   while (e > 0)
   {
      exponent_type s = (std::min)(e, shift);
      val             = ldexp(val, s);
      e -= s;
      long long ll = boost::multiprecision::detail::lltrunc(val);
      val -= ll;
      num <<= s;
      num += ll;
   }
   to = num.backend();
   if (neg)
      to.negate();
}

template <class To, class From, int Radix>
void generic_interconvert_float2int(To& to, const From& from, const std::integral_constant<int, Radix>& /*radix*/)
{
   using std::ilogb;
   using std::scalbn;
   //
   // This is almost the same as the binary case above, but we have to use
   // scalbn and ilogb rather than ldexp and frexp, we also only extract
   // one Radix digit at a time which is terribly inefficient!
   //
   typename From::exponent_type e;
   number<To>                   num(0u);
   number<From>                 val(from);
   e   = ilogb(val);
   val = scalbn(val, -e);
   while (e >= 0)
   {
      long long ll = boost::multiprecision::detail::lltrunc(val);
      val -= ll;
      val = scalbn(val, 1);
      num *= Radix;
      num += ll;
      --e;
   }
   to = num.backend();
}

template <class To, class From>
void generic_interconvert(To& to, const From& from, const std::integral_constant<int, number_kind_integer>& /*to_type*/, const std::integral_constant<int, number_kind_floating_point>& /*from_type*/)
{
   generic_interconvert_float2int(to, from, std::integral_constant<int, (std::numeric_limits<number<From> >::is_specialized ? std::numeric_limits<number<From> >::radix : 2)>());
}

template <class To, class From, class tag>
void generic_interconvert_complex_to_scalar(To& to, const From& from, const std::integral_constant<bool, true>&, const tag&)
{
   // We just want the real part, and "to" is the correct type already:
   eval_real(to, from);

   To im;
   eval_imag(im, from);
   if (!eval_is_zero(im))
      BOOST_MP_THROW_EXCEPTION(std::runtime_error("Could not convert imaginary number to scalar."));
}
template <class To, class From>
void generic_interconvert_complex_to_scalar(To& to, const From& from, const std::integral_constant<bool, false>&, const std::integral_constant<bool, true>&)
{
   using component_number = typename component_type<number<From> >::type;
   using component_backend = typename component_number::backend_type     ;
   //
   // Get the real part and copy-construct the result from it:
   //
   scoped_precision_options<component_number> scope(from);
   component_backend r;
   generic_interconvert_complex_to_scalar(r, from, std::integral_constant<bool, true>(), std::integral_constant<bool, true>());
   to = r;
}
template <class To, class From>
void generic_interconvert_complex_to_scalar(To& to, const From& from, const std::integral_constant<bool, false>&, const std::integral_constant<bool, false>&)
{
   using component_number = typename component_type<number<From> >::type;
   using component_backend = typename component_number::backend_type;
   //
   // Get the real part and use a generic_interconvert to type To:
   //
   scoped_precision_options<component_number> scope(from);
   component_backend r;
   generic_interconvert_complex_to_scalar(r, from, std::integral_constant<bool, true>(), std::integral_constant<bool, true>());
   generic_interconvert(to, r, std::integral_constant<int, number_category<To>::value>(), std::integral_constant<int, number_category<component_backend>::value>());
}

template <class To, class From>
void generic_interconvert(To& to, const From& from, const std::integral_constant<int, number_kind_floating_point>& /*to_type*/, const std::integral_constant<int, number_kind_complex>& /*from_type*/)
{
   using component_number = typename component_type<number<From> >::type;
   using component_backend = typename component_number::backend_type     ;

   generic_interconvert_complex_to_scalar(to, from, std::integral_constant<bool, std::is_same<component_backend, To>::value>(), std::integral_constant<bool, std::is_constructible<To, const component_backend&>::value>());
}
template <class To, class From>
void generic_interconvert(To& to, const From& from, const std::integral_constant<int, number_kind_integer>& /*to_type*/, const std::integral_constant<int, number_kind_complex>& /*from_type*/)
{
   using component_number = typename component_type<number<From> >::type;
   using component_backend = typename component_number::backend_type     ;

   generic_interconvert_complex_to_scalar(to, from, std::integral_constant<bool, std::is_same<component_backend, To>::value>(), std::integral_constant<bool, std::is_constructible<To, const component_backend&>::value>());
}
template <class To, class From>
void generic_interconvert(To& to, const From& from, const std::integral_constant<int, number_kind_rational>& /*to_type*/, const std::integral_constant<int, number_kind_complex>& /*from_type*/)
{
   using component_number = typename component_type<number<From> >::type;
   using component_backend = typename component_number::backend_type     ;

   generic_interconvert_complex_to_scalar(to, from, std::integral_constant<bool, std::is_same<component_backend, To>::value>(), std::integral_constant<bool, std::is_constructible<To, const component_backend&>::value>());
}
template <class To, class From>
void generic_interconvert(To& to, const From& from, const std::integral_constant<int, number_kind_complex>& /*to_type*/, const std::integral_constant<int, number_kind_integer>& /*from_type*/)
{
   using component_number = typename component_type<number<To> >::type;

   scoped_source_precision<number<From> >     scope1;
   scoped_precision_options<component_number> scope2(number<To>::thread_default_precision(), number<To>::thread_default_variable_precision_options());
   (void)scope1;
   (void)scope2;

   number<From>     f(from);
   component_number scalar(f);
   number<To> result(scalar);
   to = result.backend();
}
template <class To, class From>
void generic_interconvert(To& to, const From& from, const std::integral_constant<int, number_kind_complex>& /*to_type*/, const std::integral_constant<int, number_kind_rational>& /*from_type*/)
{
   using component_number = typename component_type<number<To> >::type;

   scoped_source_precision<number<From> >     scope1;
   scoped_precision_options<component_number> scope2(number<To>::thread_default_precision(), number<To>::thread_default_variable_precision_options());
   (void)scope1;
   (void)scope2;

   number<From>     f(from);
   component_number scalar(f);
   number<To> result(scalar);
   to = result.backend();
}
template <class To, class From>
void generic_interconvert(To& to, const From& from, const std::integral_constant<int, number_kind_complex>& /*to_type*/, const std::integral_constant<int, number_kind_floating_point>& /*from_type*/)
{
   using component_number = typename component_type<number<To> >::type;

   scoped_source_precision<number<From> > scope1;
   scoped_precision_options<component_number> scope2(number<To>::thread_default_precision(), number<To>::thread_default_variable_precision_options());
   (void)scope1;
   (void)scope2;

   number<From> f(from);
   component_number scalar(f);
   number<To> result(scalar);
   to = result.backend();
}
template <class To, class From, int Tag1, int Tag2>
void generic_interconvert(To& /*to*/, const From& /*from*/, const std::integral_constant<int, Tag1>& /*to_type*/, const std::integral_constant<int, Tag2>& /*from_type*/)
{
   static_assert(sizeof(To) == 0, "Sorry, you asked for a conversion bewteen types that hasn't been implemented yet!!");
}

}
}
} // namespace boost::multiprecision::detail

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif // BOOST_MP_GENERIC_INTERCONVERT_HPP

/* generic_interconvert.hpp
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
*/