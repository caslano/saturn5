///////////////////////////////////////////////////////////////
//  Copyright 2012 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt
//
// Comparison operators for cpp_int_backend:
//
#ifndef BOOST_MP_CPP_INT_DIV_HPP
#define BOOST_MP_CPP_INT_DIV_HPP

namespace boost { namespace multiprecision { namespace backends {

template <class CppInt1, class CppInt2, class CppInt3>
BOOST_MP_CXX14_CONSTEXPR void divide_unsigned_helper(
    CppInt1*       result,
    const CppInt2& x,
    const CppInt3& y,
    CppInt1&       r)
{
   if (((void*)result == (void*)&x) || ((void*)&r == (void*)&x))
   {
      CppInt2 t(x);
      divide_unsigned_helper(result, t, y, r);
      return;
   }
   if (((void*)result == (void*)&y) || ((void*)&r == (void*)&y))
   {
      CppInt3 t(y);
      divide_unsigned_helper(result, x, t, r);
      return;
   }

   /*
    Very simple, fairly braindead long division.
    Start by setting the remainder equal to x, and the
    result equal to 0.  Then in each loop we calculate our
    "best guess" for how many times y divides into r,
    add our guess to the result, and subtract guess*y
    from the remainder r.  One wrinkle is that the remainder
    may go negative, in which case we subtract the current guess
    from the result rather than adding.  The value of the guess
    is determined by dividing the most-significant-limb of the
    current remainder by the most-significant-limb of y.

    Note that there are more efficient algorithms than this
    available, in particular see Knuth Vol 2.  However for small
    numbers of limbs this generally outperforms the alternatives
    and avoids the normalisation step which would require extra storage.
    */

   using default_ops::eval_subtract;

   if (result == &r)
   {
      CppInt1 rem;
      divide_unsigned_helper(result, x, y, rem);
      r = rem;
      return;
   }

   //
   // Find the most significant words of numerator and denominator.
   //
   limb_type y_order = y.size() - 1;

   if (y_order == 0)
   {
      //
      // Only a single non-zero limb in the denominator, in this case
      // we can use a specialized divide-by-single-limb routine which is
      // much faster.  This also handles division by zero:
      //
      divide_unsigned_helper(result, x, y.limbs()[y_order], r);
      return;
   }

   typename CppInt2::const_limb_pointer px = x.limbs();
   typename CppInt3::const_limb_pointer py = y.limbs();

   limb_type r_order = x.size() - 1;
   if ((r_order == 0) && (*px == 0))
   {
      // x is zero, so is the result:
      r = x;
      if (result)
         *result = x;
      return;
   }

   r = x;
   r.sign(false);
   if (result)
      *result = static_cast<limb_type>(0u);
   //
   // Check if the remainder is already less than the divisor, if so
   // we already have the result.  Note we try and avoid a full compare
   // if we can:
   //
   if (r_order <= y_order)
   {
      if ((r_order < y_order) || (r.compare_unsigned(y) < 0))
      {
         return;
      }
   }

   CppInt1 t;
   bool    r_neg = false;

   //
   // See if we can short-circuit long division, and use basic arithmetic instead:
   //
   if (r_order == 0)
   {
      if (result)
      {
         *result = px[0] / py[0];
      }
      r = px[0] % py[0];
      return;
   }
   else if (r_order == 1)
   {
      double_limb_type a = (static_cast<double_limb_type>(px[1]) << CppInt1::limb_bits) | px[0];
      double_limb_type b = y_order ? (static_cast<double_limb_type>(py[1]) << CppInt1::limb_bits) | py[0]
                  : py[0];
      if (result)
      {
         *result = a / b;
      }
      r = a % b;
      return;
   }
   //
   // prepare result:
   //
   if (result)
      result->resize(1 + r_order - y_order, 1 + r_order - y_order);
   typename CppInt1::const_limb_pointer prem = r.limbs();
   // This is initialised just to keep the compiler from emitting useless warnings later on:
   typename CppInt1::limb_pointer pr = typename CppInt1::limb_pointer();
   if (result)
   {
      pr = result->limbs();
      for (unsigned i = 1; i < 1 + r_order - y_order; ++i)
         pr[i] = 0;
   }
   bool first_pass = true;

   do
   {
      //
      // Calculate our best guess for how many times y divides into r:
      //
      limb_type guess = 1;
      if ((prem[r_order] <= py[y_order]) && (r_order > 0))
      {
         double_limb_type a = (static_cast<double_limb_type>(prem[r_order]) << CppInt1::limb_bits) | prem[r_order - 1];
         double_limb_type b = py[y_order];
         double_limb_type v = a / b;
         if (v <= CppInt1::max_limb_value)
         {
            guess = static_cast<limb_type>(v);
            --r_order;
         }
      }
      else if (r_order == 0)
      {
         guess = prem[0] / py[y_order];
      }
      else
      {
         double_limb_type a = (static_cast<double_limb_type>(prem[r_order]) << CppInt1::limb_bits) | prem[r_order - 1];
         double_limb_type b = (y_order > 0) ? (static_cast<double_limb_type>(py[y_order]) << CppInt1::limb_bits) | py[y_order - 1] : (static_cast<double_limb_type>(py[y_order]) << CppInt1::limb_bits);
         double_limb_type v = a / b;
         guess = static_cast<limb_type>(v);
      }
      BOOST_ASSERT(guess); // If the guess ever gets to zero we go on forever....
      //
      // Update result:
      //
      limb_type shift = r_order - y_order;
      if (result)
      {
         if (r_neg)
         {
            if (pr[shift] > guess)
               pr[shift] -= guess;
            else
            {
               t.resize(shift + 1, shift + 1);
               t.limbs()[shift] = guess;
               for (unsigned i = 0; i < shift; ++i)
                  t.limbs()[i] = 0;
               eval_subtract(*result, t);
            }
         }
         else if (CppInt1::max_limb_value - pr[shift] > guess)
            pr[shift] += guess;
         else
         {
            t.resize(shift + 1, shift + 1);
            t.limbs()[shift] = guess;
            for (unsigned i = 0; i < shift; ++i)
               t.limbs()[i] = 0;
            eval_add(*result, t);
         }
      }
      //
      // Calculate guess * y, we use a fused mutiply-shift O(N) for this
      // rather than a full O(N^2) multiply:
      //
      double_limb_type carry = 0;
      t.resize(y.size() + shift + 1, y.size() + shift);
      bool                           truncated_t = (t.size() != y.size() + shift + 1);
      typename CppInt1::limb_pointer pt          = t.limbs();
      for (unsigned i = 0; i < shift; ++i)
         pt[i] = 0;
      for (unsigned i = 0; i < y.size(); ++i)
      {
         carry += static_cast<double_limb_type>(py[i]) * static_cast<double_limb_type>(guess);
#ifdef __MSVC_RUNTIME_CHECKS
         pt[i + shift] = static_cast<limb_type>(carry & ~static_cast<limb_type>(0));
#else
         pt[i + shift]    = static_cast<limb_type>(carry);
#endif
         carry >>= CppInt1::limb_bits;
      }
      if (carry && !truncated_t)
      {
#ifdef __MSVC_RUNTIME_CHECKS
         pt[t.size() - 1] = static_cast<limb_type>(carry & ~static_cast<limb_type>(0));
#else
         pt[t.size() - 1] = static_cast<limb_type>(carry);
#endif
      }
      else if (!truncated_t)
      {
         t.resize(t.size() - 1, t.size() - 1);
      }
      //
      // Update r in a way that won't actually produce a negative result
      // in case the argument types are unsigned:
      //
      if (truncated_t && carry)
      {
         // We need to calculate 2^n + t - r
         // where n is the number of bits in this type.
         // Simplest way is to get 2^n - r by complementing
         // r, then add t to it.  Note that we can't call eval_complement
         // in case this is a signed checked type:
         for (unsigned i = 0; i <= r_order; ++i)
            r.limbs()[i] = ~prem[i];
         r.normalize();
         eval_increment(r);
         eval_add(r, t);
         r_neg = !r_neg;
      }
      else if (r.compare(t) > 0)
      {
         eval_subtract(r, t);
      }
      else
      {
         r.swap(t);
         eval_subtract(r, t);
         prem  = r.limbs();
         r_neg = !r_neg;
      }
      //
      // First time through we need to strip any leading zero, otherwise
      // the termination condition goes belly-up:
      //
      if (result && first_pass)
      {
         first_pass = false;
         while (pr[result->size() - 1] == 0)
            result->resize(result->size() - 1, result->size() - 1);
      }
      //
      // Update r_order:
      //
      r_order = r.size() - 1;
      if (r_order < y_order)
         break;
   }
   // Termination condition is really just a check that r > y, but with a common
   // short-circuit case handled first:
   while ((r_order > y_order) || (r.compare_unsigned(y) >= 0));

   //
   // We now just have to normalise the result:
   //
   if (r_neg && eval_get_sign(r))
   {
      // We have one too many in the result:
      if (result)
         eval_decrement(*result);
      if (y.sign())
      {
         r.negate();
         eval_subtract(r, y);
      }
      else
         eval_subtract(r, y, r);
   }

   BOOST_ASSERT(r.compare_unsigned(y) < 0); // remainder must be less than the divisor or our code has failed
}

template <class CppInt1, class CppInt2>
BOOST_MP_CXX14_CONSTEXPR void divide_unsigned_helper(
    CppInt1*       result,
    const CppInt2& x,
    limb_type      y,
    CppInt1&       r)
{
   if (((void*)result == (void*)&x) || ((void*)&r == (void*)&x))
   {
      CppInt2 t(x);
      divide_unsigned_helper(result, t, y, r);
      return;
   }

   if (result == &r)
   {
      CppInt1 rem;
      divide_unsigned_helper(result, x, y, rem);
      r = rem;
      return;
   }

   // As above, but simplified for integer divisor:

   using default_ops::eval_subtract;

   if (y == 0)
   {
      BOOST_THROW_EXCEPTION(std::overflow_error("Integer Division by zero."));
   }
   //
   // Find the most significant word of numerator.
   //
   limb_type r_order = x.size() - 1;

   //
   // Set remainder and result to their initial values:
   //
   r = x;
   r.sign(false);
   typename CppInt1::limb_pointer pr = r.limbs();

   //
   // check for x < y, try to do this without actually having to
   // do a full comparison:
   //
   if ((r_order == 0) && (*pr < y))
   {
      if (result)
         *result = static_cast<limb_type>(0u);
      return;
   }

   //
   // See if we can short-circuit long division, and use basic arithmetic instead:
   //
   if (r_order == 0)
   {
      if (result)
      {
         *result = *pr / y;
         result->sign(x.sign());
      }
      *pr %= y;
      r.sign(x.sign());
      return;
   }
   else if (r_order == 1)
   {
      double_limb_type a = (static_cast<double_limb_type>(pr[r_order]) << CppInt1::limb_bits) | pr[0];
      if (result)
      {
         *result = a / y;
         result->sign(x.sign());
      }
      r = a % y;
      r.sign(x.sign());
      return;
   }

   // This is initialised just to keep the compiler from emitting useless warnings later on:
   typename CppInt1::limb_pointer pres = typename CppInt1::limb_pointer();
   if (result)
   {
      result->resize(r_order + 1, r_order + 1);
      pres = result->limbs();
      if (result->size() > r_order)
         pres[r_order] = 0; // just in case we don't set the most significant limb below.
   }

   do
   {
      //
      // Calculate our best guess for how many times y divides into r:
      //
      if ((pr[r_order] < y) && r_order)
      {
         double_limb_type a = (static_cast<double_limb_type>(pr[r_order]) << CppInt1::limb_bits) | pr[r_order - 1];
         double_limb_type b = a % y;
         r.resize(r.size() - 1, r.size() - 1);
         --r_order;
         pr[r_order] = static_cast<limb_type>(b);
         if (result)
            pres[r_order] = static_cast<limb_type>(a / y);
         if (r_order && pr[r_order] == 0)
         {
            --r_order; // No remainder, division was exact.
            r.resize(r.size() - 1, r.size() - 1);
            if (result)
               pres[r_order] = static_cast<limb_type>(0u);
         }
      }
      else
      {
         if (result)
            pres[r_order] = pr[r_order] / y;
         pr[r_order] %= y;
         if (r_order && pr[r_order] == 0)
         {
            --r_order; // No remainder, division was exact.
            r.resize(r.size() - 1, r.size() - 1);
            if (result)
               pres[r_order] = static_cast<limb_type>(0u);
         }
      }
   }
   // Termination condition is really just a check that r >= y, but with two common
   // short-circuit cases handled first:
   while (r_order || (pr[r_order] >= y));

   if (result)
   {
      result->normalize();
      result->sign(x.sign());
   }
   r.normalize();
   r.sign(x.sign());

   BOOST_ASSERT(r.compare(y) < 0); // remainder must be less than the divisor or our code has failed
}

template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, unsigned MinBits2, unsigned MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2, unsigned MinBits3, unsigned MaxBits3, cpp_integer_type SignType3, cpp_int_check_type Checked3, class Allocator3>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && !is_trivial_cpp_int<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value && !is_trivial_cpp_int<cpp_int_backend<MinBits3, MaxBits3, SignType3, Checked3, Allocator3> >::value>::type
eval_divide(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>& a,
    const cpp_int_backend<MinBits3, MaxBits3, SignType3, Checked3, Allocator3>& b)
{
   cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> r;
   bool                                                                 s = a.sign() != b.sign();
   divide_unsigned_helper(&result, a, b, r);
   result.sign(s);
}

template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, unsigned MinBits2, unsigned MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && !is_trivial_cpp_int<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value>::type
eval_divide(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>& a,
    limb_type&                                                                  b)
{
   cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> r;
   bool                                                                 s = a.sign();
   divide_unsigned_helper(&result, a, b, r);
   result.sign(s);
}

template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, unsigned MinBits2, unsigned MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && !is_trivial_cpp_int<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value>::type
eval_divide(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>& a,
    signed_limb_type&                                                           b)
{
   cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> r;
   bool                                                                 s = a.sign() != (b < 0);
   divide_unsigned_helper(&result, a, static_cast<limb_type>(boost::multiprecision::detail::unsigned_abs(b)), r);
   result.sign(s);
}

template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, unsigned MinBits2, unsigned MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && !is_trivial_cpp_int<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value>::type
eval_divide(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>& b)
{
   // There is no in place divide:
   cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> a(result);
   eval_divide(result, a, b);
}

template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value>::type
eval_divide(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& result,
    limb_type                                                             b)
{
   // There is no in place divide:
   cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> a(result);
   eval_divide(result, a, b);
}

template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value>::type
eval_divide(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& result,
    signed_limb_type                                                      b)
{
   // There is no in place divide:
   cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> a(result);
   eval_divide(result, a, b);
}

template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, unsigned MinBits2, unsigned MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2, unsigned MinBits3, unsigned MaxBits3, cpp_integer_type SignType3, cpp_int_check_type Checked3, class Allocator3>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && !is_trivial_cpp_int<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value && !is_trivial_cpp_int<cpp_int_backend<MinBits3, MaxBits3, SignType3, Checked3, Allocator3> >::value>::type
eval_modulus(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>& a,
    const cpp_int_backend<MinBits3, MaxBits3, SignType3, Checked3, Allocator3>& b)
{
   bool s = a.sign();
   divide_unsigned_helper(static_cast<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>*>(0), a, b, result);
   result.sign(s);
}

template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, unsigned MinBits2, unsigned MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && !is_trivial_cpp_int<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value>::type
eval_modulus(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>& a, limb_type b)
{
   bool s = a.sign();
   divide_unsigned_helper(static_cast<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>*>(0), a, b, result);
   result.sign(s);
}

template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, unsigned MinBits2, unsigned MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && !is_trivial_cpp_int<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value>::type
eval_modulus(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>& a,
    signed_limb_type                                                            b)
{
   bool s = a.sign();
   divide_unsigned_helper(static_cast<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>*>(0), a, static_cast<limb_type>(boost::multiprecision::detail::unsigned_abs(b)), result);
   result.sign(s);
}

template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, unsigned MinBits2, unsigned MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && !is_trivial_cpp_int<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value>::type
eval_modulus(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>& b)
{
   // There is no in place divide:
   cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> a(result);
   eval_modulus(result, a, b);
}

template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value>::type
eval_modulus(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& result,
    limb_type                                                             b)
{
   // There is no in place divide:
   cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> a(result);
   eval_modulus(result, a, b);
}

template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value>::type
eval_modulus(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& result,
    signed_limb_type                                                      b)
{
   // There is no in place divide:
   cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> a(result);
   eval_modulus(result, a, b);
}

//
// Over again for trivial cpp_int's:
//
template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<
    is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && (is_signed_number<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value || is_signed_number<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value)>::type
eval_divide(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& o)
{
   if (!*o.limbs())
      BOOST_THROW_EXCEPTION(std::overflow_error("Division by zero."));
   *result.limbs() /= *o.limbs();
   result.sign(result.sign() != o.sign());
}

template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<
    is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && is_unsigned_number<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && is_unsigned_number<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value>::type
eval_divide(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& o)
{
   if (!*o.limbs())
      BOOST_THROW_EXCEPTION(std::overflow_error("Division by zero."));
   *result.limbs() /= *o.limbs();
}

template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<
    is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value>::type
eval_modulus(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& o)
{
   if (!*o.limbs())
      BOOST_THROW_EXCEPTION(std::overflow_error("Division by zero."));
   *result.limbs() %= *o.limbs();
   result.sign(result.sign());
}

}}} // namespace boost::multiprecision::backends

#endif

/* divide.hpp
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
*/