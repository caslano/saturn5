///////////////////////////////////////////////////////////////
//  Copyright 2013 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_MULTIPRECISION_CPP_BIN_FLOAT_TRANSCENDENTAL_HPP
#define BOOST_MULTIPRECISION_CPP_BIN_FLOAT_TRANSCENDENTAL_HPP

namespace boost { namespace multiprecision { namespace backends {

template <unsigned Digits, digit_base_type DigitBase, class Allocator, class Exponent, Exponent MinE, Exponent MaxE>
void eval_exp_taylor(cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>& res, const cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>& arg)
{
   static const int bits = cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count;
   //
   // Taylor series for small argument, note returns exp(x) - 1:
   //
   res = limb_type(0);
   cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE> num(arg), denom, t;
   denom = limb_type(1);
   eval_add(res, num);

   for (unsigned k = 2;; ++k)
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
   if (type == (int)FP_NAN)
   {
      res   = arg;
      errno = EDOM;
      return;
   }
   else if (type == (int)FP_INFINITE)
   {
      res = arg;
      if (isneg)
         res = limb_type(0u);
      else
         res = arg;
      return;
   }
   else if (type == (int)FP_ZERO)
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

   BOOST_ASSERT(t.compare(default_ops::get_constant_ln2<cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE> >()) < 0);

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