/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   config.hpp
 * \author Andrey Semashev
 * \date   08.03.2007
 *
 * \brief  This header is the Boost.Log library implementation, see the library documentation
 *         at http://www.boost.org/doc/libs/release/libs/log/doc/html/index.html. In this file
 *         internal configuration macros are defined.
 */

#ifndef BOOST_LOG_DETAIL_CONFIG_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_CONFIG_HPP_INCLUDED_

// This check must be before any system headers are included, or __MSVCRT_VERSION__ may get defined to 0x0600
#if defined(__MINGW32__) && !defined(__MSVCRT_VERSION__)
// Target MinGW headers to at least MSVC 7.0 runtime by default. This will enable some useful functions.
#define __MSVCRT_VERSION__ 0x0700
#endif

#include <boost/predef/os.h>

// Try including WinAPI config as soon as possible so that any other headers don't include Windows SDK headers
#if defined(BOOST_OS_WINDOWS_AVAILABLE)
#include <boost/winapi/config.hpp>
#endif

#include <limits.h> // To bring in libc macros
#include <boost/config.hpp>

// The library requires dynamic_cast in a few places
#if defined(BOOST_NO_RTTI)
#   error Boost.Log: RTTI is required by the library
#endif

#if defined(_MSC_VER) && _MSC_VER >= 1600
#   define BOOST_LOG_HAS_PRAGMA_DETECT_MISMATCH
#endif

#if defined(BOOST_LOG_HAS_PRAGMA_DETECT_MISMATCH)
#include <boost/preprocessor/stringize.hpp>
#endif

#if !defined(BOOST_WINDOWS)
#   ifndef BOOST_LOG_WITHOUT_DEBUG_OUTPUT
#       define BOOST_LOG_WITHOUT_DEBUG_OUTPUT
#   endif
#   ifndef BOOST_LOG_WITHOUT_EVENT_LOG
#       define BOOST_LOG_WITHOUT_EVENT_LOG
#   endif
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if defined(BOOST_MSVC)
    // For some reason MSVC 9.0 fails to link the library if static integral constants are defined in cpp
#   define BOOST_LOG_BROKEN_STATIC_CONSTANTS_LINKAGE
#   if _MSC_VER <= 1310
        // MSVC 7.1 sometimes fails to match out-of-class template function definitions with
        // their declarations if the return type or arguments of the functions involve typename keyword
        // and depend on the template parameters.
#       define BOOST_LOG_BROKEN_TEMPLATE_DEFINITION_MATCHING
#   endif
#   if _MSC_VER <= 1400
        // Older MSVC versions reject friend declarations for class template specializations
#       define BOOST_LOG_BROKEN_FRIEND_TEMPLATE_SPECIALIZATIONS
#   endif
#   if _MSC_VER <= 1600
        // MSVC up to 10.0 attempts to invoke copy constructor when initializing a const reference from rvalue returned from a function.
        // This fails when the returned value cannot be copied (only moved):
        //
        // class base {};
        // class derived : public base { BOOST_MOVABLE_BUT_NOT_COPYABLE(derived) };
        // derived foo();
        // base const& var = foo(); // attempts to call copy constructor of derived
#       define BOOST_LOG_BROKEN_REFERENCE_FROM_RVALUE_INIT
#   endif
#   if !defined(_STLPORT_VERSION)
        // MSVC 9.0 mandates packaging of STL classes, which apparently affects alignment and
        // makes alignment_of< T >::value no longer be a power of 2 for types that derive from STL classes.
        // This breaks type_with_alignment and everything that relies on it.
        // This doesn't happen with non-native STLs, such as STLPort. Strangely, this doesn't show with
        // STL classes themselves or most of the user-defined derived classes.
        // Not sure if that happens with other MSVC versions.
        // See: http://svn.boost.org/trac/boost/ticket/1946
#       define BOOST_LOG_BROKEN_STL_ALIGNMENT
#   endif
#endif

#if defined(BOOST_INTEL) || defined(__SUNPRO_CC)
    // Intel compiler and Sun Studio 12.3 have problems with friend declarations for nested class templates
#   define BOOST_LOG_NO_MEMBER_TEMPLATE_FRIENDS
#endif

#if defined(BOOST_MSVC) && BOOST_MSVC <= 1600
    // MSVC cannot interpret constant expressions in certain contexts, such as non-type template parameters
#   define BOOST_LOG_BROKEN_CONSTANT_EXPRESSIONS
#endif

#if defined(BOOST_NO_CXX11_HDR_CODECVT)
    // The compiler does not support std::codecvt<char16_t> and std::codecvt<char32_t> specializations.
    // The BOOST_NO_CXX11_HDR_CODECVT means there's no usable <codecvt>, which is slightly different from this macro.
    // But in order for <codecvt> to be implemented the std::codecvt specializations have to be implemented as well.
