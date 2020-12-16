/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2014 Andrey Semashev
 */
/*!
 * \file   atomic/detail/int_sizes.hpp
 *
 * This header defines macros for testing buitin integer type sizes
 */

#ifndef BOOST_ATOMIC_DETAIL_INT_SIZES_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_INT_SIZES_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

// GCC and compatible compilers define internal macros with builtin type traits
#if defined(__SIZEOF_SHORT__)
#define BOOST_ATOMIC_DETAIL_SIZEOF_SHORT __SIZEOF_SHORT__
#endif
#if defined(__SIZEOF_INT__)
#define BOOST_ATOMIC_DETAIL_SIZEOF_INT __SIZEOF_INT__
#endif
#if defined(__SIZEOF_LONG__)
#define BOOST_ATOMIC_DETAIL_SIZEOF_LONG __SIZEOF_LONG__
#endif
#if defined(__SIZEOF_LONG_LONG__)
#define BOOST_ATOMIC_DETAIL_SIZEOF_LLONG __SIZEOF_LONG_LONG__
#endif
#if defined(__SIZEOF_WCHAR_T__)
#define BOOST_ATOMIC_DETAIL_SIZEOF_WCHAR_T __SIZEOF_WCHAR_T__
#endif
#if defined(__SIZEOF_POINTER__)
#define BOOST_ATOMIC_DETAIL_SIZEOF_POINTER __SIZEOF_POINTER__
#elif defined(_MSC_VER)
#if defined(_M_AMD64) || defined(_M_ARM64) || defined(_M_IA64)
#define BOOST_ATOMIC_DETAIL_SIZEOF_POINTER 8
#else
#define BOOST_ATOMIC_DETAIL_SIZEOF_POINTER 4
#endif
#endif

#if !defined(BOOST_ATOMIC_DETAIL_SIZEOF_SHORT) || !defined(BOOST_ATOMIC_DETAIL_SIZEOF_INT) ||\
    !defined(BOOST_ATOMIC_DETAIL_SIZEOF_LONG) || !defined(BOOST_ATOMIC_DETAIL_SIZEOF_LLONG)

// Try to deduce sizes from limits
#include <limits.h>
#include <boost/cstdint.hpp>

#if (USHRT_MAX + 0) == 0xff
#define BOOST_ATOMIC_DETAIL_SIZEOF_SHORT 1
#elif (USHRT_MAX + 0) == 0xffff
#define BOOST_ATOMIC_DETAIL_SIZEOF_SHORT 2
#elif (USHRT_MAX + 0) == 0xffffffff
#define BOOST_ATOMIC_DETAIL_SIZEOF_SHORT 4
#elif (USHRT_MAX + 0) == UINT64_C(0xffffffffffffffff)
#define BOOST_ATOMIC_DETAIL_SIZEOF_SHORT 8
#endif

#if (UINT_MAX + 0) == 0xff
#define BOOST_ATOMIC_DETAIL_SIZEOF_INT 1
#elif (UINT_MAX + 0) == 0xffff
#define BOOST_ATOMIC_DETAIL_SIZEOF_INT 2
#elif (UINT_MAX + 0) == 0xffffffff
#define BOOST_ATOMIC_DETAIL_SIZEOF_INT 4
#elif (UINT_MAX + 0) == UINT64_C(0xffffffffffffffff)
#define BOOST_ATOMIC_DETAIL_SIZEOF_INT 8
#endif

#if (ULONG_MAX + 0) == 0xff
#define BOOST_ATOMIC_DETAIL_SIZEOF_LONG 1
#elif (ULONG_MAX + 0) == 0xffff
#define BOOST_ATOMIC_DETAIL_SIZEOF_LONG 2
#elif (ULONG_MAX + 0) == 0xffffffff
#define BOOST_ATOMIC_DETAIL_SIZEOF_LONG 4
#elif (ULONG_MAX + 0) == UINT64_C(0xffffffffffffffff)
#define BOOST_ATOMIC_DETAIL_SIZEOF_LONG 8
#endif

#if defined(__hpux) // HP-UX's value of ULONG_LONG_MAX is unusable in preprocessor expressions
#define BOOST_ATOMIC_DETAIL_SIZEOF_LLONG 8
#else

