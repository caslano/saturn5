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
g6pzCYt13P/iMjzVz6KGIGgcMOHJ+IYcyzJ2FH8YpqgtGnG/G+WeJBoWomrECO0MYk4LhNrKKYndDBxVLpr37CGlO/jn6aN+T7iMnVqGEJZVKaULtSxDjuWhARUaY2/JVWysRY8xVtKZnoOYxmjZaDY2ydqZONuZ1PSujUYzBgIrYvRicG7vMYxdLNvVzrAuCUxDbud6NVYbPfTOee/FOwVKL3RNVLOqA9WifylUEwE7Xirn/9XKB6gy9ZpLUXFGKlqGP9Qfc03nMmdmOHriLD8qmQa+azHKENeGPB6x0RzTxCt8DGLCq+0fp+7R+ZCgXgTUOJbbeLeuq/rt4Y/H9s6J9SlBdt9QSwMECgAAAAgALWdKUrCBwvZjBgAA+BAAACgACQBjdXJsLW1hc3Rlci9kb2NzL2V4YW1wbGVzLzEwLWF0LWEtdGltZS5jVVQFAAG2SCRgrVdtc5tGEP6uX7HjTDrCIZKTfmlix1NVVlJNHcljyU0yTYc5wSKuhjt6d1hWXv57d0FIsg31l+CxgNv3Z/f2lv7hj7s6cAiPXkH5H9BF91Liwuh/MHTN3EHwDao/kvpM98eM9GEn8i3w4HGRb9AtRYKNlRN+DoLHDH1m3/inz5KfA36kFRJjyaHO10YuEwfdoQcvXr36
*/