///////////////////////////////////////////////////////////////
//  Copyright 2012 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt
//
// Comparison operators for cpp_int_backend:
//
#ifndef BOOST_MP_CPP_INT_DIV_HPP
#define BOOST_MP_CPP_INT_DIV_HPP

#include <boost/multiprecision/detail/no_exceptions_support.hpp>
#include <boost/multiprecision/detail/assert.hpp>

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
   std::size_t y_order = y.size() - 1;

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

   std::size_t r_order = x.size() - 1;
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
      for (std::size_t i = 1; i < 1 + r_order - y_order; ++i)
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
         BOOST_MP_ASSERT(b);
         double_limb_type v = a / b;
         guess              = static_cast<limb_type>(v);
      }
      BOOST_MP_ASSERT(guess); // If the guess ever gets to zero we go on forever....
      //
      // Update result:
      //
      std::size_t shift = r_order - y_order;
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
               for (std::size_t i = 0; i < shift; ++i)
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
            for (std::size_t i = 0; i < shift; ++i)
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
      for (std::size_t i = 0; i < shift; ++i)
         pt[i] = 0;
      for (std::size_t i = 0; i < y.size(); ++i)
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
         for (std::size_t i = 0; i <= r_order; ++i)
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

   BOOST_MP_ASSERT(r.compare_unsigned(y) < 0); // remainder must be less than the divisor or our code has failed
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
      BOOST_MP_THROW_EXCEPTION(std::overflow_error("Integer Division by zero."));
   }
   //
   // Find the most significant word of numerator.
   //
   std::size_t r_order = x.size() - 1;

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

   BOOST_MP_ASSERT(r.compare(y) < 0); // remainder must be less than the divisor or our code has failed
}

template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, std::size_t MinBits2, std::size_t MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2, std::size_t MinBits3, std::size_t MaxBits3, cpp_integer_type SignType3, cpp_int_check_type Checked3, class Allocator3>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && !is_trivial_cpp_int<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value && !is_trivial_cpp_int<cpp_int_backend<MinBits3, MaxBits3, SignType3, Checked3, Allocator3> >::value>::type
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

template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, std::size_t MinBits2, std::size_t MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && !is_trivial_cpp_int<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value>::type
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

template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, std::size_t MinBits2, std::size_t MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && !is_trivial_cpp_int<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value>::type
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

template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, std::size_t MinBits2, std::size_t MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && !is_trivial_cpp_int<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value>::type
eval_divide(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>& b)
{
   // There is no in place divide:
   cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> a(result);
   eval_divide(result, a, b);
}

template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value>::type
eval_divide(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& result,
    limb_type                                                             b)
{
   // There is no in place divide:
   cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> a(result);
   eval_divide(result, a, b);
}

template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value>::type
eval_divide(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& result,
    signed_limb_type                                                      b)
{
   // There is no in place divide:
   cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> a(result);
   eval_divide(result, a, b);
}

template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, std::size_t MinBits2, std::size_t MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2, std::size_t MinBits3, std::size_t MaxBits3, cpp_integer_type SignType3, cpp_int_check_type Checked3, class Allocator3>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && !is_trivial_cpp_int<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value && !is_trivial_cpp_int<cpp_int_backend<MinBits3, MaxBits3, SignType3, Checked3, Allocator3> >::value>::type
eval_modulus(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>& a,
    const cpp_int_backend<MinBits3, MaxBits3, SignType3, Checked3, Allocator3>& b)
{
   bool s = a.sign();
   if (b.size() == 1)
      eval_modulus(result, a, *b.limbs());
   else
      divide_unsigned_helper(static_cast<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>*>(0), a, b, result);
   result.sign(s);
}

template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, std::size_t MinBits2, std::size_t MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && !is_trivial_cpp_int<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value>::type
eval_modulus(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>& a,
    const limb_type                                                             mod)
{
   const std::ptrdiff_t n = a.size();
   const double_limb_type two_n_mod = static_cast<limb_type>(1u) + (~static_cast<limb_type>(0u) - mod) % mod;
   limb_type              res       = a.limbs()[n - 1] % mod;

   for (std::ptrdiff_t i = n - 2; i >= 0; --i)
      res = (res * two_n_mod + a.limbs()[i]) % mod;
   //
   // We must not modify result until here in case
   // result and a are the same object:
   //
   result.resize(1, 1);
   *result.limbs() = res;
   result.sign(a.sign());
}

