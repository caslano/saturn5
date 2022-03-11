///////////////////////////////////////////////////////////////
//  Copyright 2012 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt
//
// Comparison operators for cpp_int_backend:
//
#ifndef BOOST_MP_CPP_INT_COMPARISON_HPP
#define BOOST_MP_CPP_INT_COMPARISON_HPP

#include <boost/type_traits/make_unsigned.hpp>
#include <boost/multiprecision/detail/constexpr.hpp>

namespace boost { namespace multiprecision { namespace backends {

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable : 4018 4389 4996)
#endif

//
// Start with non-trivial cpp_int's:
//
template <unsigned MinBits, unsigned MaxBits, cpp_integer_type SignType, cpp_int_check_type Checked, class Allocator>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<
    !is_trivial_cpp_int<cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator> >::value,
    bool>::type
eval_eq(const cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>& a, const cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>& b) BOOST_NOEXCEPT
{
   return (a.sign() == b.sign()) && (a.size() == b.size()) && std_constexpr::equal(a.limbs(), a.limbs() + a.size(), b.limbs());
}
template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, unsigned MinBits2, unsigned MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<
    !is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && !is_trivial_cpp_int<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value,
    bool>::type
eval_eq(const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& a, const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>& b) BOOST_NOEXCEPT
{
   return (a.sign() == b.sign()) && (a.size() == b.size()) && std_constexpr::equal(a.limbs(), a.limbs() + a.size(), b.limbs());
}
template <unsigned MinBits, unsigned MaxBits, cpp_int_check_type Checked, class Allocator>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<
    !is_trivial_cpp_int<cpp_int_backend<MinBits, MaxBits, signed_magnitude, Checked, Allocator> >::value,
    bool>::type
eval_eq(const cpp_int_backend<MinBits, MaxBits, signed_magnitude, Checked, Allocator>& a, limb_type b) BOOST_NOEXCEPT
{
   return (a.sign() == false) && (a.size() == 1) && (*a.limbs() == b);
}
template <unsigned MinBits, unsigned MaxBits, cpp_int_check_type Checked, class Allocator>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<
    !is_trivial_cpp_int<cpp_int_backend<MinBits, MaxBits, signed_magnitude, Checked, Allocator> >::value,
    bool>::type
eval_eq(const cpp_int_backend<MinBits, MaxBits, signed_magnitude, Checked, Allocator>& a, signed_limb_type b) BOOST_NOEXCEPT
{
   return (a.sign() == (b < 0)) && (a.size() == 1) && (*a.limbs() == boost::multiprecision::detail::unsigned_abs(b));
}
template <unsigned MinBits, unsigned MaxBits, cpp_int_check_type Checked, class Allocator>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<
    !is_trivial_cpp_int<cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, Allocator> >::value,
    bool>::type
eval_eq(const cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, Allocator>& a, limb_type b) BOOST_NOEXCEPT
{
   return (a.size() == 1) && (*a.limbs() == b);
}
template <unsigned MinBits, unsigned MaxBits, cpp_int_check_type Checked, class Allocator>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<
    !is_trivial_cpp_int<cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, Allocator> >::value,
    bool>::type
eval_eq(const cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, Allocator>& a, signed_limb_type b) BOOST_NOEXCEPT
{
   return (b < 0) ? eval_eq(a, cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, Allocator>(b)) : eval_eq(a, static_cast<limb_type>(b)); // Use bit pattern of b for comparison
}

template <unsigned MinBits, unsigned MaxBits, cpp_int_check_type Checked, class Allocator>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<
    !is_trivial_cpp_int<cpp_int_backend<MinBits, MaxBits, signed_magnitude, Checked, Allocator> >::value,
    bool>::type
eval_lt(const cpp_int_backend<MinBits, MaxBits, signed_magnitude, Checked, Allocator>& a, limb_type b) BOOST_NOEXCEPT
{
   if (a.sign())
      return true;
   if (a.size() > 1)
      return false;
   return *a.limbs() < b;
}
template <unsigned MinBits, unsigned MaxBits, cpp_int_check_type Checked, class Allocator>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<
    !is_trivial_cpp_int<cpp_int_backend<MinBits, MaxBits, signed_magnitude, Checked, Allocator> >::value,
    bool>::type
eval_lt(const cpp_int_backend<MinBits, MaxBits, signed_magnitude, Checked, Allocator>& a, signed_limb_type b) BOOST_NOEXCEPT
{
   if ((b == 0) || (a.sign() != (b < 0)))
      return a.sign();
   if (a.sign())
   {
      if (a.size() > 1)
         return true;
      return *a.limbs() > boost::multiprecision::detail::unsigned_abs(b);
   }
   else
   {
      if (a.size() > 1)
         return false;
      return *a.limbs() < boost::multiprecision::detail::unsigned_abs(b);
   }
}

template <unsigned MinBits, unsigned MaxBits, cpp_int_check_type Checked, class Allocator>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<
    !is_trivial_cpp_int<cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, Allocator> >::value,
    bool>::type
eval_lt(const cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, Allocator>& a, limb_type b) BOOST_NOEXCEPT
{
   if (a.size() > 1)
      return false;
   return *a.limbs() < b;
}
template <unsigned MinBits, unsigned MaxBits, cpp_int_check_type Checked, class Allocator>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<
    !is_trivial_cpp_int<cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, Allocator> >::value,
    bool>::type
eval_lt(const cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, Allocator>& a, signed_limb_type b) BOOST_NOEXCEPT
{
   return (b < 0) ? a.compare(b) < 0 : eval_lt(a, static_cast<limb_type>(b)); // Use bit pattern of b for comparison
}

template <unsigned MinBits, unsigned MaxBits, cpp_int_check_type Checked, class Allocator>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<
    !is_trivial_cpp_int<cpp_int_backend<MinBits, MaxBits, signed_magnitude, Checked, Allocator> >::value,
    bool>::type
eval_gt(const cpp_int_backend<MinBits, MaxBits, signed_magnitude, Checked, Allocator>& a, limb_type b) BOOST_NOEXCEPT
{
   if (a.sign())
      return false;
   if (a.size() > 1)
      return true;
   return *a.limbs() > b;
}
template <unsigned MinBits, unsigned MaxBits, cpp_int_check_type Checked, class Allocator>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<
    !is_trivial_cpp_int<cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, Allocator> >::value,
    bool>::type
eval_gt(const cpp_int_backend<MinBits, MaxBits, signed_magnitude, Checked, Allocator>& a, signed_limb_type b) BOOST_NOEXCEPT
{
   if (b == 0)
      return !a.sign() && ((a.size() > 1) || *a.limbs());
   if (a.sign() != (b < 0))
      return !a.sign();
   if (a.sign())
   {
      if (a.size() > 1)
         return false;
      return *a.limbs() < boost::multiprecision::detail::unsigned_abs(b);
   }
   else
   {
      if (a.size() > 1)
         return true;
      return *a.limbs() > boost::multiprecision::detail::unsigned_abs(b);
   }
}

template <unsigned MinBits, unsigned MaxBits, cpp_int_check_type Checked, class Allocator>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<
    !is_trivial_cpp_int<cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, Allocator> >::value,
    bool>::type
eval_gt(const cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, Allocator>& a, limb_type b) BOOST_NOEXCEPT
{
   if (a.size() > 1)
      return true;
   return *a.limbs() > b;
}
template <unsigned MinBits, unsigned MaxBits, cpp_int_check_type Checked, class Allocator>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<
    !is_trivial_cpp_int<cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, Allocator> >::value,
    bool>::type
eval_gt(const cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, Allocator>& a, signed_limb_type b) BOOST_NOEXCEPT
{
   return (b < 0) ? a.compare(b) > 0 : eval_gt(a, static_cast<limb_type>(b)); // Use bit pattern of b for comparison.
}
//
// And again for trivial cpp_ints:
//
template <unsigned MinBits, unsigned MaxBits, cpp_int_check_type Checked>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<
    is_trivial_cpp_int<cpp_int_backend<MinBits, MaxBits, signed_magnitude, Checked, void> >::value,
    bool>::value
eval_eq(const cpp_int_backend<MinBits, MaxBits, signed_magnitude, Checked, void>& a, const cpp_int_backend<MinBits, MaxBits, signed_magnitude, Checked, void>& b) BOOST_NOEXCEPT
{
   return (a.sign() == b.sign()) && (*a.limbs() == *b.limbs());
}
template <unsigned MinBits, unsigned MaxBits, cpp_int_check_type Checked>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<
    is_trivial_cpp_int<cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, void> >::value,
    bool>::value
eval_eq(const cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, void>& a, const cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, void>& b) BOOST_NOEXCEPT
{
   return *a.limbs() == *b.limbs();
}
template <unsigned MinBits, unsigned MaxBits, cpp_int_check_type Checked, class U>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<
    is_unsigned<U>::value && is_trivial_cpp_int<cpp_int_backend<MinBits, MaxBits, signed_magnitude, Checked, void> >::value,
    bool>::type
eval_eq(const cpp_int_backend<MinBits, MaxBits, signed_magnitude, Checked, void>& a, U b) BOOST_NOEXCEPT
{
   return !a.sign() && (*a.limbs() == b);
}
template <unsigned MinBits, unsigned MaxBits, cpp_int_check_type Checked, class S>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<
    is_signed<S>::value && is_trivial_cpp_int<cpp_int_backend<MinBits, MaxBits, signed_magnitude, Checked, void> >::value,
    bool>::type
eval_eq(const cpp_int_backend<MinBits, MaxBits, signed_magnitude, Checked, void>& a, S b) BOOST_NOEXCEPT
{
   return (a.sign() == (b < 0)) && (*a.limbs() == boost::multiprecision::detail::unsigned_abs(b));
}
template <unsigned MinBits, unsigned MaxBits, cpp_int_check_type Checked, class U>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<
    is_unsigned<U>::value && is_trivial_cpp_int<cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, void> >::value,
    bool>::type
eval_eq(const cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, void>& a, U b) BOOST_NOEXCEPT
{
   return *a.limbs() == b;
}
template <unsigned MinBits, unsigned MaxBits, cpp_int_check_type Checked, class S>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<
    is_signed<S>::value && is_trivial_cpp_int<cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, void> >::value,
    bool>::type
eval_eq(const cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, void>& a, S b) BOOST_NOEXCEPT
{
   typedef typename make_unsigned<S>::type ui_type;
   if (b < 0)
   {
      cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, void> t(b);
      return *a.limbs() == *t.limbs();
   }
   else
   {
      return *a.limbs() == static_cast<ui_type>(b);
   }
}

template <unsigned MinBits, unsigned MaxBits, cpp_int_check_type Checked>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<
    is_trivial_cpp_int<cpp_int_backend<MinBits, MaxBits, signed_magnitude, Checked, void> >::value,
    bool>::type
eval_lt(const cpp_int_backend<MinBits, MaxBits, signed_magnitude, Checked, void>& a, const cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, void>& b) BOOST_NOEXCEPT
{
   if (a.sign() != b.sign())
      return a.sign();
   return a.sign() ? *a.limbs() > *b.limbs() : *a.limbs() < *b.limbs();
}
template <unsigned MinBits, unsigned MaxBits, cpp_int_check_type Checked>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<
    is_trivial_cpp_int<cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, void> >::value,
    bool>::type
eval_lt(const cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, void>& a, const cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, void>& b) BOOST_NOEXCEPT
{
   return *a.limbs() < *b.limbs();
}
template <unsigned MinBits, unsigned MaxBits, cpp_int_check_type Checked, class U>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<
    is_unsigned<U>::value && is_trivial_cpp_int<cpp_int_backend<MinBits, MaxBits, signed_magnitude, Checked, void> >::value,
    bool>::type
eval_lt(const cpp_int_backend<MinBits, MaxBits, signed_magnitude, Checked, void>& a, U b) BOOST_NOEXCEPT
{
   if (a.sign())
      return true;
   return *a.limbs() < b;
}
template <unsigned MinBits, unsigned MaxBits, cpp_int_check_type Checked, class S>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<
    is_signed<S>::value && is_trivial_cpp_int<cpp_int_backend<MinBits, MaxBits, signed_magnitude, Checked, void> >::value,
    bool>::type
eval_lt(const cpp_int_backend<MinBits, MaxBits, signed_magnitude, Checked, void>& a, S b) BOOST_NOEXCEPT
{
   if (a.sign() != (b < 0))
      return a.sign();
   return a.sign() ? (*a.limbs() > boost::multiprecision::detail::unsigned_abs(b)) : (*a.limbs() < boost::multiprecision::detail::unsigned_abs(b));
}
template <unsigned MinBits, unsigned MaxBits, cpp_int_check_type Checked, class U>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<
    is_unsigned<U>::value && is_trivial_cpp_int<cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, void> >::value,
    bool>::type
eval_lt(const cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, void>& a, U b) BOOST_NOEXCEPT
{
   return *a.limbs() < b;
}
template <unsigned MinBits, unsigned MaxBits, cpp_int_check_type Checked, class S>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<
    is_signed<S>::value && is_trivial_cpp_int<cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, void> >::value,
    bool>::type
eval_lt(const cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, void>& a, S b) BOOST_NOEXCEPT
{
   typedef typename make_unsigned<S>::type ui_type;
   if (b < 0)
   {
      cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, void> t(b);
      return *a.limbs() < *t.limbs();
   }
   else
   {
      return *a.limbs() < static_cast<ui_type>(b);
   }
}

template <unsigned MinBits, unsigned MaxBits, cpp_int_check_type Checked>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<
    is_trivial_cpp_int<cpp_int_backend<MinBits, MaxBits, signed_magnitude, Checked, void> >::value,
    bool>::type
eval_gt(const cpp_int_backend<MinBits, MaxBits, signed_magnitude, Checked, void>& a, const cpp_int_backend<MinBits, MaxBits, signed_magnitude, Checked, void>& b) BOOST_NOEXCEPT
{
   if (a.sign() != b.sign())
      return !a.sign();
   return a.sign() ? *a.limbs() < *b.limbs() : *a.limbs() > *b.limbs();
}
template <unsigned MinBits, unsigned MaxBits, cpp_int_check_type Checked>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<
    is_trivial_cpp_int<cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, void> >::value,
    bool>::type
eval_gt(const cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, void>& a, const cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, void>& b) BOOST_NOEXCEPT
{
   return *a.limbs() > *b.limbs();
}
template <unsigned MinBits, unsigned MaxBits, cpp_int_check_type Checked, class U>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<
    is_unsigned<U>::value && is_trivial_cpp_int<cpp_int_backend<MinBits, MaxBits, signed_magnitude, Checked, void> >::value,
    bool>::type
eval_gt(const cpp_int_backend<MinBits, MaxBits, signed_magnitude, Checked, void>& a, U b) BOOST_NOEXCEPT
{
   if (a.sign())
      return false;
   return *a.limbs() > b;
}
template <unsigned MinBits, unsigned MaxBits, cpp_int_check_type Checked, class S>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<
    is_signed<S>::value && is_trivial_cpp_int<cpp_int_backend<MinBits, MaxBits, signed_magnitude, Checked, void> >::value,
    bool>::type
eval_gt(const cpp_int_backend<MinBits, MaxBits, signed_magnitude, Checked, void>& a, S b) BOOST_NOEXCEPT
{
   if (a.sign() != (b < 0))
      return !a.sign();
   return a.sign() ? (*a.limbs() < boost::multiprecision::detail::unsigned_abs(b)) : (*a.limbs() > boost::multiprecision::detail::unsigned_abs(b));
}
template <unsigned MinBits, unsigned MaxBits, cpp_int_check_type Checked, class U>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<
    is_unsigned<U>::value && is_trivial_cpp_int<cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, void> >::value,
    bool>::type
eval_gt(const cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, void>& a, U b) BOOST_NOEXCEPT
{
   return *a.limbs() > b;
}
template <unsigned MinBits, unsigned MaxBits, cpp_int_check_type Checked, class S>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<
    is_signed<S>::value && is_trivial_cpp_int<cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, void> >::value,
    bool>::type
eval_gt(const cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, void>& a, S b) BOOST_NOEXCEPT
{
   typedef typename make_unsigned<S>::type ui_type;
   if (b < 0)
   {
      cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, void> t(b);
      return *a.limbs() > *t.limbs();
   }
   else
   {
      return *a.limbs() > static_cast<ui_type>(b);
   }
}

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

}}} // namespace boost::multiprecision::backends

#endif

/* comparison.hpp
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
*/