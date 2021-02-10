/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2009 Helge Bahmann
 * Copyright (c) 2012 Tim Blechmann
 * Copyright (c) 2013 - 2014 Andrey Semashev
 */
/*!
 * \file   atomic/detail/caps_gcc_x86.hpp
 *
 * This header defines feature capabilities macros
 */

#ifndef BOOST_ATOMIC_DETAIL_CAPS_GCC_X86_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_CAPS_GCC_X86_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/hwcaps_gcc_x86.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#define BOOST_ATOMIC_INT8_LOCK_FREE 2
#define BOOST_ATOMIC_INT16_LOCK_FREE 2
#define BOOST_ATOMIC_INT32_LOCK_FREE 2
#if defined(__x86_64__) || defined(BOOST_ATOMIC_DETAIL_X86_HAS_CMPXCHG8B)
#define BOOST_ATOMIC_INT64_LOCK_FREE 2
#endif
#if defined(BOOST_ATOMIC_DETAIL_X86_HAS_CMPXCHG16B) && (defined(BOOST_HAS_INT128) || !defined(BOOST_NO_ALIGNMENT))
#define BOOST_ATOMIC_INT128_LOCK_FREE 2
#endif
#define BOOST_ATOMIC_POINTER_LOCK_FREE 2

#define BOOST_ATOMIC_THREAD_FENCE 2
#define BOOST_ATOMIC_SIGNAL_FENCE 2

#endif // BOOST_ATOMIC_DETAIL_CAPS_GCC_X86_HPP_INCLUDED_

/* caps_gcc_x86.hpp
UlpGaRnzrTCrlLkFi7l2MOHRLaYcPt1hE6JPn9HZnEfY51ZVpTjHsEOV1oIGSp2dShqoedBRmmBLJo1ra8qjR9MPJ8hSpCkONIPNCx0Q89oh8n+rjBSF5EvgUpWLxPaQ8ZyiRnITLtIhL41GJhp+b0CzFdm2KdhErX0jQGUI1HOgATzvxrGbyNgVL4KTgyYPlodlwXfqzIpFmSGohgVOZEkZbURdtWzhyY+tws85MxZtgPNFoyT6SKNcRGXKCuxAdKGS0VXdbCr4muNLnP6WtZhDg753jWcHncg4cWlZCINm/Zq1WCWa2nWZw3Dgw/urtyeUyf747tcAzpXNB9MaQ/KYXG16pAqcpG5PueWrJX7VrnYzjtMcBRlNyNmK0oncRAqRLCaBjM64J5XEoe7+0fzHIrB0DVXtgeRmk6OEp/luupudq+qQRhizQn2UqOW6AVNuyDnbWrTuSGJHMbp4u9Fnlp8UjeSu/DZcD6tJgrRcAMtxZEeOi5TxB82Mw30u7lue3UOEc8M9c1PA0mGzek1NAxjUg8uqyfWSh848cyiHqGtDEMiYhDPa2twEsHtVQ5ANjbrapKWVV58KKq9oq+OOPrgBNLRtItmITBkVqVQ/xtdG4LtcxZTqMs9VYf4tYy8nk7Fv/4c+XND9
*/