template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, std::size_t MinBits2, std::size_t MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && !is_trivial_cpp_int<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value>::type
eval_modulus(
   cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& result,
   const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>& a,
   signed_limb_type                                                            b)
{
   const limb_type t = b < 0 ? -b : b;
   eval_modulus(result, a, t);
   result.sign(a.sign());
}

template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, std::size_t MinBits2, std::size_t MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && !is_trivial_cpp_int<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value>::type
eval_modulus(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>& b)
{
   // There is no in place divide:
   cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> a(result);
   eval_modulus(result, a, b);
}

template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value>::type
eval_modulus(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& result,
    limb_type                                                             b)
{
   // Single limb modulus is in place:
   eval_modulus(result, result, b);
}

template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value>::type
eval_modulus(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& result,
    signed_limb_type                                                      b)
{
   // Single limb modulus is in place:
   eval_modulus(result, result, b);
}

//
// Over again for trivial cpp_int's:
//
template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
    is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && (is_signed_number<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value || is_signed_number<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value)>::type
eval_divide(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& o)
{
   if (!*o.limbs())
      BOOST_MP_THROW_EXCEPTION(std::overflow_error("Division by zero."));
   *result.limbs() /= *o.limbs();
   result.sign(result.sign() != o.sign());
}

template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
    is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && is_unsigned_number<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && is_unsigned_number<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value>::type
eval_divide(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& o)
{
   if (!*o.limbs())
      BOOST_MP_THROW_EXCEPTION(std::overflow_error("Division by zero."));
   *result.limbs() /= *o.limbs();
}

template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
    is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value>::type
eval_modulus(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& o)
{
   if (!*o.limbs())
      BOOST_MP_THROW_EXCEPTION(std::overflow_error("Division by zero."));
   *result.limbs() %= *o.limbs();
   result.sign(result.sign());
}

}}} // namespace boost::multiprecision::backends

#endif

