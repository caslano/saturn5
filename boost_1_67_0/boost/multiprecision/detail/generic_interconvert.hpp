///////////////////////////////////////////////////////////////////////////////
//  Copyright 2011 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MP_GENERIC_INTERCONVERT_HPP
#define BOOST_MP_GENERIC_INTERCONVERT_HPP

#include <boost/multiprecision/detail/default_ops.hpp>

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
void generic_interconvert(To& to, const From& from, const mpl::int_<number_kind_floating_point>& /*to_type*/, const mpl::int_<number_kind_integer>& /*from_type*/)
{
   using default_ops::eval_add;
   using default_ops::eval_bitwise_and;
   using default_ops::eval_convert_to;
   using default_ops::eval_get_sign;
   using default_ops::eval_is_zero;
   using default_ops::eval_ldexp;
   using default_ops::eval_right_shift;
   // smallest unsigned type handled natively by "From" is likely to be it's limb_type:
   typedef typename canonical<unsigned char, From>::type l_limb_type;
   // get the corresponding type that we can assign to "To":
   typedef typename canonical<l_limb_type, To>::type to_type;
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
void generic_interconvert(To& to, const From& from, const mpl::int_<number_kind_integer>& /*to_type*/, const mpl::int_<number_kind_integer>& /*from_type*/)
{
   using default_ops::eval_bitwise_and;
   using default_ops::eval_bitwise_or;
   using default_ops::eval_convert_to;
   using default_ops::eval_get_sign;
   using default_ops::eval_is_zero;
   using default_ops::eval_left_shift;
   using default_ops::eval_right_shift;
   // smallest unsigned type handled natively by "From" is likely to be it's limb_type:
   typedef typename canonical<unsigned char, From>::type limb_type;
   // get the corresponding type that we can assign to "To":
   typedef typename canonical<limb_type, To>::type to_type;
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
void generic_interconvert(To& to, const From& from, const mpl::int_<number_kind_floating_point>& /*to_type*/, const mpl::int_<number_kind_floating_point>& /*from_type*/)
{
#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable : 4127)
#endif
   //
   // The code here only works when the radix of "From" is 2, we could try shifting by other
   // radixes but it would complicate things.... use a string conversion when the radix is other
   // than 2:
   //
   if (std::numeric_limits<number<From> >::radix != 2)
   {
      to = from.str(0, std::ios_base::fmtflags()).c_str();
      return;
   }

   typedef typename canonical<unsigned char, To>::type ui_type;

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

   if (c == (int)FP_ZERO)
   {
      to = ui_type(0);
      return;
   }
   else if (c == (int)FP_NAN)
   {
      to = static_cast<const char*>("nan");
      return;
   }
   else if (c == (int)FP_INFINITE)
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

   static const int shift = std::numeric_limits<boost::intmax_t>::digits - 1;

   while (!eval_is_zero(f))
   {
      // extract int sized bits from f:
      eval_ldexp(f, f, shift);
      eval_floor(term, f);
      e -= shift;
      eval_ldexp(to, to, shift);
      typename boost::multiprecision::detail::canonical<boost::intmax_t, To>::type ll;
      eval_convert_to(&ll, term);
      eval_add(to, ll);
      eval_subtract(f, term);
   }
   typedef typename To::exponent_type to_exponent;
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
#ifdef BOOST_MSVC
#pragma warning(pop)
#endif
}

template <class To, class From>
void generic_interconvert(To& to, const From& from, const mpl::int_<number_kind_rational>& /*to_type*/, const mpl::int_<number_kind_rational>& /*from_type*/)
{
   typedef typename component_type<number<To> >::type to_component_type;

   number<From>      t(from);
   to_component_type n(numerator(t)), d(denominator(t));
   using default_ops::assign_components;
   assign_components(to, n.backend(), d.backend());
}

template <class To, class From>
void generic_interconvert(To& to, const From& from, const mpl::int_<number_kind_rational>& /*to_type*/, const mpl::int_<number_kind_integer>& /*from_type*/)
{
   typedef typename component_type<number<To> >::type to_component_type;

   number<From>      t(from);
   to_component_type n(t), d(1);
   using default_ops::assign_components;
   assign_components(to, n.backend(), d.backend());
}

template <class R, class LargeInteger>
R safe_convert_to_float(const LargeInteger& i)
{
   using std::ldexp;
   if (!i)
      return R(0);
   if (std::numeric_limits<R>::is_specialized && std::numeric_limits<R>::max_exponent)
   {
      LargeInteger val(i);
      if (val.sign() < 0)
         val = -val;
      unsigned mb = msb(val);
      if (mb >= std::numeric_limits<R>::max_exponent)
      {
         int scale_factor = (int)mb + 1 - std::numeric_limits<R>::max_exponent;
         BOOST_ASSERT(scale_factor >= 1);
         val >>= scale_factor;
         R result = val.template convert_to<R>();
         if (std::numeric_limits<R>::digits == 0 || std::numeric_limits<R>::digits >= std::numeric_limits<R>::max_exponent)
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
inline typename disable_if_c<is_number<To>::value || is_floating_point<To>::value>::type
generic_convert_rational_to_float_imp(To& result, const Integer& n, const Integer& d, const mpl::true_&)
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
inline typename enable_if_c<is_number<To>::value || is_floating_point<To>::value>::type
generic_convert_rational_to_float_imp(To& result, const Integer& n, const Integer& d, const mpl::true_&)
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
typename enable_if_c<is_number<To>::value || is_floating_point<To>::value>::type
generic_convert_rational_to_float_imp(To& result, Integer& num, Integer& denom, const mpl::false_&)
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
   int denom_bits = msb(denom);
   int shift      = std::numeric_limits<To>::digits + denom_bits - msb(num);
   if (shift > 0)
      num <<= shift;
   else if (shift < 0)
      denom <<= boost::multiprecision::detail::unsigned_abs(shift);
   Integer q, r;
   divide_qr(num, denom, q, r);
   int q_bits = msb(q);
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
      BOOST_ASSERT(q_bits == std::numeric_limits<To>::digits);
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
   result = ldexp(result, -shift);
   if (s)
      result = -result;
}
template <class To, class Integer>
inline typename disable_if_c<is_number<To>::value || is_floating_point<To>::value>::type
generic_convert_rational_to_float_imp(To& result, Integer& num, Integer& denom, const mpl::false_& tag)
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
   typedef typename mpl::if_c<is_number<From>::value, From, number<From> >::type                                                                                                                                                                                                            actual_from_type;
   typedef typename mpl::if_c<is_number<To>::value || is_floating_point<To>::value, To, number<To> >::type                                                                                                                                                                                  actual_to_type;
   typedef typename component_type<actual_from_type>::type                                                                                                                                                                                                                                  integer_type;
   typedef mpl::bool_<!std::numeric_limits<integer_type>::is_specialized || std::numeric_limits<integer_type>::is_bounded || !std::numeric_limits<actual_to_type>::is_specialized || !std::numeric_limits<actual_to_type>::is_bounded || (std::numeric_limits<actual_to_type>::radix != 2)> dispatch_tag;

   integer_type n(numerator(static_cast<actual_from_type>(f))), d(denominator(static_cast<actual_from_type>(f)));
   generic_convert_rational_to_float_imp(result, n, d, dispatch_tag());
}

template <class To, class From>
inline void generic_interconvert(To& to, const From& from, const mpl::int_<number_kind_floating_point>& /*to_type*/, const mpl::int_<number_kind_rational>& /*from_type*/)
{
   generic_convert_rational_to_float(to, from);
}

template <class To, class From>
void generic_interconvert_float2rational(To& to, const From& from, const mpl::int_<2>& /*radix*/)
{
   typedef typename mpl::front<typename To::unsigned_types>::type ui_type;
   static const int                                               shift = std::numeric_limits<boost::long_long_type>::digits;
   typename From::exponent_type                                   e;
   typename component_type<number<To> >::type                     num, denom;
   number<From>                                                   val(from);
   val = frexp(val, &e);
   while (val)
   {
      val = ldexp(val, shift);
      e -= shift;
      boost::long_long_type ll = boost::math::lltrunc(val);
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
void generic_interconvert_float2rational(To& to, const From& from, const mpl::int_<Radix>& /*radix*/)
{
   //
   // This is almost the same as the binary case above, but we have to use
   // scalbn and ilogb rather than ldexp and frexp, we also only extract
   // one Radix digit at a time which is terribly inefficient!
   //
   typedef typename mpl::front<typename To::unsigned_types>::type ui_type;
   typename From::exponent_type                                   e;
   typename component_type<number<To> >::type                     num, denom;
   number<From>                                                   val(from);

   if (!val)
   {
      to = ui_type(0u);
      return;
   }

   e   = ilogb(val);
   val = scalbn(val, -e);
   while (val)
   {
      boost::long_long_type ll = boost::math::lltrunc(val);
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
void generic_interconvert(To& to, const From& from, const mpl::int_<number_kind_rational>& /*to_type*/, const mpl::int_<number_kind_floating_point>& /*from_type*/)
{
   generic_interconvert_float2rational(to, from, mpl::int_<std::numeric_limits<number<From> >::radix>());
}

template <class To, class From>
void generic_interconvert(To& to, const From& from, const mpl::int_<number_kind_integer>& /*to_type*/, const mpl::int_<number_kind_rational>& /*from_type*/)
{
   number<From> t(from);
   number<To>   result(numerator(t) / denominator(t));
   to = result.backend();
}

template <class To, class From>
void generic_interconvert_float2int(To& to, const From& from, const mpl::int_<2>& /*radix*/)
{
   typedef typename From::exponent_type exponent_type;
   static const exponent_type           shift = std::numeric_limits<boost::long_long_type>::digits;
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
      boost::long_long_type ll = boost::math::lltrunc(val);
      val -= ll;
      num <<= s;
      num += ll;
   }
   to = num.backend();
   if (neg)
      to.negate();
}

template <class To, class From, int Radix>
void generic_interconvert_float2int(To& to, const From& from, const mpl::int_<Radix>& /*radix*/)
{
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
      boost::long_long_type ll = boost::math::lltrunc(val);
      val -= ll;
      val = scalbn(val, 1);
      num *= Radix;
      num += ll;
      --e;
   }
   to = num.backend();
}

template <class To, class From>
void generic_interconvert(To& to, const From& from, const mpl::int_<number_kind_integer>& /*to_type*/, const mpl::int_<number_kind_floating_point>& /*from_type*/)
{
   generic_interconvert_float2int(to, from, mpl::int_<std::numeric_limits<number<From> >::radix>());
}

template <class To, class From, class tag>
void generic_interconvert_complex_to_scalar(To& to, const From& from, const mpl::true_&, const tag&)
{
   // We just want the real part, and "to" is the correct type already:
   eval_real(to, from);

   To im;
   eval_imag(im, from);
   if (!eval_is_zero(im))
      BOOST_THROW_EXCEPTION(std::runtime_error("Could not convert imaginary number to scalar."));
}
template <class To, class From>
void generic_interconvert_complex_to_scalar(To& to, const From& from, const mpl::false_&, const mpl::true_&)
{
   typedef typename component_type<number<From> >::type component_number;
   typedef typename component_number::backend_type      component_backend;
   //
   // Get the real part and copy-construct the result from it:
   //
   component_backend r;
   generic_interconvert_complex_to_scalar(r, from, mpl::true_(), mpl::true_());
   to = r;
}
template <class To, class From>
void generic_interconvert_complex_to_scalar(To& to, const From& from, const mpl::false_&, const mpl::false_&)
{
   typedef typename component_type<number<From> >::type component_number;
   typedef typename component_number::backend_type      component_backend;
   //
   // Get the real part and use a generic_interconvert to type To:
   //
   component_backend r;
   generic_interconvert_complex_to_scalar(r, from, mpl::true_(), mpl::true_());
   generic_interconvert(to, r, mpl::int_<number_category<To>::value>(), mpl::int_<number_category<To>::value>());
}

template <class To, class From>
void generic_interconvert(To& to, const From& from, const mpl::int_<number_kind_floating_point>& /*to_type*/, const mpl::int_<number_kind_complex>& /*from_type*/)
{
   typedef typename component_type<number<From> >::type component_number;
   typedef typename component_number::backend_type      component_backend;

   generic_interconvert_complex_to_scalar(to, from, mpl::bool_<boost::is_same<component_backend, To>::value>(), mpl::bool_<boost::is_constructible<To, const component_backend&>::value>());
}
template <class To, class From>
void generic_interconvert(To& to, const From& from, const mpl::int_<number_kind_integer>& /*to_type*/, const mpl::int_<number_kind_complex>& /*from_type*/)
{
   typedef typename component_type<number<From> >::type component_number;
   typedef typename component_number::backend_type      component_backend;

   generic_interconvert_complex_to_scalar(to, from, mpl::bool_<boost::is_same<component_backend, To>::value>(), mpl::bool_<boost::is_constructible<To, const component_backend&>::value>());
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