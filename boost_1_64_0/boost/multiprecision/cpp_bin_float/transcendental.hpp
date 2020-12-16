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
UGYRAyB+rnMwWQyb8IOlbl8Mau8gzdOY1TNKXtrOYixovYwTlc/jTHhfQw1h+WjAiL3jaSPkjhmmYRX6wo5e1kCTe0iXOxUkUeHHWcnWevPrFvYwweaOEzmJF7K1+Z6NnSLYtPDyIOE524LlGLEPbf2UYdFA7LEy9tw6Ssd634hd8ljSzw7zEsAFsVv3M6Dn+vMrgxVlm425xA2+KKyyijthzQeDBTY6sNgY9E2+RcLnMT8PvAJ6Uudb3zzd21qndtrnP2DY7/Moc3gg2OqJpWIbKDvti5SnrIIgdbOGR3RwF88lnUek+w6LJOS54oFkbj1pEC7uwJ+8bzuP6DR6JJwXPvGQWtfv5TNzKuuByNDlLa0tL+B7B76JfFrhZ2rnI4FVrwO1zC/oMheW18UVNWgONb3FDErXhD4U8F/pwKNYDffNITh86pBn4I8Arkll0tT5u511FpVQdf7hf+wHLKKW+dNumYBSMm/+536Q8Ab/6/9QB+wO2R+/75CPTdPk/uE/1EMX/AAtx9jzR5qzCi5li4q+NSro9ViCQYVJU/Cs8GdKFzVC2qUxShtsrKDc145bNOEtjvQ7dhA6nqPRBvVOhK7O0pL+lglCFy80yHtwJ9LUTNfOPzcoXRw8kPfwbqTpByC8u/l7Ougi8wf8m37GevKdBa6OBDc3OL15Rt+/DrzfOMNGaRyVt52mWW5f9Ay1NeRsIcKazR1R2FeO/gfsUZWba2UMseTMSyUr/OK2/4gH6Zpd+XaBB8csMPhYlUm8es9V9PP/4uxKg/RqpvDMZJIMgiD22GMplVIjZkgspe/Sfbfue69kbEXJN5l5I8NkZsw7w3wEQRAEQeyxxx77rpSiCuUHhSpV/KCKKj+oovih7Kqcvrfv6T5935eET94v3z3P6fX0dvr0OSPozx4492Aj6CvD5jYc01jd08esOnL22xH0s0Mbo+9pe/v0IZh7LDkxuX4/FqPPAbbfv/FZt98FC/Vr9bhWrILOhoPEE+d1S8HVefzIJ85DMzaejDO4iYDQk3xzZemJ809fZ1rGzJ7pV7/bMzFpdOtbzSF1iHn9luQlWSa1EU580/t0eFfSnE9vafSf8LU9MJxcBz6zibP+4eHPrbr/TY+bamFbHp0EepPGqdWVtUZAoNGeT+64ZqZ6mBUDsXc4iIF6I87Sn7nL0NtSnobJYXjGGZvfJ3Q6d8xNE5rWd8L+wPb1hT2EbjyD4vxl779mRuIGax7uB7eluG2ozhImZ3GH943CYXLY7xe9fo8DGWRpccM+Nky/E53TCyfa/lSJeKR7HoOMgDZ6LqkCXrtzwy/+B9YcgGzcy2nE07kEOWzaG7tHYv3UsY8fNgP4/ryDMnitR+/PK/e4DcH05o2LPXp/3jh4W4qh84Z9h5t+lvhUqBPJ4yBgZeNIGaptNpYoAwueDITa8Xeibvq8dy8z9g/i2Ie723bUYzv8GP68SLe9ptGxhv4UkI5jzfgPQBqmu77sxuabIvSxY+07BDd+rF3YRXBjx1o8TXBjx9oBr52lKotUlje9kLs6vnO9MQLHPjem6qSPQa+P5Iz8q8/QstU8j0NR3rT+w50HXqzzbbpJ35lb2uwkoeldqPVlT2kwYc+eXNzYaFTJE65d3FQPZzwd2Lpf6mFg7cMp2nk7scvHoVwiZqeHaQPlkrcDfYyWXxuHY7pHx70m2nH2MFhgxKS7exgtw1oyEfOtMZjBmsUc3dPDgOw2ySDm+mgMJGPrff+9PYzeI2MaV3p03CejTMzMEAwYfji2lpQ2HCcTh2/j4x7Zk4nv9zCjZeJpt/VxfZn4VQ/Tl4kzt6MYXyb+1KP3ZWJnn4/py8TE7X1MXyYu9zA=
*/