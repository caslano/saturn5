/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2009 Helge Bahmann
 * Copyright (c) 2012 Tim Blechmann
 * Copyright (c) 2013-2018, 2020-2021 Andrey Semashev
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
#include <boost/atomic/detail/type_traits/has_unique_object_representations.hpp>
#include <boost/atomic/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if !defined(BOOST_ATOMIC_DETAIL_NO_HAS_UNIQUE_OBJECT_REPRESENTATIONS)

#if defined(__has_builtin)
#if __has_builtin(__builtin_bit_cast)
#define BOOST_ATOMIC_DETAIL_BIT_CAST(x, y) __builtin_bit_cast(x, y)
#endif
#endif

#if !defined(BOOST_ATOMIC_DETAIL_BIT_CAST) && defined(BOOST_MSVC) && BOOST_MSVC >= 1926
#define BOOST_ATOMIC_DETAIL_BIT_CAST(x, y) __builtin_bit_cast(x, y)
#endif

#endif // !defined(BOOST_ATOMIC_DETAIL_NO_HAS_UNIQUE_OBJECT_REPRESENTATIONS)

#if defined(BOOST_NO_CXX11_CONSTEXPR) || !defined(BOOST_ATOMIC_DETAIL_BIT_CAST) || !defined(BOOST_ATOMIC_DETAIL_HAS_BUILTIN_ADDRESSOF)
#define BOOST_ATOMIC_DETAIL_NO_CXX11_CONSTEXPR_BITWISE_CAST
#endif

#if !defined(BOOST_ATOMIC_DETAIL_NO_CXX11_CONSTEXPR_BITWISE_CAST)
#define BOOST_ATOMIC_DETAIL_CONSTEXPR_BITWISE_CAST BOOST_CONSTEXPR
#else
#define BOOST_ATOMIC_DETAIL_CONSTEXPR_BITWISE_CAST
#endif

#if defined(BOOST_GCC) && BOOST_GCC >= 80000
#pragma GCC diagnostic push
// copying an object of non-trivial type X from an array of Y. This is benign because we use memcpy to copy trivially copyable objects.
#pragma GCC diagnostic ignored "-Wclass-memaccess"
#endif

namespace boost {
namespace atomics {
namespace detail {

template< std::size_t ValueSize, typename To >
BOOST_FORCEINLINE void clear_tail_padding_bits(To& to, atomics::detail::true_type) BOOST_NOEXCEPT
{
    BOOST_ATOMIC_DETAIL_MEMSET(reinterpret_cast< unsigned char* >(atomics::detail::addressof(to)) + ValueSize, 0, sizeof(To) - ValueSize);
}

template< std::size_t ValueSize, typename To >
BOOST_FORCEINLINE void clear_tail_padding_bits(To&, atomics::detail::false_type) BOOST_NOEXCEPT
{
}

template< std::size_t ValueSize, typename To >
BOOST_FORCEINLINE void clear_tail_padding_bits(To& to) BOOST_NOEXCEPT
{
    atomics::detail::clear_tail_padding_bits< ValueSize >(to, atomics::detail::integral_constant< bool, ValueSize < sizeof(To) >());
}

template< typename To, std::size_t FromValueSize, typename From >
BOOST_FORCEINLINE To bitwise_cast_memcpy(From const& from) BOOST_NOEXCEPT
{
    To to;
#if !defined(BOOST_ATOMIC_NO_CLEAR_PADDING)
    From from2(from);
    BOOST_ATOMIC_DETAIL_CLEAR_PADDING(atomics::detail::addressof(from2));
    BOOST_ATOMIC_DETAIL_MEMCPY
    (
        atomics::detail::addressof(to),
        atomics::detail::addressof(from2),
        (FromValueSize < sizeof(To) ? FromValueSize : sizeof(To))
    );
#else
    BOOST_ATOMIC_DETAIL_MEMCPY
    (
        atomics::detail::addressof(to),
        atomics::detail::addressof(from),
        (FromValueSize < sizeof(To) ? FromValueSize : sizeof(To))
    );
#endif
    atomics::detail::clear_tail_padding_bits< FromValueSize >(to);
    return to;
}

#if defined(BOOST_ATOMIC_DETAIL_BIT_CAST)

template< typename To, std::size_t FromValueSize, typename From >
BOOST_FORCEINLINE BOOST_ATOMIC_DETAIL_CONSTEXPR_BITWISE_CAST To bitwise_cast_impl(From const& from, atomics::detail::true_type) BOOST_NOEXCEPT
{
    // This implementation is only called when the From type has no padding and From and To have the same size
    return BOOST_ATOMIC_DETAIL_BIT_CAST(To, from);
}

template< typename To, std::size_t FromValueSize, typename From >
BOOST_FORCEINLINE To bitwise_cast_impl(From const& from, atomics::detail::false_type) BOOST_NOEXCEPT
{
    return atomics::detail::bitwise_cast_memcpy< To, FromValueSize >(from);
}

template< typename To, std::size_t FromValueSize, typename From >
BOOST_FORCEINLINE BOOST_ATOMIC_DETAIL_CONSTEXPR_BITWISE_CAST To bitwise_cast(From const& from) BOOST_NOEXCEPT
{
    return atomics::detail::bitwise_cast_impl< To, FromValueSize >(from, atomics::detail::integral_constant< bool,
        FromValueSize == sizeof(To) && atomics::detail::has_unique_object_representations< From >::value >());
}

#else // defined(BOOST_ATOMIC_DETAIL_BIT_CAST)

template< typename To, std::size_t FromValueSize, typename From >
BOOST_FORCEINLINE To bitwise_cast(From const& from) BOOST_NOEXCEPT
{
    return atomics::detail::bitwise_cast_memcpy< To, FromValueSize >(from);
}

#endif // defined(BOOST_ATOMIC_DETAIL_BIT_CAST)

//! Converts the source object to the target type, possibly by padding or truncating it on the right, and clearing any padding bits (if supported by compiler). Preserves value bits unchanged.
template< typename To, typename From >
BOOST_FORCEINLINE BOOST_ATOMIC_DETAIL_CONSTEXPR_BITWISE_CAST To bitwise_cast(From const& from) BOOST_NOEXCEPT
{
    return atomics::detail::bitwise_cast< To, sizeof(From) >(from);
}

} // namespace detail
} // namespace atomics
} // namespace boost

#if defined(BOOST_GCC) && BOOST_GCC >= 80000
#pragma GCC diagnostic pop
#endif

#include <boost/atomic/detail/footer.hpp>

#endif // BOOST_ATOMIC_DETAIL_BITWISE_CAST_HPP_INCLUDED_

/* bitwise_cast.hpp
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
*/