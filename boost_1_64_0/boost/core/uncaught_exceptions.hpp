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
fcWj8e0jofuqQIc20p5Ox2LZda+v+zSyPRidftOnZ5tI8G+tcHEu0Mj+bS+/bxtpdL4NtKfShbr/jkdjbAH4fC+kYXuAmPzLcJ7Rs5XbLxWfZYKkjJtwnuIak6H5AdKAIeEY9CEsBwzJ7F0hD8+IsI/92KOTxspbkAYMKLGfWxFPMx6MvYL0bDzmbXDETL0hlgninuGY/SukcY3G8Pm1SyPq+LdIYw3G4L9H3BiLLUPGSUHPhTs4S715K9hUKg3YldmXwrLCgcrQ/VGiE/R8FdqXN1itSvadfF6hndm9LIFWGkf/5tOBvWWSfaqARrY5bMv7MQ8MWkm5//RxLhTr8EBAMyjq+MGQDm3Q8PtvSCe2xcM+HdiimW+u92jAHjv2SaNs0vq584iOJFEOXsNzR/bTUu5aXLO82TMDzC+edod+/afFuehBun66VurAUzySWx09TsSVIizNwUQTTVgSs7IA5Rzi06hVBcAP9XFyt9EWDwdcOk+60MPZDTfjZyvXw0gPtrKIMeVOZXea9xUVG+PPHcU0hUqycG/zH+PryFqLyX/aSk1Dh1nyyVtnCXZswrs4wW/iWOw43/6atAX5zs03RFs4aUkiB0WVo8nD6Eh+AttgKcsyurdejMAOWpNxiO416qkqlQz3wDooXxx6sTRj1ijWQHvgWuU6rK+SDXir+mj+0fTYWGm22X5WqUtx0W7a735Wndgk8PuBOH9ez/Uy84FNdl6RCbDcwGDvzpx6KsE/g7jRs2NNb/3Skzxc4of2tQn1rYltPNcQE+dUpxBdoaLUEc9Kxqpw5uXpc/FQ14uA9plIKwkO9rAZaUERCa8eCceyMaa+I7/V5Vafhyy/oX9WQC/XoR18flpTCbjiuLFtPdDECOzjEKbSMdZMO8wxJd5jas0P5C1lRJNzZBjgcjCuTIJtRh4qF74JxJhQPxtnFmjS5NzKNIL2Y14J3dPT6YhfYzGXTN8W3/v/kzhuDkKfM64o6GHY65MSzU6fRljf2OXYl60g+lvP823Qo8s0QEernyOFkgoRx2dmZH8PhWz4nCTrN16tDfV7vzh2Pm+hLneI8vhvBe5ebzB+s9BiLwQsfoq2wfeAExln6XseyvhvUcYXcVlmTQTsY9RvW4VD3gK2RQw2KefI9Gwo58O+rcpy5rp27GI7lGRFmjZJXkvAPMR9RaZpol4zE2NlMYbLgR1SPJqx9SS7Gu92PtsZu/bosZ2Srd+WYC8mTMfELxbUEz7oh0yafDp6o9nL5HKgVxk/p6LzEGznu9WA3vWZTjd5dLpfjrR+V/UxHneNHIwXosj4W5Gt6+iUQKuWEZO0Os9l8A7RjE7TT/qNUWzESi1y7rsgnqetXB7hFks4ja2o6zMJo9hVo3yswsZBWc/+pDpcQJi/pny2j6tK4BvBXOa4UOYrGKOckZSuwj5iWeciL6x/UJZc//MI11GYc2TaShq4U8M2QCpgI7U2db7GSplRS/96StN9iw0X+sEbDUbKgvQLTHrNSb/Q8FdGZMt9K6VTouoAxobebtMwrjF9Fzjds/EAR3sFGS6C+pBx6rdkKO1VNB9pJ/xqvrf8AU5rhbQrOO1gSPsQpx2q0hqMH1CdyFN4sN0UlUztoUvjzgkw7sC9EfaNKF8StC+agHWNj1lchaohs1DTl5Gx4ujIONrqxy3d5q4tQ07f+4TFhrpOzRLu3YN28/IahB3TP2dwXfzIdH2PEiHy7mMyTdeO4a2qnCG8a/t5j0f1ZBUj2I5j1zF+shIt4IuyK7Y2362Hcz4v/sAXg/LI94yLhHj2pkx+PBnyX+/pnfxC470mNN+wNNNTrmYMzTeRBmqO+v020rjS2rV0Vx42Fn0=
*/