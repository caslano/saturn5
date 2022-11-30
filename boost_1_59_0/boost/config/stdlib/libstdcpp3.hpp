//  (C) Copyright John Maddock 2001.
//  (C) Copyright Jens Maurer 2001.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  config for libstdc++ v3
//  not much to go in here:

#define BOOST_GNU_STDLIB 1

#ifdef __GLIBCXX__
#define BOOST_STDLIB "GNU libstdc++ version " BOOST_STRINGIZE(__GLIBCXX__)
#else
#define BOOST_STDLIB "GNU libstdc++ version " BOOST_STRINGIZE(__GLIBCPP__)
#endif

#if !defined(_GLIBCPP_USE_WCHAR_T) && !defined(_GLIBCXX_USE_WCHAR_T)
#  define BOOST_NO_CWCHAR
#  define BOOST_NO_CWCTYPE
#  define BOOST_NO_STD_WSTRING
#  define BOOST_NO_STD_WSTREAMBUF
#endif

#if defined(__osf__) && !defined(_REENTRANT) \
  && ( defined(_GLIBCXX_HAVE_GTHR_DEFAULT) || defined(_GLIBCPP_HAVE_GTHR_DEFAULT) )
// GCC 3 on Tru64 forces the definition of _REENTRANT when any std lib header
// file is included, therefore for consistency we define it here as well.
#  define _REENTRANT
#endif

#ifdef __GLIBCXX__ // gcc 3.4 and greater:
#  if defined(_GLIBCXX_HAVE_GTHR_DEFAULT) \
        || defined(_GLIBCXX__PTHREADS) \
        || defined(_GLIBCXX_HAS_GTHREADS) \
        || defined(_WIN32) \
        || defined(_AIX) \
        || defined(__HAIKU__)
      //
      // If the std lib has thread support turned on, then turn it on in Boost
      // as well.  We do this because some gcc-3.4 std lib headers define _REENTANT
      // while others do not...
      //
#     define BOOST_HAS_THREADS
#  else
#     define BOOST_DISABLE_THREADS
#  endif
#elif defined(__GLIBCPP__) \
        && !defined(_GLIBCPP_HAVE_GTHR_DEFAULT) \
        && !defined(_GLIBCPP__PTHREADS)
   // disable thread support if the std lib was built single threaded:
#  define BOOST_DISABLE_THREADS
#endif

#if (defined(linux) || defined(__linux) || defined(__linux__)) && defined(__arm__) && defined(_GLIBCPP_HAVE_GTHR_DEFAULT)
// linux on arm apparently doesn't define _REENTRANT
// so just turn on threading support whenever the std lib is thread safe:
#  define BOOST_HAS_THREADS
#endif

#if !defined(_GLIBCPP_USE_LONG_LONG) \
    && !defined(_GLIBCXX_USE_LONG_LONG)\
    && defined(BOOST_HAS_LONG_LONG)
// May have been set by compiler/*.hpp, but "long long" without library
// support is useless.
#  undef BOOST_HAS_LONG_LONG
#endif

// Apple doesn't seem to reliably defined a *unix* macro
#if !defined(CYGWIN) && (  defined(__unix__)  \
                        || defined(__unix)    \
                        || defined(unix)      \
                        || defined(__APPLE__) \
                        || defined(__APPLE)   \
                        || defined(APPLE))
#  include <unistd.h>
#endif

#ifndef __VXWORKS__ // VxWorks uses Dinkum, not GNU STL with GCC 
#if defined(__GLIBCXX__) || (defined(__GLIBCPP__) && __GLIBCPP__>=20020514) // GCC >= 3.1.0
#  define BOOST_STD_EXTENSION_NAMESPACE __gnu_cxx
#  define BOOST_HAS_SLIST
#  define BOOST_HAS_HASH
#  define BOOST_SLIST_HEADER <ext/slist>
# if !defined(__GNUC__) || __GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 3)
#   define BOOST_HASH_SET_HEADER <ext/hash_set>
#   define BOOST_HASH_MAP_HEADER <ext/hash_map>
# else
#   define BOOST_HASH_SET_HEADER <backward/hash_set>
#   define BOOST_HASH_MAP_HEADER <backward/hash_map>
# endif
#endif
#endif

