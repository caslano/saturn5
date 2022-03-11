///////////////////////////////////////////////////////////////
//  Copyright 2012 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt
//
// Comparison operators for cpp_int_backend:
//
#ifndef BOOST_MP_CPP_INT_BIT_HPP
#define BOOST_MP_CPP_INT_BIT_HPP

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4319)
#endif

namespace boost { namespace multiprecision { namespace backends {

template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, unsigned MinBits2, unsigned MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2>
BOOST_MP_CXX14_CONSTEXPR void is_valid_bitwise_op(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>& o, const mpl::int_<checked>&)
{
   if (result.sign() || o.sign())
      BOOST_THROW_EXCEPTION(std::range_error("Bitwise operations on negative values results in undefined behavior."));
}

template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, unsigned MinBits2, unsigned MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2>
BOOST_MP_CXX14_CONSTEXPR void is_valid_bitwise_op(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&,
    const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>&, const mpl::int_<unchecked>&) {}

template <unsigned MinBits1, unsigned MaxBits1, cpp_int_check_type Checked1, class Allocator1>
BOOST_MP_CXX14_CONSTEXPR void is_valid_bitwise_op(
    const cpp_int_backend<MinBits1, MaxBits1, signed_magnitude, Checked1, Allocator1>& result, const mpl::int_<checked>&)
{
   if (result.sign())
      BOOST_THROW_EXCEPTION(std::range_error("Bitwise operations on negative values results in undefined behavior."));
}

template <unsigned MinBits1, unsigned MaxBits1, cpp_int_check_type Checked1, class Allocator1>
BOOST_MP_CXX14_CONSTEXPR void is_valid_bitwise_op(
    const cpp_int_backend<MinBits1, MaxBits1, unsigned_magnitude, Checked1, Allocator1>&, const mpl::int_<checked>&) {}

template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
BOOST_MP_CXX14_CONSTEXPR void is_valid_bitwise_op(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&, const mpl::int_<unchecked>&) {}

template <class CppInt1, class CppInt2, class Op>
BOOST_MP_CXX14_CONSTEXPR void bitwise_op(
    CppInt1&       result,
    const CppInt2& o,
    Op             op, const mpl::true_&) BOOST_MP_NOEXCEPT_IF((is_non_throwing_cpp_int<CppInt1>::value))
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
   unsigned rs = result.size();
   unsigned os = o.size();
   unsigned m(0), x(0);
   minmax(rs, os, m, x);
   result.resize(x, x);
   typename CppInt1::limb_pointer       pr = result.limbs();
   typename CppInt2::const_limb_pointer po = o.limbs();
   for (unsigned i = rs; i < x; ++i)
      pr[i] = 0;

   limb_type next_limb = 0;

