//  (C) Copyright Christopher Jefferson 2011.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  config for libc++
//  Might need more in here later.

#if !defined(_LIBCPP_VERSION)
#  include <ciso646>
#  if !defined(_LIBCPP_VERSION)
#      error "This is not libc++!"
#  endif
#endif

#define BOOST_STDLIB "libc++ version " BOOST_STRINGIZE(_LIBCPP_VERSION)

#define BOOST_HAS_THREADS

#ifdef _LIBCPP_HAS_NO_VARIADICS
#    define BOOST_NO_CXX11_HDR_TUPLE
#endif

// BOOST_NO_CXX11_ALLOCATOR should imply no support for the C++11
// allocator model. The C++11 allocator model requires a conforming
// std::allocator_traits which is only possible with C++11 template
// aliases since members rebind_alloc and rebind_traits require it.
#if defined(_LIBCPP_HAS_NO_TEMPLATE_ALIASES)
#    define BOOST_NO_CXX11_ALLOCATOR
#    define BOOST_NO_CXX11_POINTER_TRAITS
#endif

#if __cplusplus < 201103
//
// These two appear to be somewhat useable in C++03 mode, there may be others...
//
//#  define BOOST_NO_CXX11_HDR_ARRAY
//#  define BOOST_NO_CXX11_HDR_FORWARD_LIST

#  define BOOST_NO_CXX11_HDR_CODECVT
#  define BOOST_NO_CXX11_HDR_CONDITION_VARIABLE
#  define BOOST_NO_CXX11_HDR_EXCEPTION
#  define BOOST_NO_CXX11_HDR_INITIALIZER_LIST
#  define BOOST_NO_CXX11_HDR_MUTEX
#  define BOOST_NO_CXX11_HDR_RANDOM
#  define BOOST_NO_CXX11_HDR_RATIO
#  define BOOST_NO_CXX11_HDR_REGEX
#  define BOOST_NO_CXX11_HDR_SYSTEM_ERROR
#  define BOOST_NO_CXX11_HDR_THREAD
#  define BOOST_NO_CXX11_HDR_TUPLE
#  define BOOST_NO_CXX11_HDR_TYPEINDEX
#  define BOOST_NO_CXX11_HDR_UNORDERED_MAP
#  define BOOST_NO_CXX11_HDR_UNORDERED_SET
#  define BOOST_NO_CXX11_NUMERIC_LIMITS
#  define BOOST_NO_CXX11_ALLOCATOR
#  define BOOST_NO_CXX11_POINTER_TRAITS
#  define BOOST_NO_CXX11_SMART_PTR
#  define BOOST_NO_CXX11_HDR_FUNCTIONAL
#  define BOOST_NO_CXX11_STD_ALIGN
#  define BOOST_NO_CXX11_ADDRESSOF
#  define BOOST_NO_CXX11_HDR_ATOMIC
#  define BOOST_NO_CXX11_ATOMIC_SMART_PTR
#  define BOOST_NO_CXX11_HDR_CHRONO
#  define BOOST_NO_CXX11_HDR_TYPE_TRAITS
#  define BOOST_NO_CXX11_HDR_FUTURE
#elif _LIBCPP_VERSION < 3700
//
// These appear to be unusable/incomplete so far:
//
#  define BOOST_NO_CXX11_HDR_ATOMIC
#  define BOOST_NO_CXX11_ATOMIC_SMART_PTR
#  define BOOST_NO_CXX11_HDR_CHRONO
#  define BOOST_NO_CXX11_HDR_TYPE_TRAITS
#  define BOOST_NO_CXX11_HDR_FUTURE
#endif


#if _LIBCPP_VERSION < 3700
// libc++ uses a non-standard messages_base
#define BOOST_NO_STD_MESSAGES
#endif

// C++14 features
#if (_LIBCPP_VERSION < 3700) || (__cplusplus <= 201402L)
#  define BOOST_NO_CXX14_STD_EXCHANGE
#endif

