/*
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 *
 * (C) Copyright 2013 Tim Blechmann
 * (C) Copyright 2013 Andrey Semashev
 */

#ifndef BOOST_ATOMIC_DETAIL_PAUSE_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_PAUSE_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if defined(_MSC_VER) && (defined(_M_AMD64) || defined(_M_IX86))
extern "C" void _mm_pause(void);
#if defined(BOOST_MSVC)
#pragma intrinsic(_mm_pause)
#endif
#endif

namespace boost {
namespace atomics {
namespace detail {

BOOST_FORCEINLINE void pause() BOOST_NOEXCEPT
{
#if defined(_MSC_VER) && (defined(_M_AMD64) || defined(_M_IX86))
    _mm_pause();
#elif defined(__GNUC__) && (defined(__i386__) || defined(__x86_64__))
    __asm__ __volatile__("pause;");
#endif
}

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_PAUSE_HPP_INCLUDED_

/* pause.hpp
rs83tqzG1CFMUTitLua7ggH3F5l8K3LEVgxUl44ClWlTnImbKjV2uHlGcDTcIgtuEeAuJsdfnac3BAv3LnIg+Lqwoq4/4IeWw05MXltk5HOh7aOOw34sLE1G9dmwbWE977KK7K4vMl/W59FyRA/6h/Sb29+LVdmiFoViC6v5KHLjkXzoYc5KYwenCvmGBn/HrS5lcImkwWIxwqlynPVBvsjES7U2aJweS0pruQcyFZcYc23Q
*/