#   define BOOST_LOG_NO_CXX11_CODECVT_FACETS
#endif

#if defined(__CYGWIN__)
    // Boost.ASIO is broken on Cygwin
#   define BOOST_LOG_NO_ASIO
#endif

#if defined(__VXWORKS__)
#   define BOOST_LOG_NO_GETPGRP
#   define BOOST_LOG_NO_GETSID
    // for _WRS_CONFIG_USER_MANAGEMENT used below
#   include <vsbConfig.h>
#endif

#if (!defined(__CRYSTAX__) && defined(__ANDROID__) && (__ANDROID_API__+0) < 21) \
     || (defined(__VXWORKS__) && !defined(_WRS_CONFIG_USER_MANAGEMENT))
// Until Android API version 21 Google NDK does not provide getpwuid_r
#    define BOOST_LOG_NO_GETPWUID_R
#endif

#if !defined(BOOST_LOG_USE_NATIVE_SYSLOG) && defined(BOOST_LOG_NO_ASIO)
#   ifndef BOOST_LOG_WITHOUT_SYSLOG
#       define BOOST_LOG_WITHOUT_SYSLOG
#   endif
#endif

#if defined(__GNUC__) && (__GNUC__ == 4 && __GNUC_MINOR__ <= 2)
    // GCC 4.1 and 4.2 have buggy anonymous namespaces support, which interferes with symbol linkage
#   define BOOST_LOG_ANONYMOUS_NAMESPACE namespace anonymous {} using namespace anonymous; namespace anonymous
#else
#   define BOOST_LOG_ANONYMOUS_NAMESPACE namespace
#endif

#if defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || (defined(__GNUC__) && (__GNUC__ == 4 && __GNUC_MINOR__ <= 6))
// GCC up to 4.6 (inclusively) did not support expanding template argument packs into non-variadic template arguments
#define BOOST_LOG_NO_CXX11_ARG_PACKS_TO_NON_VARIADIC_ARGS_EXPANSION
#endif

#if defined(BOOST_NO_CXX11_CONSTEXPR) || (defined(BOOST_GCC) && ((BOOST_GCC+0) / 100) <= 406)
// GCC 4.6 does not support in-class brace initializers for static constexpr array members
#define BOOST_LOG_NO_CXX11_CONSTEXPR_DATA_MEMBER_BRACE_INITIALIZERS
#endif

#if defined(BOOST_NO_CXX11_DEFAULTED_FUNCTIONS) || (defined(BOOST_GCC) && ((BOOST_GCC+0) / 100) <= 406)
// GCC 4.6 cannot handle a defaulted function with noexcept specifier
#define BOOST_LOG_NO_CXX11_DEFAULTED_NOEXCEPT_FUNCTIONS
#endif

#if defined(BOOST_NO_CXX11_DEFAULTED_FUNCTIONS) || (defined(BOOST_CLANG) && (((__clang_major__+0) == 3) && ((__clang_minor__+0) <= 1)))
// Clang 3.1 cannot handle a defaulted constexpr constructor in some cases (presumably, if the class contains a member with a constexpr constructor)
#define BOOST_LOG_NO_CXX11_DEFAULTED_CONSTEXPR_CONSTRUCTORS
#endif

#if defined(_MSC_VER)
#   define BOOST_LOG_NO_VTABLE __declspec(novtable)
#else
#   define BOOST_LOG_NO_VTABLE
#endif

// An MS-like compilers' extension that allows to optimize away the needless code
#if defined(_MSC_VER)
#   define BOOST_LOG_ASSUME(expr) __assume(expr)
#else
#   define BOOST_LOG_ASSUME(expr)
#endif

// The statement marking unreachable branches of code to avoid warnings
#if defined(BOOST_CLANG)
#   if __has_builtin(__builtin_unreachable)
#       define BOOST_LOG_UNREACHABLE() __builtin_unreachable()
#   endif
#elif defined(__GNUC__)
#   if (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 5))
#       define BOOST_LOG_UNREACHABLE() __builtin_unreachable()
#   endif
#elif defined(_MSC_VER)
#   define BOOST_LOG_UNREACHABLE() __assume(0)
#endif
#if !defined(BOOST_LOG_UNREACHABLE)
#   define BOOST_LOG_UNREACHABLE()
#   define BOOST_LOG_UNREACHABLE_RETURN(r) return r
#else
#   define BOOST_LOG_UNREACHABLE_RETURN(r) BOOST_LOG_UNREACHABLE()
#endif

