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
bOWTBqB1PMkejEDEaBvc3ByIkXpV4lbapM5ij2gGL9Ga2ZFoKrarvVRQe2kU76WC+KNd30vR5DiyxwsJgtPqv6BWLPOitwnyy8TulMm6U/L6dBxnMA+p7XlZ9v+UCx749H2ySFEXhVlSKduTXZ5ZwUtdRj+rQ3sL8lX+CBMN/PE9Zs0iOl8iOvHpa8RzXUXIBUoVmX6O9WtqyBZncJyD+jQJMAJlBtlStA2nEwYz5yNpVMpWxkNUHg84wOSX/QD17rvZZcYRunQ/wPq6XufRsd67Vc/6P0ie6bcVf+B/oaTZGSXIj7xwimwi9wGAmVn5oLc2IoceoX8SR7+5uBt86F1j0As1+oYa10phtSwblC7SrZUMEObiefDud6wTvRBa1EVdQtSVq6KutbZftGydfhp0unJfviKrsrgDUtB3hde4a0Gg2szYotSmUO9yuON0tM452Vi2Jp9WMBvkQtDtUJ01yH8f8RR15sn4Om4f4+tz+4iT3x6iywh2N4RdBu0L9hOgKGuxRS/KTmbAFFpAZAdpggWngsWZ3dM/hRS2n0ZmFJ1xxkinfqQ9uplFJRc36NYJqDtPhSOgcu8LWLfvOgHzV7dyXDMM9E34JlPRuMA9WVk4pLdzcNpu3Ryoq1OfVU21H/wRTYF5QFKmOaOUNsvHIfYlwf0tm/W8y6Y7jTM9U9jmP9ZXY7gPnKTvcOibiwImTgq5/f8Ih9zn
*/