/* divide.hpp
uvzqa/C1zqRaJb8WvTeQVKTpM8X0z0Frd0rNkia9Jw4l2wuVceRGahTJWEHTyyD+pqxpKd72ccmoOHdSsBo5aF34AZOI5u2CIBNn76G8vZhCNrvshMK7H377ehecLKvOKbX0TavMzj403Z9l76WxSS5Qem5893WgNDFA06GBxtaBbc7E2AF1mzz1ghD198hwoVIHUCcZFLv7P5oRilGYJIbnQlK8U+pZFCtY0/jnLRkrl3c7f0olL3YXrTLJtsDwwfDRvXQCZvUlbkxzybag8cFy0fccAfhOdh2pp8DGE2B91V7XLmNgumauU6+mVr7fLdWBwUxM0sfwM4F3BL/z1tdmVZ2hha5dYCPkol3dtZeVq87TprkHct/iK3rCYGIkvGYl7NlSRtIPCLq2/ikz6Ld+CLD582kEWiCoD/Z3Iata14S4SpACEp3Z0gNcldQM5GgYn0JWcvh39VTQcgVYb8bCVLIqxu6MozmsI5jRmWkMhOSPPzhx2+jfHUgONRz8OM9XcJglUi/yDHePlFBQntEUk9kVciChvSP+Sdcb9u3WMcC+S+Alm4Eeho0DIzzZBmsT8gtrkIJk3GhzwF61WgGtZNu/vgO2dz76Fid02rCPll9SkJXTIs5XOVTD3l/GNjgrBLyk72btY5BG/ab+nFC4z1GY8zRo1YOHuipWPetHO+1Z05DZET3bv3bq9cC+SVo/ChO9sGceSIuahbZs9cHvuiqYmhi3cVLt2q0Qe6XFAMVrwVFF245w+HYcenzP29swv72qdNDNCuU6Q6bt/fr4+olIMiR/y4o93fSVNCgJrRZ4Y1VxX+eVSsBr05bLvzKS5N/KMhUvZ7GXrs9yM6TMuaGdaZEQ/O40R5MUTVoxpwQrQi5/U6KLhkcG2D88V7FlXXzwXHS77+teimDO1HMr8jEbRM8ZLY6C8zGgPHk5KcR7TszrG9OTvyJw+jsI53uKXVnuLR3HK1tixcznFEG2lR6C7n/Xz9XyGIy/07yq1zbB1ezIX2DRBwddb1gimiD8uex/SFhWL5etHkD+anP08aJd/nlORMX/EkrZuxtxxC3yVgv3Kjih63D0PItw9aM/oet49Bx5r3v14z3JXqY5d6u0ZhaE72ORSEKEUyfFBaKpzJCBNoofugYX5BWpKyfWXXITkkAbuXBL7/D4sDcRQxcJBRZBaKVMxGPYFjeYQUei6NDUUB6s1xV716iLbrktQn11NzjeUXB9XFDo2OMuGEBNynG1CQ8bL5gBfAaYVKgOWhAIVLeFmwNeKS1niOxjzNZykFp4N8fDw8GJQ5WMHG6zC+P+FYQESxSklCDccnJOjrSf73uOaSI71PM1PHhmtkTFS6X0BejJ7IosFh3ear/ndyTRlhQPu834PbQISGj7uPdNBlMwpx9L702p1+S6mfGR1S6gNOHrwpnOYzakuTTyh0IxtLtfvUOaRZxvQTxpOdmJWr66qbE5SIEWnYRtV/RexEsXBXLsr7Zq7+hNc5FZXHf+UAga6oh9WMY5IwlfhBjq557o8Dv3+1YZ9ot5D5XmfOGwjR7p1rmjtPQyuOx9NJxMlWieeE/vgHWGI79LlnyGcTwarVwrAvLXqsOVa3it/pk/TWIIPrHWwjvXN58HF74DIzf87Orb/MJI9UM+Z3LsFKvfpU1OreA10cC19INqkLaL3/J+VohgjF3V51YJDcjxJmMuyloEOCuuTISI9OuxjOQdI34pueY6DP8IIRL3/wAtgNJ/9uZc7YbBB1u8tCn3ObUAavQMfya5BookYh7X+xtU/8BBwLWhdsXwBmbDrw2OIZOk9aIpqkPuemoosALnVvRkBVLp9eZrBnrNqQF6lT5spJdc0xOUGK2V1NkoLNEgsXsIGr28+HoWqkB2+pfDM4n1/qXZ6PXbEs5CImCaJdHg35whSbP5I2u0RCu8vxMNr/iKzVqiLRQefxdlggC1vKNionrHDiRANG3PhpclKGoHegOIOw7+5ldpEpdyLwPPqwoVBP5WNr1AuPmidQ486uZXLS1Ws+kXIuue+fcVC4DqIDue2OmfMUY3PeQli7WKOrftWL9LSngK4xcLKvo1FiB7ZkvYC3EMrKe3+KOjx0iV6/074XoNHTxHVkXscDOAN62LxyABkVT4QiGm/U94DLYcKVWqpn2CaQ1E6NlqWlOY3iXiqWmvi3cPWQzvPivSCsbg7ojjDgPTXUeo2IjOzX95b7GkLVR8R8Ai5SVRz1vzv1a1mQPg/Q+rIK/Zz4xV0/pjOXG09wiN14inlMPXyWPUtAyCvr1wT7HeUa98peVsU2rLazcZhsR6ahXf/oxh7AiKcFkfOhrlOINBFj+WVMZesxiRO598GS8xJVPMp0ljeswnfbDiC3zpnybiYzTGU5B3cR7AdHrhAYG8K9a7qiv5FyuLXf2mBZC39zdjxXJHXr/8obnjJd3b9847+nQwFv5FAdh2XFUbUC7hGdFbAq7qQzielAA1CCLgJNReOyvxoOYRUUa8aFUnZ7KaoyCdhZfZSRO18sFdIrr2Fd5FG6FwbQ6UYYXxjNls1LIBlmLzd8xGeVdUYSlWobnGPVmY8Bgqk7Y+lQqMxHiXx7UW0e+T/uoJ3mmSyAil0fDdhvYopwP12s0X7CTAGG9u1G5uEU0w3OTL9g2SEoGowCBREwdnCwuVJbgfUsGypiavnoWJVKAsR9ylTTUdN5EFhjHX97OE9cs1FMkAn52tZzAABSZZaZC715Y8m9YSjftQmI+xx4q11oVRZUpKx9QGkpGZeEQOb+2VOGHLZ+av62Tflk72kJ1Nd6Kde0t69Z/vqyO2p3VE4jYpMnSadJ1X/5Qov9ca0nfB9UX4TBo2TSqFz3a4rsbvYeL+Z/B9CD5n4eOG3+n8Sr3Or5ixKzp+RyAaiXN7dHKcD3RVv0CQOpkyHcFr59vQ/tl2aH+CDPdSsDzOrMBYoCvPSdF/0WQDgrKrrSI8V9QQEinuAVKcKUCsQw3ilaIEok4HX0Ctgaw7YuFxjD6Rws/ZDQMMyZkGE9grnI9Cjy9uNeIL9QKRGNLaTS49+d9EB6seDbrTkqoH6ZDJFQeffgP1KmSPcf1/OhSvnxxGiqpfE3IX6qpA8uGdX+jKhfba8lNvoJYl/xtXFR7I6BnrChaWgdo0eZIwb4lGy0wesqtKFYOFloNlDS8ARnOqD/+P8OP/oUpID3QonOdkI0ZDYt28TDXQRxY+hPcCTkjFvmGz3VguNezkl9Z0PVVR55XAGeGvqRKdyyx5+1P0N3ddUV8n3hMxf41AneXAgyJUSpDfL5Hsy9f9+6Ae6nVLMDG3E7Ye3/FBwrk073z1/tXjgXu5Tao+v/Le/M6KZSyL3EozX0PbFCcq4iM5yRP09Mz8zlWt+9CVgu+Fdge1vhdjv6eWukMz9TWhhjB3MONPH08ZkqbHyxf43s+1ERP1ZwLb59btTM5H765sRicbEdTtuEDS5OzztON8wk4C5mAEnuUXksgzON6IEcEGAsOQweRxSjAXeUJEKiM7phOErsT/esqqn9O/Dz/oSCv9sL4nHunPb03Rz6X1Lv/ib73q2XIJ1Wv7Fw6F5BY0g5ggjCWE9alZP/A8rXZ9IqiI+m27emuf9YsQPYUtl6t6F0mxSGpc6xJv45WrCh9kWWi5QSFDfBPpCHgYyJKT29LDNbIMma95/lbFZnKs0AiQIr4zpGicBAXK1AbN/jSZBDH3p3zXZyqthLtJrKO2qLOuqBtoRTYIPqGsXt0ff2BcnhY1i2s+t/Ytbar0OJzY2if+Ggagb7fbYIWInQJZF10dY7wu1q2t+iGKiu26yWIAW+OILdcX1prRv/w1NF6XecVNWZKKcE8P8jMfJ5Pa6mGYP/9m7EK3cfp4tenzaLtV2taAg2yGPnt8CrD4dDQXVBmWWH8ZXaBWOwyWpKUO3MVIhZepq/D8OJ38ErfZSWzyEaHfgi4iW3+v0eIZK63V95DxvH50arQrE0A5WOdlOwWLcsJ/H4NlGUMkypkY02scXE9QgsiO8Id306hqi02JLDRGdPTWLfQXIrCVzK97P0cN5EjIcKy1jt5Dq7iNyHVXZMKIflUI8x7N16gQewIkJpQjP/gkhyDqrDATMTangKj76iIOaSdIW94U1S08OcNWypqEMlmnXsBeFoQv2crzPhT5WdQ91oBa5zF4T0xO1QJg7KgL96iiv4DRu8Rv7MxBV6vV/wHTtRZFh/xbMl2J3UjIoJMVPJawP4aNYM18VWMOlYTqWejwqcdzpDJ2lv/pyxwJY7x4UtTH2IoM/OfgDVAC0HJBGI8OheuLOJx9o18tkDn8mUj2aX4thU603MH4fmi9kxzSAIsJPqm7zeBDDt1XxIjad/oSBmDquXfo8zUv5TzR3H6drXVPQlViYgN+k9p18at23fKczfSxrFP1u8jGJjZ+PLBYdJA3fWming7yWsIN+9Cm/FOMKtMZfgV+wFK1ZzB6CuE1xlrcQ/dwGCEPw7OnWnAy3U+rs2HbDq8dLokle9xEDRxDuDR36OyOfn49twMm52w5+QFf1eb4LlvtQbLyPdlzA1BvwmL+eK6ZKbohHkdTDZrvo+2tG0hDC7RbsW0so/CYkEF6RA/RH9OMi5HTbP0kt2h+9Z9hsTjdhjt0QwqWgiX/mHDedYZCCs9111+sgnuBpX0UsC0LgW2ZJ8AwMncoXItTjtgMXMvHJkva7404ek5zftmu8ykKfv4rKfxZWnt2k+mCr82qg0LUlmtBG44A+6tYDRzm+ZPQzs7VcFDdlNZ9apXWHewJoPJ99XlkEL+vP8nZwto76mI1Adyju2wxO+s6kyNi5W0VNx37bORcpQT41FUZtZNsVOVhaxonU8Ce7IjUtIYu+eKJt0t8wbewxHUNqBhIcRmP8XcXjZH4jz+xavbiKWrDI9EBaDOO2np9H36qzdobNKto764HdHy1YMgMMpwaPQI5koiC1+eq2k9x/gzmTZ3otvsywSgNJSQ/RTHtqkbDT7bCL0QcxdS2mhCGN7hJUu9hyQ4lsE40WsOc1dxaUExTVN0D2SJfGV/9t2TyTAF/+6QDT95Wj4YFduAKSatibEAZa+Xz8aFhrNCHP4rxxwBhK48d0dfQvNMEAC9ECIYjWE2D8EjLwbAH6pCPOjgFna1X/TbLUJO064/XU6xAzX3JqLBS4mcfSPEHMhlvHzcXdRLnOrbVqjl8pXCuyeiy6jbgyNBzS3HausOLti9Ra14bq9kk6utFUy4QLI21tue1AX2G4dntcYJSGUbvxWyJeRZjsjS0WIKBbWMVWjTvqR9bYROPDmL1SI/4LoQhkbDA+N4GcsCbo52nlCkHKv+9nyqVzzY2KFRqfgxfE0YRmBZECLz4np5UE/Np+4MpIVV6qkxEDopJBWRT0Ec2BzX636afV/Q6+OuJgkeiC4HSN6E4AHxN9vaxkmi6KBG7+93dfVR84yZ1ZCD+8hZ8NMWxrY/hqOGZQH19RvmmUFduBkMGGcdyUjuzj+1sKmoEIRi49vxOV1U1tkfAP7RGH6kraq8rOkUAIR2JOHYFAh1jND+sMUMgmcTc9tkiKiGag+N2hhHqEiV7eOaCYkkRkqYXRGzhCTFhZAobQ/h1dIxFp0l0rCnjBxaj6swnpKc9/P7kHZrwdP6ktcfMI5Xm4+U9w7Hp/Gz7TAMJZuj8bEEKOysrtLh7hAdWWw+sOk/ur53hz8GDxzeRCnGhbu4YBf9rMTwh24H2gqyRHIDWTMb44AeeHvvO/5f3NNBNlVm+lNfygJQGmmIcixYsWgQViT+tqbMt0FKUlCQlad3BwiKjma4zg0yelDmAreHH7DdxnN09iiMyRXcdZnUddpbVcmQwCEuKw/Ano4y4Hhw5+th2xrqDUKCSvfd+7728NGnS9lBnz1nOKS95+X7vd7/73Xu/+8M6wuJd8Dx64WhPiOdRtSk/O264FSkEfqoIGfwGVZCciwk3lc6G+chpwU5Cq7Q4hI4hhBYuBQh5l1Jq1umuOmVLIwcRNkK1nZcXIGPWQFA68js4uWDwmLMwIZByOTClyxYlwSoBXlONKo+SlEy/vlVVfwKQM5DMnxcMQgklEdW9ClA+OBFn12mf5HPXAuTR0aWEfAv4vV2h5l2QF9rAS85ahHmxUQoBiiCHlxVT9SWog3Dp/ii+RINZn3Jvo2Z25dDNruDLLXF3zTnFheiZFp4ncJdN+E7WM2iAK1eWwVf50+BqEMXkHyez/fBDsZC3fhS8nJkkAXA/98PcyBhoZA4KOp0jgZ5SJmQ0VvJK7Alu6uMmUx+ViVMePQbYMpHO7EXF0yliAQkgQD8nsRFYNRvNfDDKxnTV7mdhcYmLZSGMKPC2cujdLL3zRAtnJf+YQe8Sbz0LKBYFyVroIyBJwGsqb1wiE1BocM27WSkEn+2mlNNOwKc24/5bGN9/8+uMmLVEswgv3eInrcXH5A98VD/DVquCMSbEdFzKW7eDTgEUxhHTtOzlWtZw5ipye9RcmYCdLj1XJvme+8+jD+kHkWnA8AWmsnZKaFmzmj1NjEYLJkYwQaOmhZQut5CtphgrmJj8dmWOl7apnx94dXyXHkY6ZvJ/QF4rXDgtd/uUnr+mXQrSlJ/qbrtIm9RPm3QarMPfbcDJYvJOwzE1v3g+bNNfNyRuUx2em7a2ZbT3vKDcfAQpDjp+EQuMl7EwDJtBKVeEdGah6qCcj18a6GBRtWidK/AyL1BcojwBi6D812Gdj5zPm0JwA86MQQ66kMwiyql4HRZ/7bBRuaf1nMUZT6uq3gs2SwLZNFj2xnhXVx3NSmFwuTeeD0anPKy1nPyvJFYhte4pp6uSI7jKaJOXIlzXQRCeLnCpY9vKnQbh8hmsu7V02ZsCCCqu8FPl3DojtxzfbKBOXJJbex8reBXPusOLG2NTsKfE+Ag+9ns2u6ge+tjB81ZNx07Qln8Emys2NeCFDcqhC0RWB/iJmuB2KBi8vETG6ALRStt6AFHnlODlZu0FpqPutDYt8fnxp1jBKazvlEKVtmhl4TkyQfqNsvwhNR6B2Pc+Ieuu5zP5j38RkkFcfRpG+gu8HM9b58M5A7OxXMt2jbTwGlfcaTQwNtFXoa8QTRi3Ppa37gBuBZB3qYB6x3IDfTly84ukB7Ezb7f9XNmKs2tv8NEPT0IP1Q8Fe26Qc5vUVwehbDWr6nYsP7v6AyZ3UbBLPSkUuuLCyNYhofN2Nwke+ll1Tiuwn9xNwYjR/0gNkdlZ1vQAfTmRpkwBkyXOf2hvRvBgAJOQqV9/Ur4aBoKSnc4b5wMnAiPpzGbOLgqaZDDHSmHuluQxg/u7q1Tn0HoxmISPokkUAT8vz2QbMXQWYD7wW6cRCe7oeKNdaN/3Boak7GAxGFsxq5WQgkuwKHd2/qn10gyoGZCghS+ghZx6ZdNYZLGOuNnhaNWR6XRar+YrOop5T4SeRakU03xQ+Ilm0kP0Lm60//Zbyq0L+xqxsEpN9bC/tYJ7vePhZbw/wQgayvGrLajmS0p4w/FzVeCn6fOh9cUtOJWaKJ2G32MmwlsQoBmszVb++04LDBhz57o9JD8vz7QExpzhg/Pn5XQmuEYaiV6y8vd2tmMKedvaqSq55UGUtr2TigoKBirIVQ9HxswXQhRSQ7/DyD2YpYVi
*/