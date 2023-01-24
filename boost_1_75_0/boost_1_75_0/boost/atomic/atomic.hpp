/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2011 Helge Bahmann
 * Copyright (c) 2013 Tim Blechmann
 * Copyright (c) 2014 Andrey Semashev
 */
/*!
 * \file   atomic/atomic.hpp
 *
 * This header contains definition of \c atomic template and \c atomic_flag.
 */

#ifndef BOOST_ATOMIC_ATOMIC_HPP_INCLUDED_
#define BOOST_ATOMIC_ATOMIC_HPP_INCLUDED_

#include <boost/atomic/capabilities.hpp>
#include <boost/atomic/detail/atomic_template.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

using atomics::atomic;

using atomics::atomic_char;
using atomics::atomic_uchar;
using atomics::atomic_schar;
using atomics::atomic_uint8_t;
using atomics::atomic_int8_t;
using atomics::atomic_ushort;
using atomics::atomic_short;
using atomics::atomic_uint16_t;
using atomics::atomic_int16_t;
using atomics::atomic_uint;
using atomics::atomic_int;
using atomics::atomic_uint32_t;
using atomics::atomic_int32_t;
using atomics::atomic_ulong;
using atomics::atomic_long;
using atomics::atomic_uint64_t;
using atomics::atomic_int64_t;
#ifdef BOOST_HAS_LONG_LONG
using atomics::atomic_ullong;
using atomics::atomic_llong;
#endif
using atomics::atomic_address;
using atomics::atomic_bool;
using atomics::atomic_wchar_t;
#if !defined(BOOST_NO_CXX11_CHAR16_T)
using atomics::atomic_char16_t;
#endif
#if !defined(BOOST_NO_CXX11_CHAR32_T)
using atomics::atomic_char32_t;
#endif

using atomics::atomic_int_least8_t;
using atomics::atomic_uint_least8_t;
using atomics::atomic_int_least16_t;
using atomics::atomic_uint_least16_t;
using atomics::atomic_int_least32_t;
using atomics::atomic_uint_least32_t;
using atomics::atomic_int_least64_t;
using atomics::atomic_uint_least64_t;
using atomics::atomic_int_fast8_t;
using atomics::atomic_uint_fast8_t;
using atomics::atomic_int_fast16_t;
using atomics::atomic_uint_fast16_t;
using atomics::atomic_int_fast32_t;
using atomics::atomic_uint_fast32_t;
using atomics::atomic_int_fast64_t;
using atomics::atomic_uint_fast64_t;
using atomics::atomic_intmax_t;
using atomics::atomic_uintmax_t;

#if !defined(BOOST_ATOMIC_NO_FLOATING_POINT)
using atomics::atomic_float_t;
using atomics::atomic_double_t;
using atomics::atomic_long_double_t;
#endif

using atomics::atomic_size_t;
using atomics::atomic_ptrdiff_t;

#if defined(BOOST_HAS_INTPTR_T)
using atomics::atomic_intptr_t;
using atomics::atomic_uintptr_t;
#endif

} // namespace boost

#endif // BOOST_ATOMIC_ATOMIC_HPP_INCLUDED_

/* atomic.hpp
uUfRGMjdUYpzmzpEUxr34xaWo+xHgtqX4rdQeG4hrsSyM9K7HH08XvBO4cbeQ51zaSZVz7jjgOGW0JAjnH6Vq0sLZ9XCSII4OYJWYg6VHHzwAqTsCRLjcMPsXnUR+3wLg3CmA8P8zuarBpJ36hGBXfwcJnmt75pvYEr7vdRxo3sP9DR5WxsZwpNgXMAZGr+QvCv60Ea/hotn+eBWyAuty28zXOIdS4VVX370ab1H6mvBtpGbxsaH4kVu8UyM2okGuon5lLOpX6Zm8WDtRt18frEHf4N6lysDAbMnpqh2pKuBvMyF5pqaSrWr3VnSn4N86IIyiQCbt9IEJuTdmfR0AzIrHCtNO4ovOF+OgYNUmdkVGU0NVi9vFE6nZPRcdG6BsHig4L/3pGtNg7az6NZX2YuF5Xia117LISxsvaewSeB8Eg52rP40o9UdyfDMpiWD6jaBFXzXU3AlChIG4GjCiW37xrZxY9u27Qkntm3bNk6cnGhi+8Tm7tbWVu3D1nZXV9f/8r9/wTiao6mn4T+6RrsmiaZ0HPUP01U2s0pvU39sP9s2odcn98d1y3vl5sHoxXgwbDAnVXL4kndEODwQto41Lz3LOD7t1uYOMzu6bbgz6esyyJxDNvqPnbGy46kWT+DyHQJSdvvEL29imK+hoMwpIQpqXmBvbsAOnxyXpoRwWnfst+2kvypl3sntFlBFtE5AJmvu/enMItwD
*/