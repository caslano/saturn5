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
nB6a+StE6f7aYLNZ4yag27DGK9BxnWFgc/BPNdRdD2yvWoc1CHDPYlWry7SsMMzgdV5AHsXsob9nM3zrcClL29e+JTGfltSpUbx944LeAGq7PW2aB7mnV8U3c6qlylFoYP99InhBnazii+4ykJcV4Qj5k8s7SN3ir08P1SFvmrxFdb1K+vwUTPlFN/9UtiV3620HnXp/JzwrPu/GEo/QLZuaxiQReaoR4GZ9/HTvr9xagFDfr1lRHhX0AcXYFW5GZhY7PAEQapU4GHmOCFjUyw39WYECT24i0tVcyb1v4ke0JzJEqDH/8NzU81EqSh+QbMf6tj/54Tstf8wuR50LXqjRtnFPjnTfRzJidinMGvZWLuFRr6L5XgejctiJHVtzvTasrZleQaCWckwSe5sRXT6Rgw6u2yhjCHvszpttcnc/QZRDcX4aeFmKFAH2trjCCEbpK4eTKmtcBeL9457D2nnDDf/tuy4hvfXm/z6wZj4HprotYzxTwipH5CTfLWWUFS5rQjT8A41sYYPAXu2Ts/D8rlByGgY+BSVQUuBScrHuHc2dgY9LcgVpwt+TJTQXShnFvJAJwDhdbSAdqaj0LKUsEw+/ulD+LIXsJh1bxHLZ0OPXHouJLgODrXfGnChygwUz62ydrqJGhU9g15zK5cZWHjdCJJewziF7n5pvpIKRd0iAD3DvpOV412urJcg6jc1g8rxv5Y77SFQL
*/