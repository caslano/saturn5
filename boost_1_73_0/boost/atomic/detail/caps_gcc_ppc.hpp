/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2009 Helge Bahmann
 * Copyright (c) 2013 Tim Blechmann
 * Copyright (c) 2014 Andrey Semashev
 */
/*!
 * \file   atomic/detail/caps_gcc_ppc.hpp
 *
 * This header defines feature capabilities macros
 */

#ifndef BOOST_ATOMIC_DETAIL_CAPS_GCC_PPC_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_CAPS_GCC_PPC_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/hwcaps_gcc_ppc.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#define BOOST_ATOMIC_INT8_LOCK_FREE 2
#define BOOST_ATOMIC_INT16_LOCK_FREE 2
#define BOOST_ATOMIC_INT32_LOCK_FREE 2
#if defined(BOOST_ATOMIC_DETAIL_PPC_HAS_LDARX_STDCX)
#define BOOST_ATOMIC_INT64_LOCK_FREE 2
#endif
#define BOOST_ATOMIC_POINTER_LOCK_FREE 2

#define BOOST_ATOMIC_THREAD_FENCE 2
#define BOOST_ATOMIC_SIGNAL_FENCE 2

#endif // BOOST_ATOMIC_DETAIL_CAPS_GCC_PPC_HPP_INCLUDED_

/* caps_gcc_ppc.hpp
8D6Fq+Ae7GXguglXBNfX7sVeBu4zv/3Jyvo94H+B60e4/vSdfsui/KRCOWjObnoG9Dz6OQubf5vGlB39K31uJn2ldR/9Gdh1iT76Zx600LbDESU/Cp7G9HH/DmLqO62UxxpLXsQdsu+6COk0XAjI5PoTas2vdztL8ejA8jJaMsQhx6N/LWgR0/Dvt75rB34ZjFUxtQr8Qr5yqV/SNVXryu20Y/FhTRCbWVVZrg9WJ5wzI+5N
*/