#if defined(__has_include)
#if defined(BOOST_HAS_HASH)
#if !__has_include(BOOST_HASH_SET_HEADER) || (__GNUC__ >= 10)
#undef BOOST_HAS_HASH
#undef BOOST_HAS_SET_HEADER
#undef BOOST_HAS_MAP_HEADER
#endif
#if !__has_include(BOOST_SLIST_HEADER)
#undef BOOST_HAS_SLIST
#undef BOOST_HAS_SLIST_HEADER
#endif
#endif
#endif

//
// Decide whether we have C++11 support turned on:
//
#if defined(__GXX_EXPERIMENTAL_CXX0X__) || (__cplusplus >= 201103)
#  define BOOST_LIBSTDCXX11
#endif

//
//  Decide which version of libstdc++ we have, normally
//  libstdc++ C++0x support is detected via __GNUC__, __GNUC_MINOR__, and possibly
//  __GNUC_PATCHLEVEL__ at the suggestion of Jonathan Wakely, one of the libstdc++
//  developers. He also commented:
//
//       "I'm not sure how useful __GLIBCXX__ is for your purposes, for instance in
//       GCC 4.2.4 it is set to 20080519 but in GCC 4.3.0 it is set to 20080305.
//       Although 4.3.0 was released earlier than 4.2.4, it has better C++0x support
//       than any release in the 4.2 series."
//
//  Another resource for understanding libstdc++ features is:
//  http://gcc.gnu.org/onlinedocs/libstdc++/manual/status.html#manual.intro.status.standard.200x
//
//  However, using the GCC version number fails when the compiler is clang since this
//  only ever claims to emulate GCC-4.2, see https://svn.boost.org/trac/boost/ticket/7473
//  for a long discussion on this issue.  What we can do though is use clang's __has_include
//  to detect the presence of a C++11 header that was introduced with a specific GCC release.
//  We still have to be careful though as many such headers were buggy and/or incomplete when
//  first introduced, so we only check for headers that were fully featured from day 1, and then
//  use that to infer the underlying GCC version:
//
#ifdef __clang__

#if __has_include(<compare>)
#  define BOOST_LIBSTDCXX_VERSION 100100
#elif __has_include(<memory_resource>)
#  define BOOST_LIBSTDCXX_VERSION 90100
#elif __has_include(<charconv>)
#  define BOOST_LIBSTDCXX_VERSION 80100
#elif __has_include(<variant>)
#  define BOOST_LIBSTDCXX_VERSION 70100
#elif __has_include(<experimental/memory_resource>)
#  define BOOST_LIBSTDCXX_VERSION 60100
#elif __has_include(<experimental/any>)
#  define BOOST_LIBSTDCXX_VERSION 50100
#elif __has_include(<shared_mutex>)
#  define BOOST_LIBSTDCXX_VERSION 40900
#elif __has_include(<ext/cmath>)
#  define BOOST_LIBSTDCXX_VERSION 40800
#elif __has_include(<scoped_allocator>)
#  define BOOST_LIBSTDCXX_VERSION 40700
#elif __has_include(<typeindex>)
#  define BOOST_LIBSTDCXX_VERSION 40600
#elif __has_include(<future>)
#  define BOOST_LIBSTDCXX_VERSION 40500
#elif  __has_include(<ratio>)
#  define BOOST_LIBSTDCXX_VERSION 40400
#elif __has_include(<array>)
#  define BOOST_LIBSTDCXX_VERSION 40300
#endif
//
// If BOOST_HAS_FLOAT128 is set, now that we know the std lib is libstdc++3, check to see if the std lib is
// configured to support this type.  If not disable it:
//
#if defined(BOOST_HAS_FLOAT128) && !defined(_GLIBCXX_USE_FLOAT128)
#  undef BOOST_HAS_FLOAT128
#endif

