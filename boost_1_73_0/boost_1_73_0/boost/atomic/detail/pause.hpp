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
1JcZxi0E2QT3ZDUaVuqbCqKyqN8ipgfQ7577xMrjVtjco79RtLe787K12zyEsuoddF1gWo8HmcT2vl//hcn67k7rBf6ncdDcO9jZh9e/Dg9xsjfxsXdYhPh4paL+t2R+vNv+5w+shVKQcCaz6cI1GnZ4gjX4tQGQhpDCkaVjaxnq8/qEUwIVA6uV3KHJ6S9QSwMECgAAAAgALWdKUtvvd/hdCQAAIhoAACMACQBjdXJsLW1hc3Rlci9kb2NzL2V4YW1wbGVzL2NyYXdsZXIuY1VUBQABtkgkYK0YaXPaSvI7v2JCNi7JBoOperuvfNUjWNhsMFAgJ07FKZVAI9CLrieNjJ21//t2z6ED2DXZWhKjoafv6elDrcP/36dGDsmbH4v/WfCBJ6eYJNGfdMF2Y1vWCxH/gOoBnm8JaZGC5MXSydskL0TjJJaUco5ry3pL0APqhl8tpHywcAkQIEPKL3ROFom99mlC5nZKHRKFZJElPrFDh/je/CnwO8eI2Yvi58RbrhjRejrptE9+J014dNrknzSJaEjGUZCS8z/5jwjWfywD2/OPF1FwifRDb0HDlJ6S24EphZsRgd3Y8+mpsGK5WChtjhfkb1r8Y9lcRKHrLUmzuXB9e5nCArRKpWrNznEbl6ixLri2aq1D
*/