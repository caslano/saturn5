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
#include <boost/atomic/detail/aligned_variable.hpp>
#include <boost/atomic/detail/type_traits/alignment_of.hpp>
#include <boost/atomic/detail/header.hpp>

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
    typedef unsigned char data_type[Size];
    BOOST_ATOMIC_DETAIL_ALIGNED_VAR_TPL(Alignment, data_type, data);

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

#include <boost/atomic/detail/footer.hpp>

#endif // BOOST_ATOMIC_DETAIL_STORAGE_TRAITS_HPP_INCLUDED_

/* storage_traits.hpp
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
*/