//  Copyright (C) 2011-2013, 2016 Tim Blechmann
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_LOCKFREE_DETAIL_ATOMIC_HPP
#define BOOST_LOCKFREE_DETAIL_ATOMIC_HPP

#include <boost/config.hpp>

#ifndef BOOST_LOCKFREE_FORCE_STD_ATOMIC

#define BOOST_LOCKFREE_NO_HDR_ATOMIC

// MSVC supports atomic<> from version 2012 onwards.
#if defined(BOOST_MSVC) && (BOOST_MSVC >= 1700)
#undef BOOST_LOCKFREE_NO_HDR_ATOMIC
#endif


// GCC supports atomic<> from version 4.8 onwards.
#if (BOOST_GCC >= 40800) && (__cplusplus >= 201103L)
#undef BOOST_LOCKFREE_NO_HDR_ATOMIC
#endif


// Apple clang is 2 mayor versions ahead, but in fact 1 minor version behind
#ifdef BOOST_CLANG

#define BOOST_ATOMIC_CLANG_VERSION (__clang_major__ * 10000 + __clang_minor__ * 100 + __clang_patchlevel__)

#if  defined(__apple_build_version__) && (BOOST_ATOMIC_CLANG_VERSION >= 60100) && (__cplusplus >= 201103L)
#undef BOOST_LOCKFREE_NO_HDR_ATOMIC
#endif

#if !defined(__apple_build_version__) && (BOOST_ATOMIC_CLANG_VERSION >= 30600) && (__cplusplus >= 201103L)
#undef BOOST_LOCKFREE_NO_HDR_ATOMIC
#endif

#undef BOOST_ATOMIC_CLANG_VERSION

#endif // BOOST_CLANG

// Stdlib should also be checked
#include <boost/config.hpp>
#if defined(BOOST_NO_CXX11_HDR_ATOMIC) && !defined(BOOST_LOCKFREE_NO_HDR_ATOMIC)
#  define BOOST_LOCKFREE_NO_HDR_ATOMIC
#endif

#endif // BOOST_LOCKFREE_FORCE_STD_ATOMIC


#if defined(BOOST_LOCKFREE_NO_HDR_ATOMIC) || defined(BOOST_LOCKFREE_FORCE_BOOST_ATOMIC)
#include <boost/atomic.hpp>
#else
#include <atomic>
#endif

namespace boost {
namespace lockfree {
namespace detail {

#if defined(BOOST_LOCKFREE_NO_HDR_ATOMIC) || defined(BOOST_LOCKFREE_FORCE_BOOST_ATOMIC)
using boost::atomic;
using boost::memory_order_acquire;
using boost::memory_order_consume;
using boost::memory_order_relaxed;
using boost::memory_order_release;
#else
using std::atomic;
using std::memory_order_acquire;
using std::memory_order_consume;
using std::memory_order_relaxed;
using std::memory_order_release;
#endif

}
using detail::atomic;
using detail::memory_order_acquire;
using detail::memory_order_consume;
using detail::memory_order_relaxed;
using detail::memory_order_release;

}}

#endif /* BOOST_LOCKFREE_DETAIL_ATOMIC_HPP */

/* atomic.hpp
wwVvwa9Cqw0vzW1wrF5HM/N5zX/8w88Nr5PdBsfq5SWvSsELBCLvGV49boNj9ZpBXtMEL/nKcy8YXre5DY7VayZ5TRa8x3+94/eG1x/dBsfqRXNYPa/UEw8eb3gdNcLgWL2KmTmvTR9v2GV4tY8wOFYvmv1qRwje1pIZ8w2va0cYHKvXMeQleZt2vf2x4fXaCINj9aJ5s36VPyj8bdbw+mSEwbF6HUteHsHzXzHV1A4r8g2O1WsOecnxf9cT1ac=
*/