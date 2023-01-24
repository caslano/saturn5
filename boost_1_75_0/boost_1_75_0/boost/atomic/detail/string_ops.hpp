/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2018 Andrey Semashev
 */
/*!
 * \file   atomic/detail/string_ops.hpp
 *
 * This header defines string operations for Boost.Atomic
 */

#ifndef BOOST_ATOMIC_DETAIL_STRING_OPS_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_STRING_OPS_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if defined(__has_builtin)
#if __has_builtin(__builtin_memcpy)
#define BOOST_ATOMIC_DETAIL_HAS_BUILTIN_MEMCPY
#endif
#if __has_builtin(__builtin_memcmp)
#define BOOST_ATOMIC_DETAIL_HAS_BUILTIN_MEMCMP
#endif
#if __has_builtin(__builtin_memset)
#define BOOST_ATOMIC_DETAIL_HAS_BUILTIN_MEMSET
#endif
#elif defined(BOOST_GCC)
#define BOOST_ATOMIC_DETAIL_HAS_BUILTIN_MEMCPY
#define BOOST_ATOMIC_DETAIL_HAS_BUILTIN_MEMCMP
#define BOOST_ATOMIC_DETAIL_HAS_BUILTIN_MEMSET
#endif

#if defined(BOOST_ATOMIC_DETAIL_HAS_BUILTIN_MEMCPY)
#define BOOST_ATOMIC_DETAIL_MEMCPY __builtin_memcpy
#else
#define BOOST_ATOMIC_DETAIL_MEMCPY std::memcpy
#endif

#if defined(BOOST_ATOMIC_DETAIL_HAS_BUILTIN_MEMCMP)
#define BOOST_ATOMIC_DETAIL_MEMCMP __builtin_memcmp
#else
#define BOOST_ATOMIC_DETAIL_MEMCMP std::memcmp
#endif

#if defined(BOOST_ATOMIC_DETAIL_HAS_BUILTIN_MEMSET)
#define BOOST_ATOMIC_DETAIL_MEMSET __builtin_memset
#else
#define BOOST_ATOMIC_DETAIL_MEMSET std::memset
#endif

#if !defined(BOOST_ATOMIC_DETAIL_HAS_BUILTIN_MEMCPY) || !defined(BOOST_ATOMIC_DETAIL_HAS_BUILTIN_MEMCMP) || !defined(BOOST_ATOMIC_DETAIL_HAS_BUILTIN_MEMSET)
#include <cstring>
#endif

#endif // BOOST_ATOMIC_DETAIL_STRING_OPS_HPP_INCLUDED_

/* string_ops.hpp
m8lhBudkFDjHfLbayKny9XgGhpbkITJQM+y7PxnV7U2phMppktEvUKV3iD/Il45ge0ruj0SVDbttY3shRDJ5ZnnGnn5JI+oUHzpE49KS2ZUqynh0ctjbSo2z2JXTy9g10ysq0RAfm+I7MnSLWTwyV2vfq4Fl8KcifB+4fBc0v6/jit2/5W6hjzTBzom5N6c7wUZwx9vWBPYQ2D0a9uNGHbxYqzpYV5VSkj+giWZYnioNN5yujZN83/cHiuB17OzAhG5V5EdYb2sgkfh6MfVyEGGw+RTVH37p4oKihuKvNi8iPwkDc6A2PzPPfcd8aUbZH7mbrFlXUhxG+LptxIXyQvby+LkjhwD7mksZ7/b5WFhDe36rPTZWFufZioo7l2ZqNuMVmY3Cub9e4INI7FmNShZsb+OVNNjmZYrkCqW136+LDo95FPwhf56Hbp1Z8xvuyR0ec5pmW/krtPnd1spPnF9T9fDENe8/pcdiFspqx7Cf7OFNqVWsoitZSx0PZfd/1OCuYBvodPqgdVBgQTF601n+pWxvTxmn+PeDOufl0ks5yxh9dsHonWGvUL56h2t2eBdGDystF20QOjRFG8XP910S5R9Mcgxz2FPWjZjunh2vDbjHxnsMRzUq9qzS1zsqr1uW43jH5JQrmdOpTSRio4V2wvHlkmQPjiLccRbqzEwP4t48T1imtxK4puoDnEk5LEax6nWrX2LU2VI1
*/