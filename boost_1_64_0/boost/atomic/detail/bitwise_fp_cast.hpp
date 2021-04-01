/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2018 Andrey Semashev
 */
/*!
 * \file   atomic/detail/bitwise_fp_cast.hpp
 *
 * This header defines \c bitwise_fp_cast used to convert between storage and floating point value types
 */

#ifndef BOOST_ATOMIC_DETAIL_BITWISE_FP_CAST_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_BITWISE_FP_CAST_HPP_INCLUDED_

#include <cstddef>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/float_sizes.hpp>
#include <boost/atomic/detail/bitwise_cast.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

/*!
 * \brief The type trait returns the size of the value of the specified floating point type
 *
 * This size may be less than <tt>sizeof(T)</tt> if the implementation uses padding bytes for a particular FP type. This is
 * often the case with 80-bit extended double, which is stored in 12 or 16 bytes with padding filled with garbage.
 */
template< typename T >
struct value_sizeof
{
    static BOOST_CONSTEXPR_OR_CONST std::size_t value = sizeof(T);
};

#if defined(BOOST_ATOMIC_DETAIL_SIZEOF_FLOAT_VALUE)
template< >
struct value_sizeof< float >
{
    static BOOST_CONSTEXPR_OR_CONST std::size_t value = BOOST_ATOMIC_DETAIL_SIZEOF_FLOAT_VALUE;
};
#endif

#if defined(BOOST_ATOMIC_DETAIL_SIZEOF_DOUBLE_VALUE)
template< >
struct value_sizeof< double >
{
    static BOOST_CONSTEXPR_OR_CONST std::size_t value = BOOST_ATOMIC_DETAIL_SIZEOF_DOUBLE_VALUE;
};
#endif

#if defined(BOOST_ATOMIC_DETAIL_SIZEOF_LONG_DOUBLE_VALUE)
template< >
struct value_sizeof< long double >
{
    static BOOST_CONSTEXPR_OR_CONST std::size_t value = BOOST_ATOMIC_DETAIL_SIZEOF_LONG_DOUBLE_VALUE;
};
#endif

template< typename T >
struct value_sizeof< const T > : value_sizeof< T > {};

template< typename T >
struct value_sizeof< volatile T > : value_sizeof< T > {};

template< typename T >
struct value_sizeof< const volatile T > : value_sizeof< T > {};


template< typename To, typename From >
BOOST_FORCEINLINE To bitwise_fp_cast(From const& from) BOOST_NOEXCEPT
{
    return atomics::detail::bitwise_cast< To, atomics::detail::value_sizeof< From >::value >(from);
}

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_BITWISE_FP_CAST_HPP_INCLUDED_

/* bitwise_fp_cast.hpp
v+0+oO17UlNyVViySkcZuuFaVQQdbCnb2JsHe/5bPX9z+44qSCEYjxr8ixHJeHSzTC8aSoseVMhd+M0xn/hvXpfpoyUFnSF1T9KZqwCOC+MxxbMdN23B396l3imwORbs7g0DJYoNRwwSuLZ1Fx0ZLvK4pkOhnTNiKzv+boWjZCHHKiyAkY7H430fki9pZagSvIDldgjkMqAXAbZdV1qEXQn/xM6rQAq/E61s6T4uVUbQ94ITB1n+3/HF5DNeDpv46sL/O4VYaZCSP5rRxOp5OK/LrrBkTxzrq4lyoF0mPfAKMakdF+9MQ3qLc22Iq4nhYmiPA+Ii/cfqmVRdkXJ3PppUHwBtGolMUWqZM0K1qtHULRxib3pSxE9eLjuuxDUms3At4ec2bt8cKXBA+WbykWGUOjBQdgQgJXBhX1V/HvqA7Yg4uLpCeSIdLwPTZBNzHC8Q7i5QgPiPsL0rL77BDwehyUzcE6n/bB+GHaNDH1x733TemUgHRbIdIy9ds9WE577ySo7Cy9oAQmJU8KiiKJb8h2ykmJOUt5pSgGN2/tsCRCCOYnA2QY37gg==
*/