// The list of the non-standard macros (the ones except ULLONG_MAX) is taken from cstdint.hpp
#if defined(ULLONG_MAX)
#define BOOST_ATOMIC_DETAIL_ULLONG_MAX ULLONG_MAX
#elif defined(ULONG_LONG_MAX)
#define BOOST_ATOMIC_DETAIL_ULLONG_MAX ULONG_LONG_MAX
#elif defined(ULONGLONG_MAX)
#define BOOST_ATOMIC_DETAIL_ULLONG_MAX ULONGLONG_MAX
#elif defined(_LLONG_MAX) // strangely enough, this one seems to be holding the limit for the unsigned integer
#define BOOST_ATOMIC_DETAIL_ULLONG_MAX _LLONG_MAX
#endif

#if (BOOST_ATOMIC_DETAIL_ULLONG_MAX + 0) == 0xff
#define BOOST_ATOMIC_DETAIL_SIZEOF_LLONG 1
#elif (BOOST_ATOMIC_DETAIL_ULLONG_MAX + 0) == 0xffff
#define BOOST_ATOMIC_DETAIL_SIZEOF_LLONG 2
#elif (BOOST_ATOMIC_DETAIL_ULLONG_MAX + 0) == 0xffffffff
#define BOOST_ATOMIC_DETAIL_SIZEOF_LLONG 4
#elif (BOOST_ATOMIC_DETAIL_ULLONG_MAX + 0) == UINT64_C(0xffffffffffffffff)
#define BOOST_ATOMIC_DETAIL_SIZEOF_LLONG 8
#endif

#endif // defined(__hpux)

#endif

#if !defined(BOOST_ATOMIC_DETAIL_SIZEOF_WCHAR_T)

#include <wchar.h>
#include <boost/cstdint.hpp>

#if defined(_MSC_VER) && (_MSC_VER <= 1310 || defined(UNDER_CE) && _MSC_VER <= 1500)
// MSVC 7.1 and MSVC 8 (arm) define WCHAR_MAX to a value not suitable for constant expressions
#define BOOST_ATOMIC_DETAIL_SIZEOF_WCHAR_T 2
#elif (WCHAR_MAX + 0) == 0xff || (WCHAR_MAX + 0) == 0x7f
#define BOOST_ATOMIC_DETAIL_SIZEOF_WCHAR_T 1
#elif (WCHAR_MAX + 0) == 0xffff || (WCHAR_MAX + 0) == 0x7fff
#define BOOST_ATOMIC_DETAIL_SIZEOF_WCHAR_T 2
#elif (WCHAR_MAX + 0) == 0xffffffff || (WCHAR_MAX + 0) == 0x7fffffff
#define BOOST_ATOMIC_DETAIL_SIZEOF_WCHAR_T 4
#elif (WCHAR_MAX + 0) == UINT64_C(0xffffffffffffffff) || (WCHAR_MAX + 0) == INT64_C(0x7fffffffffffffff)
#define BOOST_ATOMIC_DETAIL_SIZEOF_WCHAR_T 8
#endif
#endif

#if !defined(BOOST_ATOMIC_DETAIL_SIZEOF_SHORT) || !defined(BOOST_ATOMIC_DETAIL_SIZEOF_INT) ||\
    !defined(BOOST_ATOMIC_DETAIL_SIZEOF_LONG) || !defined(BOOST_ATOMIC_DETAIL_SIZEOF_LLONG) ||\
    !defined(BOOST_ATOMIC_DETAIL_SIZEOF_WCHAR_T)
#error Boost.Atomic: Failed to determine builtin integer sizes, the target platform is not supported. Please, report to the developers (patches are welcome).
#endif

#endif // BOOST_ATOMIC_DETAIL_INT_SIZES_HPP_INCLUDED_