   if (!result.sign())
   {
      if (!o.sign())
      {
         for (unsigned i = 0; i < os; ++i)
            pr[i] = op(pr[i], po[i]);
         for (unsigned i = os; i < x; ++i)
            pr[i] = op(pr[i], limb_type(0));
      }
      else
      {
         // "o" is negative:
         double_limb_type carry = 1;
         for (unsigned i = 0; i < os; ++i)
         {
            carry += static_cast<double_limb_type>(~po[i]);
            pr[i] = op(pr[i], static_cast<limb_type>(carry));
            carry >>= CppInt1::limb_bits;
         }
         for (unsigned i = os; i < x; ++i)
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
         for (unsigned i = 0; i < os; ++i)
         {
            carry += static_cast<double_limb_type>(~pr[i]);
            pr[i] = op(static_cast<limb_type>(carry), po[i]);
            carry >>= CppInt1::limb_bits;
         }
         for (unsigned i = os; i < x; ++i)
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
         for (unsigned i = 0; i < os; ++i)
         {
            r_carry += static_cast<double_limb_type>(~pr[i]);
            o_carry += static_cast<double_limb_type>(~po[i]);
            pr[i] = op(static_cast<limb_type>(r_carry), static_cast<limb_type>(o_carry));
            r_carry >>= CppInt1::limb_bits;
            o_carry >>= CppInt1::limb_bits;
         }
         for (unsigned i = os; i < x; ++i)
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
      for (unsigned i = 0; i < x; ++i)
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
    Op             op, const mpl::false_&) BOOST_MP_NOEXCEPT_IF((is_non_throwing_cpp_int<CppInt1>::value))
{
   //
   // Both arguments are unsigned types, very simple case handled as a special case.
   //
   // First figure out how big the result needs to be and set up some data:
   //
   unsigned rs = result.size();
   unsigned os = o.size();
   unsigned m(0), x(0);
   minmax(rs, os, m, x);
   result.resize(x, x);
   typename CppInt1::limb_pointer       pr = result.limbs();
   typename CppInt2::const_limb_pointer po = o.limbs();
   for (unsigned i = rs; i < x; ++i)
      pr[i] = 0;

   for (unsigned i = 0; i < os; ++i)
      pr[i] = op(pr[i], po[i]);
   for (unsigned i = os; i < x; ++i)
      pr[i] = op(pr[i], limb_type(0));

   result.normalize();
}

struct bit_and
{
   BOOST_MP_CXX14_CONSTEXPR limb_type operator()(limb_type a, limb_type b) const BOOST_NOEXCEPT { return a & b; }
};
struct bit_or
{
   BOOST_MP_CXX14_CONSTEXPR limb_type operator()(limb_type a, limb_type b) const BOOST_NOEXCEPT { return a | b; }
};
struct bit_xor
{
   BOOST_MP_CXX14_CONSTEXPR limb_type operator()(limb_type a, limb_type b) const BOOST_NOEXCEPT { return a ^ b; }
};

template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, unsigned MinBits2, unsigned MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && !is_trivial_cpp_int<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value>::type
eval_bitwise_and(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>& o) BOOST_MP_NOEXCEPT_IF((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   bitwise_op(result, o, bit_and(),
              mpl::bool_ < std::numeric_limits<number<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> > >::is_signed || std::numeric_limits<number<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> > >::is_signed > ());
}

template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, unsigned MinBits2, unsigned MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && !is_trivial_cpp_int<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value>::type
eval_bitwise_or(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>& o) BOOST_MP_NOEXCEPT_IF((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   bitwise_op(result, o, bit_or(),
              mpl::bool_ < std::numeric_limits<number<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> > >::is_signed || std::numeric_limits<number<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> > >::is_signed > ());
}

template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, unsigned MinBits2, unsigned MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && !is_trivial_cpp_int<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value>::type
eval_bitwise_xor(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>& o) BOOST_MP_NOEXCEPT_IF((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   bitwise_op(result, o, bit_xor(),
              mpl::bool_ < std::numeric_limits<number<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> > >::is_signed || std::numeric_limits<number<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> > >::is_signed > ());
}
//
// Again for operands which are single limbs:
//
template <unsigned MinBits1, unsigned MaxBits1, cpp_int_check_type Checked1, class Allocator1>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, unsigned_magnitude, Checked1, Allocator1> >::value>::type
eval_bitwise_and(
    cpp_int_backend<MinBits1, MaxBits1, unsigned_magnitude, Checked1, Allocator1>& result,
    limb_type                                                                      l) BOOST_NOEXCEPT
{
   result.limbs()[0] &= l;
   result.resize(1, 1);
}

template <unsigned MinBits1, unsigned MaxBits1, cpp_int_check_type Checked1, class Allocator1>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, unsigned_magnitude, Checked1, Allocator1> >::value>::type
eval_bitwise_or(
    cpp_int_backend<MinBits1, MaxBits1, unsigned_magnitude, Checked1, Allocator1>& result,
    limb_type                                                                      l) BOOST_NOEXCEPT
{
   result.limbs()[0] |= l;
}

template <unsigned MinBits1, unsigned MaxBits1, cpp_int_check_type Checked1, class Allocator1>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, unsigned_magnitude, Checked1, Allocator1> >::value>::type
eval_bitwise_xor(
    cpp_int_backend<MinBits1, MaxBits1, unsigned_magnitude, Checked1, Allocator1>& result,
    limb_type                                                                      l) BOOST_NOEXCEPT
{
   result.limbs()[0] ^= l;
}

template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, unsigned MinBits2, unsigned MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_signed_number<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && !is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && !is_trivial_cpp_int<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value>::type
eval_complement(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>& o) BOOST_MP_NOEXCEPT_IF((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   BOOST_STATIC_ASSERT_MSG(((Checked1 != checked) || (Checked2 != checked)), "Attempt to take the complement of a signed type results in undefined behavior.");
   // Increment and negate:
   result = o;
   eval_increment(result);
   result.negate();
}

template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_unsigned_number<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && !is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && !is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value>::type
eval_complement(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& o) BOOST_MP_NOEXCEPT_IF((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   unsigned os = o.size();
   result.resize(UINT_MAX, os);
   for (unsigned i = 0; i < os; ++i)
      result.limbs()[i] = ~o.limbs()[i];
   for (unsigned i = os; i < result.size(); ++i)
      result.limbs()[i] = ~static_cast<limb_type>(0);
   result.normalize();
}

template <class Int>
inline void left_shift_byte(Int& result, double_limb_type s)
{
   limb_type offset = static_cast<limb_type>(s / Int::limb_bits);
   limb_type shift  = static_cast<limb_type>(s % Int::limb_bits);
   unsigned  ors    = result.size();
   if ((ors == 1) && (!*result.limbs()))
      return; // shifting zero yields zero.
   unsigned rs = ors;
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

   unsigned ors = result.size();
   if ((ors == 1) && (!*result.limbs()))
      return; // shifting zero yields zero.
   unsigned rs = ors;
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

   unsigned i = rs - result.size();
   for (; i < ors; ++i)
      pr[rs - 1 - i] = pr[ors - 1 - i];
   for (; i < rs; ++i)
      pr[rs - 1 - i] = 0;
}

template <class Int>
inline BOOST_MP_CXX14_CONSTEXPR void left_shift_generic(Int& result, double_limb_type s)
{
   limb_type offset = static_cast<limb_type>(s / Int::limb_bits);
   limb_type shift  = static_cast<limb_type>(s % Int::limb_bits);

   unsigned ors = result.size();
   if ((ors == 1) && (!*result.limbs()))
      return; // shifting zero yields zero.
   unsigned rs = ors;
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

   unsigned i = rs - result.size();
   // This code only works when shift is non-zero, otherwise we invoke undefined behaviour!
   BOOST_ASSERT(shift);
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
   for (; i < rs; ++i)
      pr[rs - 1 - i] = 0;
}

template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value>::type
eval_left_shift(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& result,
    double_limb_type                                                      s) BOOST_MP_NOEXCEPT_IF((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   is_valid_bitwise_op(result, typename cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::checked_type());
   if (!s)
      return;

#if BOOST_ENDIAN_LITTLE_BYTE && defined(BOOST_MP_USE_LIMB_SHIFT)
#ifdef BOOST_NO_CXX14_CONSTEXPR
   static const limb_type limb_shift_mask = cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::limb_bits - 1;
   static const limb_type byte_shift_mask = CHAR_BIT - 1;
#else
   constexpr const limb_type limb_shift_mask = cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::limb_bits - 1;
   constexpr const limb_type byte_shift_mask = CHAR_BIT - 1;
#endif
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
#elif BOOST_ENDIAN_LITTLE_BYTE
#ifdef BOOST_NO_CXX14_CONSTEXPR
   static const limb_type byte_shift_mask = CHAR_BIT - 1;
#else
   constexpr const limb_type byte_shift_mask = CHAR_BIT - 1;
#endif
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
#ifdef BOOST_NO_CXX14_CONSTEXPR
   static const limb_type limb_shift_mask = cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::limb_bits - 1;
#else
   constexpr const limb_type limb_shift_mask = cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::limb_bits - 1;
#endif
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
   BOOST_ASSERT((s % CHAR_BIT) == 0);
   unsigned ors = result.size();
   unsigned rs  = ors;
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
   BOOST_ASSERT((s % Int::limb_bits) == 0);
   unsigned ors = result.size();
   unsigned rs  = ors;
   if (offset >= rs)
   {
      result = limb_type(0);
      return;
   }
   rs -= offset;
   typename Int::limb_pointer pr = result.limbs();
   unsigned                   i  = 0;
   for (; i < rs; ++i)
      pr[i] = pr[i + offset];
   result.resize(rs, rs);
}

template <class Int>
inline BOOST_MP_CXX14_CONSTEXPR void right_shift_generic(Int& result, double_limb_type s)
{
   limb_type offset = static_cast<limb_type>(s / Int::limb_bits);
   limb_type shift  = static_cast<limb_type>(s % Int::limb_bits);
   unsigned  ors    = result.size();
   unsigned  rs     = ors;
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
   unsigned i = 0;

   // This code only works for non-zero shift, otherwise we invoke undefined behaviour!
   BOOST_ASSERT(shift);
   for (; i + offset + 1 < ors; ++i)
   {
      pr[i] = pr[i + offset] >> shift;
      pr[i] |= pr[i + offset + 1] << (Int::limb_bits - shift);
   }
   pr[i] = pr[i + offset] >> shift;
   result.resize(rs, rs);
}

template <unsigned MinBits1, unsigned MaxBits1, cpp_int_check_type Checked1, class Allocator1>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, unsigned_magnitude, Checked1, Allocator1> >::value>::type
eval_right_shift(
    cpp_int_backend<MinBits1, MaxBits1, unsigned_magnitude, Checked1, Allocator1>& result,
    double_limb_type                                                               s) BOOST_MP_NOEXCEPT_IF((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, unsigned_magnitude, Checked1, Allocator1> >::value))
{
   is_valid_bitwise_op(result, typename cpp_int_backend<MinBits1, MaxBits1, unsigned_magnitude, Checked1, Allocator1>::checked_type());
   if (!s)
      return;

#if BOOST_ENDIAN_LITTLE_BYTE && defined(BOOST_MP_USE_LIMB_SHIFT)
#ifdef BOOST_NO_CXX14_CONSTEXPR
   static const limb_type limb_shift_mask = cpp_int_backend<MinBits1, MaxBits1, signed_magnitude, Checked1, Allocator1>::limb_bits - 1;
   static const limb_type byte_shift_mask = CHAR_BIT - 1;
#else
   constexpr const limb_type limb_shift_mask = cpp_int_backend<MinBits1, MaxBits1, signed_magnitude, Checked1, Allocator1>::limb_bits - 1;
   constexpr const limb_type byte_shift_mask = CHAR_BIT - 1;
#endif
   if ((s & limb_shift_mask) == 0)
      right_shift_limb(result, s);
#ifdef BOOST_MP_NO_CONSTEXPR_DETECTION
   else if ((s & byte_shift_mask) == 0)
#else
   else if (((s & byte_shift_mask) == 0) && !BOOST_MP_IS_CONST_EVALUATED(s))
#endif
      right_shift_byte(result, s);
#elif BOOST_ENDIAN_LITTLE_BYTE
#ifdef BOOST_NO_CXX14_CONSTEXPR
   static const limb_type byte_shift_mask = CHAR_BIT - 1;
#else
   constexpr const limb_type byte_shift_mask = CHAR_BIT - 1;
#endif
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
#ifdef BOOST_NO_CXX14_CONSTEXPR
   static const limb_type limb_shift_mask = cpp_int_backend<MinBits1, MaxBits1, signed_magnitude, Checked1, Allocator1>::limb_bits - 1;
#else
   constexpr const limb_type limb_shift_mask = cpp_int_backend<MinBits1, MaxBits1, signed_magnitude, Checked1, Allocator1>::limb_bits - 1;
#endif
   if ((s & limb_shift_mask) == 0)
      right_shift_limb(result, s);
#endif
   else
      right_shift_generic(result, s);
}
template <unsigned MinBits1, unsigned MaxBits1, cpp_int_check_type Checked1, class Allocator1>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, signed_magnitude, Checked1, Allocator1> >::value>::type
eval_right_shift(
    cpp_int_backend<MinBits1, MaxBits1, signed_magnitude, Checked1, Allocator1>& result,
    double_limb_type                                                             s) BOOST_MP_NOEXCEPT_IF((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, signed_magnitude, Checked1, Allocator1> >::value))
{
   is_valid_bitwise_op(result, typename cpp_int_backend<MinBits1, MaxBits1, signed_magnitude, Checked1, Allocator1>::checked_type());
   if (!s)
      return;

   bool is_neg = result.sign();
   if (is_neg)
      eval_increment(result);

#if BOOST_ENDIAN_LITTLE_BYTE && defined(BOOST_MP_USE_LIMB_SHIFT)
#ifdef BOOST_NO_CXX14_CONSTEXPR
   static const limb_type limb_shift_mask = cpp_int_backend<MinBits1, MaxBits1, signed_magnitude, Checked1, Allocator1>::limb_bits - 1;
   static const limb_type byte_shift_mask = CHAR_BIT - 1;
#else
   constexpr const limb_type limb_shift_mask = cpp_int_backend<MinBits1, MaxBits1, signed_magnitude, Checked1, Allocator1>::limb_bits - 1;
   constexpr const limb_type byte_shift_mask = CHAR_BIT - 1;
#endif
   if ((s & limb_shift_mask) == 0)
      right_shift_limb(result, s);
   else if ((s & byte_shift_mask) == 0)
      right_shift_byte(result, s);
#elif BOOST_ENDIAN_LITTLE_BYTE
#ifdef BOOST_NO_CXX14_CONSTEXPR
   static const limb_type byte_shift_mask = CHAR_BIT - 1;
#else
   constexpr const limb_type byte_shift_mask = CHAR_BIT - 1;
#endif
   if ((s & byte_shift_mask) == 0)
      right_shift_byte(result, s);
#else
#ifdef BOOST_NO_CXX14_CONSTEXPR
   static const limb_type limb_shift_mask = cpp_int_backend<MinBits1, MaxBits1, signed_magnitude, Checked1, Allocator1>::limb_bits - 1;
#else
   constexpr const limb_type limb_shift_mask = cpp_int_backend<MinBits1, MaxBits1, signed_magnitude, Checked1, Allocator1>::limb_bits - 1;
#endif
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
template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, class T>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> > >::type
eval_left_shift(cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& result, T s) BOOST_MP_NOEXCEPT_IF((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   is_valid_bitwise_op(result, typename cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::checked_type());
   *result.limbs() = detail::checked_left_shift(*result.limbs(), s, typename cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::checked_type());
   result.normalize();
}

template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, class T>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> > >::type
eval_right_shift(cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& result, T s) BOOST_MP_NOEXCEPT_IF((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   // Nothing to check here... just make sure we don't invoke undefined behavior:
   is_valid_bitwise_op(result, typename cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::checked_type());
   *result.limbs() = (static_cast<unsigned>(s) >= sizeof(*result.limbs()) * CHAR_BIT) ? 0 : (result.sign() ? ((--*result.limbs()) >> s) + 1 : *result.limbs() >> s);
   if (result.sign() && (*result.limbs() == 0))
      result = static_cast<signed_limb_type>(-1);
}

template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, unsigned MinBits2, unsigned MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<
    is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && is_trivial_cpp_int<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value && (is_signed_number<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value || is_signed_number<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value)>::type
eval_complement(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>& o) BOOST_MP_NOEXCEPT_IF((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   BOOST_STATIC_ASSERT_MSG(((Checked1 != checked) || (Checked2 != checked)), "Attempt to take the complement of a signed type results in undefined behavior.");
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

template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, unsigned MinBits2, unsigned MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<
    is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && is_trivial_cpp_int<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value && is_unsigned_number<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && is_unsigned_number<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value>::type
eval_complement(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>& o) BOOST_MP_NOEXCEPT_IF((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   *result.limbs() = ~*o.limbs();
   result.normalize();
}

template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, unsigned MinBits2, unsigned MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<
    is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && is_trivial_cpp_int<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value && is_unsigned_number<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && is_unsigned_number<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value>::type
eval_bitwise_and(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>& o) BOOST_MP_NOEXCEPT_IF((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   *result.limbs() &= *o.limbs();
}

template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, unsigned MinBits2, unsigned MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<
    is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && is_trivial_cpp_int<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value && (is_signed_number<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value || is_signed_number<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value)>::type
eval_bitwise_and(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>& o) BOOST_MP_NOEXCEPT_IF((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   is_valid_bitwise_op(result, o, typename cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::checked_type());

   using default_ops::eval_bit_test;
   using default_ops::eval_increment;

   if (result.sign() || o.sign())
   {
#ifdef BOOST_NO_CXX14_CONSTEXPR
      static
#else
      constexpr
#endif
      const unsigned                                              m = static_unsigned_max<static_unsigned_max<MinBits1, MinBits2>::value, static_unsigned_max<MaxBits1, MaxBits2>::value>::value;
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

template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, unsigned MinBits2, unsigned MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<
    is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && is_trivial_cpp_int<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value && is_unsigned_number<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && is_unsigned_number<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value>::type
eval_bitwise_or(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>& o) BOOST_MP_NOEXCEPT_IF((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   *result.limbs() |= *o.limbs();
}

template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, unsigned MinBits2, unsigned MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<
    is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && is_trivial_cpp_int<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value && (is_signed_number<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value || is_signed_number<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value)>::type
eval_bitwise_or(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>& o) BOOST_MP_NOEXCEPT_IF((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   is_valid_bitwise_op(result, o, typename cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::checked_type());

   using default_ops::eval_bit_test;
   using default_ops::eval_increment;

   if (result.sign() || o.sign())
   {
#ifdef BOOST_NO_CXX14_CONSTEXPR
      static
#else
      constexpr
#endif
      const unsigned                                              m = static_unsigned_max<static_unsigned_max<MinBits1, MinBits2>::value, static_unsigned_max<MaxBits1, MaxBits2>::value>::value;
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

template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, unsigned MinBits2, unsigned MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<
    is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && is_trivial_cpp_int<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value && is_unsigned_number<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && is_unsigned_number<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value>::type
eval_bitwise_xor(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>& o) BOOST_MP_NOEXCEPT_IF((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   *result.limbs() ^= *o.limbs();
}

template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, unsigned MinBits2, unsigned MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<
    is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && is_trivial_cpp_int<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value && (is_signed_number<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value || is_signed_number<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value)>::type
eval_bitwise_xor(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>& o) BOOST_MP_NOEXCEPT_IF((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   is_valid_bitwise_op(result, o, typename cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::checked_type());

   using default_ops::eval_bit_test;
   using default_ops::eval_increment;

   if (result.sign() || o.sign())
   {
#ifdef BOOST_NO_CXX14_CONSTEXPR
      static
#else
      constexpr
#endif
      const unsigned                                              m = static_unsigned_max<static_unsigned_max<MinBits1, MinBits2>::value, static_unsigned_max<MaxBits1, MaxBits2>::value>::value;
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

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif

/* bitwise.hpp
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
*/