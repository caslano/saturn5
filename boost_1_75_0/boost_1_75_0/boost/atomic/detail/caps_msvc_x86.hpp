/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2009 Helge Bahmann
 * Copyright (c) 2013 Tim Blechmann
 * Copyright (c) 2012 - 2014 Andrey Semashev
 */
/*!
 * \file   atomic/detail/caps_msvc_x86.hpp
 *
 * This header defines feature capabilities macros
 */

#ifndef BOOST_ATOMIC_DETAIL_CAPS_MSVC_X86_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_CAPS_MSVC_X86_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if defined(_M_IX86) && _M_IX86 >= 500
#define BOOST_ATOMIC_DETAIL_X86_HAS_CMPXCHG8B 1
#endif

#if !defined(BOOST_ATOMIC_NO_CMPXCHG16B)
#if defined(__clang__) && (defined(_M_AMD64) || defined(__x86_64__)) && defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_16)
#define BOOST_ATOMIC_DETAIL_X86_HAS_CMPXCHG16B 1
#elif _MSC_VER >= 1500 && defined(_M_AMD64)
#define BOOST_ATOMIC_DETAIL_X86_HAS_CMPXCHG16B 1
#endif
#endif

#if defined(_MSC_VER) && (defined(_M_AMD64) || (defined(_M_IX86) && defined(_M_IX86_FP) && _M_IX86_FP >= 2))
// Use mfence only if SSE2 is available
#define BOOST_ATOMIC_DETAIL_X86_HAS_MFENCE 1
#endif

#define BOOST_ATOMIC_INT8_LOCK_FREE 2
#define BOOST_ATOMIC_INT16_LOCK_FREE 2
#define BOOST_ATOMIC_INT32_LOCK_FREE 2

#if defined(_M_AMD64) || defined(BOOST_ATOMIC_DETAIL_X86_HAS_CMPXCHG8B)
#define BOOST_ATOMIC_INT64_LOCK_FREE 2
#endif

#if defined(BOOST_ATOMIC_DETAIL_X86_HAS_CMPXCHG16B) && (defined(BOOST_HAS_INT128) || !defined(BOOST_NO_ALIGNMENT))
#define BOOST_ATOMIC_INT128_LOCK_FREE 2
#endif

#define BOOST_ATOMIC_POINTER_LOCK_FREE 2

#define BOOST_ATOMIC_THREAD_FENCE 2
#define BOOST_ATOMIC_SIGNAL_FENCE 2

#endif // BOOST_ATOMIC_DETAIL_CAPS_MSVC_X86_HPP_INCLUDED_

/* caps_msvc_x86.hpp
bQ3CzJrU9BFsHjdU3187z3zLUhVDsg4GhYJMqh42wHgpT69p+882r7ou81g+resDuXYbD9+eL888YPSRr76iqs2g+SdywT9FhaXGuN+OuDYvLCUN/xKe5OVQfyPYnlOY/w6uLugauQ09aLKNNjVfnssJA2aNos1bqvEACwKDaDrrqU7rnQRPu/YEj/KI3It6cG/6GcMEr3dq4HvS2ZDLL74znxH+BhHDffdDOWEb0QbN+OEa8Rj9MKI0wjTioMXXgtRC0ILRQu6ASUCmIWmNxyDtxW4Ab0BV+rkGRQOeAmEHxmfEVvCz4UcDZgNiA2EDZAO6EtLaj4qGmysRHbgKCG4whSCEAYsJBVumAdPHz9BUqt3dDhfIye2ULqpDZHAkyDgwIjCC1nXdmhbMM5YgZCc/gr6dky/tkwt2PP/xEEn7NWIEvLogJhwHx8sz1pw9oxq2Q1Yye4sCejzYiKr1l7OfER/gs0vZe4zDMU8Egi40u/EeXjHCvlItdHgckOOmyuSLVjlRGvh9VtPsOsgZAcM/Q9cJfyXMXVrf/TAd2P6DiYRbaGWb+ofoQlzSQ0Zj9SVZW3OAfb3IuLn8UbC4fBsbNIBRZMFdUbZuk6pzITxvCtVd4+KSF+lB754PJfOqdCCgYHZ0mZXUOSbMbkUxpg4zLc2u7IRL7ddo1HT6ELYeU9A6fRhKLh+OC3702afkO73qcIksXhR3Qzu6
*/