/* int_sizes.hpp
yq+FHRk54ociweOHwsg8bWTWPRBL5ggy3ZHhmOvM99Aemb5BLXviunpv2dXnhfpcNEHiW+Aa+mkWadfCfj3atn8xQ/4mHP1dUDcrMf0X0k/WkIpafW/vfjfgv16DWTsQvWKb6JVZlwHdYZvojvGBgX6wDf3w+AFoTtZvUWmnAbAHHF1A+2+T8SMDp807YJR/QOM786DIvmyXcjU30Z5k3WyP0bEVyidfnzPxpvEOJ34/90ErY72P1zR5Zi3KmDY3RnaC0WfPWDP+OF8SuVfsH3D39DvuAh+xg2rfEcpjjBm7hVLGm7hurzPjw3aPD63bZbeLf0LX+NK8+E+fWyJrxs6E/JPDY7NV0jb6HrObeYe+sLpsaYXVW8fjc5L3Ebucq+LlpNlP8PhAM+NzmeQ3VNs9lP/1PM1cKXXqIfmX1dfXVl3mfkb7qhxjmKsMSxbzpMn4KX1hW9u4r+JKvs7meoKQEvZDZPwX9pLj4TtR4p5+N88sHd9NrvVPTD7hPk6Hb0tb9dB4KK/u4mvoCGP3xSQd493X1XjH+CCV2YNtya15yHRpvD6tawr+gILB/KSUtESXr7KteW4fIeoHUNvlZClDipmLp0l8vtsHn6l7oey7SJ6bHqRsN3RR/3vBxs1piclpwdPa8XOkaVq6qD+1lGg/R06YwbbubCvPawu3E+4g3EnYTriLMBr5u2FZ97a5qIC/mzO4dyTs0L/VL1u7fhpLPX4adZ6Jel5aE+P9z8rIecr4c2RcsU3Hlcrmm3c6jm54fJYcpw91abQh8ASYT1+V3hk5V5GZbz8yZlU235y7myT+V/sZ62bjL+yWu8T+x8wpseYp8jJzz8r25imPbKPPPJWhenW9yGUH/sm40vlJ047wn4tUP8duRwYJ11yk6Wx/f5Gqq9eKzN+ZtZtt3v9I+98o27ICvdG4nZwfilLc/iOfSkvs6q+71Sr/ZBpjyZFPn5mUiP+tqakjU8/GE1dG6vSkhWljRiadxpuDhGAmoQdvEfqlLkodkzoEge6EnKRuweSklGB20pxgl9RZyPRz3B+SdGAwQDyQlpiZ9Km05BNRUMqQ7jMGbo05DvzHAGPDO08b/aiQdh1t32xt9eqHd542fdGkfRHSuaekPRONH7xnZX938378l7I/mfhUeVffLPFgINbcniPH72/m9nkSn0Y/n9Du3P5D8qUuUXN7hp5fWtnvnCP32D11m61lOWTncn3rN88/IXU5Tt+bher2KNcSC3i2Msp3ri9sZ66/d3vkXE9+Zq6f7fh/SzNz/QrvXO+ELNXBd9NC8yf+KPtE+6PsqH9a5hD1R6lzmc+81xhj3tvoM+81eeY97/VYabpej1HYXsqRlKHwbtccV7O4YHzs99DItmvLrPtzrSy97yiVuG1nczf4KsFnHhPZLDhfZBPQkBTrFYLOb5pnP997nXPN/t7Gl/NFEu9i51L7Nwk+c5vx53q3yO63rqCVXPMbeUavQ94sF9vaX6r3+0Uum6Nkmvedv5Zt13IXV2jGUbNs24o2X+LrozJL5+hKkXuf3PD+SPDOq1Tf2iwyv7Luw77Ex6ek8cG4V+QGccyA0fmuO/Raw+uDUcv+FUkz1rfczpy9kfPkh8eHfCtOSUs8Pi14BZccvtcbKp/bPeRXsdQ7VozMdOM/sPFZ7/1WlsosUf+BXLfsTeOIRs6TV5PJa123WDJ7NC/uy7p6ZdSPo9cXIXP/0e+5OnqP1d6aeJU+Y7vGf2wbO6uEDH//gS07Ouc/sGVH5/2vxfIfeCiG/8ADOzrvP/DAjqP7Dzywo/N+2I7Vf2BrDP+Bh3d0zn8g6drzX8b+zvsv64j/wNC5Y14sn37Nx+DTr7nzOhU=
*/