/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2009 Helge Bahmann
 * Copyright (c) 2012 Tim Blechmann
 * Copyright (c) 2013 - 2020 Andrey Semashev
 */
/*!
 * \file   atomic/detail/storage_traits.hpp
 *
 * This header defines underlying types used as storage
 */

#ifndef BOOST_ATOMIC_DETAIL_STORAGE_TRAITS_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_STORAGE_TRAITS_HPP_INCLUDED_

#include <cstddef>
#include <boost/cstdint.hpp>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/string_ops.hpp>
#include <boost/atomic/detail/type_traits/alignment_of.hpp>
#if defined(BOOST_ATOMIC_DETAIL_NO_CXX11_ALIGNAS)
#include <boost/type_traits/type_with_alignment.hpp>
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

template< typename T >
BOOST_FORCEINLINE void non_atomic_load(T const volatile& from, T& to) BOOST_NOEXCEPT
{
    to = from;
}

template< std::size_t Size, std::size_t Alignment = 1u >
struct BOOST_ATOMIC_DETAIL_MAY_ALIAS buffer_storage
{
#if !defined(BOOST_ATOMIC_DETAIL_NO_CXX11_ALIGNAS)
    alignas(Alignment) unsigned char data[Size];
#else
    union
    {
        unsigned char data[Size];
        typename boost::type_with_alignment< Alignment >::type aligner;
    };
#endif

    BOOST_FORCEINLINE bool operator! () const BOOST_NOEXCEPT
    {
        return (data[0] == 0u && BOOST_ATOMIC_DETAIL_MEMCMP(data, data + 1, Size - 1u) == 0);
    }

    BOOST_FORCEINLINE bool operator== (buffer_storage const& that) const BOOST_NOEXCEPT
    {
        return BOOST_ATOMIC_DETAIL_MEMCMP(data, that.data, Size) == 0;
    }

    BOOST_FORCEINLINE bool operator!= (buffer_storage const& that) const BOOST_NOEXCEPT
    {
        return BOOST_ATOMIC_DETAIL_MEMCMP(data, that.data, Size) != 0;
    }
};

template< std::size_t Size, std::size_t Alignment >
BOOST_FORCEINLINE void non_atomic_load(buffer_storage< Size, Alignment > const volatile& from, buffer_storage< Size, Alignment >& to) BOOST_NOEXCEPT
{
    BOOST_ATOMIC_DETAIL_MEMCPY(to.data, const_cast< unsigned char const* >(from.data), Size);
}

template< std::size_t Size >
struct storage_traits
{
    typedef buffer_storage< Size, 1u > type;

    static BOOST_CONSTEXPR_OR_CONST std::size_t native_alignment = 1u;

    // By default, prefer the maximum supported alignment
    static BOOST_CONSTEXPR_OR_CONST std::size_t alignment = 16u;
};

template< >
struct storage_traits< 1u >
{
    typedef boost::uint8_t BOOST_ATOMIC_DETAIL_MAY_ALIAS type;

    static BOOST_CONSTEXPR_OR_CONST std::size_t native_alignment = 1u;
    static BOOST_CONSTEXPR_OR_CONST std::size_t alignment = 1u;
};

template< >
struct storage_traits< 2u >
{
    typedef boost::uint16_t BOOST_ATOMIC_DETAIL_MAY_ALIAS type;

    static BOOST_CONSTEXPR_OR_CONST std::size_t native_alignment = atomics::detail::alignment_of< boost::uint16_t >::value;
    static BOOST_CONSTEXPR_OR_CONST std::size_t alignment = 2u;
};

template< >
struct storage_traits< 4u >
{
    typedef boost::uint32_t BOOST_ATOMIC_DETAIL_MAY_ALIAS type;

    static BOOST_CONSTEXPR_OR_CONST std::size_t native_alignment = atomics::detail::alignment_of< boost::uint32_t >::value;
    static BOOST_CONSTEXPR_OR_CONST std::size_t alignment = 4u;
};

template< >
struct storage_traits< 8u >
{
    typedef boost::uint64_t BOOST_ATOMIC_DETAIL_MAY_ALIAS type;

    static BOOST_CONSTEXPR_OR_CONST std::size_t native_alignment = atomics::detail::alignment_of< boost::uint64_t >::value;
    static BOOST_CONSTEXPR_OR_CONST std::size_t alignment = 8u;
};

#if defined(BOOST_HAS_INT128)

template< >
struct storage_traits< 16u >
{
    typedef boost::uint128_type BOOST_ATOMIC_DETAIL_MAY_ALIAS type;

    static BOOST_CONSTEXPR_OR_CONST std::size_t native_alignment = atomics::detail::alignment_of< boost::uint128_type >::value;
    static BOOST_CONSTEXPR_OR_CONST std::size_t alignment = 16u;
};

#else

#if (__cplusplus >= 201103L || (defined(_MSVC_LANG) && _MSVC_LANG >= 201103L)) &&\
    (!defined(BOOST_GCC_VERSION) || BOOST_GCC_VERSION >= 40900)
using std::max_align_t;
#else

#if defined(BOOST_MSVC)
#pragma warning(push)
// alignment is sensitive to packing
#pragma warning(disable: 4121)
#endif

class max_align_helper;
union max_align_t
{
    void* ptr;
    void (*fun_ptr)();
    int max_align_helper::*mem_ptr;
    void (max_align_helper::*mem_fun_ptr)();
    long long ll;
    long double ld;
#if defined(BOOST_HAS_INT128)
    boost::int128_type i128;
#endif
#if defined(BOOST_HAS_FLOAT128)
    boost::float128_type f128;
#endif
};

#if defined(BOOST_MSVC)
#pragma warning(pop)
#endif

#endif // __cplusplus >= 201103L || (defined(_MSVC_LANG) && _MSVC_LANG >= 201103L)

template< >
struct storage_traits< 16u >
{
    typedef buffer_storage< 16u, atomics::detail::alignment_of< atomics::detail::max_align_t >::value > type;

    static BOOST_CONSTEXPR_OR_CONST std::size_t native_alignment = atomics::detail::alignment_of< atomics::detail::max_align_t >::value;
    static BOOST_CONSTEXPR_OR_CONST std::size_t alignment = 16u;
};

#endif

template< typename T >
struct storage_size_of
{
    static BOOST_CONSTEXPR_OR_CONST std::size_t size = sizeof(T);
    static BOOST_CONSTEXPR_OR_CONST std::size_t value = (size == 3u ? 4u : (size >= 5u && size <= 7u ? 8u : (size >= 9u && size <= 15u ? 16u : size)));
};

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_STORAGE_TRAITS_HPP_INCLUDED_

/* storage_traits.hpp
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
*/