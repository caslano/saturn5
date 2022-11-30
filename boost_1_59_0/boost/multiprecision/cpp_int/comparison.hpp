///////////////////////////////////////////////////////////////
//  Copyright 2012 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt
//
// Comparison operators for cpp_int_backend:
//
#ifndef BOOST_MP_CPP_INT_COMPARISON_HPP
#define BOOST_MP_CPP_INT_COMPARISON_HPP

#include <boost/multiprecision/detail/constexpr.hpp>

namespace boost { namespace multiprecision { namespace backends {

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable : 4018 4389 4996)
#endif

//
// Start with non-trivial cpp_int's:
//
template <std::size_t MinBits, std::size_t MaxBits, cpp_integer_type SignType, cpp_int_check_type Checked, class Allocator>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
    !is_trivial_cpp_int<cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator> >::value,
    bool>::type
eval_eq(const cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>& a, const cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>& b) noexcept
{
   return (a.sign() == b.sign()) && (a.size() == b.size()) && std_constexpr::equal(a.limbs(), a.limbs() + a.size(), b.limbs());
}
template <std::size_t MinBits1, std::size_t MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, std::size_t MinBits2, std::size_t MaxBits2, cpp_integer_type SignType2, cpp_int_check_type Checked2, class Allocator2>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
    !is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && !is_trivial_cpp_int<cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2> >::value,
    bool>::type
eval_eq(const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& a, const cpp_int_backend<MinBits2, MaxBits2, SignType2, Checked2, Allocator2>& b) noexcept
{
   return (a.sign() == b.sign()) && (a.size() == b.size()) && std_constexpr::equal(a.limbs(), a.limbs() + a.size(), b.limbs());
}
template <std::size_t MinBits, std::size_t MaxBits, cpp_int_check_type Checked, class Allocator>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
    !is_trivial_cpp_int<cpp_int_backend<MinBits, MaxBits, signed_magnitude, Checked, Allocator> >::value,
    bool>::type
eval_eq(const cpp_int_backend<MinBits, MaxBits, signed_magnitude, Checked, Allocator>& a, limb_type b) noexcept
{
   return (a.sign() == false) && (a.size() == 1) && (*a.limbs() == b);
}
template <std::size_t MinBits, std::size_t MaxBits, cpp_int_check_type Checked, class Allocator>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
    !is_trivial_cpp_int<cpp_int_backend<MinBits, MaxBits, signed_magnitude, Checked, Allocator> >::value,
    bool>::type
eval_eq(const cpp_int_backend<MinBits, MaxBits, signed_magnitude, Checked, Allocator>& a, signed_limb_type b) noexcept
{
   return (a.sign() == (b < 0)) && (a.size() == 1) && (*a.limbs() == boost::multiprecision::detail::unsigned_abs(b));
}
template <std::size_t MinBits, std::size_t MaxBits, cpp_int_check_type Checked, class Allocator>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
    !is_trivial_cpp_int<cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, Allocator> >::value,
    bool>::type
eval_eq(const cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, Allocator>& a, limb_type b) noexcept
{
   return (a.size() == 1) && (*a.limbs() == b);
}
template <std::size_t MinBits, std::size_t MaxBits, cpp_int_check_type Checked, class Allocator>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
    !is_trivial_cpp_int<cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, Allocator> >::value,
    bool>::type
eval_eq(const cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, Allocator>& a, signed_limb_type b) noexcept
{
   return (b < 0) ? eval_eq(a, cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, Allocator>(b)) : eval_eq(a, static_cast<limb_type>(b)); // Use bit pattern of b for comparison
}

template <std::size_t MinBits, std::size_t MaxBits, cpp_int_check_type Checked, class Allocator>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
    !is_trivial_cpp_int<cpp_int_backend<MinBits, MaxBits, signed_magnitude, Checked, Allocator> >::value,
    bool>::type
eval_lt(const cpp_int_backend<MinBits, MaxBits, signed_magnitude, Checked, Allocator>& a, limb_type b) noexcept
{
   if (a.sign())
      return true;
   if (a.size() > 1)
      return false;
   return *a.limbs() < b;
}
template <std::size_t MinBits, std::size_t MaxBits, cpp_int_check_type Checked, class Allocator>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
    !is_trivial_cpp_int<cpp_int_backend<MinBits, MaxBits, signed_magnitude, Checked, Allocator> >::value,
    bool>::type
eval_lt(const cpp_int_backend<MinBits, MaxBits, signed_magnitude, Checked, Allocator>& a, signed_limb_type b) noexcept
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

template <std::size_t MinBits, std::size_t MaxBits, cpp_int_check_type Checked, class Allocator>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
    !is_trivial_cpp_int<cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, Allocator> >::value,
    bool>::type
eval_lt(const cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, Allocator>& a, limb_type b) noexcept
{
   if (a.size() > 1)
      return false;
   return *a.limbs() < b;
}
template <std::size_t MinBits, std::size_t MaxBits, cpp_int_check_type Checked, class Allocator>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
    !is_trivial_cpp_int<cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, Allocator> >::value,
    bool>::type
eval_lt(const cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, Allocator>& a, signed_limb_type b) noexcept
{
   return (b < 0) ? a.compare(b) < 0 : eval_lt(a, static_cast<limb_type>(b)); // Use bit pattern of b for comparison
}

template <std::size_t MinBits, std::size_t MaxBits, cpp_int_check_type Checked, class Allocator>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
    !is_trivial_cpp_int<cpp_int_backend<MinBits, MaxBits, signed_magnitude, Checked, Allocator> >::value,
    bool>::type
eval_gt(const cpp_int_backend<MinBits, MaxBits, signed_magnitude, Checked, Allocator>& a, limb_type b) noexcept
{
   if (a.sign())
      return false;
   if (a.size() > 1)
      return true;
   return *a.limbs() > b;
}
template <std::size_t MinBits, std::size_t MaxBits, cpp_int_check_type Checked, class Allocator>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
    !is_trivial_cpp_int<cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, Allocator> >::value,
    bool>::type
eval_gt(const cpp_int_backend<MinBits, MaxBits, signed_magnitude, Checked, Allocator>& a, signed_limb_type b) noexcept
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

template <std::size_t MinBits, std::size_t MaxBits, cpp_int_check_type Checked, class Allocator>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
    !is_trivial_cpp_int<cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, Allocator> >::value,
    bool>::type
eval_gt(const cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, Allocator>& a, limb_type b) noexcept
{
   if (a.size() > 1)
      return true;
   return *a.limbs() > b;
}
template <std::size_t MinBits, std::size_t MaxBits, cpp_int_check_type Checked, class Allocator>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
    !is_trivial_cpp_int<cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, Allocator> >::value,
    bool>::type
eval_gt(const cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, Allocator>& a, signed_limb_type b) noexcept
{
   return (b < 0) ? a.compare(b) > 0 : eval_gt(a, static_cast<limb_type>(b)); // Use bit pattern of b for comparison.
}
//
// And again for trivial cpp_ints:
//
template <std::size_t MinBits, std::size_t MaxBits, cpp_int_check_type Checked>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
    is_trivial_cpp_int<cpp_int_backend<MinBits, MaxBits, signed_magnitude, Checked, void> >::value,
    bool>::value
eval_eq(const cpp_int_backend<MinBits, MaxBits, signed_magnitude, Checked, void>& a, const cpp_int_backend<MinBits, MaxBits, signed_magnitude, Checked, void>& b) noexcept
{
   return (a.sign() == b.sign()) && (*a.limbs() == *b.limbs());
}
template <std::size_t MinBits, std::size_t MaxBits, cpp_int_check_type Checked>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
    is_trivial_cpp_int<cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, void> >::value,
    bool>::value
eval_eq(const cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, void>& a, const cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, void>& b) noexcept
{
   return *a.limbs() == *b.limbs();
}
template <std::size_t MinBits, std::size_t MaxBits, cpp_int_check_type Checked, class U>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
    boost::multiprecision::detail::is_unsigned<U>::value && is_trivial_cpp_int<cpp_int_backend<MinBits, MaxBits, signed_magnitude, Checked, void> >::value,
    bool>::type
eval_eq(const cpp_int_backend<MinBits, MaxBits, signed_magnitude, Checked, void>& a, U b) noexcept
{
   return !a.sign() && (*a.limbs() == b);
}
template <std::size_t MinBits, std::size_t MaxBits, cpp_int_check_type Checked, class S>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
    boost::multiprecision::detail::is_signed<S>::value && boost::multiprecision::detail::is_integral<S>::value && is_trivial_cpp_int<cpp_int_backend<MinBits, MaxBits, signed_magnitude, Checked, void> >::value,
    bool>::type
eval_eq(const cpp_int_backend<MinBits, MaxBits, signed_magnitude, Checked, void>& a, S b) noexcept
{
   return (a.sign() == (b < 0)) && (*a.limbs() == boost::multiprecision::detail::unsigned_abs(b));
}
template <std::size_t MinBits, std::size_t MaxBits, cpp_int_check_type Checked, class U>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
    boost::multiprecision::detail::is_unsigned<U>::value && is_trivial_cpp_int<cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, void> >::value,
    bool>::type
eval_eq(const cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, void>& a, U b) noexcept
{
   return *a.limbs() == b;
}
template <std::size_t MinBits, std::size_t MaxBits, cpp_int_check_type Checked, class S>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
    boost::multiprecision::detail::is_signed<S>::value && boost::multiprecision::detail::is_integral<S>::value && is_trivial_cpp_int<cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, void> >::value,
    bool>::type
eval_eq(const cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, void>& a, S b) noexcept
{
   using ui_type = typename boost::multiprecision::detail::make_unsigned<S>::type;
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

template <std::size_t MinBits, std::size_t MaxBits, cpp_int_check_type Checked>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
    is_trivial_cpp_int<cpp_int_backend<MinBits, MaxBits, signed_magnitude, Checked, void> >::value,
    bool>::type
eval_lt(const cpp_int_backend<MinBits, MaxBits, signed_magnitude, Checked, void>& a, const cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, void>& b) noexcept
{
   if (a.sign() != b.sign())
      return a.sign();
   return a.sign() ? *a.limbs() > *b.limbs() : *a.limbs() < *b.limbs();
}
template <std::size_t MinBits, std::size_t MaxBits, cpp_int_check_type Checked>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
    is_trivial_cpp_int<cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, void> >::value,
    bool>::type
eval_lt(const cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, void>& a, const cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, void>& b) noexcept
{
   return *a.limbs() < *b.limbs();
}
template <std::size_t MinBits, std::size_t MaxBits, cpp_int_check_type Checked, class U>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
    boost::multiprecision::detail::is_unsigned<U>::value && is_trivial_cpp_int<cpp_int_backend<MinBits, MaxBits, signed_magnitude, Checked, void> >::value,
    bool>::type
eval_lt(const cpp_int_backend<MinBits, MaxBits, signed_magnitude, Checked, void>& a, U b) noexcept
{
   if (a.sign())
      return true;
   return *a.limbs() < b;
}
template <std::size_t MinBits, std::size_t MaxBits, cpp_int_check_type Checked, class S>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
    boost::multiprecision::detail::is_signed<S>::value && boost::multiprecision::detail::is_integral<S>::value && is_trivial_cpp_int<cpp_int_backend<MinBits, MaxBits, signed_magnitude, Checked, void> >::value,
    bool>::type
eval_lt(const cpp_int_backend<MinBits, MaxBits, signed_magnitude, Checked, void>& a, S b) noexcept
{
   if (a.sign() != (b < 0))
      return a.sign();
   return a.sign() ? (*a.limbs() > boost::multiprecision::detail::unsigned_abs(b)) : (*a.limbs() < boost::multiprecision::detail::unsigned_abs(b));
}
template <std::size_t MinBits, std::size_t MaxBits, cpp_int_check_type Checked, class U>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
    boost::multiprecision::detail::is_unsigned<U>::value && is_trivial_cpp_int<cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, void> >::value,
    bool>::type
eval_lt(const cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, void>& a, U b) noexcept
{
   return *a.limbs() < b;
}
template <std::size_t MinBits, std::size_t MaxBits, cpp_int_check_type Checked, class S>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
    boost::multiprecision::detail::is_signed<S>::value && boost::multiprecision::detail::is_integral<S>::value && is_trivial_cpp_int<cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, void> >::value,
    bool>::type
eval_lt(const cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, void>& a, S b) noexcept
{
   using ui_type = typename boost::multiprecision::detail::make_unsigned<S>::type;
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

template <std::size_t MinBits, std::size_t MaxBits, cpp_int_check_type Checked>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
    is_trivial_cpp_int<cpp_int_backend<MinBits, MaxBits, signed_magnitude, Checked, void> >::value,
    bool>::type
eval_gt(const cpp_int_backend<MinBits, MaxBits, signed_magnitude, Checked, void>& a, const cpp_int_backend<MinBits, MaxBits, signed_magnitude, Checked, void>& b) noexcept
{
   if (a.sign() != b.sign())
      return !a.sign();
   return a.sign() ? *a.limbs() < *b.limbs() : *a.limbs() > *b.limbs();
}
template <std::size_t MinBits, std::size_t MaxBits, cpp_int_check_type Checked>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
    is_trivial_cpp_int<cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, void> >::value,
    bool>::type
eval_gt(const cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, void>& a, const cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, void>& b) noexcept
{
   return *a.limbs() > *b.limbs();
}
template <std::size_t MinBits, std::size_t MaxBits, cpp_int_check_type Checked, class U>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
    boost::multiprecision::detail::is_unsigned<U>::value && is_trivial_cpp_int<cpp_int_backend<MinBits, MaxBits, signed_magnitude, Checked, void> >::value,
    bool>::type
eval_gt(const cpp_int_backend<MinBits, MaxBits, signed_magnitude, Checked, void>& a, U b) noexcept
{
   if (a.sign())
      return false;
   return *a.limbs() > b;
}
template <std::size_t MinBits, std::size_t MaxBits, cpp_int_check_type Checked, class S>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
    boost::multiprecision::detail::is_signed<S>::value && boost::multiprecision::detail::is_integral<S>::value && is_trivial_cpp_int<cpp_int_backend<MinBits, MaxBits, signed_magnitude, Checked, void> >::value,
    bool>::type
eval_gt(const cpp_int_backend<MinBits, MaxBits, signed_magnitude, Checked, void>& a, S b) noexcept
{
   if (a.sign() != (b < 0))
      return !a.sign();
   return a.sign() ? (*a.limbs() < boost::multiprecision::detail::unsigned_abs(b)) : (*a.limbs() > boost::multiprecision::detail::unsigned_abs(b));
}
template <std::size_t MinBits, std::size_t MaxBits, cpp_int_check_type Checked, class U>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
    boost::multiprecision::detail::is_unsigned<U>::value && is_trivial_cpp_int<cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, void> >::value,
    bool>::type
eval_gt(const cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, void>& a, U b) noexcept
{
   return *a.limbs() > b;
}
template <std::size_t MinBits, std::size_t MaxBits, cpp_int_check_type Checked, class S>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
    boost::multiprecision::detail::is_signed<S>::value && boost::multiprecision::detail::is_integral<S>::value && is_trivial_cpp_int<cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, void> >::value,
    bool>::type
eval_gt(const cpp_int_backend<MinBits, MaxBits, unsigned_magnitude, Checked, void>& a, S b) noexcept
{
   using ui_type = typename boost::multiprecision::detail::make_unsigned<S>::type;
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