#if (BOOST_LIBSTDCXX_VERSION >= 100000) && defined(BOOST_HAS_HASH)
//
// hash_set/hash_map deprecated and have terminal bugs:
//
#undef BOOST_HAS_HASH
#undef BOOST_HAS_SET_HEADER
#undef BOOST_HAS_MAP_HEADER
#endif


#if (BOOST_LIBSTDCXX_VERSION >= 100000) && defined(BOOST_HAS_HASH)
//
// hash_set/hash_map deprecated and have terminal bugs:
//
#undef BOOST_HAS_HASH
#undef BOOST_HAS_SET_HEADER
#undef BOOST_HAS_MAP_HEADER
#endif


#if (BOOST_LIBSTDCXX_VERSION < 50100)
// libstdc++ does not define this function as it's deprecated in C++11, but clang still looks for it,
// defining it here is a terrible cludge, but should get things working:
extern "C" char *gets (char *__s);
#endif
//
// clang is unable to parse some GCC headers, add those workarounds here:
//
#if BOOST_LIBSTDCXX_VERSION < 50000
#  define BOOST_NO_CXX11_HDR_REGEX
#endif
//
// GCC 4.7.x has no __cxa_thread_atexit which
// thread_local objects require for cleanup:
//
#if BOOST_LIBSTDCXX_VERSION < 40800
#  define BOOST_NO_CXX11_THREAD_LOCAL
#endif
//
// Early clang versions can handle <chrono>, not exactly sure which versions
// but certainly up to clang-3.8 and gcc-4.6:
//
#if (__clang_major__ < 5)
#  if BOOST_LIBSTDCXX_VERSION < 40800
#     define BOOST_NO_CXX11_HDR_FUTURE
#     define BOOST_NO_CXX11_HDR_MUTEX
#     define BOOST_NO_CXX11_HDR_CONDITION_VARIABLE
#     define BOOST_NO_CXX11_HDR_CHRONO
#  endif
#endif

//
//  GCC 4.8 and 9 add working versions of <atomic> and <regex> respectively.
//  However, we have no test for these as the headers were present but broken
//  in early GCC versions.
//
#endif

#if defined(__SUNPRO_CC) && (__SUNPRO_CC >= 0x5130) && (__cplusplus >= 201103L)
//
// Oracle Solaris compiler uses it's own verison of libstdc++ but doesn't 
// set __GNUC__
//
#if __SUNPRO_CC >= 0x5140
#define BOOST_LIBSTDCXX_VERSION 50100
#else
#define BOOST_LIBSTDCXX_VERSION 40800
#endif
#endif

#if !defined(BOOST_LIBSTDCXX_VERSION)
#  define BOOST_LIBSTDCXX_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#endif

// std::auto_ptr isn't provided with _GLIBCXX_DEPRECATED=0 (GCC 4.5 and earlier)
// or _GLIBCXX_USE_DEPRECATED=0 (GCC 4.6 and later).
#if defined(BOOST_LIBSTDCXX11)
#  if BOOST_LIBSTDCXX_VERSION < 40600
#     if !_GLIBCXX_DEPRECATED
#        define BOOST_NO_AUTO_PTR
#     endif
#  elif !_GLIBCXX_USE_DEPRECATED
#     define BOOST_NO_AUTO_PTR
#     define BOOST_NO_CXX98_BINDERS
#  endif
#endif

//  C++0x headers in GCC 4.3.0 and later
//
#if (BOOST_LIBSTDCXX_VERSION < 40300) || !defined(BOOST_LIBSTDCXX11)
#  define BOOST_NO_CXX11_HDR_ARRAY
#  define BOOST_NO_CXX11_HDR_TUPLE
#  define BOOST_NO_CXX11_HDR_UNORDERED_MAP
#  define BOOST_NO_CXX11_HDR_UNORDERED_SET
#  define BOOST_NO_CXX11_HDR_FUNCTIONAL
#endif