// The macro efficiently returns a local lvalue from a function.
// It employs NRVO, if supported by compiler, or uses a move constructor otherwise.
#if defined(BOOST_HAS_NRVO)
#define BOOST_LOG_NRVO_RESULT(x) x
#else
#define BOOST_LOG_NRVO_RESULT(x) boost::move(x)
#endif

// Some compilers support a special attribute that shows that a function won't return
#if defined(__GNUC__) || (defined(__SUNPRO_CC) && __SUNPRO_CC >= 0x590)
    // GCC and Sun Studio 12 support attribute syntax
#   define BOOST_LOG_NORETURN __attribute__((noreturn))
#elif defined (_MSC_VER)
    // Microsoft-compatible compilers go here
#   define BOOST_LOG_NORETURN __declspec(noreturn)
#else
    // The rest compilers might emit bogus warnings about missing return statements
    // in functions with non-void return types when throw_exception is used.
#   define BOOST_LOG_NORETURN
#endif

// Some compilers may require marking types that may alias other types
#define BOOST_LOG_MAY_ALIAS BOOST_MAY_ALIAS

#if !defined(BOOST_LOG_BUILDING_THE_LIB)

// Detect if we're dealing with dll
#   if defined(BOOST_LOG_DYN_LINK) || defined(BOOST_ALL_DYN_LINK)
#       define BOOST_LOG_DLL
#   endif

#   if defined(BOOST_LOG_DLL)
#       define BOOST_LOG_API BOOST_SYMBOL_IMPORT
#   else
#       define BOOST_LOG_API
#   endif
//
// Automatically link to the correct build variant where possible.
//
#   if !defined(BOOST_ALL_NO_LIB)
#       if !defined(BOOST_LOG_NO_LIB)
#          define BOOST_LIB_NAME boost_log
#          if defined(BOOST_LOG_DLL)
#              define BOOST_DYN_LINK
#          endif
#          include <boost/config/auto_link.hpp>
#       endif
        // In static-library builds compilers ignore auto-link comments from Boost.Log binary to
        // other Boost libraries. We explicitly add comments here for other libraries.
        // In dynamic-library builds this is not needed.
#       if !defined(BOOST_LOG_DLL)
#           include <boost/system/config.hpp>
#           include <boost/filesystem/config.hpp>
#           if !defined(BOOST_DATE_TIME_NO_LIB) && !defined(BOOST_DATE_TIME_SOURCE)
#               define BOOST_LIB_NAME boost_date_time
#               if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_DATE_TIME_DYN_LINK)
#                   define BOOST_DYN_LINK
#               endif
#               include <boost/config/auto_link.hpp>
#           endif
            // Boost.Thread's config is included below, if needed
#       endif
#   endif  // auto-linking disabled

#else // !defined(BOOST_LOG_BUILDING_THE_LIB)

#   if defined(BOOST_LOG_DLL)
#       define BOOST_LOG_API BOOST_SYMBOL_EXPORT
#   else
#       define BOOST_LOG_API BOOST_SYMBOL_VISIBLE
#   endif

#endif // !defined(BOOST_LOG_BUILDING_THE_LIB)

// By default we provide support for both char and wchar_t
#if !defined(BOOST_LOG_WITHOUT_CHAR)
#   define BOOST_LOG_USE_CHAR
#endif
#if !defined(BOOST_LOG_WITHOUT_WCHAR_T)
#   define BOOST_LOG_USE_WCHAR_T
#endif

#if !defined(BOOST_LOG_DOXYGEN_PASS)
    // Check if multithreading is supported
#   if !defined(BOOST_LOG_NO_THREADS) && !defined(BOOST_HAS_THREADS)
#       define BOOST_LOG_NO_THREADS
#   endif // !defined(BOOST_LOG_NO_THREADS) && !defined(BOOST_HAS_THREADS)
#endif // !defined(BOOST_LOG_DOXYGEN_PASS)

#if !defined(BOOST_LOG_NO_THREADS)
    // We need this header to (i) enable auto-linking with Boost.Thread and
    // (ii) to bring in configuration macros of Boost.Thread.
#   include <boost/thread/detail/config.hpp>
#endif // !defined(BOOST_LOG_NO_THREADS)

#if !defined(BOOST_LOG_NO_THREADS)
#   define BOOST_LOG_EXPR_IF_MT(expr) expr
#else
#   undef BOOST_LOG_USE_COMPILER_TLS
#   define BOOST_LOG_EXPR_IF_MT(expr)
#endif // !defined(BOOST_LOG_NO_THREADS)

#if defined(BOOST_LOG_USE_COMPILER_TLS)
#   if defined(__GNUC__) || defined(__SUNPRO_CC)
#       define BOOST_LOG_TLS __thread
#   elif defined(BOOST_MSVC)
#       define BOOST_LOG_TLS __declspec(thread)
#   else
#       undef BOOST_LOG_USE_COMPILER_TLS
#   endif
#endif // defined(BOOST_LOG_USE_COMPILER_TLS)

