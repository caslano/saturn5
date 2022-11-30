/*
 *          Copyright Andrey Semashev 2018 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          https://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   uncaught_exceptions.hpp
 * \author Andrey Semashev
 * \date   2018-11-10
 *
 * \brief  This header provides an `uncaught_exceptions` function implementation, which was introduced in C++17.
 *
 * The code in this file is based on the implementation by Evgeny Panasyuk:
 *
 * https://github.com/panaseleus/stack_unwinding/blob/master/boost/exception/uncaught_exception_count.hpp
 */

#ifndef BOOST_CORE_UNCAUGHT_EXCEPTIONS_HPP_INCLUDED_
#define BOOST_CORE_UNCAUGHT_EXCEPTIONS_HPP_INCLUDED_

#include <exception>
#include <boost/config.hpp>

#if defined(BOOST_HAS_PRAGMA_ONCE)
#pragma once
#endif

#if (defined(__cpp_lib_uncaught_exceptions) && __cpp_lib_uncaught_exceptions >= 201411)
#if defined(__APPLE__)
#include <Availability.h>
// Apple systems only support std::uncaught_exceptions starting with specific versions:
// - Mac OS >= 10.12
// - iOS >= 10.0
// - tvOS >= 10.0
// - watchOS >= 3.0
// https://github.com/boostorg/core/issues/80
#if (defined(__MAC_OS_X_VERSION_MIN_REQUIRED) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 101200) || \
    (defined(__IPHONE_OS_VERSION_MIN_REQUIRED) && __IPHONE_OS_VERSION_MIN_REQUIRED >= 100000)
#define BOOST_CORE_HAS_UNCAUGHT_EXCEPTIONS
#endif
#else
#define BOOST_CORE_HAS_UNCAUGHT_EXCEPTIONS
#endif // defined(__APPLE__)
// Visual Studio 14.0 supports N4152 std::uncaught_exceptions() but doesn't define __cpp_lib_uncaught_exceptions
#elif (defined(_MSC_VER) && _MSC_VER >= 1900)
#define BOOST_CORE_HAS_UNCAUGHT_EXCEPTIONS
#endif

#if !defined(BOOST_CORE_HAS_UNCAUGHT_EXCEPTIONS)

// cxxabi.h availability macro
#if defined(__has_include) && (!defined(BOOST_GCC) || (__GNUC__ >= 5))
#   if __has_include(<cxxabi.h>)
#       define BOOST_CORE_HAS_CXXABI_H
#   endif
#elif defined(__GLIBCXX__) || defined(__GLIBCPP__)
#   define BOOST_CORE_HAS_CXXABI_H
#endif

#if defined(BOOST_CORE_HAS_CXXABI_H)
// MinGW GCC 4.4 seem to not work the same way the newer GCC versions do. As a result, __cxa_get_globals based implementation will always return 0.
// Just disable it for now and fall back to std::uncaught_exception().
// On AIX, xlclang++ does have cxxabi.h but doesn't have __cxa_get_globals (https://github.com/boostorg/core/issues/78).
#if !( \
        (defined(__MINGW32__) && (defined(__GNUC__) && (__GNUC__ * 100 + __GNUC_MINOR__) < 405)) || \
        defined(__ibmxl__) \
    )
#include <cxxabi.h>
#include <cstring>
#define BOOST_CORE_HAS_CXA_GET_GLOBALS
// At least on MinGW and Linux, only GCC since 4.7 declares __cxa_get_globals() in cxxabi.h. Older versions of GCC do not expose this function but it's there.
// On OpenBSD, it seems, the declaration is also missing.
// Note that at least on FreeBSD 11, cxxabi.h declares __cxa_get_globals with a different exception specification, so we can't declare the function unconditionally.
// On Linux with clang and libc++ and on OS X, there is a version of cxxabi.h from libc++abi that doesn't declare __cxa_get_globals, but provides __cxa_uncaught_exceptions.
// The function only appeared in version _LIBCPPABI_VERSION >= 1002 of the library. Unfortunately, there are linking errors about undefined reference to __cxa_uncaught_exceptions
// on Ubuntu Trusty and OS X, so we avoid using it and forward-declare __cxa_get_globals instead.
// On QNX SDP 7.0 (QCC 5.4.0), there are multiple cxxabi.h, one from glibcxx from gcc and another from libc++abi from LLVM. Which one is included will be determined by the qcc
// command line arguments (-V and/or -Y; http://www.qnx.com/developers/docs/7.0.0/#com.qnx.doc.neutrino.utilities/topic/q/qcc.html). The LLVM libc++abi is missing the declaration
// of __cxa_get_globals but it is also patched by QNX developers to not define _LIBCPPABI_VERSION. Older QNX SDP versions, up to and including 6.6, don't provide LLVM and libc++abi.
// See https://github.com/boostorg/core/issues/59.
#if !defined(__FreeBSD__) && \
    ( \
        (defined(__GNUC__) && (__GNUC__ * 100 + __GNUC_MINOR__) < 407) || \
        defined(__OpenBSD__) || \
        (defined(__QNXNTO__) && !defined(__GLIBCXX__) && !defined(__GLIBCPP__)) || \
        defined(_LIBCPPABI_VERSION) \
    )
