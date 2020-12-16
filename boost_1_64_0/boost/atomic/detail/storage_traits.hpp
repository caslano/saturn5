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
BzMukz5qFuMJtWWkPTsydUZ58fQy20xRwuMJX1rsDK/dW4IIYj+w2mE/kB/SySR9ljzBIqwdz2U18jw5dOzYqfJOtuZEWUrN/pDPkcNacfpcGLw2bp73CkNBzw+Nf07zfx4Iem4Jvu//uTz/vH9Am8Mebdsya3u/5sff+IfTOwc9hwQ9JwQ9hwQ9Hzbd81vQc2Nk7JZrqdd4qVV/7D5bx+rZ8BB9b6iPvjfUX98XOkHfF0qL44/VYSt9dTjmcc05pjnHM8YyM46ZMcyMWbGNVzlmnJIxSsanvjjGJPd4xFjkHIOgGXfMmMN4E32MyRrkO7bImJKvY0jfwc5xI2i8cI4VvuOEc2zQccE5JrjGAt8xILjPHyF9feP7efp1Z39u+vKs1fu+j97/2//b/9v/2//b/9v/2//b/9v/a6rfj/T8zzdX9v75335+n9PdMnZazNPKrzfuIFwX3J0ZzO2+3are3vhDxp2UPbdo3rSyguEF5we/A6Dp2kv40Wmyn2jpNIdd/VgJTzHr3lnq97P5z3bk57ZrGuM610aRpuScstklxg5nkoQnG/vDc5F7bvfY96lz2+EfC5GJY8ikx7J87PCHWf7f/B6m62XH6FxJpuq6wqvrqdnjBw0fOilQz5qmj9XS6Hm+6jQS9hN/nZrwbl6dmrB2Zs1+fVqtvo5t5HsLogejr/kxv7MQ0VVZgr+uqr26Kpk2d9rs0mh7OEfRVXUDuqqOoqvq/7CuIm14Zdirq3vQVfo79XU1dHD28GxbWQVlBXNLg/VFOqOvq3s49aVhwfoiPFBfhDWtvq7usWf6Sm7u7fPuQ18lHn05u7xgfZHO9ENHSP1ig0OSRPq8RYSbPs/ED+zzCA/s8wiL3uddRri7zztvL/u8I6ReikyN7vMGtnDVTdV1pUfXpssL1HOlo14e4WrHlQ3Uy8oo9bKyievlEY1sxydH+rwDvLp6IMNeCK2vq1FDc8YNPil76NTBQ8fmTB03dMx4vnM1NFhvpDd6W+LSG2HBepPwQL0R1rR6W9JIvUX2HL21pVdvD6G3bJfesocPHtcvSv3KduipMqO+nrIb0FN2FD1lN7GeKjP2TE/PJ3r19FvyWlFfTw3eexDf6KmTqz6taEBPK6LoaUUT66lTI+tTZHzIPNA7PqxGTzUuPY2N8Z6YdKbP7if6mlvvnjhuk3N80PjB4wPhgeMDYdHHhwM2eceHi/ZyfOgnep7bqHviiK7zWrnqpOgabvLquvysWUXTo47Fks7UzX6uuklYcN2U8MC6SVjT1s1+jaybkfH0yoP89VXh1lcszxBRdFURXVeER3mG+C/R1Zpkr64et58hXLoSi+fBY0dE/Q6MQ1ePZbieIaLrivAozxBNrKvHGjk2RHT1UWuvrp6ynyHe89HV2KFjgnUlaYyunnDpirBgXUl4oK4Ia1pdPdFIXQ1SXeW08Y4PfyCvEqMr8xa9a94k8P020kafN1lEuBkjTPzAMYLw4DGCsOjPEIQ7x4gTuzRu3kTfF9rreZPIGLG4ratuqr4r/fRt+r1AXZMueD6gMnr9JDzKc4Srfr7aiPqpOmuS+YDV7fz1ZW326svMnwTXTdIF64uwYH1JeKC+CPvP6ivSnrelevVVZT8/ePXlmkMJ1Blpg+dQsqPrjPAozxJNrLPGzqFEdJab5u0Dn7OfJXx15ugCg+sZad3zKMw4OPrAhwg3faCJH9gHEh7YBxIWvQ98fLO7D2zcPIrq2mceBZn2oA9c0t5VR1XfW3z1rV1gsK5JFzyXsqWB+rklSv3c0sT1s7FzKadFnnU7uPXFsQz4vkdfAfMpgbojj+D5FMKCdSfhgbojrGl119j5lMi9YE1Hr+4=
*/