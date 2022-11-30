///////////////////////////////////////////////////////////////
//  Copyright 2013 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_MULTIPRECISION_CPP_BIN_FLOAT_TRANSCENDENTAL_HPP
#define BOOST_MULTIPRECISION_CPP_BIN_FLOAT_TRANSCENDENTAL_HPP

#include <boost/multiprecision/detail/assert.hpp>

namespace boost { namespace multiprecision { namespace backends {

template <unsigned Digits, digit_base_type DigitBase, class Allocator, class Exponent, Exponent MinE, Exponent MaxE>
void eval_exp_taylor(cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>& res, const cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>& arg)
{
   constexpr const std::ptrdiff_t bits = cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count;
   //
   // Taylor series for small argument, note returns exp(x) - 1:
   //
   res = limb_type(0);
   cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE> num(arg), denom, t;
   denom = limb_type(1);
   eval_add(res, num);

   for (std::size_t k = 2;; ++k)
   {
      eval_multiply(denom, k);
      eval_multiply(num, arg);
      eval_divide(t, num, denom);
      eval_add(res, t);
      if (eval_is_zero(t) || (res.exponent() - bits > t.exponent()))
         break;
   }
}

template <unsigned Digits, digit_base_type DigitBase, class Allocator, class Exponent, Exponent MinE, Exponent MaxE>
void eval_exp(cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>& res, const cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>& arg)
{
   //
   // This is based on MPFR's method, let:
   //
   // n = floor(x / ln(2))
   //
   // Then:
   //
   // r = x - n ln(2) : 0 <= r < ln(2)
   //
   // We can reduce r further by dividing by 2^k, with k ~ sqrt(n),
   // so if:
   //
   // e0 = exp(r / 2^k) - 1
   //
   // With e0 evaluated by taylor series for small arguments, then:
   //
   // exp(x) = 2^n (1 + e0)^2^k
   //
   // Note that to preserve precision we actually square (1 + e0) k times, calculating
   // the result less one each time, i.e.
   //
   // (1 + e0)^2 - 1 = e0^2 + 2e0
   //
   // Then add the final 1 at the end, given that e0 is small, this effectively wipes
   // out the error in the last step.
   //
   using default_ops::eval_add;
   using default_ops::eval_convert_to;
   using default_ops::eval_increment;
   using default_ops::eval_multiply;
   using default_ops::eval_subtract;

   int  type  = eval_fpclassify(arg);
   bool isneg = eval_get_sign(arg) < 0;
   if (type == static_cast<int>(FP_NAN))
   {
      res   = arg;
      errno = EDOM;
      return;
   }
   else if (type == static_cast<int>(FP_INFINITE))
   {
      res = arg;
      if (isneg)
         res = limb_type(0u);
      else
         res = arg;
      return;
   }
   else if (type == static_cast<int>(FP_ZERO))
   {
      res = limb_type(1);
      return;
   }
   cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE> t, n;
   if (isneg)
   {
      t = arg;
      t.negate();
      eval_exp(res, t);
      t.swap(res);
      res = limb_type(1);
      eval_divide(res, t);
      return;
   }

   eval_divide(n, arg, default_ops::get_constant_ln2<cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE> >());
   eval_floor(n, n);
   eval_multiply(t, n, default_ops::get_constant_ln2<cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE> >());
   eval_subtract(t, arg);
   t.negate();
   if (t.compare(default_ops::get_constant_ln2<cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE> >()) > 0)
   {
      // There are some rare cases where the multiply rounds down leaving a remainder > ln2
      // See https://github.com/boostorg/multiprecision/issues/120
      eval_increment(n);
      t = limb_type(0);
   }
   if (eval_get_sign(t) < 0)
   {
      // There are some very rare cases where arg/ln2 is an integer, and the subsequent multiply
      // rounds up, in that situation t ends up negative at this point which breaks our invariants below:
      t = limb_type(0);
   }

   Exponent k, nn;
   eval_convert_to(&nn, n);

   if (nn == (std::numeric_limits<Exponent>::max)())
   {
      // The result will necessarily oveflow:
      res = std::numeric_limits<number<cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE> > >::infinity().backend();
      return;
   }

   BOOST_MP_ASSERT(t.compare(default_ops::get_constant_ln2<cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE> >()) < 0);

   k = nn ? Exponent(1) << (msb(nn) / 2) : 0;
   k = (std::min)(k, (Exponent)(cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count / 4));
   eval_ldexp(t, t, -k);

   eval_exp_taylor(res, t);
   //
   // Square 1 + res k times:
   //
   for (Exponent s = 0; s < k; ++s)
   {
      t.swap(res);
      eval_multiply(res, t, t);
      eval_ldexp(t, t, 1);
      eval_add(res, t);
   }
   eval_add(res, limb_type(1));
   eval_ldexp(res, res, nn);
}

}}} // namespace boost::multiprecision::backends

#endif

/* transcendental.hpp
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
*/