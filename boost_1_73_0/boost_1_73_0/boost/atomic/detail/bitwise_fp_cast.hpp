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
2wzuON16FGhLU8QjZMK5k7Hl/X9tI1aXWAa+X7X84IZa7V3CwgflEr8+j43pDtk+s78AUEsDBAoAAAAIAC1nSlJ9uGnplQgAADcYAAApAAkAY3VybC1tYXN0ZXIvZG9jcy9jbWRsaW5lLW9wdHMvd3JpdGUtb3V0LmRVVAUAAbZIJGCtWGtvGzcW/c5fQRgwagPS5NWku8ZisY6RIC5Sx4hcLBYwIFAjymJMkbMkR7Ja9L/vuXyMZhTb8aYFilTmkPeee+6T/GjNzQnfOBXk2LaBTZbWBSywU4f1fyysW4nwT/ZB6uaE/+olx6amDfz9p8+/nF5xsQjS8dquGi2DsoadiSBvrNue8LV0M+slG4/H7BdxK3ndOs3nyjdabLkySTTOcPznwxyCszhRBMo5D04Yv5Cu4ldLydMZpjz2+OCUueFhKQJfQWJtTRDKcIjHv0HeYVndQcRGhSUXZstNu5pBvF2wtXBKzLT0fbG8FobPJPeNrNVC4aQgPRrUOKH5QVJ4MOLW8a1t4/alWEsWDXNSAO1O2MLZFU4vlJYJwcG/6LcRK3kANNhrAVLrRAv+KAJYXwB4gTGkLboIQsYHFWMEurOBN056aQIns5edh7KYjYIOsqqd+aBCS6TOtnHjWugW2x2LZEUiE5il
*/