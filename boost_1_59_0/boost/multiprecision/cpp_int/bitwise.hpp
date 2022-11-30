///////////////////////////////////////////////////////////////
//  Copyright 2012 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt
//
// Comparison operators for cpp_int_backend:
//
#ifndef BOOST_MP_CPP_INT_BIT_HPP
#define BOOST_MP_CPP_INT_BIT_HPP

#include <stdexcept>
#include <type_traits>
#include <boost/multiprecision/detail/endian.hpp>
#include <boost/multiprecision/detail/no_exceptions_support.hpp>
#include <boost/multiprecision/detail/assert.hpp>

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable : 4319)
#endif


namespace boost { namespace multiprecision { namespace backends {

template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, std::size_t MinBits2, std::size_t MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2>
BOOST_MP_CXX14_CONSTEXPR void is_valid_bitwise_op(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>& o, const std::integral_constant<int, checked>&)
{
   if (result.sign() || o.sign())
      BOOST_MP_THROW_EXCEPTION(std::range_error("Bitwise operations on negative values results in undefined behavior."));
}

template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, std::size_t MinBits2, std::size_t MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2>
BOOST_MP_CXX14_CONSTEXPR void is_valid_bitwise_op(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&,
    const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>&, const std::integral_constant<int, unchecked>&) {}

template <std::size_t MinBits1, std::size_t MaxBits1, cpp_int_check_type Checked1, class Allocator1>
BOOST_MP_CXX14_CONSTEXPR void is_valid_bitwise_op(
    const cpp_int_backend<MinBits1, MaxBits1, signed_magnitude, Checked1, Allocator1>& result, const std::integral_constant<int, checked>&)
{
   if (result.sign())
      BOOST_MP_THROW_EXCEPTION(std::range_error("Bitwise operations on negative values results in undefined behavior."));
}

template <std::size_t MinBits1, std::size_t MaxBits1, cpp_int_check_type Checked1, class Allocator1>
BOOST_MP_CXX14_CONSTEXPR void is_valid_bitwise_op(
    const cpp_int_backend<MinBits1, MaxBits1, unsigned_magnitude, Checked1, Allocator1>&, const std::integral_constant<int, checked>&) {}

template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
BOOST_MP_CXX14_CONSTEXPR void is_valid_bitwise_op(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&, const std::integral_constant<int, unchecked>&) {}

template <class CppInt1, class CppInt2, class Op>
BOOST_MP_CXX14_CONSTEXPR void bitwise_op(
    CppInt1&       result,
    const CppInt2& o,
    Op             op, const std::integral_constant<bool, true>&) noexcept((is_non_throwing_cpp_int<CppInt1>::value))
{
   //
   // There are 4 cases:
   // * Both positive.
   // * result negative, o positive.
   // * o negative, result positive.
   // * Both negative.
   //
   // When one arg is negative we convert to 2's complement form "on the fly",
   // and then convert back to signed-magnitude form at the end.
   //
   // Note however, that if the type is checked, then bitwise ops on negative values
   // are not permitted and an exception will result.
   //
   is_valid_bitwise_op(result, o, typename CppInt1::checked_type());
   //
   // First figure out how big the result needs to be and set up some data:
   //
   std::size_t rs = result.size();
   std::size_t os = o.size();
   std::size_t m(0), x(0);
   minmax(rs, os, m, x);
   result.resize(x, x);
   typename CppInt1::limb_pointer       pr = result.limbs();
   typename CppInt2::const_limb_pointer po = o.limbs();
   for (std::size_t i = rs; i < x; ++i)
      pr[i] = 0;

   limb_type next_limb = 0;

   if (!result.sign())
   {
      if (!o.sign())
      {
         for (std::size_t i = 0; i < os; ++i)
            pr[i] = op(pr[i], po[i]);
         for (std::size_t i = os; i < x; ++i)
            pr[i] = op(pr[i], limb_type(0));
      }
      else
      {
         // "o" is negative:
         double_limb_type carry = 1;
         for (std::size_t i = 0; i < os; ++i)
         {
            carry += static_cast<double_limb_type>(~po[i]);
            pr[i] = op(pr[i], static_cast<limb_type>(carry));
            carry >>= CppInt1::limb_bits;
         }
         for (std::size_t i = os; i < x; ++i)
         {
            carry += static_cast<double_limb_type>(~limb_type(0));
            pr[i] = op(pr[i], static_cast<limb_type>(carry));
            carry >>= CppInt1::limb_bits;
         }
         // Set the overflow into the "extra" limb:
         carry += static_cast<double_limb_type>(~limb_type(0));
         next_limb = op(limb_type(0), static_cast<limb_type>(carry));
      }
   }
   else
   {
      if (!o.sign())
      {
         // "result" is negative:
         double_limb_type carry = 1;
         for (std::size_t i = 0; i < os; ++i)
         {
            carry += static_cast<double_limb_type>(~pr[i]);
            pr[i] = op(static_cast<limb_type>(carry), po[i]);
            carry >>= CppInt1::limb_bits;
         }
         for (std::size_t i = os; i < x; ++i)
         {
            carry += static_cast<double_limb_type>(~pr[i]);
            pr[i] = op(static_cast<limb_type>(carry), limb_type(0));
            carry >>= CppInt1::limb_bits;
         }
         // Set the overflow into the "extra" limb:
         carry += static_cast<double_limb_type>(~limb_type(0));
         next_limb = op(static_cast<limb_type>(carry), limb_type(0));
      }
      else
      {
         // both are negative:
         double_limb_type r_carry = 1;
         double_limb_type o_carry = 1;
         for (std::size_t i = 0; i < os; ++i)
         {
            r_carry += static_cast<double_limb_type>(~pr[i]);
            o_carry += static_cast<double_limb_type>(~po[i]);
            pr[i] = op(static_cast<limb_type>(r_carry), static_cast<limb_type>(o_carry));
            r_carry >>= CppInt1::limb_bits;
            o_carry >>= CppInt1::limb_bits;
         }
         for (std::size_t i = os; i < x; ++i)
         {
            r_carry += static_cast<double_limb_type>(~pr[i]);
            o_carry += static_cast<double_limb_type>(~limb_type(0));
            pr[i] = op(static_cast<limb_type>(r_carry), static_cast<limb_type>(o_carry));
            r_carry >>= CppInt1::limb_bits;
            o_carry >>= CppInt1::limb_bits;
         }
         // Set the overflow into the "extra" limb:
         r_carry += static_cast<double_limb_type>(~limb_type(0));
         o_carry += static_cast<double_limb_type>(~limb_type(0));
         next_limb = op(static_cast<limb_type>(r_carry), static_cast<limb_type>(o_carry));
      }
   }
   //
   // See if the result is negative or not:
   //
   if (static_cast<signed_limb_type>(next_limb) < 0)
   {
      double_limb_type carry = 1;
      for (std::size_t i = 0; i < x; ++i)
      {
         carry += static_cast<double_limb_type>(~pr[i]);
         pr[i] = static_cast<limb_type>(carry);
         carry >>= CppInt1::limb_bits;
      }
      if (carry)
      {
         result.resize(x + 1, x);
         if (result.size() > x)
            result.limbs()[x] = static_cast<limb_type>(carry);
      }
      result.sign(true);
   }
   else
      result.sign(false);

   result.normalize();
}

template <class CppInt1, class CppInt2, class Op>
BOOST_MP_CXX14_CONSTEXPR void bitwise_op(
    CppInt1&       result,
    const CppInt2& o,
    Op             op, const std::integral_constant<bool, false>&) noexcept((is_non_throwing_cpp_int<CppInt1>::value))
{
   //
   // Both arguments are unsigned types, very simple case handled as a special case.
   //
   // First figure out how big the result needs to be and set up some data:
   //
   std::size_t rs = result.size();
   std::size_t os = o.size();
   std::size_t m(0), x(0);
   minmax(rs, os, m, x);
   result.resize(x, x);
   typename CppInt1::limb_pointer       pr = result.limbs();
   typename CppInt2::const_limb_pointer po = o.limbs();
   for (std::size_t i = rs; i < x; ++i)
      pr[i] = 0;

   for (std::size_t i = 0; i < os; ++i)
      pr[i] = op(pr[i], po[i]);
   for (std::size_t i = os; i < x; ++i)
      pr[i] = op(pr[i], limb_type(0));

   result.normalize();
}

struct bit_and
{
   BOOST_MP_CXX14_CONSTEXPR limb_type operator()(limb_type a, limb_type b) const noexcept { return a & b; }
};
struct bit_or
{
   BOOST_MP_CXX14_CONSTEXPR limb_type operator()(limb_type a, limb_type b) const noexcept { return a | b; }
};
struct bit_xor
{
   BOOST_MP_CXX14_CONSTEXPR limb_type operator()(limb_type a, limb_type b) const noexcept { return a ^ b; }
};

template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, std::size_t MinBits2, std::size_t MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && !is_trivial_cpp_int<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value>::type
eval_bitwise_and(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>& o) noexcept((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   bitwise_op(result, o, bit_and(),
              std::integral_constant<bool, std::numeric_limits<number<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> > >::is_signed || std::numeric_limits<number<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> > >::is_signed > ());
}

template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, std::size_t MinBits2, std::size_t MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && !is_trivial_cpp_int<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value>::type
eval_bitwise_or(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>& o) noexcept((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   bitwise_op(result, o, bit_or(),
              std::integral_constant<bool, std::numeric_limits<number<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> > >::is_signed || std::numeric_limits<number<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> > >::is_signed > ());
}

template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, std::size_t MinBits2, std::size_t MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && !is_trivial_cpp_int<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value>::type
eval_bitwise_xor(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>& o) noexcept((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   bitwise_op(result, o, bit_xor(),
              std::integral_constant<bool, std::numeric_limits<number<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> > >::is_signed || std::numeric_limits<number<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> > >::is_signed > ());
}
//
// Again for operands which are single limbs:
//
template <std::size_t MinBits1, std::size_t MaxBits1, cpp_int_check_type Checked1, class Allocator1>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, unsigned_magnitude, Checked1, Allocator1> >::value>::type
eval_bitwise_and(
    cpp_int_backend<MinBits1, MaxBits1, unsigned_magnitude, Checked1, Allocator1>& result,
    limb_type                                                                      l) noexcept
{
   result.limbs()[0] &= l;
   result.resize(1, 1);
}

template <std::size_t MinBits1, std::size_t MaxBits1, cpp_int_check_type Checked1, class Allocator1>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, unsigned_magnitude, Checked1, Allocator1> >::value>::type
eval_bitwise_or(
    cpp_int_backend<MinBits1, MaxBits1, unsigned_magnitude, Checked1, Allocator1>& result,
    limb_type                                                                      l) noexcept
{
   result.limbs()[0] |= l;
}

template <std::size_t MinBits1, std::size_t MaxBits1, cpp_int_check_type Checked1, class Allocator1>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, unsigned_magnitude, Checked1, Allocator1> >::value>::type
eval_bitwise_xor(
    cpp_int_backend<MinBits1, MaxBits1, unsigned_magnitude, Checked1, Allocator1>& result,
    limb_type                                                                      l) noexcept
{
   result.limbs()[0] ^= l;
}

template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, std::size_t MinBits2, std::size_t MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_signed_number<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && !is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && !is_trivial_cpp_int<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value>::type
eval_complement(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>& o) noexcept((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   static_assert(((Checked1 != checked) || (Checked2 != checked)), "Attempt to take the complement of a signed type results in undefined behavior.");
   // Increment and negate:
   result = o;
   eval_increment(result);
   result.negate();
}

template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_unsigned_number<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && !is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && !is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value>::type
eval_complement(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& o) noexcept((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   std::size_t os = o.size();
   result.resize(SIZE_MAX, os);
   for (std::size_t i = 0; i < os; ++i)
      result.limbs()[i] = ~o.limbs()[i];
   for (std::size_t i = os; i < result.size(); ++i)
      result.limbs()[i] = ~static_cast<limb_type>(0);
   result.normalize();
}

template <class Int>
inline void left_shift_byte(Int& result, double_limb_type s)
{
   limb_type offset = static_cast<limb_type>(s / Int::limb_bits);
   limb_type shift  = static_cast<limb_type>(s % Int::limb_bits);
   std::size_t  ors    = result.size();
   if ((ors == 1) && (!*result.limbs()))
      return; // shifting zero yields zero.
   std::size_t rs = ors;
   if (shift && (result.limbs()[ors - 1] >> (Int::limb_bits - shift)))
      ++rs; // Most significant limb will overflow when shifted
   rs += offset;
   result.resize(rs, rs);
   rs = result.size();

   typename Int::limb_pointer pr = result.limbs();

   if (rs != ors)
      pr[rs - 1] = 0u;
   std::size_t bytes = static_cast<std::size_t>(s / CHAR_BIT);
   std::size_t len   = (std::min)(ors * sizeof(limb_type), rs * sizeof(limb_type) - bytes);
   if (bytes >= rs * sizeof(limb_type))
      result = static_cast<limb_type>(0u);
   else
   {
      unsigned char* pc = reinterpret_cast<unsigned char*>(pr);
      std::memmove(pc + bytes, pc, len);
      std::memset(pc, 0, bytes);
   }
}

template <class Int>
inline BOOST_MP_CXX14_CONSTEXPR void left_shift_limb(Int& result, double_limb_type s)
{
   limb_type offset = static_cast<limb_type>(s / Int::limb_bits);
   limb_type shift  = static_cast<limb_type>(s % Int::limb_bits);

   std::size_t ors = result.size();
   if ((ors == 1) && (!*result.limbs()))
      return; // shifting zero yields zero.
   std::size_t rs = ors;
   if (shift && (result.limbs()[ors - 1] >> (Int::limb_bits - shift)))
      ++rs; // Most significant limb will overflow when shifted
   rs += offset;
   result.resize(rs, rs);

   typename Int::limb_pointer pr = result.limbs();

   if (offset > rs)
   {
      // The result is shifted past the end of the result:
      result = static_cast<limb_type>(0);
      return;
   }

   std::size_t i = rs - result.size();
   for (; i < ors; ++i)
      pr[rs - 1 - i] = pr[ors - 1 - i];
#ifndef BOOST_MP_NO_CONSTEXPR_DETECTION
   if (BOOST_MP_IS_CONST_EVALUATED(s))
   {
      for (; i < rs; ++i)
         pr[rs - 1 - i] = 0;
   }
   else
#endif
   {
      std::memset(pr, 0, (rs - i) * sizeof(*pr));
   }
}

template <class Int>
inline BOOST_MP_CXX14_CONSTEXPR void left_shift_generic(Int& result, double_limb_type s)
{
   limb_type offset = static_cast<limb_type>(s / Int::limb_bits);
   limb_type shift  = static_cast<limb_type>(s % Int::limb_bits);

   std::size_t ors = result.size();
   if ((ors == 1) && (!*result.limbs()))
      return; // shifting zero yields zero.
   std::size_t rs = ors;
   if (shift && (result.limbs()[ors - 1] >> (Int::limb_bits - shift)))
      ++rs; // Most significant limb will overflow when shifted
   rs += offset;
   result.resize(rs, rs);
   bool truncated = result.size() != rs;

   typename Int::limb_pointer pr = result.limbs();

   if (offset > rs)
   {
      // The result is shifted past the end of the result:
      result = static_cast<limb_type>(0);
      return;
   }

   std::size_t i = rs - result.size();
   // This code only works when shift is non-zero, otherwise we invoke undefined behaviour!
   BOOST_MP_ASSERT(shift);
   if (!truncated)
   {
      if (rs > ors + offset)
      {
         pr[rs - 1 - i] = pr[ors - 1 - i] >> (Int::limb_bits - shift);
         --rs;
      }
      else
      {
         pr[rs - 1 - i] = pr[ors - 1 - i] << shift;
         if (ors > 1)
            pr[rs - 1 - i] |= pr[ors - 2 - i] >> (Int::limb_bits - shift);
         ++i;
      }
   }
   for (; rs - i >= 2 + offset; ++i)
   {
      pr[rs - 1 - i] = pr[rs - 1 - i - offset] << shift;
      pr[rs - 1 - i] |= pr[rs - 2 - i - offset] >> (Int::limb_bits - shift);
   }
   if (rs - i >= 1 + offset)
   {
      pr[rs - 1 - i] = pr[rs - 1 - i - offset] << shift;
      ++i;
   }
#ifndef BOOST_MP_NO_CONSTEXPR_DETECTION
   if (BOOST_MP_IS_CONST_EVALUATED(s))
   {
      for (; i < rs; ++i)
         pr[rs - 1 - i] = 0;
   }
   else
#endif
   {
      std::memset(pr, 0, (rs - i) * sizeof(*pr));
   }
}

template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value>::type
eval_left_shift(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& result,
    double_limb_type                                                      s) noexcept((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   is_valid_bitwise_op(result, typename cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::checked_type());
   if (!s)
      return;

#if BOOST_MP_ENDIAN_LITTLE_BYTE && defined(BOOST_MP_USE_LIMB_SHIFT)
   constexpr const limb_type limb_shift_mask = cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::limb_bits - 1;
   constexpr const limb_type byte_shift_mask = CHAR_BIT - 1;

   if ((s & limb_shift_mask) == 0)
   {
      left_shift_limb(result, s);
   }
#ifdef BOOST_MP_NO_CONSTEXPR_DETECTION
   else if ((s & byte_shift_mask) == 0)
#else
   else if (((s & byte_shift_mask) == 0) && !BOOST_MP_IS_CONST_EVALUATED(s))
#endif
   {
      left_shift_byte(result, s);
   }
#elif BOOST_MP_ENDIAN_LITTLE_BYTE
   constexpr const limb_type byte_shift_mask = CHAR_BIT - 1;

#ifdef BOOST_MP_NO_CONSTEXPR_DETECTION
   if ((s & byte_shift_mask) == 0)
#else
   constexpr limb_type limb_shift_mask = cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::limb_bits - 1;
   if (BOOST_MP_IS_CONST_EVALUATED(s) && ((s & limb_shift_mask) == 0))
      left_shift_limb(result, s);
   else if (((s & byte_shift_mask) == 0) && !BOOST_MP_IS_CONST_EVALUATED(s))
#endif
   {
      left_shift_byte(result, s);
   }
#else
   constexpr const limb_type limb_shift_mask = cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::limb_bits - 1;

   if ((s & limb_shift_mask) == 0)
   {
      left_shift_limb(result, s);
   }
#endif
   else
   {
      left_shift_generic(result, s);
   }
   //
   // We may have shifted off the end and have leading zeros:
   //
   result.normalize();
}

template <class Int>
inline void right_shift_byte(Int& result, double_limb_type s)
{
   limb_type offset = static_cast<limb_type>(s / Int::limb_bits);
   BOOST_MP_ASSERT((s % CHAR_BIT) == 0);
   std::size_t ors = result.size();
   std::size_t rs  = ors;
   if (offset >= rs)
   {
      result = limb_type(0);
      return;
   }
   rs -= offset;
   typename Int::limb_pointer pr = result.limbs();
   unsigned char*             pc = reinterpret_cast<unsigned char*>(pr);
   limb_type                  shift = static_cast<limb_type>(s / CHAR_BIT);
   std::memmove(pc, pc + shift, ors * sizeof(pr[0]) - shift);
   shift = (sizeof(limb_type) - shift % sizeof(limb_type)) * CHAR_BIT;
   if (shift < Int::limb_bits)
   {
      pr[ors - offset - 1] &= (static_cast<limb_type>(1u) << shift) - 1;
      if (!pr[ors - offset - 1] && (rs > 1))
         --rs;
   }
   result.resize(rs, rs);
}

template <class Int>
inline BOOST_MP_CXX14_CONSTEXPR void right_shift_limb(Int& result, double_limb_type s)
{
   limb_type offset = static_cast<limb_type>(s / Int::limb_bits);
   BOOST_MP_ASSERT((s % Int::limb_bits) == 0);
   std::size_t ors = result.size();
   std::size_t rs  = ors;
   if (offset >= rs)
   {
      result = limb_type(0);
      return;
   }
   rs -= offset;
   typename Int::limb_pointer pr = result.limbs();
   std::size_t                   i  = 0;
   for (; i < rs; ++i)
      pr[i] = pr[i + offset];
   result.resize(rs, rs);
}

template <class Int>
inline BOOST_MP_CXX14_CONSTEXPR void right_shift_generic(Int& result, double_limb_type s)
{
   limb_type offset = static_cast<limb_type>(s / Int::limb_bits);
   limb_type shift  = static_cast<limb_type>(s % Int::limb_bits);
   std::size_t  ors    = result.size();
   std::size_t  rs     = ors;
   if (offset >= rs)
   {
      result = limb_type(0);
      return;
   }
   rs -= offset;
   typename Int::limb_pointer pr = result.limbs();
   if ((pr[ors - 1] >> shift) == 0)
   {
      if (--rs == 0)
      {
         result = limb_type(0);
         return;
      }
   }
   std::size_t i = 0;

   // This code only works for non-zero shift, otherwise we invoke undefined behaviour!
   BOOST_MP_ASSERT(shift);
   for (; i + offset + 1 < ors; ++i)
   {
      pr[i] = pr[i + offset] >> shift;
      pr[i] |= pr[i + offset + 1] << (Int::limb_bits - shift);
   }
   pr[i] = pr[i + offset] >> shift;
   result.resize(rs, rs);
}

template <std::size_t MinBits1, std::size_t MaxBits1, cpp_int_check_type Checked1, class Allocator1>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, unsigned_magnitude, Checked1, Allocator1> >::value>::type
eval_right_shift(
    cpp_int_backend<MinBits1, MaxBits1, unsigned_magnitude, Checked1, Allocator1>& result,
    double_limb_type                                                               s) noexcept((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, unsigned_magnitude, Checked1, Allocator1> >::value))
{
   is_valid_bitwise_op(result, typename cpp_int_backend<MinBits1, MaxBits1, unsigned_magnitude, Checked1, Allocator1>::checked_type());
   if (!s)
      return;

#if BOOST_MP_ENDIAN_LITTLE_BYTE && defined(BOOST_MP_USE_LIMB_SHIFT)
   constexpr const limb_type limb_shift_mask = cpp_int_backend<MinBits1, MaxBits1, signed_magnitude, Checked1, Allocator1>::limb_bits - 1;
   constexpr const limb_type byte_shift_mask = CHAR_BIT - 1;

   if ((s & limb_shift_mask) == 0)
      right_shift_limb(result, s);
#ifdef BOOST_MP_NO_CONSTEXPR_DETECTION
   else if ((s & byte_shift_mask) == 0)
#else
   else if (((s & byte_shift_mask) == 0) && !BOOST_MP_IS_CONST_EVALUATED(s))
#endif
      right_shift_byte(result, s);
#elif BOOST_MP_ENDIAN_LITTLE_BYTE
   constexpr const limb_type byte_shift_mask = CHAR_BIT - 1;

#ifdef BOOST_MP_NO_CONSTEXPR_DETECTION
   if ((s & byte_shift_mask) == 0)
#else
   constexpr limb_type limb_shift_mask = cpp_int_backend<MinBits1, MaxBits1, signed_magnitude, Checked1, Allocator1>::limb_bits - 1;
   if (BOOST_MP_IS_CONST_EVALUATED(s) && ((s & limb_shift_mask) == 0))
      right_shift_limb(result, s);
   else if (((s & byte_shift_mask) == 0) && !BOOST_MP_IS_CONST_EVALUATED(s))
#endif
      right_shift_byte(result, s);
#else
   constexpr const limb_type limb_shift_mask = cpp_int_backend<MinBits1, MaxBits1, signed_magnitude, Checked1, Allocator1>::limb_bits - 1;

   if ((s & limb_shift_mask) == 0)
      right_shift_limb(result, s);
#endif
   else
      right_shift_generic(result, s);
}
template <std::size_t MinBits1, std::size_t MaxBits1, cpp_int_check_type Checked1, class Allocator1>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, signed_magnitude, Checked1, Allocator1> >::value>::type
eval_right_shift(
    cpp_int_backend<MinBits1, MaxBits1, signed_magnitude, Checked1, Allocator1>& result,
    double_limb_type                                                             s) noexcept((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, signed_magnitude, Checked1, Allocator1> >::value))
{
   is_valid_bitwise_op(result, typename cpp_int_backend<MinBits1, MaxBits1, signed_magnitude, Checked1, Allocator1>::checked_type());
   if (!s)
      return;

   bool is_neg = result.sign();
   if (is_neg)
      eval_increment(result);

#if BOOST_MP_ENDIAN_LITTLE_BYTE && defined(BOOST_MP_USE_LIMB_SHIFT)
   constexpr const limb_type limb_shift_mask = cpp_int_backend<MinBits1, MaxBits1, signed_magnitude, Checked1, Allocator1>::limb_bits - 1;
   constexpr const limb_type byte_shift_mask = CHAR_BIT - 1;

   if ((s & limb_shift_mask) == 0)
      right_shift_limb(result, s);
#ifdef BOOST_MP_NO_CONSTEXPR_DETECTION
   else if ((s & byte_shift_mask) == 0)
#else
   else if (((s & byte_shift_mask) == 0) && !BOOST_MP_IS_CONST_EVALUATED(s))
#endif
      right_shift_byte(result, s);
#elif BOOST_MP_ENDIAN_LITTLE_BYTE
   constexpr const limb_type byte_shift_mask = CHAR_BIT - 1;

#ifdef BOOST_MP_NO_CONSTEXPR_DETECTION
   if ((s & byte_shift_mask) == 0)
#else
   constexpr limb_type limb_shift_mask = cpp_int_backend<MinBits1, MaxBits1, signed_magnitude, Checked1, Allocator1>::limb_bits - 1;
   if (BOOST_MP_IS_CONST_EVALUATED(s) && ((s & limb_shift_mask) == 0))
      right_shift_limb(result, s);
   else if (((s & byte_shift_mask) == 0) && !BOOST_MP_IS_CONST_EVALUATED(s))
#endif
      right_shift_byte(result, s);
#else
   constexpr const limb_type limb_shift_mask = cpp_int_backend<MinBits1, MaxBits1, signed_magnitude, Checked1, Allocator1>::limb_bits - 1;

   if ((s & limb_shift_mask) == 0)
      right_shift_limb(result, s);
#endif
   else
      right_shift_generic(result, s);
   if (is_neg)
      eval_decrement(result);
}

//
// Over again for trivial cpp_int's:
//
template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, class T>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value >::type
eval_left_shift(cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& result, T s) noexcept((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   is_valid_bitwise_op(result, typename cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::checked_type());
   *result.limbs() = detail::checked_left_shift(*result.limbs(), s, typename cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::checked_type());
   result.normalize();
}

template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, class T>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value >::type
eval_right_shift(cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& result, T s) noexcept((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   // Nothing to check here... just make sure we don't invoke undefined behavior:
   is_valid_bitwise_op(result, typename cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::checked_type());
   *result.limbs() = (static_cast<unsigned>(s) >= sizeof(*result.limbs()) * CHAR_BIT) ? 0 : (result.sign() ? ((--*result.limbs()) >> s) + 1 : *result.limbs() >> s);
   if (result.sign() && (*result.limbs() == 0))
      result = static_cast<signed_limb_type>(-1);
}

template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, std::size_t MinBits2, std::size_t MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
    is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && is_trivial_cpp_int<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value && (is_signed_number<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value || is_signed_number<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value)>::type
eval_complement(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>& o) noexcept((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   static_assert(((Checked1 != checked) || (Checked2 != checked)), "Attempt to take the complement of a signed type results in undefined behavior.");
   //
   // If we're not checked then emulate 2's complement behavior:
   //
   if (o.sign())
   {
      *result.limbs() = *o.limbs() - 1;
      result.sign(false);
   }
   else
   {
      *result.limbs() = 1 + *o.limbs();
      result.sign(true);
   }
   result.normalize();
}

template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, std::size_t MinBits2, std::size_t MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
    is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && is_trivial_cpp_int<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value && is_unsigned_number<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && is_unsigned_number<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value>::type
eval_complement(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>& o) noexcept((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   *result.limbs() = ~*o.limbs();
   result.normalize();
}

template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, std::size_t MinBits2, std::size_t MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
    is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && is_trivial_cpp_int<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value && is_unsigned_number<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && is_unsigned_number<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value>::type
eval_bitwise_and(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>& o) noexcept((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   *result.limbs() &= *o.limbs();
}

template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, std::size_t MinBits2, std::size_t MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
    is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && is_trivial_cpp_int<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value && (is_signed_number<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value || is_signed_number<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value)>::type
eval_bitwise_and(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>& o) noexcept((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   is_valid_bitwise_op(result, o, typename cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::checked_type());

   using default_ops::eval_bit_test;
   using default_ops::eval_increment;

   if (result.sign() || o.sign())
   {
      constexpr const std::size_t m = detail::static_unsigned_max<detail::static_unsigned_max<MinBits1, MinBits2>::value, detail::static_unsigned_max<MaxBits1, MaxBits2>::value>::value;
      cpp_int_backend<m + 1, m + 1, unsigned_magnitude, unchecked, void> t1(result);
      cpp_int_backend<m + 1, m + 1, unsigned_magnitude, unchecked, void> t2(o);
      eval_bitwise_and(t1, t2);
      bool s = eval_bit_test(t1, m + 1);
      if (s)
      {
         eval_complement(t1, t1);
         eval_increment(t1);
      }
      result = t1;
      result.sign(s);
   }
   else
   {
      *result.limbs() &= *o.limbs();
   }
}

template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, std::size_t MinBits2, std::size_t MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
    is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && is_trivial_cpp_int<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value && is_unsigned_number<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && is_unsigned_number<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value>::type
eval_bitwise_or(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>& o) noexcept((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   *result.limbs() |= *o.limbs();
}

template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, std::size_t MinBits2, std::size_t MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
    is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && is_trivial_cpp_int<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value && (is_signed_number<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value || is_signed_number<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value)>::type
eval_bitwise_or(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>& o) noexcept((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   is_valid_bitwise_op(result, o, typename cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::checked_type());

   using default_ops::eval_bit_test;
   using default_ops::eval_increment;

   if (result.sign() || o.sign())
   {
      constexpr const std::size_t m = detail::static_unsigned_max<detail::static_unsigned_max<MinBits1, MinBits2>::value, detail::static_unsigned_max<MaxBits1, MaxBits2>::value>::value;
      cpp_int_backend<m + 1, m + 1, unsigned_magnitude, unchecked, void> t1(result);
      cpp_int_backend<m + 1, m + 1, unsigned_magnitude, unchecked, void> t2(o);
      eval_bitwise_or(t1, t2);
      bool s = eval_bit_test(t1, m + 1);
      if (s)
      {
         eval_complement(t1, t1);
         eval_increment(t1);
      }
      result = t1;
      result.sign(s);
   }
   else
   {
      *result.limbs() |= *o.limbs();
      result.normalize();
   }
}

template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, std::size_t MinBits2, std::size_t MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
    is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && is_trivial_cpp_int<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value && is_unsigned_number<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && is_unsigned_number<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value>::type
eval_bitwise_xor(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>& o) noexcept((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   *result.limbs() ^= *o.limbs();
}

template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, std::size_t MinBits2, std::size_t MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
    is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && is_trivial_cpp_int<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value && (is_signed_number<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value || is_signed_number<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value)>::type
eval_bitwise_xor(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>& o) noexcept((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   is_valid_bitwise_op(result, o, typename cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::checked_type());

   using default_ops::eval_bit_test;
   using default_ops::eval_increment;

   if (result.sign() || o.sign())
   {
      constexpr const std::size_t m = detail::static_unsigned_max<detail::static_unsigned_max<MinBits1, MinBits2>::value, detail::static_unsigned_max<MaxBits1, MaxBits2>::value>::value;
      cpp_int_backend<m + 1, m + 1, unsigned_magnitude, unchecked, void> t1(result);
      cpp_int_backend<m + 1, m + 1, unsigned_magnitude, unchecked, void> t2(o);
      eval_bitwise_xor(t1, t2);
      bool s = eval_bit_test(t1, m + 1);
      if (s)
      {
         eval_complement(t1, t1);
         eval_increment(t1);
      }
      result = t1;
      result.sign(s);
   }
   else
   {
      *result.limbs() ^= *o.limbs();
   }
}

}}} // namespace boost::multiprecision::backends

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif

/* bitwise.hpp
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
*/