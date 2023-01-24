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

#define BOOST_NO_CXX17_ITERATOR_TRAITS
#define BOOST_NO_CXX17_STD_INVOKE      // Invoke support is incomplete (no invoke_result)

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
c8ty+ZS9kmdL6y+vms0/32SEZyC4iiolq0LI5pidiHqwnjgq3MCzkcef/9Db9oFgSmZydQA8PezdHG0aejnNih6F+KrVxQMTWWM902oxbqZ+ubt/wuB0U/D4JM/kamEAgXeNorR+BUrrzH9paou8NJ2cqGDUY1HSPnC/5od0F0+TLupCvvrYzUrPTh4Nw4PENLw0y5MWZ1HpKY6gzH7z0OdcaoxCP3iWPnsixou+fX2DZrEVs7KudgZopigHLXQbSO33Fkzu6wR4f/lWDHYMWeXRkqmWCBXiLD+UPRFz1nqiMCnDdzh7j9daP0hWP1pXPODelNkW3VKflhakJcO7ehyL7jATLmGQWTCt4kCoPKZh+VG6StJ2AV5wNCFPIChyzOxkSXbR902t+dOOg/i2DN/J16xrMRESggn1xG+qvoHAWFeCIN7XTUdMY3aOBJcm8KIVUMTsP4YXoJG83E6qBLnLPh/E10QZD6GpXmrQUMaiF7NeNOSaKBl7/keK75auztSUmVdRCdwIKgGfwtaBtHyDPFdUF2jEY1c5Zx3qMjLoT6r4xlseyt4YZBRua0rgeV142zhvq9BOkedsY+xAFeymnWbSaLX/ESySvLVI7p98iL6EKsnPCDmC8huRR5zTnjSr17mVkkMdzv+6PIYyPmCQQcF0fWOajG01pprQIKj7bv00WrMu8EII/0g0b8AObkyKamorSvYL9pMC
*/