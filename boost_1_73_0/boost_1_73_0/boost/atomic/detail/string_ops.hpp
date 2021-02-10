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
wgS+63EbeeuD9VVCoMDWWy279ccqoW5dot5PAKmHZemJoVILsQQytTmia7mvobwy3XiOYwiSQSMCLi9RGY+2bzzF2MhCX6pxXRqKe4VJP6FUCSjvo4GC7U4bR5FDZ5QLD2EJkcm7BcRvXkoI6CA55cYIqkFqBDF71iSernqGsk7COE2qsLsBkCEIURoyVWwwojxcuBE0cxxKPHKutBTKjRIAHh0puU6UYRPHGx4IWk2KQ1ZPCMPmqUoOU9u0O7rC/ClwwXUwLkjHkEPEAsoKlWnPvz19b17yePB8GCVCRD5TpouwwegQB4mbQy9l15TNeMOLAdDgPCGxKB1dbWd3r0wrcY5gaMOIBwFncq8Q9jEDje6mAw1BjTxoCUStaApyZng4GvKSwFdhP0dG0RjyC0layMJw4rsvL9ga+zTU8KcOJ9Np65I7xp8XZrQgAdRwEcQctyEmExhM6g3yDx057dpPBcLveuECnkFFUrIdR/VtG1mq1NFxzXKbQQ8eYUdH5OJie8xSyhMyh0bxR9kpylucnwra/x7kMsS5QJ6seTynFuYp6dYFjhgifSpshJB3FzxJkYMD5WGBSS6htkso/BdQcBZe9RbyxdIoJcGgHvK5Q00SOEJps8H1AAtqMSZxXYeDj/eQYk0oeqrh
*/