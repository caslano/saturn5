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
4iEQJuCXPlfNJgrbNQ/qo1I4PT96NZk9KAwTA0/73D44TPvwRAsc/zVSNxbh3HzkN3FEFtRNyWrz/V6vNCxPg+t2nRwaKy+KKNGbayPifozbNTCUpNXCms8PqX5sgLrv16KHA5FNc3RQNAvkBxL4cav5tAcGG6VbBmWKO/p2a1UEB++anZtrYGmnM+3HB+X8Ui6ahOzrsNFImVzQTwIqJbKonMyztIeeAqroTGnbe5mROJTUHRlNxRuiykUHe08kUGLPbu+sSG8hIfJOFJPHzRAax5YX7EiLe+ud8xSBEcgRlyKgVlC2J+9dFvrcp+SJ51vJkZd6mR7OQvytoalWfZIp8V0VjSTebqvErw06ocAbsmsfL+k9tea41DW0OGnmyJ34qxKQsEk17f9Jx9Hyi92y/qBOcLrohJib+wLg2pVtuKEnVYsSQmt8tJcLNWneUjulGaCjkp6sOvk5+fRzzZUaeoX+EiA4N1UYRDuRbRQAvA9SijB80Sag8sVuVid65dk1/KH4++nDv4azry4TEVg20H6nMOceIxRh/YXeJS941SIS2qj2mZoPcA==
*/