//  C++0x headers in GCC 4.4.0 and later
//
#if (BOOST_LIBSTDCXX_VERSION < 40400) || !defined(BOOST_LIBSTDCXX11)
#  define BOOST_NO_CXX11_HDR_CONDITION_VARIABLE
#  define BOOST_NO_CXX11_HDR_FORWARD_LIST
#  define BOOST_NO_CXX11_HDR_INITIALIZER_LIST
#  define BOOST_NO_CXX11_HDR_MUTEX
#  define BOOST_NO_CXX11_HDR_RATIO
#  define BOOST_NO_CXX11_HDR_SYSTEM_ERROR
#  define BOOST_NO_CXX11_SMART_PTR
#  define BOOST_NO_CXX11_HDR_EXCEPTION
#else
#  define BOOST_HAS_TR1_COMPLEX_INVERSE_TRIG 
#  define BOOST_HAS_TR1_COMPLEX_OVERLOADS 
#endif

//  C++0x features in GCC 4.5.0 and later
//
#if (BOOST_LIBSTDCXX_VERSION < 40500) || !defined(BOOST_LIBSTDCXX11)
#  define BOOST_NO_CXX11_NUMERIC_LIMITS
#  define BOOST_NO_CXX11_HDR_FUTURE
#  define BOOST_NO_CXX11_HDR_RANDOM
#endif

//  C++0x features in GCC 4.6.0 and later
//
#if (BOOST_LIBSTDCXX_VERSION < 40600) || !defined(BOOST_LIBSTDCXX11)
#  define BOOST_NO_CXX11_HDR_TYPEINDEX
#  define BOOST_NO_CXX11_ADDRESSOF
#  define BOOST_NO_CXX17_ITERATOR_TRAITS
#endif

//  C++0x features in GCC 4.7.0 and later
//
#if (BOOST_LIBSTDCXX_VERSION < 40700) || !defined(BOOST_LIBSTDCXX11)
// Note that although <chrono> existed prior to 4.7, "steady_clock" is spelled "monotonic_clock"
// so 4.7.0 is the first truly conforming one.
#  define BOOST_NO_CXX11_HDR_CHRONO
#  define BOOST_NO_CXX11_ALLOCATOR
#  define BOOST_NO_CXX11_POINTER_TRAITS
#endif
//  C++0x features in GCC 4.8.0 and later
//
#if (BOOST_LIBSTDCXX_VERSION < 40800) || !defined(BOOST_LIBSTDCXX11)
// Note that although <atomic> existed prior to gcc 4.8 it was largely unimplemented for many types:
#  define BOOST_NO_CXX11_HDR_ATOMIC
#  define BOOST_NO_CXX11_HDR_THREAD
#endif
//  C++0x features in GCC 4.9.0 and later
//
#if (BOOST_LIBSTDCXX_VERSION < 40900) || !defined(BOOST_LIBSTDCXX11)
// Although <regex> is present and compilable against, the actual implementation is not functional
// even for the simplest patterns such as "\d" or "[0-9]". This is the case at least in gcc up to 4.8, inclusively.
#  define BOOST_NO_CXX11_HDR_REGEX
#endif
#if (BOOST_LIBSTDCXX_VERSION < 40900) || (__cplusplus <= 201103)
#  define BOOST_NO_CXX14_STD_EXCHANGE
#endif

//
//  C++0x features in GCC 5.1 and later
//
#if (BOOST_LIBSTDCXX_VERSION < 50100) || !defined(BOOST_LIBSTDCXX11)
#  define BOOST_NO_CXX11_HDR_TYPE_TRAITS
#  define BOOST_NO_CXX11_HDR_CODECVT
#  define BOOST_NO_CXX11_ATOMIC_SMART_PTR
#  define BOOST_NO_CXX11_STD_ALIGN
#endif

//
//  C++17 features in GCC 7.1 and later
//
#if (BOOST_LIBSTDCXX_VERSION < 70100) || (__cplusplus <= 201402L)
#  define BOOST_NO_CXX17_STD_INVOKE
#  define BOOST_NO_CXX17_STD_APPLY
#  define BOOST_NO_CXX17_HDR_OPTIONAL
#  define BOOST_NO_CXX17_HDR_STRING_VIEW
#  define BOOST_NO_CXX17_HDR_VARIANT
#endif

