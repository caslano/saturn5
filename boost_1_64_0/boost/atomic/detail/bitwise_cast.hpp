/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2009 Helge Bahmann
 * Copyright (c) 2012 Tim Blechmann
 * Copyright (c) 2013 - 2018, 2020 Andrey Semashev
 */
/*!
 * \file   atomic/detail/bitwise_cast.hpp
 *
 * This header defines \c bitwise_cast used to convert between storage and value types
 */

#ifndef BOOST_ATOMIC_DETAIL_BITWISE_CAST_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_BITWISE_CAST_HPP_INCLUDED_

#include <cstddef>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/addressof.hpp>
#include <boost/atomic/detail/string_ops.hpp>
#include <boost/atomic/detail/type_traits/integral_constant.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if defined(BOOST_GCC) && BOOST_GCC >= 80000
#pragma GCC diagnostic push
// copying an object of non-trivial type X from an array of Y. This is benign because we use memcpy to copy trivially copyable objects.
#pragma GCC diagnostic ignored "-Wclass-memaccess"
#endif

namespace boost {
namespace atomics {
namespace detail {

template< std::size_t FromSize, typename To >
BOOST_FORCEINLINE void clear_tail_padding_bits(To& to, atomics::detail::true_type) BOOST_NOEXCEPT
{
    BOOST_ATOMIC_DETAIL_MEMSET(reinterpret_cast< unsigned char* >(atomics::detail::addressof(to)) + FromSize, 0, sizeof(To) - FromSize);
}

template< std::size_t FromSize, typename To >
BOOST_FORCEINLINE void clear_tail_padding_bits(To&, atomics::detail::false_type) BOOST_NOEXCEPT
{
}

template< std::size_t FromSize, typename To >
BOOST_FORCEINLINE void clear_tail_padding_bits(To& to) BOOST_NOEXCEPT
{
    atomics::detail::clear_tail_padding_bits< FromSize >(to, atomics::detail::integral_constant< bool, FromSize < sizeof(To) >());
}

template< typename To, std::size_t FromSize, typename From >
BOOST_FORCEINLINE To bitwise_cast(From const& from) BOOST_NOEXCEPT
{
    To to;
    BOOST_ATOMIC_DETAIL_MEMCPY
    (
        atomics::detail::addressof(to),
        atomics::detail::addressof(from),
        (FromSize < sizeof(To) ? FromSize : sizeof(To))
    );
    atomics::detail::clear_tail_padding_bits< FromSize >(to);
    return to;
}

template< typename To, typename From >
BOOST_FORCEINLINE To bitwise_cast(From const& from) BOOST_NOEXCEPT
{
    return atomics::detail::bitwise_cast< To, sizeof(From) >(from);
}

} // namespace detail
} // namespace atomics
} // namespace boost

#if defined(BOOST_GCC) && BOOST_GCC >= 80000
#pragma GCC diagnostic pop
#endif

#endif // BOOST_ATOMIC_DETAIL_BITWISE_CAST_HPP_INCLUDED_

/* bitwise_cast.hpp
ZbUIHP+xv2PnuJgJWQ5GB6a3grKwcfEOuPsRZbHqC0121zkRcr2Apx6mRjO62TI1EEShHIvtv8LdqHV216eeam4hTxKky8Me7yKsBkw4J8CFu5fyGs5IYoWuMMgig9HGDoumZxwmq+YBVOsNEgLMS4B6pTtL7Ykwugsj2rgMtn0HMTwwxST4eQwGJxHYrJFTXOCyA3wOSrzEDuW2Lsge2o/i4j8YtN2dMLNqWkIEezNImFs1lKTPjWIm4l54JZtVgHhfUNgMhb0zpeKB7a+rPR2EDJIMsVNsr+zC3MvLlTdA7bnlVDi6K40wtOyTLcC4VJrxjZ4stQvlK8MEoIPF+ao3HfT5e8v1NM6mjoWmlvEY6X4VTn0t1MIRSsaKjWUdCkT9l5W8fwckaMi2rmxB2NDPiqdFz1q3/L1uQQI5woev3xa+KBtoylYyFf1GtNp/4zsAEIhgWonLyVVU+rZNKGrSlwj0GWhB0qSE7EQEtpgK8BAyUdYs21yAylwZb+mg/nGAgjrFF/gYWftenYXW1k57xrkzKNf4bHWvh1Owk4onhvfvNKjhM9QOtw==
*/