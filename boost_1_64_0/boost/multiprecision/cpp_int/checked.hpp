
//  Copyright 2012 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_MP_CPP_INT_CHECKED_HPP
#define BOOST_MP_CPP_INT_CHECKED_HPP

namespace boost { namespace multiprecision { namespace backends { namespace detail {

//
// Simple routines for performing checked arithmetic with a builtin arithmetic type.
// Note that this is not a complete header, it must be included as part of boost/multiprecision/cpp_int.hpp.
//

inline void raise_overflow(std::string op)
{
   BOOST_THROW_EXCEPTION(std::overflow_error("overflow in " + op));
}
inline void raise_add_overflow()
{
   raise_overflow("addition");
}
inline void raise_subtract_overflow()
{
   BOOST_THROW_EXCEPTION(std::range_error("Subtraction resulted in a negative value, but the type is unsigned"));
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
inline BOOST_MP_CXX14_CONSTEXPR A checked_add_imp(A a, A b, const mpl::true_&)
{
   if (a > 0)
   {
      if ((b > 0) && ((integer_traits<A>::const_max - b) < a))
         raise_add_overflow();
   }
   else
   {
      if ((b < 0) && ((integer_traits<A>::const_min - b) > a))
         raise_add_overflow();
   }
   return a + b;
}
template <class A>
inline BOOST_MP_CXX14_CONSTEXPR A checked_add_imp(A a, A b, const mpl::false_&)
{
   if ((integer_traits<A>::const_max - b) < a)
      raise_add_overflow();
   return a + b;
}
template <class A>
inline BOOST_MP_CXX14_CONSTEXPR A checked_add(A a, A b, const mpl::int_<checked>&)
{
   return checked_add_imp(a, b, mpl::bool_<boost::is_signed<A>::value>());
}
template <class A>
inline BOOST_MP_CXX14_CONSTEXPR A checked_add(A a, A b, const mpl::int_<unchecked>&)
{
   return a + b;
}

template <class A>
inline BOOST_MP_CXX14_CONSTEXPR A checked_subtract_imp(A a, A b, const mpl::true_&)
{
   if (a > 0)
   {
      if ((b < 0) && ((integer_traits<A>::const_max + b) < a))
         raise_subtract_overflow();
   }
   else
   {
      if ((b > 0) && ((integer_traits<A>::const_min + b) > a))
         raise_subtract_overflow();
   }
   return a - b;
}
template <class A>
inline BOOST_MP_CXX14_CONSTEXPR A checked_subtract_imp(A a, A b, const mpl::false_&)
{
   if (a < b)
      raise_subtract_overflow();
   return a - b;
}
template <class A>
inline BOOST_MP_CXX14_CONSTEXPR A checked_subtract(A a, A b, const mpl::int_<checked>&)
{
   return checked_subtract_imp(a, b, mpl::bool_<boost::is_signed<A>::value>());
}
template <class A>
inline BOOST_MP_CXX14_CONSTEXPR A checked_subtract(A a, A b, const mpl::int_<unchecked>&)
{
   return a - b;
}

template <class A>
inline BOOST_MP_CXX14_CONSTEXPR A checked_multiply(A a, A b, const mpl::int_<checked>&)
{
   BOOST_MP_USING_ABS
   if (a && (integer_traits<A>::const_max / abs(a) < abs(b)))
      raise_mul_overflow();
   return a * b;
}
template <class A>
inline BOOST_MP_CXX14_CONSTEXPR A checked_multiply(A a, A b, const mpl::int_<unchecked>&)
{
   return a * b;
}

template <class A>
inline BOOST_MP_CXX14_CONSTEXPR A checked_divide(A a, A b, const mpl::int_<checked>&)
{
   if (b == 0)
      raise_div_overflow();
   return a / b;
}
template <class A>
inline BOOST_MP_CXX14_CONSTEXPR A checked_divide(A a, A b, const mpl::int_<unchecked>&)
{
   return a / b;
}

template <class A>
inline BOOST_MP_CXX14_CONSTEXPR A checked_left_shift(A a, boost::ulong_long_type shift, const mpl::int_<checked>&)
{
   if (a && shift)
   {
      if ((shift > sizeof(A) * CHAR_BIT) || (a >> (sizeof(A) * CHAR_BIT - shift)))
         BOOST_THROW_EXCEPTION(std::overflow_error("Shift out of range"));
   }
   return a << shift;
}
template <class A>
inline BOOST_MP_CXX14_CONSTEXPR A checked_left_shift(A a, boost::ulong_long_type shift, const mpl::int_<unchecked>&)
{
   return (shift >= sizeof(A) * CHAR_BIT) ? 0 : a << shift;
}

}}}} // namespace boost::multiprecision::backends::detail

#endif

/* checked.hpp
zlEy4f5pA0c1/QxuYlbiDzEnj1xaN9oVwiaMFMo7Le7xuUwSd8LqhjuatFVOejRXKDIBTVm6qTRsO5RwLWyyWbSqlCuE6yYYjcqNyEqZndOAWsOyyKJxjqCIr7+19ei2zWLIQdc7XkMY6rpRmUHf3XSTCk2G/6gXTa/VBMqLdGlruCUtbRzvhJ5CGpL9Gi7OaJjP4rFbowAuyHJ2DgsEDN5dZ1eK9aQSPzEOm7pMI/FlUoi/kXmu0L9ntdn1C1hO2ETnIs2EGdjGDoKunfM10T6a0Z13YDjCVWmlDKxZa+ArJylXPDyhyHHUi8I6ofdL0LemVPPIFT4g8Lll6HqWN8fmn4nPO86twJmliSlverFIdbIvlBLPnladO3nCjmFNPYV4SN0O9r6JKg5P/kzYf16JKDCnT+KStBVPb045V2G1BgfdQHb1VjYd3a3trQZ7Toc3R10SH3ib4CEaYidDnaMvt6oeytrx1KiVdV7a6Tcu+lNnMT2u4CnNFwqYYLxHxXWIV0A8zKaXKdY0dKswSZ/D9fCOkSWruRb2UTaHV7P9qIGbnINoNY4IDA==
*/