namespace __cxxabiv1 {
struct __cxa_eh_globals;
#if defined(__OpenBSD__)
extern "C" __cxa_eh_globals* __cxa_get_globals();
#else
extern "C" __cxa_eh_globals* __cxa_get_globals() BOOST_NOEXCEPT_OR_NOTHROW __attribute__((__const__));
#endif
} // namespace __cxxabiv1
#endif
#endif
#endif // defined(BOOST_CORE_HAS_CXXABI_H)

#if defined(_MSC_VER) && _MSC_VER >= 1400
#include <cstring>
#define BOOST_CORE_HAS_GETPTD
namespace boost {
namespace core {
namespace detail {
extern "C" void* _getptd();
} // namespace detail
} // namespace core
} // namespace boost
#endif // defined(_MSC_VER) && _MSC_VER >= 1400

#endif // !defined(BOOST_CORE_HAS_UNCAUGHT_EXCEPTIONS)

#if !defined(BOOST_CORE_HAS_UNCAUGHT_EXCEPTIONS) && !defined(BOOST_CORE_HAS_CXA_GET_GLOBALS) && !defined(BOOST_CORE_HAS_GETPTD)
//! This macro is defined when `uncaught_exceptions` is not guaranteed to return values greater than 1 if multiple exceptions are pending
#define BOOST_CORE_UNCAUGHT_EXCEPTIONS_EMULATED
#endif

namespace boost {

namespace core {

//! Returns the number of currently pending exceptions
inline unsigned int uncaught_exceptions() BOOST_NOEXCEPT
{
#if defined(BOOST_CORE_HAS_UNCAUGHT_EXCEPTIONS)
    // C++17 implementation
    return static_cast< unsigned int >(std::uncaught_exceptions());
#elif defined(BOOST_CORE_HAS_CXA_GET_GLOBALS)
    // Tested on {clang 3.2,GCC 3.5.6,GCC 4.1.2,GCC 4.4.6,GCC 4.4.7}x{x32,x64}
    unsigned int count;
    std::memcpy(&count, reinterpret_cast< const unsigned char* >(::abi::__cxa_get_globals()) + sizeof(void*), sizeof(count)); // __cxa_eh_globals::uncaughtExceptions, x32 offset - 0x4, x64 - 0x8
    return count;
#elif defined(BOOST_CORE_HAS_GETPTD)
    // MSVC specific. Tested on {MSVC2005SP1,MSVC2008SP1,MSVC2010SP1,MSVC2012}x{x32,x64}.
    unsigned int count;
    std::memcpy(&count, static_cast< const unsigned char* >(boost::core::detail::_getptd()) + (sizeof(void*) == 8u ? 0x100 : 0x90), sizeof(count)); // _tiddata::_ProcessingThrow, x32 offset - 0x90, x64 - 0x100
    return count;
#else
    // Portable C++03 implementation. Does not allow to detect multiple nested exceptions.
    return static_cast< unsigned int >(std::uncaught_exception());
#endif
}

} // namespace core

} // namespace boost

#undef BOOST_CORE_HAS_CXXABI_H
#undef BOOST_CORE_HAS_CXA_GET_GLOBALS
#undef BOOST_CORE_HAS_UNCAUGHT_EXCEPTIONS
#undef BOOST_CORE_HAS_GETPTD

#endif // BOOST_CORE_UNCAUGHT_EXCEPTIONS_HPP_INCLUDED_

/* uncaught_exceptions.hpp
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
*/