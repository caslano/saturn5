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

#if (defined(BOOST_NO_CXX11_HDR_CODECVT) && BOOST_CXX_VERSION < 201703) || (defined(_MSVC_STL_VERSION) && _MSVC_STL_VERSION < 142)
    // The compiler does not support std::codecvt<char16_t> and std::codecvt<char32_t> specializations.
    // The BOOST_NO_CXX11_HDR_CODECVT means there's no usable <codecvt>, which is slightly different from this macro.
    // But in order for <codecvt> to be implemented the std::codecvt specializations have to be implemented as well.
    // We need to check the C++ version as well, since <codecvt> is deprecated from C++17 onwards which may cause
    // BOOST_NO_CXX11_HDR_CODECVT to be set, even though std::codecvt in <locale> is just fine.
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

#if (!defined(__CRYSTAX__) && defined(__ANDROID__) && (__ANDROID_API__ < 21)) \
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

#if defined(BOOST_NO_CXX11_CONSTEXPR) || (defined(BOOST_GCC) && (BOOST_GCC / 100) <= 406)
// GCC 4.6 does not support in-class brace initializers for static constexpr array members
#define BOOST_LOG_NO_CXX11_CONSTEXPR_DATA_MEMBER_BRACE_INITIALIZERS
#endif

#if defined(BOOST_NO_CXX11_DEFAULTED_FUNCTIONS) || (defined(BOOST_GCC) && (BOOST_GCC / 100) <= 406)
// GCC 4.6 cannot handle defaulted functions with noexcept specifier or virtual functions
#define BOOST_LOG_NO_CXX11_DEFAULTED_NOEXCEPT_FUNCTIONS
#define BOOST_LOG_NO_CXX11_DEFAULTED_VIRTUAL_FUNCTIONS
#endif

#if defined(BOOST_NO_CXX11_DEFAULTED_FUNCTIONS) || (defined(BOOST_CLANG) && ((__clang_major__ == 3) && (__clang_minor__ <= 1)))
// Clang 3.1 cannot handle a defaulted constexpr constructor in some cases (presumably, if the class contains a member with a constexpr constructor)
#define BOOST_LOG_NO_CXX11_DEFAULTED_CONSTEXPR_CONSTRUCTORS
#endif

// The macro indicates that the compiler does not support C++20 pack expansions in lambda init-captures.
// Early gcc, clang and MSVC versions support C++20 pack expansions in lambda init-captures,
// but define __cpp_init_captures to a lower value.
#if (!defined(__cpp_init_captures) || (__cpp_init_captures < 201803)) && \
    !(\
        BOOST_CXX_VERSION > 201703 && \
        (\
            (defined(BOOST_GCC) && (BOOST_GCC >= 90000)) || \
            (defined(BOOST_CLANG) && (BOOST_CLANG_VERSION >= 90000)) || \
            (defined(BOOST_MSVC) && (BOOST_MSVC >= 1922))\
        )\
    )
#define BOOST_LOG_NO_CXX20_PACK_EXPANSION_IN_LAMBDA_INIT_CAPTURE
#endif

#if defined(_MSC_VER)
#   define BOOST_LOG_NO_VTABLE __declspec(novtable)
#else
#   define BOOST_LOG_NO_VTABLE
#endif

// An MS-like compilers' extension that allows to optimize away the needless code
#if defined(_MSC_VER)
#   define BOOST_LOG_ASSUME(expr) __assume(expr)
#elif defined(__has_builtin)
// Clang 3.6 adds __builtin_assume, but enabling it causes weird compilation errors, where the compiler
// doesn't see one of attachable_sstream_buf::append overloads. It works fine with Clang 3.7 and later.
#   if __has_builtin(__builtin_assume) && (!defined(__clang__) || (__clang_major__ * 100 + __clang_minor__) >= 307)
#       define BOOST_LOG_ASSUME(expr) __builtin_assume(expr)
#   else
#       define BOOST_LOG_ASSUME(expr)
#   endif
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
#           include <boost/filesystem/config.hpp>
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
#               if BOOST_USE_WINAPI_VERSION >= BOOST_WINAPI_VERSION_WIN8
#                   define BOOST_LOG_VERSION_NAMESPACE v2_mt_nt62
#               elif BOOST_USE_WINAPI_VERSION >= BOOST_WINAPI_VERSION_WIN6
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
#               if BOOST_USE_WINAPI_VERSION >= BOOST_WINAPI_VERSION_WIN8
#                   define BOOST_LOG_VERSION_NAMESPACE v2s_mt_nt62
#               elif BOOST_USE_WINAPI_VERSION >= BOOST_WINAPI_VERSION_WIN6
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

#   elif defined(BOOST_GCC) && (BOOST_GCC >= 40400)

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