#if defined(__has_include)
#if !__has_include(<shared_mutex>)
#  define BOOST_NO_CXX14_HDR_SHARED_MUTEX
#elif __cplusplus <= 201103
#  define BOOST_NO_CXX14_HDR_SHARED_MUTEX
#endif
//
// <execution> has a dependency to Intel's thread building blocks:
// unless these are installed seperately, including <execution> leads
// to inscrutable errors inside libstdc++'s own headers.
//
#if (BOOST_LIBSTDCXX_VERSION < 100100)
#if !__has_include(<tbb/tbb.h>)
#define BOOST_NO_CXX17_HDR_EXECUTION
#endif
#endif
#elif __cplusplus < 201402 || (BOOST_LIBSTDCXX_VERSION < 40900) || !defined(BOOST_LIBSTDCXX11)
#  define BOOST_NO_CXX14_HDR_SHARED_MUTEX
#endif

#if BOOST_LIBSTDCXX_VERSION < 100100
//
// The header may be present but is incomplete:
//
#  define BOOST_NO_CXX17_HDR_CHARCONV
#endif

#if BOOST_LIBSTDCXX_VERSION < 110000
//
// Header <bit> may be present but lacks std::bit_cast:
//
#define BOOST_NO_CXX20_HDR_BIT
#endif

#ifndef __cpp_impl_coroutine
#  define BOOST_NO_CXX20_HDR_COROUTINE
#endif

//
// These next defines are mostly for older clang versions with a newer libstdc++ :
//
#if !defined(__cpp_lib_concepts)
#if !defined(BOOST_NO_CXX20_HDR_COMPARE)
#  define BOOST_NO_CXX20_HDR_COMPARE
#endif
#if !defined(BOOST_NO_CXX20_HDR_CONCEPTS)
#  define BOOST_NO_CXX20_HDR_CONCEPTS
#endif
#if !defined(BOOST_NO_CXX20_HDR_SPAN)
#  define BOOST_NO_CXX20_HDR_SPAN
#endif
#if !defined(BOOST_NO_CXX20_HDR_RANGES)
#  define BOOST_NO_CXX20_HDR_RANGES
#endif
#endif

//
// Headers not present on Solaris with the Oracle compiler:
#if defined(__SUNPRO_CC) && (__SUNPRO_CC < 0x5140)
#define BOOST_NO_CXX11_HDR_FUTURE
#define BOOST_NO_CXX11_HDR_FORWARD_LIST 
#define BOOST_NO_CXX11_HDR_ATOMIC
// shared_ptr is present, but is not convertible to bool
// which causes all kinds of problems especially in Boost.Thread
// but probably elsewhere as well.
#define BOOST_NO_CXX11_SMART_PTR
#endif

#if (!defined(_GLIBCXX_HAS_GTHREADS) || !defined(_GLIBCXX_USE_C99_STDINT_TR1))
   // Headers not always available:
#  ifndef BOOST_NO_CXX11_HDR_CONDITION_VARIABLE
#     define BOOST_NO_CXX11_HDR_CONDITION_VARIABLE
#  endif
#  ifndef BOOST_NO_CXX11_HDR_MUTEX
#     define BOOST_NO_CXX11_HDR_MUTEX
#  endif
#  ifndef BOOST_NO_CXX11_HDR_THREAD
#     define BOOST_NO_CXX11_HDR_THREAD
#  endif
#  ifndef BOOST_NO_CXX14_HDR_SHARED_MUTEX
#     define BOOST_NO_CXX14_HDR_SHARED_MUTEX
#  endif
#endif

#if (!defined(_GTHREAD_USE_MUTEX_TIMEDLOCK) || (_GTHREAD_USE_MUTEX_TIMEDLOCK == 0)) && !defined(BOOST_NO_CXX11_HDR_MUTEX)
// Timed mutexes are not always available:
#  define BOOST_NO_CXX11_HDR_MUTEX
#endif

//  --- end ---

/* libstdcpp3.hpp
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
*/