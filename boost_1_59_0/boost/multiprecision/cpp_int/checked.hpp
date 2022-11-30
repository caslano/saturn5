
//  Copyright 2012 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_MP_CPP_INT_CHECKED_HPP
#define BOOST_MP_CPP_INT_CHECKED_HPP

#include <climits>
#include <limits>
#include <type_traits>
#include <stdexcept>
#include <string>
#include <boost/multiprecision/detail/standalone_config.hpp>
#include <boost/multiprecision/detail/no_exceptions_support.hpp>

namespace boost { namespace multiprecision { namespace backends { namespace detail {

//
// Simple routines for performing checked arithmetic with a builtin arithmetic type.
// Note that this is not a complete header, it must be included as part of boost/multiprecision/cpp_int.hpp.
//

template <typename T>
inline constexpr T type_max() noexcept
{
   return 
   #ifdef BOOST_HAS_INT128
   std::is_same<T, boost::multiprecision::int128_type>::value ? INT128_MAX :
   std::is_same<T, boost::multiprecision::uint128_type>::value ? UINT128_MAX :
   #endif
   (std::numeric_limits<T>::max)();
}

template <typename T>
inline constexpr T type_min() noexcept
{
   return 
   #ifdef BOOST_HAS_INT128
   std::is_same<T, boost::multiprecision::int128_type>::value ? INT128_MIN :
   std::is_same<T, boost::multiprecision::uint128_type>::value ? T(0) :
   #endif
   (std::numeric_limits<T>::min)();
}

inline void raise_overflow(std::string op)
{
   BOOST_MP_THROW_EXCEPTION(std::overflow_error("overflow in " + op));
}
inline void raise_add_overflow()
{
   raise_overflow("addition");
}
inline void raise_subtract_overflow()
{
   BOOST_MP_THROW_EXCEPTION(std::range_error("Subtraction resulted in a negative value, but the type is unsigned"));
}
inline void raise_mul_overflow()
{
   raise_overflow("multiplication");
}
inline void raise_div_overflow()
{
   raise_overflow("division");
}

template <class A>
inline BOOST_MP_CXX14_CONSTEXPR A checked_add_imp(A a, A b, const std::integral_constant<bool, true>&)
{
   if (a > 0)
   {
      if ((b > 0) && ((type_max<A>() - b) < a))
         raise_add_overflow();
   }
   else
   {
      if ((b < 0) && ((type_min<A>() - b) > a))
         raise_add_overflow();
   }
   return a + b;
}
template <class A>
inline BOOST_MP_CXX14_CONSTEXPR A checked_add_imp(A a, A b, const std::integral_constant<bool, false>&)
{
   if ((type_max<A>() - b) < a)
      raise_add_overflow();
   return a + b;
}
template <class A>
inline BOOST_MP_CXX14_CONSTEXPR A checked_add(A a, A b, const std::integral_constant<int, checked>&)
{
   return checked_add_imp(a, b, std::integral_constant<bool, boost::multiprecision::detail::is_signed<A>::value && boost::multiprecision::detail::is_integral<A>::value > ());
}
template <class A>
inline BOOST_MP_CXX14_CONSTEXPR A checked_add(A a, A b, const std::integral_constant<int, unchecked>&)
{
   return a + b;
}

template <class A>
inline BOOST_MP_CXX14_CONSTEXPR A checked_subtract_imp(A a, A b, const std::integral_constant<bool, true>&)
{
   if (a > 0)
   {
      if ((b < 0) && ((type_max<A>() + b) < a))
         raise_subtract_overflow();
   }
   else
   {
      if ((b > 0) && ((type_min<A>() + b) > a))
         raise_subtract_overflow();
   }
   return a - b;
}
template <class A>
inline BOOST_MP_CXX14_CONSTEXPR A checked_subtract_imp(A a, A b, const std::integral_constant<bool, false>&)
{
   if (a < b)
      raise_subtract_overflow();
   return a - b;
}
template <class A>
inline BOOST_MP_CXX14_CONSTEXPR A checked_subtract(A a, A b, const std::integral_constant<int, checked>&)
{
   return checked_subtract_imp(a, b, std::integral_constant<bool, boost::multiprecision::detail::is_signed<A>::value && boost::multiprecision::detail::is_integral<A>::value>());
}
template <class A>
inline BOOST_MP_CXX14_CONSTEXPR A checked_subtract(A a, A b, const std::integral_constant<int, unchecked>&)
{
   return a - b;
}

template <class A>
inline BOOST_MP_CXX14_CONSTEXPR A checked_multiply(A a, A b, const std::integral_constant<int, checked>&)
{
   BOOST_MP_USING_ABS
   if (a && (type_max<A>() / abs(a) < abs(b)))
      raise_mul_overflow();
   return a * b;
}
template <class A>
inline BOOST_MP_CXX14_CONSTEXPR A checked_multiply(A a, A b, const std::integral_constant<int, unchecked>&)
{
   return a * b;
}

template <class A>
inline BOOST_MP_CXX14_CONSTEXPR A checked_divide(A a, A b, const std::integral_constant<int, checked>&)
{
   if (b == 0)
      raise_div_overflow();
   return a / b;
}
template <class A>
inline BOOST_MP_CXX14_CONSTEXPR A checked_divide(A a, A b, const std::integral_constant<int, unchecked>&)
{
   return a / b;
}

template <class A>
inline BOOST_MP_CXX14_CONSTEXPR A checked_left_shift(A a, unsigned long long shift, const std::integral_constant<int, checked>&)
{
   if (a && shift)
   {
      if ((shift > sizeof(A) * CHAR_BIT) || (a >> (sizeof(A) * CHAR_BIT - shift)))
         BOOST_MP_THROW_EXCEPTION(std::overflow_error("Shift out of range"));
   }
   return a << shift;
}
template <class A>
inline BOOST_MP_CXX14_CONSTEXPR A checked_left_shift(A a, unsigned long long shift, const std::integral_constant<int, unchecked>&)
{
   return (shift >= sizeof(A) * CHAR_BIT) ? 0 : a << shift;
}

}}}} // namespace boost::multiprecision::backends::detail

#endif

/* checked.hpp
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
*/