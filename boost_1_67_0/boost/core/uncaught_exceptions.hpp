/*
 *             Copyright Andrey Semashev 2018.
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

// Visual Studio 14 supports N4152 std::uncaught_exceptions()
#if (defined(__cpp_lib_uncaught_exceptions) && __cpp_lib_uncaught_exceptions >= 201411) || \
    (defined(_MSC_VER) && _MSC_VER >= 1900)
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
#if !(defined(__MINGW32__) && (defined(__GNUC__) && (__GNUC__ * 100 + __GNUC_MINOR__) < 405))
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
#endif // !(defined(__MINGW32__) && (defined(__GNUC__) && (__GNUC__ * 100 + __GNUC_MINOR__) < 405))
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