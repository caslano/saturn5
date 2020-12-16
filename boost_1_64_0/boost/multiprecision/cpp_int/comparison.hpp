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
6IcuNl/XG/3zcMJ5szJpaNa9G/GT9xpNM75Ntid02uC2sVxo/vvDTV5HdF5Ev/na5uv6afA6jLObS39dQ18idO2z6tOQ3sOu6vrq4ds43Cc+Sy9pPltOkubrNY242aP0N2g6daGHaW/s6ujLA592cdrQSLpmr+XGG4GneaBU1iEN7niv7i7NpZ/W0VYm1jtaSmhNtBOMYzIzbWlQXe2KA2n7XBro9OBggH7cNn50Jz12zNHl5Gn9F12eB3b6XsJ7WoehffTcyqOOaFqH+cWKo5c7ksd1wjZPtfKFerFvvHvawSRKijAs2QsMDGSisw1zcI9s3qIkeR1Vgmngcf3TKNJK/dNstYT+yfSP1D9c/5i9CNq7u2keS6sil2EUNimm+qfSPwq58X7yVLe3JGXKtOFiLuu0SeDJ+udEw4slrPFv1bgS4p7nWd2e8qqbR8LKSlZ5AE2E6T8d/7aAySiaU4VUtEvs2v/gVbf9RaqkkkHJIv9Mc38XN6eEimQe6tuCzTV8G+OOkTdOHA/KuBFkfLOK7+emkK4vNzSI0L+4C+mNMBsA6gd/4MazetI2XGXWg0091y5CYKEmhtdgk81Z39IPmxwZk6veXF8Cm5gmKNdmJ7PfmaDYhZWl5zZJsllM7/sEs7p+anFVDc6ub956ognGrLPe7Nr3gIuN9KAHjeTxxbXl9bMMPN2y7xkcc2VJKMZlEKVZXDIUksaKpLltbBTqq013zqOwLuqf5vas6Y8X0G8Di47wY2M4toHJNkGOn43URaQ2auAV/bNkkzmByW66OnaYWLWuRd94rbJHnT496/4PzqMd7rNQX8TNzc77uDuY+FyyOVfaNeOp5r/1nuBHhzRdcVUdf3ob/q79/kP9PTiecL268IQfN3rLn8B3iqb3HpdbmRs8H4TDvZ9JJ5G2AVffyLM1hd+HS3CiWHP28z9oaHqe1m4tNnFeveWXd2n2JCABGFNsZa1dsx54F9iHNG96m/tA/Wyy0f/umoZ5svmu2dq3thjPCui/hnp9i74FhjI15yPk/w7yN98Nd8uv2/n7SG9IGJfk4UDf0vVp018/SSHts5ZNWEaNz9g/QFl07saZK/HP+5aWAvfftt0PTeF3bZdL7kC/hbTmAgwLv77szCW7ELMxHGxDAZtkMN+ZaaRrV7Y2/qn7HdK2DevEc9lNMCR/9D/uYJrRP+Gcr/YArd9m6GfjMqXTNnXfMTe4nsjgfHjQXUMlkzwR+uURw1b1bO4OA568tUziQlaBYPXxMjGGKrqxjGlIIyN/0zEc2zttSJVcWiN9A+nk0pvcaV+xd9oaiJfadzZy+swmjeXts2dvxfrNevP3iVuHcKZcgHEVDAUsDfpvbM659/6ZHWNnXnByBw6WW2Vns/wuz26wVGkU6fDrN/iP52vm/Lt8P1NZKBN5w7EIdCFd/e9X3fR4xiKVS55mkj19fRu6BnqlNZSFxoW/NQY1qKUWwZOYrmI3x+6nc+ycN8cO9JyzrcfmrbrNtfi2UV3uZb6fc77DrfVgx/g4/7uebyyt+Xb8rnBmbr6152yd9j8Ad958O9nY27ffA70Xbr7DRLvZhJ5r8tzSY6L5voKBOhsdiZGNK7eSOQp42u/vsN+3QEQ0Dee1q0ij89p9TR3f39Db3mgRGtvSH6h1IC/WdE3QJghbTRjPleW2THquY08g8yrOl9duvbH58kFaIQejGY4vwNZ++2ezrolM8oVMcWgbJ+7e25rxha7FbMykhjZ+rvk9pdPyOOtWvUvjNMjM052PoWn8jvM0+lPeg7Se/8TZvUiDoahnFVufdxgaDlNHx7F/Bmlr62Rmt3W+jBh/7jdp3AbpOmMs00X8bufsO3c=
*/