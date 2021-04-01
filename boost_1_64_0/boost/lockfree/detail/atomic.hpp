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
Ix3Ph0RjQSwmrwia1jHlaeoAXAHikW+EtFzDNzIj+p+Hz9Bxo6J54y1Gxgdo4KvlnX4gAicULZPoMpweda02CLZBoK9ItMn3d7IiSXofG+GKwMEDXgbrOtft29sVmjQcVWbEJBpmBko3bureLHVMcghiwPqyePy4/gnhom+CZz4CtkieH68evaLEHx4ZIBfVkG0zPKQrLPDXQMlswDHfqWfK4BvJbgRdA3WqC37G024+3Xs8ICL3MpthvWmGL95SSyAtGQMAtBIk/QJdxgS4ZLB++XAd1yo3H3GV71ndqzsJWTIm7ACc+WkeAYi1ZiqUz/jKWaFAC46VR4C2O/tDy9m5E7R0nr2Ofe06MWnO2QjnpHQ3BlzsnWByJQFbQDKlNK6Cr+GvPrnpoOa/hiwocn80CyLe9naAwHOgOcwjLfwRFSRFni8XM9lwXtCXW0longmUq53uMDjtKtIoscIz7fmv9WsvPc4bTqm8CTQTk7Es+2axCEYwhZH5SL/v+vIHuN3EdGwAFLn/zPRex91qsydS5KTq7FY4larJoAhLuO5Fse1euiJBllpaoQ==
*/