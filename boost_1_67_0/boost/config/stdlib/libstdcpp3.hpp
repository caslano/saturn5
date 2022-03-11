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

#if __has_include(<memory_resource>)
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

#if defined(__clang_major__) && ((__clang_major__ < 3) || ((__clang_major__ == 3) && (__clang_minor__ < 7)))
// As of clang-3.6, libstdc++ header <atomic> throws up errors with clang:
#  define BOOST_NO_CXX11_HDR_ATOMIC
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
#elif __cplusplus < 201402 || (BOOST_LIBSTDCXX_VERSION < 40900) || !defined(BOOST_LIBSTDCXX11)
#  define BOOST_NO_CXX14_HDR_SHARED_MUTEX
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