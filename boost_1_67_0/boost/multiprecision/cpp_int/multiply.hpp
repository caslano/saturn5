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

#include <boost/multiprecision/integer.hpp>

namespace boost { namespace multiprecision { namespace backends {

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4127) // conditional expression is constant
#endif
//
// Multiplication by a single limb:
//
template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, unsigned MinBits2, unsigned MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && !is_trivial_cpp_int<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value>::type
eval_multiply(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>& a,
    const limb_type&                                                            val) BOOST_MP_NOEXCEPT_IF((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
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
      unsigned i = result.size();
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
template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
inline BOOST_MP_CXX14_CONSTEXPR void resize_for_carry(cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& /*result*/, unsigned /*required*/) {}

template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, class Allocator1>
inline BOOST_MP_CXX14_CONSTEXPR void resize_for_carry(cpp_int_backend<MinBits1, MaxBits1, SignType1, checked, Allocator1>& result, unsigned required)
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
template <unsigned MinBits, unsigned MaxBits, cpp_int_check_type Checked, class Allocator>
inline void multiply_karatsuba(
    cpp_int_backend<MinBits, MaxBits, signed_magnitude, Checked, Allocator>&       result,
    const cpp_int_backend<MinBits, MaxBits, signed_magnitude, Checked, Allocator>& a,
    const cpp_int_backend<MinBits, MaxBits, signed_magnitude, Checked, Allocator>& b,
    typename cpp_int_backend<MinBits, MaxBits, signed_magnitude, Checked, Allocator>::scoped_shared_storage& storage)
{
   typedef cpp_int_backend<MinBits, MaxBits, signed_magnitude, Checked, Allocator> cpp_int_type;

   unsigned as = a.size();
   unsigned bs = b.size();
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
   unsigned n  = (as > bs ? as : bs) / 2 + 1;
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
   unsigned          sz = (std::min)(as, n);
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
   for (unsigned i = result_low.size(); i < 2 * n; ++i)
      result.limbs()[i] = 0;
   //
   // Set the high part of result to a_h * b_h:
   //
   multiply_karatsuba(result_high, a_h, b_h, storage);
   for (unsigned i = result_high.size() + 2 * n; i < result.size(); ++i)
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

inline unsigned karatsuba_storage_size(unsigned s)
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
template <unsigned MinBits, unsigned MaxBits, cpp_integer_type SignType, cpp_int_check_type Checked, class Allocator>
inline typename enable_if_c<!is_fixed_precision<cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator> >::value>::type
setup_karatsuba(
   cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>& result,
   const cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>& a,
   const cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>& b)
{
   unsigned as = a.size();
   unsigned bs = b.size();
   unsigned s = as > bs ? as : bs;
   unsigned storage_size = karatsuba_storage_size(s);
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

template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, unsigned MinBits2, unsigned MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2, unsigned MinBits3, unsigned MaxBits3, cpp_integer_type SignType3, cpp_int_check_type Checked3, class Allocator3>
inline typename enable_if_c<is_fixed_precision<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value || is_fixed_precision<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value || is_fixed_precision<cpp_int_backend<MinBits3, MaxBits3, SignType3, Checked3, Allocator3> >::value>::type
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
   typedef cpp_int_backend<0, 0, signed_magnitude, unchecked, std::allocator<limb_type> > variable_precision_type;
   variable_precision_type a_t(a.limbs(), 0, a.size()), b_t(b.limbs(), 0, b.size());
   unsigned as = a.size();
   unsigned bs = b.size();
   unsigned s = as > bs ? as : bs;
   unsigned sz = as + bs;
   unsigned storage_size = karatsuba_storage_size(s);

   if (sz * sizeof(limb_type) * CHAR_BIT <= MaxBits1)
   {
      // Result is large enough for all the bits of the result, so we can use aliasing:
      result.resize(sz, sz);
      variable_precision_type t(result.limbs(), 0, result.size());
      typename variable_precision_type::scoped_shared_storage storage(t.allocator(), storage_size);
      multiply_karatsuba(t, a_t, b_t, storage);
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

template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, unsigned MinBits2, unsigned MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2, unsigned MinBits3, unsigned MaxBits3, cpp_integer_type SignType3, cpp_int_check_type Checked3, class Allocator3>
inline BOOST_MP_CXX14_CONSTEXPR void
eval_multiply_comba(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>& a,
    const cpp_int_backend<MinBits3, MaxBits3, SignType3, Checked3, Allocator3>& b) BOOST_MP_NOEXCEPT_IF((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   // 
   // see PR #182
   // Comba Multiplier - based on Paul Comba's
   // Exponentiation cryptosystems on the IBM PC, 1990
   //
   int as                                                                                         = a.size(),
       bs                                                                                         = b.size(),
       rs                                                                                         = result.size();
   typename cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::limb_pointer pr = result.limbs();

   double_limb_type carry    = 0,
                    temp     = 0;
   limb_type      overflow   = 0;
   const unsigned limb_bits  = sizeof(limb_type) * CHAR_BIT;
   const bool     must_throw = rs < as + bs - 1;
   for (int r = 0, lim = (std::min)(rs, as + bs - 1); r < lim; ++r, overflow = 0)
   {
      int i = r >= as ? as - 1 : r,
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
      if ((int)result.size() >= as + bs)
         *pr = static_cast<limb_type>(carry);
   }
}
template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, unsigned MinBits2, unsigned MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2, unsigned MinBits3, unsigned MaxBits3, cpp_integer_type SignType3, cpp_int_check_type Checked3, class Allocator3>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && !is_trivial_cpp_int<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value && !is_trivial_cpp_int<cpp_int_backend<MinBits3, MaxBits3, SignType3, Checked3, Allocator3> >::value>::type
eval_multiply(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>& a,
    const cpp_int_backend<MinBits3, MaxBits3, SignType3, Checked3, Allocator3>& b) 
   BOOST_MP_NOEXCEPT_IF((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value 
      && (karatsuba_cutoff * sizeof(limb_type) * CHAR_BIT > MaxBits1) 
      && (karatsuba_cutoff * sizeof(limb_type)* CHAR_BIT > MaxBits2) 
      && (karatsuba_cutoff * sizeof(limb_type)* CHAR_BIT > MaxBits3)))
{
   // Uses simple (O(n^2)) multiplication when the limbs are less
   // otherwise switches to karatsuba algorithm based on experimental value (~40 limbs)
   //
   // Trivial cases first:
   //
   unsigned                                                                                          as = a.size();
   unsigned                                                                                          bs = b.size();
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

#ifdef BOOST_NO_CXX14_CONSTEXPR
   static const double_limb_type limb_max        = ~static_cast<limb_type>(0u);
   static const double_limb_type double_limb_max = ~static_cast<double_limb_type>(0u);
#else
   constexpr const double_limb_type limb_max = ~static_cast<limb_type>(0u);
   constexpr const double_limb_type double_limb_max = ~static_cast<double_limb_type>(0u);
#endif
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
   BOOST_STATIC_ASSERT(double_limb_max - 2 * limb_max >= limb_max * limb_max);

#ifndef BOOST_MP_NO_CONSTEXPR_DETECTION
   if (BOOST_MP_IS_CONST_EVALUATED(as))
   {
      for (unsigned i = 0; i < result.size(); ++i)
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
   for (unsigned i = 0; i < as; ++i)
   {
      BOOST_ASSERT(result.size() > i);
      unsigned inner_limit = !is_fixed_precision<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value ? bs : (std::min)(result.size() - i, bs);
      unsigned j           = 0;
      for (; j < inner_limit; ++j)
      {
         BOOST_ASSERT(i + j < result.size());
#if (!defined(__GLIBCXX__) && !defined(__GLIBCPP__)) || !BOOST_WORKAROUND(BOOST_GCC_VERSION, <= 50100)
         BOOST_ASSERT(!std::numeric_limits<double_limb_type>::is_specialized || ((std::numeric_limits<double_limb_type>::max)() - carry >
                                                                                 static_cast<double_limb_type>(cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::max_limb_value) * static_cast<double_limb_type>(cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::max_limb_value)));
#endif
         carry += static_cast<double_limb_type>(pa[i]) * static_cast<double_limb_type>(pb[j]);
         BOOST_ASSERT(!std::numeric_limits<double_limb_type>::is_specialized || ((std::numeric_limits<double_limb_type>::max)() - carry >= pr[i + j]));
         carry += pr[i + j];
#ifdef __MSVC_RUNTIME_CHECKS
         pr[i + j] = static_cast<limb_type>(carry & ~static_cast<limb_type>(0));
#else
         pr[i + j] = static_cast<limb_type>(carry);
#endif
         carry >>= cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::limb_bits;
         BOOST_ASSERT(carry <= (cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::max_limb_value));
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

template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, unsigned MinBits2, unsigned MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && !is_trivial_cpp_int<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value>::type
eval_multiply(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>& a) 
   BOOST_MP_NOEXCEPT_IF((noexcept(eval_multiply(std::declval<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&>(), std::declval<const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&>(), std::declval<const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>&>()))))
{
   eval_multiply(result, result, a);
}

template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value>::type
eval_multiply(cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& result, const limb_type& val) 
   BOOST_MP_NOEXCEPT_IF((noexcept(eval_multiply(std::declval<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&>(), std::declval<const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&>(), std::declval<const limb_type&>()))))
{
   eval_multiply(result, result, val);
}

template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, unsigned MinBits2, unsigned MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && !is_trivial_cpp_int<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value>::type
eval_multiply(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>& a,
    const double_limb_type&                                                     val) 
   BOOST_MP_NOEXCEPT_IF(
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
#if BOOST_ENDIAN_LITTLE_BYTE && !defined(BOOST_MP_TEST_NO_LE)
      cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> t(val);
#else
      cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> t;
      t = val;
#endif
      eval_multiply(result, a, t);
   }
}

template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value>::type
eval_multiply(cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& result, const double_limb_type& val)
   BOOST_MP_NOEXCEPT_IF((noexcept(eval_multiply(std::declval<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&>(), std::declval<const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&>(), std::declval<const double_limb_type&>()))))
{
   eval_multiply(result, result, val);
}

template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, unsigned MinBits2, unsigned MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && !is_trivial_cpp_int<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value>::type
eval_multiply(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>& a,
    const signed_limb_type&                                                     val) 
   BOOST_MP_NOEXCEPT_IF((noexcept(eval_multiply(std::declval<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&>(), std::declval<const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>&>(), std::declval<const limb_type&>()))))
{
   if (val > 0)
      eval_multiply(result, a, static_cast<limb_type>(val));
   else
   {
      eval_multiply(result, a, static_cast<limb_type>(boost::multiprecision::detail::unsigned_abs(val)));
      result.negate();
   }
}

template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value>::type
eval_multiply(cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& result, const signed_limb_type& val)
   BOOST_MP_NOEXCEPT_IF((noexcept(eval_multiply(std::declval<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&>(), std::declval<const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&>(), std::declval<const limb_type&>()))))
{
   eval_multiply(result, result, val);
}

template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, unsigned MinBits2, unsigned MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && !is_trivial_cpp_int<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value>::type
eval_multiply(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>& a,
    const signed_double_limb_type&                                              val)
   BOOST_MP_NOEXCEPT_IF(
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
#if BOOST_ENDIAN_LITTLE_BYTE && !defined(BOOST_MP_TEST_NO_LE)
   cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> t(val);
#else
   cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> t;
   t = val;
#endif
   eval_multiply(result, a, t);
}

template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value>::type
eval_multiply(cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& result, const signed_double_limb_type& val)
   BOOST_MP_NOEXCEPT_IF(
   (noexcept(eval_multiply(std::declval<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&>(), std::declval<const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&>(), std::declval<const limb_type&>())))
   && (noexcept(eval_multiply(std::declval<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&>(), std::declval<const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&>(), std::declval<const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&>())))
   )
{
   eval_multiply(result, result, val);
}

//
// Now over again for trivial cpp_int's:
//
template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<
    is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && (is_signed_number<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value || is_signed_number<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value)>::type
eval_multiply(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& o) BOOST_MP_NOEXCEPT_IF((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   *result.limbs() = detail::checked_multiply(*result.limbs(), *o.limbs(), typename cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::checked_type());
   result.sign(result.sign() != o.sign());
   result.normalize();
}

template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<
    is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && is_unsigned_number<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value>::type
eval_multiply(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& o) BOOST_MP_NOEXCEPT_IF((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   *result.limbs() = detail::checked_multiply(*result.limbs(), *o.limbs(), typename cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::checked_type());
   result.normalize();
}

template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<
    is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && (is_signed_number<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value || is_signed_number<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value)>::type
eval_multiply(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& a,
    const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& b) BOOST_MP_NOEXCEPT_IF((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   *result.limbs() = detail::checked_multiply(*a.limbs(), *b.limbs(), typename cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::checked_type());
   result.sign(a.sign() != b.sign());
   result.normalize();
}

template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<
    is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && is_unsigned_number<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value>::type
eval_multiply(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& a,
    const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& b) BOOST_MP_NOEXCEPT_IF((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   *result.limbs() = detail::checked_multiply(*a.limbs(), *b.limbs(), typename cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::checked_type());
   result.normalize();
}

//
// Special routines for multiplying two integers to obtain a multiprecision result:
//
template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<
    !is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value>::type
eval_multiply(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& result,
    signed_double_limb_type a, signed_double_limb_type b)
{
#ifdef BOOST_NO_CXX14_CONSTEXPR
   static const signed_double_limb_type mask      = ~static_cast<limb_type>(0);
   static const unsigned                limb_bits = sizeof(limb_type) * CHAR_BIT;
#else
   constexpr const signed_double_limb_type mask = ~static_cast<limb_type>(0);
   constexpr const unsigned limb_bits = sizeof(limb_type) * CHAR_BIT;
#endif
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

template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<
    !is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value>::type
eval_multiply(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& result,
    double_limb_type a, double_limb_type b)
{
#ifdef BOOST_NO_CXX14_CONSTEXPR
   static const signed_double_limb_type mask      = ~static_cast<limb_type>(0);
   static const unsigned                limb_bits = sizeof(limb_type) * CHAR_BIT;
#else
   constexpr const signed_double_limb_type mask = ~static_cast<limb_type>(0);
   constexpr const unsigned limb_bits = sizeof(limb_type) * CHAR_BIT;
#endif

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

template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1,
          unsigned MinBits2, unsigned MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<
    !is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && is_trivial_cpp_int<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value && is_trivial_cpp_int<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value>::type
eval_multiply(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> const& a,
    cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> const& b)
{
   typedef typename boost::multiprecision::detail::canonical<typename cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>::local_limb_type, cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::type canonical_type;
   eval_multiply(result, static_cast<canonical_type>(*a.limbs()), static_cast<canonical_type>(*b.limbs()));
   result.sign(a.sign() != b.sign());
}

template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, class SI>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_signed<SI>::value && (sizeof(SI) <= sizeof(signed_double_limb_type) / 2)>::type
eval_multiply(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& result,
    SI a, SI b)
{
   result = static_cast<signed_double_limb_type>(a) * static_cast<signed_double_limb_type>(b);
}

template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, class UI>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_unsigned<UI>::value && (sizeof(UI) <= sizeof(signed_double_limb_type) / 2)>::type
eval_multiply(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& result,
    UI a, UI b)
{
   result = static_cast<double_limb_type>(a) * static_cast<double_limb_type>(b);
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif

}}} // namespace boost::multiprecision::backends

#endif

/* multiply.hpp
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
*/