#ifndef BOOST_LOG_CPU_CACHE_LINE_SIZE
//! The macro defines the CPU cache line size for the target architecture. This is mostly used for optimization.
#if defined(__s390__) || defined(__s390x__)
#define BOOST_LOG_CPU_CACHE_LINE_SIZE 256
#elif defined(powerpc) || defined(__powerpc__) || defined(__ppc__)
#define BOOST_LOG_CPU_CACHE_LINE_SIZE 128
#else
#define BOOST_LOG_CPU_CACHE_LINE_SIZE 64
#endif
#endif

namespace boost {

// Setup namespace name
#if !defined(BOOST_LOG_DOXYGEN_PASS)
#   if defined(BOOST_LOG_DLL)
#       if defined(BOOST_LOG_NO_THREADS)
#           define BOOST_LOG_VERSION_NAMESPACE v2_st
#       else
#           if defined(BOOST_THREAD_PLATFORM_PTHREAD)
#               define BOOST_LOG_VERSION_NAMESPACE v2_mt_posix
#           elif defined(BOOST_THREAD_PLATFORM_WIN32)
#               if BOOST_USE_WINAPI_VERSION >= BOOST_WINAPI_VERSION_WIN6
#                   define BOOST_LOG_VERSION_NAMESPACE v2_mt_nt6
#               else
#                   define BOOST_LOG_VERSION_NAMESPACE v2_mt_nt5
#               endif
#           else
#               define BOOST_LOG_VERSION_NAMESPACE v2_mt
#           endif
#       endif // defined(BOOST_LOG_NO_THREADS)
#   else
#       if defined(BOOST_LOG_NO_THREADS)
#           define BOOST_LOG_VERSION_NAMESPACE v2s_st
#       else
#           if defined(BOOST_THREAD_PLATFORM_PTHREAD)
#               define BOOST_LOG_VERSION_NAMESPACE v2s_mt_posix
#           elif defined(BOOST_THREAD_PLATFORM_WIN32)
#               if BOOST_USE_WINAPI_VERSION >= BOOST_WINAPI_VERSION_WIN6
#                   define BOOST_LOG_VERSION_NAMESPACE v2s_mt_nt6
#               else
#                   define BOOST_LOG_VERSION_NAMESPACE v2s_mt_nt5
#               endif
#           else
#               define BOOST_LOG_VERSION_NAMESPACE v2s_mt
#           endif
#       endif // defined(BOOST_LOG_NO_THREADS)
#   endif // defined(BOOST_LOG_DLL)


namespace log {

#   if !defined(BOOST_NO_CXX11_INLINE_NAMESPACES)

inline namespace BOOST_LOG_VERSION_NAMESPACE {}

#       define BOOST_LOG_OPEN_NAMESPACE namespace log { inline namespace BOOST_LOG_VERSION_NAMESPACE {
#       define BOOST_LOG_CLOSE_NAMESPACE }}

#   elif defined(BOOST_GCC) && (BOOST_GCC+0) >= 40400

// GCC 7 deprecated strong using directives but allows inline namespaces in C++03 mode since GCC 4.4.
__extension__ inline namespace BOOST_LOG_VERSION_NAMESPACE {}

#       define BOOST_LOG_OPEN_NAMESPACE namespace log { __extension__ inline namespace BOOST_LOG_VERSION_NAMESPACE {
#       define BOOST_LOG_CLOSE_NAMESPACE }}

#   else

namespace BOOST_LOG_VERSION_NAMESPACE {}

using namespace BOOST_LOG_VERSION_NAMESPACE
#       if defined(__GNUC__) && (__GNUC__ >= 4 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4)) && !defined(__clang__)
__attribute__((__strong__))
#       endif
;

#       define BOOST_LOG_OPEN_NAMESPACE namespace log { namespace BOOST_LOG_VERSION_NAMESPACE {
#       define BOOST_LOG_CLOSE_NAMESPACE }}
#   endif

} // namespace log

#else // !defined(BOOST_LOG_DOXYGEN_PASS)

namespace log {}
#   define BOOST_LOG_OPEN_NAMESPACE namespace log {
#   define BOOST_LOG_CLOSE_NAMESPACE }

#endif // !defined(BOOST_LOG_DOXYGEN_PASS)

#if defined(BOOST_LOG_HAS_PRAGMA_DETECT_MISMATCH)
#pragma detect_mismatch("boost_log_abi", BOOST_PP_STRINGIZE(BOOST_LOG_VERSION_NAMESPACE))
#endif

} // namespace boost

#endif // BOOST_LOG_DETAIL_CONFIG_HPP_INCLUDED_

/* config.hpp
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
*/