// C++17 features
#if (_LIBCPP_VERSION < 4000) || (__cplusplus <= 201402L)
#  define BOOST_NO_CXX17_STD_APPLY
#  define BOOST_NO_CXX17_HDR_OPTIONAL
#  define BOOST_NO_CXX17_HDR_STRING_VIEW
#  define BOOST_NO_CXX17_HDR_VARIANT
#endif
#if (_LIBCPP_VERSION > 4000) && (__cplusplus > 201402L) && !defined(_LIBCPP_ENABLE_CXX17_REMOVED_AUTO_PTR)
#  define BOOST_NO_AUTO_PTR
#endif
#if (_LIBCPP_VERSION > 4000) && (__cplusplus > 201402L) && !defined(_LIBCPP_ENABLE_CXX17_REMOVED_RANDOM_SHUFFLE)
#  define BOOST_NO_CXX98_RANDOM_SHUFFLE
#endif
#if (_LIBCPP_VERSION > 4000) && (__cplusplus > 201402L) && !defined(_LIBCPP_ENABLE_CXX17_REMOVED_BINDERS)
#  define BOOST_NO_CXX98_BINDERS
#endif

#if defined(__cplusplus) && defined(__has_include)
#if __has_include(<version>)
#include <version>

#if !defined(__cpp_lib_execution) || (__cpp_lib_execution < 201603L)
#  define BOOST_NO_CXX17_HDR_EXECUTION
#endif
#if !defined(__cpp_lib_invoke) || (__cpp_lib_invoke < 201411L)
#define BOOST_NO_CXX17_STD_INVOKE
#endif

#if(_LIBCPP_VERSION < 9000)
// as_writable_bytes is missing.
#  define BOOST_NO_CXX20_HDR_SPAN
#endif

#else
#define BOOST_NO_CXX17_STD_INVOKE      // Invoke support is incomplete (no invoke_result)
#define BOOST_NO_CXX17_HDR_EXECUTION
#endif
#else
#define BOOST_NO_CXX17_STD_INVOKE      // Invoke support is incomplete (no invoke_result)
#define BOOST_NO_CXX17_HDR_EXECUTION
#endif

#if _LIBCPP_VERSION < 10000  // What's the correct version check here?
#define BOOST_NO_CXX17_ITERATOR_TRAITS
#endif

#if (_LIBCPP_VERSION <= 1101) && !defined(BOOST_NO_CXX11_THREAD_LOCAL)
// This is a bit of a sledgehammer, because really it's just libc++abi that has no
// support for thread_local, leading to linker errors such as
// "undefined reference to `__cxa_thread_atexit'".  It is fixed in the
// most recent releases of libc++abi though...
#  define BOOST_NO_CXX11_THREAD_LOCAL
#endif

#if defined(__linux__) && (_LIBCPP_VERSION < 6000) && !defined(BOOST_NO_CXX11_THREAD_LOCAL)
// After libc++-dev is installed on Trusty, clang++-libc++ almost works,
// except uses of `thread_local` fail with undefined reference to
// `__cxa_thread_atexit`.
//
// clang's libc++abi provides an implementation by deferring to the glibc
// implementation, which may or may not be available (it is not on Trusty).
// clang 4's libc++abi will provide an implementation if one is not in glibc
// though, so thread local support should work with clang 4 and above as long
// as libc++abi is linked in.
#  define BOOST_NO_CXX11_THREAD_LOCAL
#endif

#if defined(__has_include)
#if !__has_include(<shared_mutex>)
#  define BOOST_NO_CXX14_HDR_SHARED_MUTEX
#elif __cplusplus <= 201103
#  define BOOST_NO_CXX14_HDR_SHARED_MUTEX
#endif
#elif __cplusplus < 201402
#  define BOOST_NO_CXX14_HDR_SHARED_MUTEX
#endif

#if !defined(BOOST_NO_CXX14_HDR_SHARED_MUTEX) && (_LIBCPP_VERSION < 5000)
#  define BOOST_NO_CXX14_HDR_SHARED_MUTEX
#endif

//  --- end ---

/* libcpp.hpp
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
*/