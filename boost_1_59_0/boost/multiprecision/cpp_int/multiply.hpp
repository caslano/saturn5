///////////////////////////////////////////////////////////////
//  Copyright 2012-20 John Maddock. 
//  Copyright 2019-20 Christopher Kormanyos. 
//  Copyright 2019-20 Madhur Chauhan. 
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt
//
// Comparison operators for cpp_int_backend:
//
#ifndef BOOST_MP_CPP_INT_MUL_HPP
#define BOOST_MP_CPP_INT_MUL_HPP

#include <limits>
#include <boost/multiprecision/detail/standalone_config.hpp>
#include <boost/multiprecision/detail/endian.hpp>
#include <boost/multiprecision/detail/assert.hpp>
#include <boost/multiprecision/integer.hpp>

namespace boost { namespace multiprecision { namespace backends {

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable : 4127) // conditional expression is constant
#endif
//
// Multiplication by a single limb:
//
template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, std::size_t MinBits2, std::size_t MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && !is_trivial_cpp_int<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value>::type
eval_multiply(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>& a,
    const limb_type&                                                            val) noexcept((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   if (!val)
   {
      result = static_cast<limb_type>(0);
      return;
   }
   if ((void*)&a != (void*)&result)
      result.resize(a.size(), a.size());
   double_limb_type                                                                                  carry = 0;
   typename cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::limb_pointer       p     = result.limbs();
   typename cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::limb_pointer       pe    = result.limbs() + result.size();
   typename cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>::const_limb_pointer pa    = a.limbs();
   while (p != pe)
   {
      carry += static_cast<double_limb_type>(*pa) * static_cast<double_limb_type>(val);
#ifdef __MSVC_RUNTIME_CHECKS
      *p = static_cast<limb_type>(carry & ~static_cast<limb_type>(0));
#else
      *p = static_cast<limb_type>(carry);
#endif
      carry >>= cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::limb_bits;
      ++p, ++pa;
   }
   if (carry)
   {
      std::size_t i = result.size();
      result.resize(i + 1, i + 1);
      if (result.size() > i)
         result.limbs()[i] = static_cast<limb_type>(carry);
   }
   result.sign(a.sign());
   if (is_fixed_precision<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value)
      result.normalize();
}

//
// resize_for_carry forces a resize of the underlying buffer only if a previous request
// for "required" elements could possibly have failed, *and* we have checking enabled.
// This will cause an overflow error inside resize():
//
template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
inline BOOST_MP_CXX14_CONSTEXPR void resize_for_carry(cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& /*result*/, std::size_t /*required*/) {}

template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, class Allocator1>
inline BOOST_MP_CXX14_CONSTEXPR void resize_for_carry(cpp_int_backend<MinBits1, MaxBits1, SignType1, checked, Allocator1>& result, std::size_t required)
{
   if (result.size() < required)
      result.resize(required, required);
}
//
// Minimum number of limbs required for Karatsuba to be worthwhile:
//
#ifdef BOOST_MP_KARATSUBA_CUTOFF
const size_t karatsuba_cutoff = BOOST_MP_KARATSUBA_CUTOFF;
#else
const size_t karatsuba_cutoff = 40;
#endif
//
// Core (recursive) Karatsuba multiplication, all the storage required is allocated upfront and 
// passed down the stack in this routine.  Note that all the cpp_int_backend's must be the same type
// and full variable precision.  Karatsuba really doesn't play nice with fixed-size integers.  If necessary
// fixed precision integers will get aliased as variable-precision types before this is called.
//
template <std::size_t MinBits, std::size_t MaxBits, cpp_int_check_type Checked, class Allocator>
inline void multiply_karatsuba(
    cpp_int_backend<MinBits, MaxBits, signed_magnitude, Checked, Allocator>&       result,
    const cpp_int_backend<MinBits, MaxBits, signed_magnitude, Checked, Allocator>& a,
    const cpp_int_backend<MinBits, MaxBits, signed_magnitude, Checked, Allocator>& b,
    typename cpp_int_backend<MinBits, MaxBits, signed_magnitude, Checked, Allocator>::scoped_shared_storage& storage)
{
   using cpp_int_type = cpp_int_backend<MinBits, MaxBits, signed_magnitude, Checked, Allocator>;

   std::size_t as = a.size();
   std::size_t bs = b.size();
   //
   // Termination condition: if either argument is smaller than karatsuba_cutoff
   // then schoolboy multiplication will be faster:
   //
   if ((as < karatsuba_cutoff) || (bs < karatsuba_cutoff))
   {
      eval_multiply(result, a, b);
      return;
   }
   //
   // Partitioning size: split the larger of a and b into 2 halves
   //
   std::size_t n  = (as > bs ? as : bs) / 2 + 1;
   //
   // Partition a and b into high and low parts.
   // ie write a, b as a = a_h * 2^n + a_l, b = b_h * 2^n + b_l
   //
   // We could copy the high and low parts into new variables, but we'll
   // use aliasing to reference the internal limbs of a and b.  There is one wart here:
   // if a and b are mismatched in size, then n may be larger than the smaller
   // of a and b.  In that situation the high part is zero, and we have no limbs
   // to alias, so instead alias a local variable.
   // This raises 2 questions:
   // * Is this the best way to partition a and b?
   // * Since we have one high part zero, the arithmetic simplifies considerably, 
   //   so should we have a special routine for this?
   // 
   std::size_t          sz = (std::min)(as, n);
   const cpp_int_type a_l(a.limbs(), 0, sz);

   sz = (std::min)(bs, n);
   const cpp_int_type b_l(b.limbs(), 0, sz);

   limb_type          zero = 0;
   const cpp_int_type a_h(as > n ? a.limbs() + n : &zero, 0, as > n ? as - n : 1);
   const cpp_int_type b_h(bs > n ? b.limbs() + n : &zero, 0, bs > n ? bs - n : 1);
   //
   // The basis for the Karatsuba algorithm is as follows:
   //
   // let                x = a_h * b_ h
   //                    y = a_l * b_l
   //                    z = (a_h + a_l)*(b_h + b_l) - x - y
   // and therefore  a * b = x * (2 ^ (2 * n))+ z * (2 ^ n) + y
   //
   // Begin by allocating our temporaries, these alias the memory already allocated in the shared storage:
   //
   cpp_int_type t1(storage, 2 * n + 2);
   cpp_int_type t2(storage, n + 1);
   cpp_int_type t3(storage, n + 1);
   //
   // Now we want:
   //
   // result = | a_h*b_h  | a_l*b_l |
   // (bits)              <-- 2*n -->
   //
   // We create aliases for the low and high parts of result, and multiply directly into them:
   //
   cpp_int_type result_low(result.limbs(), 0, 2 * n);
   cpp_int_type result_high(result.limbs(), 2 * n, result.size() - 2 * n);
   //
   // low part of result is a_l * b_l:
   //
   multiply_karatsuba(result_low, a_l, b_l, storage);
   //
   // We haven't zeroed out memory in result, so set to zero any unused limbs,
   // if a_l and b_l have mostly random bits then nothing happens here, but if
   // one is zero or nearly so, then a memset might be faster... it's not clear
   // that it's worth the extra logic though (and is darn hard to measure
   // what the "average" case is).
   //
   for (std::size_t i = result_low.size(); i < 2 * n; ++i)
      result.limbs()[i] = 0;
   //
   // Set the high part of result to a_h * b_h:
   //
   multiply_karatsuba(result_high, a_h, b_h, storage);
   for (std::size_t i = result_high.size() + 2 * n; i < result.size(); ++i)
      result.limbs()[i] = 0;
   //
   // Now calculate (a_h+a_l)*(b_h+b_l):
   //
   add_unsigned(t2, a_l, a_h);
   add_unsigned(t3, b_l, b_h);
   multiply_karatsuba(t1, t2, t3, storage); // t1 = (a_h+a_l)*(b_h+b_l)
   //
   // There is now a slight deviation from Karatsuba, we want to subtract
   // a_l*b_l + a_h*b_h from t1, but rather than use an addition and a subtraction
   // plus one temporary, we'll use 2 subtractions.  On the minus side, a subtraction
   // is on average slightly slower than an addition, but we save a temporary (ie memory)
   // and also hammer the same piece of memory over and over rather than 2 disparate
   // memory regions.  Overall it seems to be a slight win.
   //
   subtract_unsigned(t1, t1, result_high);
   subtract_unsigned(t1, t1, result_low);
   //
   // The final step is to left shift t1 by n bits and add to the result.
   // Rather than do an actual left shift, we can simply alias the result
   // and add to the alias:
   //
   cpp_int_type result_alias(result.limbs(), n, result.size() - n);
   add_unsigned(result_alias, result_alias, t1);
   //
   // Free up storage for use by sister branches to this one:
   //
   storage.deallocate(t1.capacity() + t2.capacity() + t3.capacity());

   result.normalize();
}

inline std::size_t karatsuba_storage_size(std::size_t s)
{
   // 
   // This estimates how much memory we will need based on
   // s-limb multiplication.  In an ideal world the number of limbs
   // would halve with each recursion, and our storage requirements
   // would be 4s in the limit, and rather less in practice since
   // we bail out long before we reach one limb.  In the real world
   // we don't quite halve s in each recursion, so this is an heuristic
   // which over-estimates how much we need.  We could compute an exact
   // value, but it would be rather time consuming.
   //
   return 5 * s;
}
//
// There are 2 entry point routines for Karatsuba multiplication:
// one for variable precision types, and one for fixed precision types.
// These are responsible for allocating all the storage required for the recursive
// routines above, and are always at the outermost level.
//
// Normal variable precision case comes first:
//
template <std::size_t MinBits, std::size_t MaxBits, cpp_integer_type SignType, cpp_int_check_type Checked, class Allocator>
inline typename std::enable_if<!is_fixed_precision<cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator> >::value>::type
setup_karatsuba(
   cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>& result,
   const cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>& a,
   const cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>& b)
{
   std::size_t as = a.size();
   std::size_t bs = b.size();
   std::size_t s = as > bs ? as : bs;
   std::size_t storage_size = karatsuba_storage_size(s);
   if (storage_size < 300)
   {
      //
      // Special case: if we don't need too much memory, we can use stack based storage
      // and save a call to the allocator, this allows us to use Karatsuba multiply
      // at lower limb counts than would otherwise be possible:
      //
      limb_type limbs[300];
      typename cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>::scoped_shared_storage storage(limbs, storage_size);
      multiply_karatsuba(result, a, b, storage);
   }
   else
   {
      typename cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>::scoped_shared_storage storage(result.allocator(), storage_size);
      multiply_karatsuba(result, a, b, storage);
   }
}

template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, std::size_t MinBits2, std::size_t MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2, std::size_t MinBits3, std::size_t MaxBits3, cpp_integer_type SignType3, cpp_int_check_type Checked3, class Allocator3>
inline typename std::enable_if<is_fixed_precision<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value || is_fixed_precision<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value || is_fixed_precision<cpp_int_backend<MinBits3, MaxBits3, SignType3, Checked3, Allocator3> >::value>::type
setup_karatsuba(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>& a,
    const cpp_int_backend<MinBits3, MaxBits3, SignType3, Checked3, Allocator3>& b)
{
   //
   // Now comes the fixed precision case.
   // In fact Karatsuba doesn't really work with fixed precision since the logic
   // requires that we calculate all the bits of the result (especially in the
   // temporaries used internally).  So... we'll convert all the arguments
   // to variable precision types by aliasing them, this also
   // reduce the number of template instantations:
   //
   using variable_precision_type = cpp_int_backend<0, 0, signed_magnitude, unchecked, std::allocator<limb_type> >;
   variable_precision_type a_t(a.limbs(), 0, a.size()), b_t(b.limbs(), 0, b.size());
   std::size_t as = a.size();
   std::size_t bs = b.size();
   std::size_t s = as > bs ? as : bs;
   std::size_t sz = as + bs;
   std::size_t storage_size = karatsuba_storage_size(s);

   if (!is_fixed_precision<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value || (sz * sizeof(limb_type) * CHAR_BIT <= MaxBits1))
   {
      // Result is large enough for all the bits of the result, so we can use aliasing:
      result.resize(sz, sz);
      variable_precision_type t(result.limbs(), 0, result.size());
      typename variable_precision_type::scoped_shared_storage storage(t.allocator(), storage_size);
      multiply_karatsuba(t, a_t, b_t, storage);
      result.resize(t.size(), t.size());
   }
   else
   {
      //
      // Not enough bit in result for the answer, so we must use a temporary
      // and then truncate (ie modular arithmetic):
      //
      typename variable_precision_type::scoped_shared_storage storage(variable_precision_type::allocator_type(), sz + storage_size);
      variable_precision_type t(storage, sz);
      multiply_karatsuba(t, a_t, b_t, storage);
      //
      // If there is truncation, and result is a checked type then this will throw:
      //
      result = t;
   }
}
template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, std::size_t MinBits2, std::size_t MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2, std::size_t MinBits3, std::size_t MaxBits3, cpp_integer_type SignType3, cpp_int_check_type Checked3, class Allocator3>
inline typename std::enable_if<!is_fixed_precision<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && !is_fixed_precision<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value && !is_fixed_precision<cpp_int_backend<MinBits3, MaxBits3, SignType3, Checked3, Allocator3> >::value>::type
setup_karatsuba(
   cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& result,
   const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>& a,
   const cpp_int_backend<MinBits3, MaxBits3, SignType3, Checked3, Allocator3>& b)
{
   //
   // Variable precision, mixed arguments, just alias and forward:
   //
   using variable_precision_type = cpp_int_backend<0, 0, signed_magnitude, unchecked, std::allocator<limb_type> >;
   variable_precision_type a_t(a.limbs(), 0, a.size()), b_t(b.limbs(), 0, b.size());
   std::size_t as = a.size();
   std::size_t bs = b.size();
   std::size_t s = as > bs ? as : bs;
   std::size_t sz = as + bs;
   std::size_t storage_size = karatsuba_storage_size(s);

   result.resize(sz, sz);
   variable_precision_type t(result.limbs(), 0, result.size());
   typename variable_precision_type::scoped_shared_storage storage(t.allocator(), storage_size);
   multiply_karatsuba(t, a_t, b_t, storage);
}

template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, std::size_t MinBits2, std::size_t MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2, std::size_t MinBits3, std::size_t MaxBits3, cpp_integer_type SignType3, cpp_int_check_type Checked3, class Allocator3>
inline BOOST_MP_CXX14_CONSTEXPR void
eval_multiply_comba(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>& a,
    const cpp_int_backend<MinBits3, MaxBits3, SignType3, Checked3, Allocator3>& b) noexcept((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   // 
   // see PR #182
   // Comba Multiplier - based on Paul Comba's
   // Exponentiation cryptosystems on the IBM PC, 1990
   //
   std::ptrdiff_t as                                                                                         = a.size(),
       bs                                                                                         = b.size(),
       rs                                                                                         = result.size();
   typename cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::limb_pointer pr = result.limbs();

   double_limb_type carry    = 0,
                    temp     = 0;
   limb_type      overflow   = 0;
   const std::size_t limb_bits  = sizeof(limb_type) * CHAR_BIT;
   const bool     must_throw = rs < as + bs - 1;
   for (std::ptrdiff_t r = 0, lim = (std::min)(rs, as + bs - 1); r < lim; ++r, overflow = 0)
   {
      std::ptrdiff_t i = r >= as ? as - 1 : r,
          j = r - i,
          k = i < bs - j ? i + 1 : bs - j; // min(i+1, bs-j);

      typename cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>::const_limb_pointer pa = a.limbs() + i;
      typename cpp_int_backend<MinBits3, MaxBits3, SignType3, Checked3, Allocator3>::const_limb_pointer pb = b.limbs() + j;

      temp = carry;
      carry += static_cast<double_limb_type>(*(pa)) * (*(pb));
      overflow += carry < temp;
      for (--k; k; k--)
      {
         temp = carry;
         carry += static_cast<double_limb_type>(*(--pa)) * (*(++pb));
         overflow += carry < temp;
      }
      *(pr++) = static_cast<limb_type>(carry);
      carry   = (static_cast<double_limb_type>(overflow) << limb_bits) | (carry >> limb_bits);
   }
   if (carry || must_throw)
   {
      resize_for_carry(result, as + bs);
      if (static_cast<int>(result.size()) >= as + bs)
         *pr = static_cast<limb_type>(carry);
   }
}
template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, std::size_t MinBits2, std::size_t MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2, std::size_t MinBits3, std::size_t MaxBits3, cpp_integer_type SignType3, cpp_int_check_type Checked3, class Allocator3>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && !is_trivial_cpp_int<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value && !is_trivial_cpp_int<cpp_int_backend<MinBits3, MaxBits3, SignType3, Checked3, Allocator3> >::value>::type
eval_multiply(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>& a,
    const cpp_int_backend<MinBits3, MaxBits3, SignType3, Checked3, Allocator3>& b) 
   noexcept((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value 
      && (karatsuba_cutoff * sizeof(limb_type) * CHAR_BIT > MaxBits1) 
      && (karatsuba_cutoff * sizeof(limb_type)* CHAR_BIT > MaxBits2) 
      && (karatsuba_cutoff * sizeof(limb_type)* CHAR_BIT > MaxBits3)))
{
   // Uses simple (O(n^2)) multiplication when the limbs are less
   // otherwise switches to karatsuba algorithm based on experimental value (~40 limbs)
   //
   // Trivial cases first:
   //
   std::size_t                                                                                          as = a.size();
   std::size_t                                                                                          bs = b.size();
   typename cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>::const_limb_pointer pa = a.limbs();
   typename cpp_int_backend<MinBits3, MaxBits3, SignType3, Checked3, Allocator3>::const_limb_pointer pb = b.limbs();
   if (as == 1)
   {
      bool s = b.sign() != a.sign();
      if (bs == 1)
      {
         result = static_cast<double_limb_type>(*pa) * static_cast<double_limb_type>(*pb);
      }
      else
      {
         limb_type l = *pa;
         eval_multiply(result, b, l);
      }
      result.sign(s);
      return;
   }
   if (bs == 1)
   {
      bool      s = b.sign() != a.sign();
      limb_type l = *pb;
      eval_multiply(result, a, l);
      result.sign(s);
      return;
   }

   if ((void*)&result == (void*)&a)
   {
      cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> t(a);
      eval_multiply(result, t, b);
      return;
   }
   if ((void*)&result == (void*)&b)
   {
      cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> t(b);
      eval_multiply(result, a, t);
      return;
   }

   constexpr const double_limb_type limb_max = ~static_cast<limb_type>(0u);
   constexpr const double_limb_type double_limb_max = ~static_cast<double_limb_type>(0u);

   result.resize(as + bs, as + bs - 1);
#ifndef BOOST_MP_NO_CONSTEXPR_DETECTION
   if (!BOOST_MP_IS_CONST_EVALUATED(as) && (as >= karatsuba_cutoff && bs >= karatsuba_cutoff))
#else
   if (as >= karatsuba_cutoff && bs >= karatsuba_cutoff)
#endif
   {
      setup_karatsuba(result, a, b);
      //
      // Set the sign of the result:
      //
      result.sign(a.sign() != b.sign());
      return;
   }
   typename cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::limb_pointer pr = result.limbs();
   static_assert(double_limb_max - 2 * limb_max >= limb_max * limb_max, "failed limb size sanity check");

#ifndef BOOST_MP_NO_CONSTEXPR_DETECTION
   if (BOOST_MP_IS_CONST_EVALUATED(as))
   {
      for (std::size_t i = 0; i < result.size(); ++i)
         pr[i] = 0;
   }
   else
#endif
   std::memset(pr, 0, result.size() * sizeof(limb_type));   

#if defined(BOOST_MP_COMBA)
       // 
       // Comba Multiplier might not be efficient because of less efficient assembly
       // by the compiler as of 09/01/2020 (DD/MM/YY). See PR #182
       // Till then this will lay dormant :(
       //
       eval_multiply_comba(result, a, b);
#else

   double_limb_type carry = 0;
   for (std::size_t i = 0; i < as; ++i)
   {
      BOOST_MP_ASSERT(result.size() > i);
      std::size_t inner_limit = !is_fixed_precision<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value ? bs : (std::min)(result.size() - i, bs);
      std::size_t j           = 0;
      for (; j < inner_limit; ++j)
      {
         BOOST_MP_ASSERT(i + j < result.size());
#if (!defined(__GLIBCXX__) && !defined(__GLIBCPP__)) || !BOOST_WORKAROUND(BOOST_GCC_VERSION, <= 50100)
         BOOST_MP_ASSERT(!std::numeric_limits<double_limb_type>::is_specialized || ((std::numeric_limits<double_limb_type>::max)() - carry >
                                                                                 static_cast<double_limb_type>(cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::max_limb_value) * static_cast<double_limb_type>(cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::max_limb_value)));
#endif
         carry += static_cast<double_limb_type>(pa[i]) * static_cast<double_limb_type>(pb[j]);
         BOOST_MP_ASSERT(!std::numeric_limits<double_limb_type>::is_specialized || ((std::numeric_limits<double_limb_type>::max)() - carry >= pr[i + j]));
         carry += pr[i + j];
#ifdef __MSVC_RUNTIME_CHECKS
         pr[i + j] = static_cast<limb_type>(carry & ~static_cast<limb_type>(0));
#else
         pr[i + j] = static_cast<limb_type>(carry);
#endif
         carry >>= cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::limb_bits;
         BOOST_MP_ASSERT(carry <= (cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::max_limb_value));
      }
      if (carry)
      {
         resize_for_carry(result, i + j + 1); // May throw if checking is enabled
         if (i + j < result.size())
#ifdef __MSVC_RUNTIME_CHECKS
            pr[i + j] = static_cast<limb_type>(carry & ~static_cast<limb_type>(0));
#else
            pr[i + j] = static_cast<limb_type>(carry);
#endif
      }
      carry = 0;
   }
#endif // ifdef(BOOST_MP_COMBA) ends

   result.normalize();
   //
   // Set the sign of the result:
   //
   result.sign(a.sign() != b.sign());
}

template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, std::size_t MinBits2, std::size_t MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && !is_trivial_cpp_int<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value>::type
eval_multiply(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>& a) 
   noexcept((noexcept(eval_multiply(std::declval<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&>(), std::declval<const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&>(), std::declval<const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>&>()))))
{
   eval_multiply(result, result, a);
}

template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value>::type
eval_multiply(cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& result, const limb_type& val) 
   noexcept((noexcept(eval_multiply(std::declval<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&>(), std::declval<const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&>(), std::declval<const limb_type&>()))))
{
   eval_multiply(result, result, val);
}

template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, std::size_t MinBits2, std::size_t MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && !is_trivial_cpp_int<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value>::type
eval_multiply(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>& a,
    const double_limb_type&                                                     val) 
   noexcept(
      (noexcept(eval_multiply(std::declval<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&>(), std::declval<const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>&>(), std::declval<const limb_type&>())))
      && (noexcept(eval_multiply(std::declval<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&>(), std::declval<const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>&>(), std::declval<const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&>())))
   )
{
   if (val <= (std::numeric_limits<limb_type>::max)())
   {
      eval_multiply(result, a, static_cast<limb_type>(val));
   }
   else
   {
#if BOOST_MP_ENDIAN_LITTLE_BYTE && !defined(BOOST_MP_TEST_NO_LE)
      cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> t(val);
#else
      cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> t;
      t = val;
#endif
      eval_multiply(result, a, t);
   }
}

template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value>::type
eval_multiply(cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& result, const double_limb_type& val)
   noexcept((noexcept(eval_multiply(std::declval<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&>(), std::declval<const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&>(), std::declval<const double_limb_type&>()))))
{
   eval_multiply(result, result, val);
}

template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, std::size_t MinBits2, std::size_t MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && !is_trivial_cpp_int<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value>::type
eval_multiply(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>& a,
    const signed_limb_type&                                                     val) 
   noexcept((noexcept(eval_multiply(std::declval<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&>(), std::declval<const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>&>(), std::declval<const limb_type&>()))))
{
   if (val > 0)
      eval_multiply(result, a, static_cast<limb_type>(val));
   else
   {
      eval_multiply(result, a, static_cast<limb_type>(boost::multiprecision::detail::unsigned_abs(val)));
      result.negate();
   }
}

template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value>::type
eval_multiply(cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& result, const signed_limb_type& val)
   noexcept((noexcept(eval_multiply(std::declval<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&>(), std::declval<const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&>(), std::declval<const limb_type&>()))))
{
   eval_multiply(result, result, val);
}

template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, std::size_t MinBits2, std::size_t MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && !is_trivial_cpp_int<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value>::type
eval_multiply(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>& a,
    const signed_double_limb_type&                                              val)
   noexcept(
   (noexcept(eval_multiply(std::declval<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&>(), std::declval<const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>&>(), std::declval<const limb_type&>())))
      && (noexcept(eval_multiply(std::declval<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&>(), std::declval<const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>&>(), std::declval<const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&>())))
   )
{
   if (val > 0)
   {
      if (val <= (std::numeric_limits<limb_type>::max)())
      {
         eval_multiply(result, a, static_cast<limb_type>(val));
         return;
      }
   }
   else if (val >= -static_cast<signed_double_limb_type>((std::numeric_limits<limb_type>::max)()))
   {
      eval_multiply(result, a, static_cast<limb_type>(boost::multiprecision::detail::unsigned_abs(val)));
      result.negate();
      return;
   }
#if BOOST_MP_ENDIAN_LITTLE_BYTE && !defined(BOOST_MP_TEST_NO_LE)
   cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> t(val);
#else
   cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> t;
   t = val;
#endif
   eval_multiply(result, a, t);
}

template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value>::type
eval_multiply(cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& result, const signed_double_limb_type& val)
   noexcept(
   (noexcept(eval_multiply(std::declval<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&>(), std::declval<const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&>(), std::declval<const limb_type&>())))
   && (noexcept(eval_multiply(std::declval<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&>(), std::declval<const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&>(), std::declval<const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&>())))
   )
{
   eval_multiply(result, result, val);
}

//
// Now over again for trivial cpp_int's:
//
template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
    is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && (is_signed_number<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value || is_signed_number<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value)>::type
eval_multiply(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& o) noexcept((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   *result.limbs() = detail::checked_multiply(*result.limbs(), *o.limbs(), typename cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::checked_type());
   result.sign(result.sign() != o.sign());
   result.normalize();
}

template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
    is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && is_unsigned_number<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value>::type
eval_multiply(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& o) noexcept((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   *result.limbs() = detail::checked_multiply(*result.limbs(), *o.limbs(), typename cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::checked_type());
   result.normalize();
}

template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
    is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && (is_signed_number<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value || is_signed_number<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value)>::type
eval_multiply(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& a,
    const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& b) noexcept((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   *result.limbs() = detail::checked_multiply(*a.limbs(), *b.limbs(), typename cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::checked_type());
   result.sign(a.sign() != b.sign());
   result.normalize();
}

template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
    is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && is_unsigned_number<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value>::type
eval_multiply(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& a,
    const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& b) noexcept((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   *result.limbs() = detail::checked_multiply(*a.limbs(), *b.limbs(), typename cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::checked_type());
   result.normalize();
}

//
// Special routines for multiplying two integers to obtain a multiprecision result:
//
template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
    !is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value>::type
eval_multiply(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& result,
    signed_double_limb_type a, signed_double_limb_type b)
{
   constexpr const signed_double_limb_type mask = ~static_cast<limb_type>(0);
   constexpr const std::size_t limb_bits = sizeof(limb_type) * CHAR_BIT;

   bool s = false;
   if (a < 0)
   {
      a = -a;
      s = true;
   }
   if (b < 0)
   {
      b = -b;
      s = !s;
   }
   double_limb_type w = a & mask;
   double_limb_type x = a >> limb_bits;
   double_limb_type y = b & mask;
   double_limb_type z = b >> limb_bits;

   result.resize(4, 4);
   limb_type* pr = result.limbs();

   double_limb_type carry = w * y;
#ifdef __MSVC_RUNTIME_CHECKS
   pr[0] = static_cast<limb_type>(carry & ~static_cast<limb_type>(0));
   carry >>= limb_bits;
   carry += w * z + x * y;
   pr[1] = static_cast<limb_type>(carry & ~static_cast<limb_type>(0));
   carry >>= limb_bits;
   carry += x * z;
   pr[2] = static_cast<limb_type>(carry & ~static_cast<limb_type>(0));
   pr[3] = static_cast<limb_type>(carry >> limb_bits);
#else
   pr[0] = static_cast<limb_type>(carry);
   carry >>= limb_bits;
   carry += w * z + x * y;
   pr[1] = static_cast<limb_type>(carry);
   carry >>= limb_bits;
   carry += x * z;
   pr[2] = static_cast<limb_type>(carry);
   pr[3] = static_cast<limb_type>(carry >> limb_bits);
#endif
   result.sign(s);
   result.normalize();
}

template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
    !is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value>::type
eval_multiply(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& result,
    double_limb_type a, double_limb_type b)
{
   constexpr const signed_double_limb_type mask = ~static_cast<limb_type>(0);
   constexpr const std::size_t limb_bits = sizeof(limb_type) * CHAR_BIT;

   double_limb_type w = a & mask;
   double_limb_type x = a >> limb_bits;
   double_limb_type y = b & mask;
   double_limb_type z = b >> limb_bits;

   result.resize(4, 4);
   limb_type* pr = result.limbs();

   double_limb_type carry = w * y;
#ifdef __MSVC_RUNTIME_CHECKS
   pr[0] = static_cast<limb_type>(carry & ~static_cast<limb_type>(0));
   carry >>= limb_bits;
   carry += w * z;
   pr[1] = static_cast<limb_type>(carry & ~static_cast<limb_type>(0));
   carry >>= limb_bits;
   pr[2] = static_cast<limb_type>(carry & ~static_cast<limb_type>(0));
   carry = x * y + pr[1];
   pr[1] = static_cast<limb_type>(carry & ~static_cast<limb_type>(0));
   carry >>= limb_bits;
   carry += pr[2] + x * z;
   pr[2] = static_cast<limb_type>(carry & ~static_cast<limb_type>(0));
   pr[3] = static_cast<limb_type>(carry >> limb_bits);
#else
   pr[0] = static_cast<limb_type>(carry);
   carry >>= limb_bits;
   carry += w * z;
   pr[1] = static_cast<limb_type>(carry);
   carry >>= limb_bits;
   pr[2] = static_cast<limb_type>(carry);
   carry = x * y + pr[1];
   pr[1] = static_cast<limb_type>(carry);
   carry >>= limb_bits;
   carry += pr[2] + x * z;
   pr[2] = static_cast<limb_type>(carry);
   pr[3] = static_cast<limb_type>(carry >> limb_bits);
#endif
   result.sign(false);
   result.normalize();
}

template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1,
          std::size_t MinBits2, std::size_t MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
    !is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && is_trivial_cpp_int<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value && is_trivial_cpp_int<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value>::type
eval_multiply(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> const& a,
    cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> const& b)
{
   using canonical_type = typename boost::multiprecision::detail::canonical<typename cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>::local_limb_type, cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::type;
   eval_multiply(result, static_cast<canonical_type>(*a.limbs()), static_cast<canonical_type>(*b.limbs()));
   result.sign(a.sign() != b.sign());
}

template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, class SI>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<boost::multiprecision::detail::is_signed<SI>::value && boost::multiprecision::detail::is_integral<SI>::value && (sizeof(SI) <= sizeof(signed_double_limb_type) / 2)>::type
eval_multiply(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& result,
    SI a, SI b)
{
   result = static_cast<signed_double_limb_type>(a) * static_cast<signed_double_limb_type>(b);
}

template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, class UI>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<boost::multiprecision::detail::is_unsigned<UI>::value && (sizeof(UI) <= sizeof(signed_double_limb_type) / 2)>::type
eval_multiply(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& result,
    UI a, UI b)
{
   result = static_cast<double_limb_type>(a) * static_cast<double_limb_type>(b);
}

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

}}} // namespace boost::multiprecision::backends

#endif

/* multiply.hpp
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
*/