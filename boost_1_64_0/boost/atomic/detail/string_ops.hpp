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
A33T3RpVkkhxVZqaojJ8aqd48TK5FWje+3KHCAVEQeYAWmDREsnPIbkJhP77EFt03ECCUsmfYslx8ozdSH/luvJ/ef3dZwPG2jwYo4mnEJopJcYgibKjv/upgqWvtjnbszOKXdQhQKEBHBE1rQUxN+6wkW+0ek8Wfqkj6Law2vY1t0K/9rSUA9zwKDxDRyRKJfzgASxnSFNXOpCNgR3CJicSdp+bqQkBUyj4XV/uyJLeF3zM2m63+DUykwQpKpQkToJpvW6GVpeh5wpJCqfRSqRfGfQJeua52/z0esS8Wcal1iaG9UknvKDCG5Xd1yAZZyYVBByW6BMFV9sN7QBdOJIC/L61uplo1ggrFBxuT3P/Wh6c6tGXQkQZN7xlVbAUZuv5BfCx+7yZH0BKPhJsWWTQX4zdqjb6UozJj0M1ylVpEhI1SKDkfrbiOIEs2V5sMhQe9l00jsOVg9sOPR02pLsKlibt6s6H5dwZzEgRkFCW2CPyyt6w7gz8z0J3/lus05s41LlP2henl8kmN8xcQBGsxzmegKixyy3U4fuhryk5KgRTEsryEvnyvA==
*/