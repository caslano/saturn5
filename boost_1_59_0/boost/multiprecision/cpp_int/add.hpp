///////////////////////////////////////////////////////////////
//  Copyright 2012 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt
//
// Comparison operators for cpp_int_backend:
//
#ifndef BOOST_MP_CPP_INT_ADD_HPP
#define BOOST_MP_CPP_INT_ADD_HPP

#include <boost/multiprecision/detail/constexpr.hpp>
#include <boost/multiprecision/cpp_int/add_unsigned.hpp>

namespace boost { namespace multiprecision { namespace backends {

//
// As above, but for adding a single limb to a non-trivial cpp_int:
//
template <class CppInt1, class CppInt2>
inline BOOST_MP_CXX14_CONSTEXPR void add_unsigned(CppInt1& result, const CppInt2& a, const limb_type& o) noexcept(is_non_throwing_cpp_int<CppInt1>::value)
{
   // Addition using modular arithmetic.
   // Nothing fancy, just let uintmax_t take the strain:
   if (&result != &a)
      result.resize(a.size(), a.size());
   double_limb_type                     carry = o;
   typename CppInt1::limb_pointer       pr    = result.limbs();
   typename CppInt2::const_limb_pointer pa    = a.limbs();
   std::size_t                             i     = 0;
   // Addition with carry until we either run out of digits or carry is zero:
   for (; carry && (i < result.size()); ++i)
   {
      carry += static_cast<double_limb_type>(pa[i]);
#ifdef __MSVC_RUNTIME_CHECKS
      pr[i] = static_cast<limb_type>(carry & ~static_cast<limb_type>(0));
#else
      pr[i] = static_cast<limb_type>(carry);
#endif
      carry >>= CppInt1::limb_bits;
   }
   // Just copy any remaining digits:
   if (&a != &result)
   {
      std_constexpr::copy(pa + i, pa + a.size(), pr + i);
   }
   if (carry)
   {
      // We overflowed, need to add one more limb:
      std::size_t x = result.size();
      result.resize(x + 1, x + 1);
      if (result.size() > x)
         result.limbs()[x] = static_cast<limb_type>(carry);
   }
   result.normalize();
   result.sign(a.sign());
}
//
// And again to subtract a single limb:
//
template <class CppInt1, class CppInt2>
inline BOOST_MP_CXX14_CONSTEXPR void subtract_unsigned(CppInt1& result, const CppInt2& a, const limb_type& b) noexcept(is_non_throwing_cpp_int<CppInt1>::value)
{
   // Subtract one limb.
   // Nothing fancy, just let uintmax_t take the strain:
   constexpr double_limb_type borrow = static_cast<double_limb_type>(CppInt1::max_limb_value) + 1;
   result.resize(a.size(), a.size());
   typename CppInt1::limb_pointer       pr = result.limbs();
   typename CppInt2::const_limb_pointer pa = a.limbs();
   if (*pa >= b)
   {
      *pr = *pa - b;
      if (&result != &a)
      {
         std_constexpr::copy(pa + 1, pa + a.size(), pr + 1);
         result.sign(a.sign());
      }
      else if ((result.size() == 1) && (*pr == 0))
      {
         result.sign(false); // zero is unsigned.
      }
   }
   else if (result.size() == 1)
   {
      *pr = b - *pa;
      result.sign(!a.sign());
   }
   else
   {
      *pr        = static_cast<limb_type>((borrow + *pa) - b);
      std::size_t i = 1;
      while (!pa[i])
      {
         pr[i] = CppInt1::max_limb_value;
         ++i;
      }
      pr[i] = pa[i] - 1;
      if (&result != &a)
      {
         ++i;
         std_constexpr::copy(pa + i, pa + a.size(), pr + i);
      }
      result.normalize();
      result.sign(a.sign());
   }
}

//
// Now the actual functions called by the front end, all of which forward to one of the above:
//
template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, std::size_t MinBits2, std::size_t MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && !is_trivial_cpp_int<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value>::type
eval_add(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>& o) noexcept((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   eval_add(result, result, o);
}
template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, std::size_t MinBits2, std::size_t MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2, std::size_t MinBits3, std::size_t MaxBits3, cpp_integer_type SignType3, cpp_int_check_type Checked3, class Allocator3>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && !is_trivial_cpp_int<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value && !is_trivial_cpp_int<cpp_int_backend<MinBits3, MaxBits3, SignType3, Checked3, Allocator3> >::value>::type
eval_add(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>& a,
    const cpp_int_backend<MinBits3, MaxBits3, SignType3, Checked3, Allocator3>& b) noexcept((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   if (a.sign() != b.sign())
   {
      subtract_unsigned(result, a, b);
      return;
   }
   add_unsigned(result, a, b);
}
template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value>::type
eval_add(cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& result, const limb_type& o) noexcept((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   if (result.sign())
   {
      subtract_unsigned(result, result, o);
   }
   else
      add_unsigned(result, result, o);
}
template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, std::size_t MinBits2, std::size_t MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && !is_trivial_cpp_int<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value>::type
eval_add(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>& a,
    const limb_type&                                                            o) noexcept((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   if (a.sign())
   {
      subtract_unsigned(result, a, o);
   }
   else
      add_unsigned(result, a, o);
}
template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value>::type
eval_add(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& result,
    const signed_limb_type&                                               o) noexcept((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   if (o < 0)
      eval_subtract(result, static_cast<limb_type>(boost::multiprecision::detail::unsigned_abs(o)));
   else if (o > 0)
      eval_add(result, static_cast<limb_type>(o));
}
template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, std::size_t MinBits2, std::size_t MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && !is_trivial_cpp_int<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value>::type
eval_add(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>& a,
    const signed_limb_type&                                                     o) noexcept((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   if (o < 0)
      eval_subtract(result, a, static_cast<limb_type>(boost::multiprecision::detail::unsigned_abs(o)));
   else if (o > 0)
      eval_add(result, a, static_cast<limb_type>(o));
   else if (&result != &a)
      result = a;
}
template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value>::type
eval_subtract(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& result,
    const limb_type&                                                      o) noexcept((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   if (result.sign())
   {
      add_unsigned(result, result, o);
   }
   else
      subtract_unsigned(result, result, o);
}
template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, std::size_t MinBits2, std::size_t MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && !is_trivial_cpp_int<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value>::type
eval_subtract(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>& a,
    const limb_type&                                                            o) noexcept((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   if (a.sign())
   {
      add_unsigned(result, a, o);
   }
   else
   {
      subtract_unsigned(result, a, o);
   }
}
template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value>::type
eval_subtract(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& result,
    const signed_limb_type&                                               o) noexcept((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   if (o)
   {
      if (o < 0)
         eval_add(result, static_cast<limb_type>(boost::multiprecision::detail::unsigned_abs(o)));
      else
         eval_subtract(result, static_cast<limb_type>(o));
   }
}
template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, std::size_t MinBits2, std::size_t MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && !is_trivial_cpp_int<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value>::type
eval_subtract(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>& a,
    const signed_limb_type&                                                     o) noexcept((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   if (o)
   {
      if (o < 0)
         eval_add(result, a, static_cast<limb_type>(boost::multiprecision::detail::unsigned_abs(o)));
      else
         eval_subtract(result, a, static_cast<limb_type>(o));
   }
   else if (&result != &a)
      result = a;
}

template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value>::type
eval_increment(cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& result) noexcept((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   constexpr const limb_type one = 1;

   if (!result.sign() && (result.limbs()[0] < cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::max_limb_value))
      ++result.limbs()[0];
   else if (result.sign() && result.limbs()[0])
   {
      --result.limbs()[0];
      if (!result.limbs()[0] && (result.size() == 1))
         result.sign(false);
   }
   else
      eval_add(result, one);
}
template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value>::type
eval_decrement(cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& result) noexcept((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   constexpr const limb_type one = 1;

   if (!result.sign() && result.limbs()[0])
      --result.limbs()[0];
   else if (result.sign() && (result.limbs()[0] < cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::max_limb_value))
      ++result.limbs()[0];
   else
      eval_subtract(result, one);
}
template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, std::size_t MinBits2, std::size_t MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && !is_trivial_cpp_int<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value>::type
eval_subtract(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>& o) noexcept((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   eval_subtract(result, result, o);
}
template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, std::size_t MinBits2, std::size_t MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2, std::size_t MinBits3, std::size_t MaxBits3, cpp_integer_type SignType3, cpp_int_check_type Checked3, class Allocator3>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && !is_trivial_cpp_int<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value && !is_trivial_cpp_int<cpp_int_backend<MinBits3, MaxBits3, SignType3, Checked3, Allocator3> >::value>::type
eval_subtract(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>& a,
    const cpp_int_backend<MinBits3, MaxBits3, SignType3, Checked3, Allocator3>& b) noexcept((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   if (a.sign() != b.sign())
   {
      add_unsigned(result, a, b);
      return;
   }
   subtract_unsigned(result, a, b);
}

//
// Simple addition and subtraction routine for trivial cpp_int's come last:
//
// One of the arguments is signed:
//
template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
    is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && (is_signed_number<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value || is_signed_number<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value)>::type
eval_add(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& o) noexcept((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   if (result.sign() != o.sign())
   {
      if (*o.limbs() > *result.limbs())
      {
         *result.limbs() = detail::checked_subtract(*o.limbs(), *result.limbs(), typename cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::checked_type());
         result.negate();
      }
      else
         *result.limbs() = detail::checked_subtract(*result.limbs(), *o.limbs(), typename cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::checked_type());
   }
   else
      *result.limbs() = detail::checked_add(*result.limbs(), *o.limbs(), typename cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::checked_type());
   result.normalize();
}
// Simple version for two unsigned arguments:
template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
    is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && is_unsigned_number<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && is_unsigned_number<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value>::type
eval_add(cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
         const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& o) noexcept((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   *result.limbs() = detail::checked_add(*result.limbs(), *o.limbs(), typename cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::checked_type());
   result.normalize();
}

// signed subtraction:
template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
    is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && (is_signed_number<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value || is_signed_number<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value)>::type
eval_subtract(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& o) noexcept((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   if (result.sign() != o.sign())
   {
      *result.limbs() = detail::checked_add(*result.limbs(), *o.limbs(), typename cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::checked_type());
   }
   else if (*result.limbs() < *o.limbs())
   {
      *result.limbs() = detail::checked_subtract(*o.limbs(), *result.limbs(), typename cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::checked_type());
      result.negate();
   }
   else
      *result.limbs() = detail::checked_subtract(*result.limbs(), *o.limbs(), typename cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::checked_type());
   result.normalize();
}

template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
    is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && is_unsigned_number<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && is_unsigned_number<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value>::type
eval_subtract(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& o) noexcept((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   *result.limbs() = detail::checked_subtract(*result.limbs(), *o.limbs(), typename cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::checked_type());
   result.normalize();
}

}}} // namespace boost::multiprecision::backends

#endif

/* add.hpp
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
*/