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

namespace boost { namespace multiprecision { namespace backends {

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4127) // conditional expression is constant
#endif

//
// This is the key addition routine where all the argument types are non-trivial cpp_int's:
//
template <class CppInt1, class CppInt2, class CppInt3>
inline BOOST_MP_CXX14_CONSTEXPR void add_unsigned(CppInt1& result, const CppInt2& a, const CppInt3& b) BOOST_MP_NOEXCEPT_IF(is_non_throwing_cpp_int<CppInt1>::value)
{
   using ::boost::multiprecision::std_constexpr::swap;

   // Nothing fancy, just let uintmax_t take the strain:
   double_limb_type carry = 0;
   unsigned         m(0), x(0);
   unsigned         as = a.size();
   unsigned         bs = b.size();
   minmax(as, bs, m, x);
   if (x == 1)
   {
      bool s = a.sign();
      result = static_cast<double_limb_type>(*a.limbs()) + static_cast<double_limb_type>(*b.limbs());
      result.sign(s);
      return;
   }
   result.resize(x, x);
   typename CppInt2::const_limb_pointer pa     = a.limbs();
   typename CppInt3::const_limb_pointer pb     = b.limbs();
   typename CppInt1::limb_pointer       pr     = result.limbs();
   typename CppInt1::limb_pointer       pr_end = pr + m;

   if (as < bs)
      swap(pa, pb);

   // First where a and b overlap:
   while (pr != pr_end)
   {
      carry += static_cast<double_limb_type>(*pa) + static_cast<double_limb_type>(*pb);
#ifdef __MSVC_RUNTIME_CHECKS
      *pr = static_cast<limb_type>(carry & ~static_cast<limb_type>(0));
#else
      *pr = static_cast<limb_type>(carry);
#endif
      carry >>= CppInt1::limb_bits;
      ++pr, ++pa, ++pb;
   }
   pr_end += x - m;
   // Now where only a has digits:
   while (pr != pr_end)
   {
      if (!carry)
      {
         if (pa != pr)
            std_constexpr::copy(pa, pa + (pr_end - pr), pr);
         break;
      }
      carry += static_cast<double_limb_type>(*pa);
#ifdef __MSVC_RUNTIME_CHECKS
      *pr = static_cast<limb_type>(carry & ~static_cast<limb_type>(0));
#else
      *pr   = static_cast<limb_type>(carry);
#endif
      carry >>= CppInt1::limb_bits;
      ++pr, ++pa;
   }
   if (carry)
   {
      // We overflowed, need to add one more limb:
      result.resize(x + 1, x + 1);
      if (result.size() > x)
         result.limbs()[x] = static_cast<limb_type>(carry);
   }
   result.normalize();
   result.sign(a.sign());
}
//
// As above, but for adding a single limb to a non-trivial cpp_int:
//
template <class CppInt1, class CppInt2>
inline BOOST_MP_CXX14_CONSTEXPR void add_unsigned(CppInt1& result, const CppInt2& a, const limb_type& o) BOOST_MP_NOEXCEPT_IF(is_non_throwing_cpp_int<CppInt1>::value)
{
   // Addition using modular arithmetic.
   // Nothing fancy, just let uintmax_t take the strain:
   if (&result != &a)
      result.resize(a.size(), a.size());
   double_limb_type                     carry = o;
   typename CppInt1::limb_pointer       pr    = result.limbs();
   typename CppInt2::const_limb_pointer pa    = a.limbs();
   unsigned                             i     = 0;
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
      for (; i < result.size(); ++i)
         pr[i] = pa[i];
   }
   if (carry)
   {
      // We overflowed, need to add one more limb:
      unsigned x = result.size();
      result.resize(x + 1, x + 1);
      if (result.size() > x)
         result.limbs()[x] = static_cast<limb_type>(carry);
   }
   result.normalize();
   result.sign(a.sign());
}
//
// Core subtraction routine for all non-trivial cpp_int's:
//
template <class CppInt1, class CppInt2, class CppInt3>
inline BOOST_MP_CXX14_CONSTEXPR void subtract_unsigned(CppInt1& result, const CppInt2& a, const CppInt3& b) BOOST_MP_NOEXCEPT_IF(is_non_throwing_cpp_int<CppInt1>::value)
{
   using ::boost::multiprecision::std_constexpr::swap;

   // Nothing fancy, just let uintmax_t take the strain:
   double_limb_type borrow = 0;
   unsigned         m(0), x(0);
   minmax(a.size(), b.size(), m, x);
   //
   // special cases for small limb counts:
   //
   if (x == 1)
   {
      bool      s  = a.sign();
      limb_type al = *a.limbs();
      limb_type bl = *b.limbs();
      if (bl > al)
      {
         ::boost::multiprecision::std_constexpr::swap(al, bl);
         s = !s;
      }
      result = al - bl;
      result.sign(s);
      return;
   }
   // This isn't used till later, but comparison has to occur before we resize the result,
   // as that may also resize a or b if this is an inplace operation:
   int c = a.compare_unsigned(b);
   // Set up the result vector:
   result.resize(x, x);
   // Now that a, b, and result are stable, get pointers to their limbs:
   typename CppInt2::const_limb_pointer pa      = a.limbs();
   typename CppInt3::const_limb_pointer pb      = b.limbs();
   typename CppInt1::limb_pointer       pr      = result.limbs();
   bool                                 swapped = false;
   if (c < 0)
   {
      swap(pa, pb);
      swapped = true;
   }
   else if (c == 0)
   {
      result = static_cast<limb_type>(0);
      return;
   }

   unsigned i = 0;
   // First where a and b overlap:
   while (i < m)
   {
      borrow = static_cast<double_limb_type>(pa[i]) - static_cast<double_limb_type>(pb[i]) - borrow;
      pr[i]  = static_cast<limb_type>(borrow);
      borrow = (borrow >> CppInt1::limb_bits) & 1u;
      ++i;
   }
   // Now where only a has digits, only as long as we've borrowed:
   while (borrow && (i < x))
   {
      borrow = static_cast<double_limb_type>(pa[i]) - borrow;
      pr[i]  = static_cast<limb_type>(borrow);
      borrow = (borrow >> CppInt1::limb_bits) & 1u;
      ++i;
   }
   // Any remaining digits are the same as those in pa:
   if ((x != i) && (pa != pr))
      std_constexpr::copy(pa + i, pa + x, pr + i);
   BOOST_ASSERT(0 == borrow);

   //
   // We may have lost digits, if so update limb usage count:
   //
   result.normalize();
   result.sign(a.sign());
   if (swapped)
      result.negate();
}
//
// And again to subtract a single limb:
//
template <class CppInt1, class CppInt2>
inline BOOST_MP_CXX14_CONSTEXPR void subtract_unsigned(CppInt1& result, const CppInt2& a, const limb_type& b) BOOST_MP_NOEXCEPT_IF(is_non_throwing_cpp_int<CppInt1>::value)
{
   // Subtract one limb.
   // Nothing fancy, just let uintmax_t take the strain:
#ifdef BOOST_NO_CXX14_CONSTEXPR
   BOOST_STATIC_CONSTANT(double_limb_type, borrow = static_cast<double_limb_type>(CppInt1::max_limb_value) + 1);
#else
   constexpr double_limb_type borrow = static_cast<double_limb_type>(CppInt1::max_limb_value) + 1;
#endif
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
      unsigned i = 1;
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
template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, unsigned MinBits2, unsigned MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && !is_trivial_cpp_int<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value>::type
eval_add(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>& o) BOOST_MP_NOEXCEPT_IF((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   eval_add(result, result, o);
}
template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, unsigned MinBits2, unsigned MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2, unsigned MinBits3, unsigned MaxBits3, cpp_integer_type SignType3, cpp_int_check_type Checked3, class Allocator3>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && !is_trivial_cpp_int<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value && !is_trivial_cpp_int<cpp_int_backend<MinBits3, MaxBits3, SignType3, Checked3, Allocator3> >::value>::type
eval_add(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>& a,
    const cpp_int_backend<MinBits3, MaxBits3, SignType3, Checked3, Allocator3>& b) BOOST_MP_NOEXCEPT_IF((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   if (a.sign() != b.sign())
   {
      subtract_unsigned(result, a, b);
      return;
   }
   add_unsigned(result, a, b);
}
template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value>::type
eval_add(cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& result, const limb_type& o) BOOST_MP_NOEXCEPT_IF((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   if (result.sign())
   {
      subtract_unsigned(result, result, o);
   }
   else
      add_unsigned(result, result, o);
}
template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, unsigned MinBits2, unsigned MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && !is_trivial_cpp_int<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value>::type
eval_add(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>& a,
    const limb_type&                                                            o) BOOST_MP_NOEXCEPT_IF((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   if (a.sign())
   {
      subtract_unsigned(result, a, o);
   }
   else
      add_unsigned(result, a, o);
}
template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value>::type
eval_add(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& result,
    const signed_limb_type&                                               o) BOOST_MP_NOEXCEPT_IF((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   if (o < 0)
      eval_subtract(result, static_cast<limb_type>(boost::multiprecision::detail::unsigned_abs(o)));
   else if (o > 0)
      eval_add(result, static_cast<limb_type>(o));
}
template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, unsigned MinBits2, unsigned MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && !is_trivial_cpp_int<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value>::type
eval_add(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>& a,
    const signed_limb_type&                                                     o) BOOST_MP_NOEXCEPT_IF((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   if (o < 0)
      eval_subtract(result, a, static_cast<limb_type>(boost::multiprecision::detail::unsigned_abs(o)));
   else if (o > 0)
      eval_add(result, a, static_cast<limb_type>(o));
   else if (&result != &a)
      result = a;
}
template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value>::type
eval_subtract(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& result,
    const limb_type&                                                      o) BOOST_MP_NOEXCEPT_IF((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   if (result.sign())
   {
      add_unsigned(result, result, o);
   }
   else
      subtract_unsigned(result, result, o);
}
template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, unsigned MinBits2, unsigned MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && !is_trivial_cpp_int<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value>::type
eval_subtract(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>& a,
    const limb_type&                                                            o) BOOST_MP_NOEXCEPT_IF((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
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
template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value>::type
eval_subtract(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& result,
    const signed_limb_type&                                               o) BOOST_MP_NOEXCEPT_IF((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   if (o)
   {
      if (o < 0)
         eval_add(result, static_cast<limb_type>(boost::multiprecision::detail::unsigned_abs(o)));
      else
         eval_subtract(result, static_cast<limb_type>(o));
   }
}
template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, unsigned MinBits2, unsigned MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && !is_trivial_cpp_int<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value>::type
eval_subtract(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>& a,
    const signed_limb_type&                                                     o) BOOST_MP_NOEXCEPT_IF((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
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

template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value>::type
eval_increment(cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& result) BOOST_MP_NOEXCEPT_IF((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
#ifdef BOOST_NO_CXX14_CONSTEXPR
   static const limb_type one = 1;
#else
   constexpr const limb_type one = 1;
#endif
   if (!result.sign() && (result.limbs()[0] < cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::max_limb_value))
      ++result.limbs()[0];
   else if (result.sign() && result.limbs()[0])
   {
      --result.limbs()[0];
      if (!result.limbs()[0])
         result.sign(false);
   }
   else
      eval_add(result, one);
}
template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value>::type
eval_decrement(cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& result) BOOST_MP_NOEXCEPT_IF((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
#ifdef BOOST_NO_CXX14_CONSTEXPR
   static const limb_type one = 1;
#else
   constexpr const limb_type one = 1;
#endif
   if (!result.sign() && result.limbs()[0])
      --result.limbs()[0];
   else if (result.sign() && (result.limbs()[0] < cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::max_limb_value))
      ++result.limbs()[0];
   else
      eval_subtract(result, one);
}
template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, unsigned MinBits2, unsigned MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && !is_trivial_cpp_int<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value>::type
eval_subtract(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>& o) BOOST_MP_NOEXCEPT_IF((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   eval_subtract(result, result, o);
}
template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, unsigned MinBits2, unsigned MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2, unsigned MinBits3, unsigned MaxBits3, cpp_integer_type SignType3, cpp_int_check_type Checked3, class Allocator3>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && !is_trivial_cpp_int<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value && !is_trivial_cpp_int<cpp_int_backend<MinBits3, MaxBits3, SignType3, Checked3, Allocator3> >::value>::type
eval_subtract(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>& a,
    const cpp_int_backend<MinBits3, MaxBits3, SignType3, Checked3, Allocator3>& b) BOOST_MP_NOEXCEPT_IF((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
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
template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<
    is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && (is_signed_number<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value || is_signed_number<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value)>::type
eval_add(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& o) BOOST_MP_NOEXCEPT_IF((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
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
template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<
    is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && is_unsigned_number<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && is_unsigned_number<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value>::type
eval_add(cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
         const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& o) BOOST_MP_NOEXCEPT_IF((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   *result.limbs() = detail::checked_add(*result.limbs(), *o.limbs(), typename cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::checked_type());
   result.normalize();
}

// signed subtraction:
template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<
    is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && (is_signed_number<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value || is_signed_number<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value)>::type
eval_subtract(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& o) BOOST_MP_NOEXCEPT_IF((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
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

template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<
    is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && is_unsigned_number<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && is_unsigned_number<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value>::type
eval_subtract(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& o) BOOST_MP_NOEXCEPT_IF((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   *result.limbs() = detail::checked_subtract(*result.limbs(), *o.limbs(), typename cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::checked_type());
   result.normalize();
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif

}}} // namespace boost::multiprecision::backends

#endif

/* add.hpp
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
*/