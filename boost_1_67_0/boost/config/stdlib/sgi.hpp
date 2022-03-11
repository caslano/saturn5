//  (C) Copyright John Maddock 2001 - 2003. 
//  (C) Copyright Darin Adler 2001. 
//  (C) Copyright Jens Maurer 2001 - 2003. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  generic SGI STL:

#if !defined(__STL_CONFIG_H)
#  include <boost/config/no_tr1/utility.hpp>
#  if !defined(__STL_CONFIG_H)
#      error "This is not the SGI STL!"
#  endif
#endif

//
// No std::iterator traits without partial specialisation:
//
#if !defined(__STL_CLASS_PARTIAL_SPECIALIZATION)
#  define BOOST_NO_STD_ITERATOR_TRAITS
#endif

//
// No std::stringstream with gcc < 3
//
#if defined(__GNUC__) && (__GNUC__ < 3) && \
     ((__GNUC_MINOR__ < 95) || (__GNUC_MINOR__ == 96)) && \
     !defined(__STL_USE_NEW_IOSTREAMS) || \
   defined(__APPLE_CC__)
   // Note that we only set this for GNU C++ prior to 2.95 since the
   // latest patches for that release do contain a minimal <sstream>
   // If you are running a 2.95 release prior to 2.95.3 then this will need
   // setting, but there is no way to detect that automatically (other
   // than by running the configure script).
   // Also, the unofficial GNU C++ 2.96 included in RedHat 7.1 doesn't
   // have <sstream>.
#  define BOOST_NO_STRINGSTREAM
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


//
// Assume no std::locale without own iostreams (this may be an
// incorrect assumption in some cases):
//
#if !defined(__SGI_STL_OWN_IOSTREAMS) && !defined(__STL_USE_NEW_IOSTREAMS)
#  define BOOST_NO_STD_LOCALE
#endif

//
// Original native SGI streams have non-standard std::messages facet:
//
#if defined(__sgi) && (_COMPILER_VERSION <= 650) && !defined(__SGI_STL_OWN_IOSTREAMS)
#  define BOOST_NO_STD_LOCALE
#endif

//
// SGI's new iostreams have missing "const" in messages<>::open
//
#if defined(__sgi) && (_COMPILER_VERSION <= 740) && defined(__STL_USE_NEW_IOSTREAMS)
#  define BOOST_NO_STD_MESSAGES
#endif

//
// No template iterator constructors, or std::allocator
// without member templates:
//
#if !defined(__STL_MEMBER_TEMPLATES)
#  define BOOST_NO_TEMPLATED_ITERATOR_CONSTRUCTORS
#  define BOOST_NO_STD_ALLOCATOR
#endif

//
// We always have SGI style hash_set, hash_map, and slist:
//
#define BOOST_HAS_HASH
#define BOOST_HAS_SLIST

//
// If this is GNU libstdc++2, then no <limits> and no std::wstring:
//
#if (defined(__GNUC__) && (__GNUC__ < 3))
#  include <string>
#  if defined(__BASTRING__)
#     define BOOST_NO_LIMITS
// Note: <boost/limits.hpp> will provide compile-time constants
#     undef BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS
#     define BOOST_NO_STD_WSTRING
#  endif
#endif

//
// There is no standard iterator unless we have namespace support:
//
#if !defined(__STL_USE_NAMESPACES)
#  define BOOST_NO_STD_ITERATOR
#endif

//
// Intrinsic type_traits support.
// The SGI STL has it's own __type_traits class, which
// has intrinsic compiler support with SGI's compilers.
// Whatever map SGI style type traits to boost equivalents:
//
#define BOOST_HAS_SGI_TYPE_TRAITS

//  C++0x headers not yet implemented
//
#  define BOOST_NO_CXX11_HDR_ARRAY
#  define BOOST_NO_CXX11_HDR_CHRONO
#  define BOOST_NO_CXX11_HDR_CODECVT
#  define BOOST_NO_CXX11_HDR_CONDITION_VARIABLE
#  define BOOST_NO_CXX11_HDR_FORWARD_LIST
#  define BOOST_NO_CXX11_HDR_FUTURE
#  define BOOST_NO_CXX11_HDR_INITIALIZER_LIST
#  define BOOST_NO_CXX11_HDR_MUTEX
#  define BOOST_NO_CXX11_HDR_RANDOM
#  define BOOST_NO_CXX11_HDR_RATIO
#  define BOOST_NO_CXX11_HDR_REGEX
#  define BOOST_NO_CXX11_HDR_SYSTEM_ERROR
#  define BOOST_NO_CXX11_HDR_THREAD
#  define BOOST_NO_CXX11_HDR_TUPLE
#  define BOOST_NO_CXX11_HDR_TYPE_TRAITS
#  define BOOST_NO_CXX11_HDR_TYPEINDEX
#  define BOOST_NO_CXX11_HDR_UNORDERED_MAP
#  define BOOST_NO_CXX11_HDR_UNORDERED_SET
#  define BOOST_NO_CXX11_NUMERIC_LIMITS
#  define BOOST_NO_CXX11_ALLOCATOR
#  define BOOST_NO_CXX11_POINTER_TRAITS
#  define BOOST_NO_CXX11_ATOMIC_SMART_PTR
#  define BOOST_NO_CXX11_SMART_PTR
#  define BOOST_NO_CXX11_HDR_FUNCTIONAL
#  define BOOST_NO_CXX11_HDR_ATOMIC
#  define BOOST_NO_CXX11_STD_ALIGN
#  define BOOST_NO_CXX11_ADDRESSOF
#  define BOOST_NO_CXX11_HDR_EXCEPTION

#if defined(__has_include)
#if !__has_include(<shared_mutex>)
#  define BOOST_NO_CXX14_HDR_SHARED_MUTEX
#elif __cplusplus < 201402
#  define BOOST_NO_CXX14_HDR_SHARED_MUTEX
#endif
#else
#  define BOOST_NO_CXX14_HDR_SHARED_MUTEX
#endif

// C++14 features
#  define BOOST_NO_CXX14_STD_EXCHANGE

// C++17 features
#  define BOOST_NO_CXX17_STD_APPLY
#  define BOOST_NO_CXX17_STD_INVOKE
#  define BOOST_NO_CXX17_ITERATOR_TRAITS

#define BOOST_STDLIB "SGI standard library"

/* sgi.hpp
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
*/