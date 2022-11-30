//  (C) Copyright John Maddock 2001 - 2002. 
//  (C) Copyright Darin Adler 2001. 
//  (C) Copyright Jens Maurer 2001. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  STLPort standard library config:

#if !defined(__SGI_STL_PORT) && !defined(_STLPORT_VERSION)
#  include <cstddef>
#  if !defined(__SGI_STL_PORT) && !defined(_STLPORT_VERSION)
#      error "This is not STLPort!"
#  endif
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
// __STL_STATIC_CONST_INIT_BUG implies BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS
// for versions prior to 4.1(beta)
//
#if (defined(__STL_STATIC_CONST_INIT_BUG) || defined(_STLP_STATIC_CONST_INIT_BUG)) && (__SGI_STL_PORT <= 0x400)
#  define BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS
#endif

//
// If STLport thinks that there is no partial specialisation, then there is no
// std::iterator traits:
//
#if !(defined(_STLP_CLASS_PARTIAL_SPECIALIZATION) || defined(__STL_CLASS_PARTIAL_SPECIALIZATION))
#  define BOOST_NO_STD_ITERATOR_TRAITS
#endif

//
// No new style iostreams on GCC without STLport's iostreams enabled:
//
#if (defined(__GNUC__) && (__GNUC__ < 3)) && !(defined(__SGI_STL_OWN_IOSTREAMS) || defined(_STLP_OWN_IOSTREAMS))
#  define BOOST_NO_STRINGSTREAM
#endif

//
// No new iostreams implies no std::locale, and no std::stringstream:
//
#if defined(__STL_NO_IOSTREAMS) || defined(__STL_NO_NEW_IOSTREAMS) || defined(_STLP_NO_IOSTREAMS) || defined(_STLP_NO_NEW_IOSTREAMS)
#  define BOOST_NO_STD_LOCALE
#  define BOOST_NO_STRINGSTREAM
#endif

//
// If the streams are not native, and we have a "using ::x" compiler bug
// then the io stream facets are not available in namespace std::
//
#ifdef _STLPORT_VERSION
#  if !(_STLPORT_VERSION >= 0x500) && !defined(_STLP_OWN_IOSTREAMS) && defined(_STLP_USE_NAMESPACES) && defined(BOOST_NO_USING_TEMPLATE) && !defined(BOOST_BORLANDC)
#     define BOOST_NO_STD_LOCALE
#  endif
#else
#  if !defined(__SGI_STL_OWN_IOSTREAMS) && defined(__STL_USE_NAMESPACES) && defined(BOOST_NO_USING_TEMPLATE) && !defined(BOOST_BORLANDC)
#     define BOOST_NO_STD_LOCALE
#  endif
#endif

#if defined(_STLPORT_VERSION) && (_STLPORT_VERSION >= 0x520)
#  define BOOST_HAS_TR1_UNORDERED_SET
#  define BOOST_HAS_TR1_UNORDERED_MAP
#endif
//
// Without member template support enabled, their are no template
// iterate constructors, and no std::allocator:
//
#if !(defined(__STL_MEMBER_TEMPLATES) || defined(_STLP_MEMBER_TEMPLATES))
#  define BOOST_NO_TEMPLATED_ITERATOR_CONSTRUCTORS
#  define BOOST_NO_STD_ALLOCATOR
#endif
//
// however we always have at least a partial allocator:
//
#define BOOST_HAS_PARTIAL_STD_ALLOCATOR

#if !defined(_STLP_MEMBER_TEMPLATE_CLASSES) || defined(_STLP_DONT_SUPPORT_REBIND_MEMBER_TEMPLATE)
#  define BOOST_NO_STD_ALLOCATOR
#endif

#if defined(_STLP_NO_MEMBER_TEMPLATE_KEYWORD) && defined(BOOST_MSVC) && (BOOST_MSVC <= 1300)
#  define BOOST_NO_STD_ALLOCATOR
#endif

//
// If STLport thinks there is no wchar_t at all, then we have to disable
// the support for the relevant specilazations of std:: templates.
//
#if !defined(_STLP_HAS_WCHAR_T) && !defined(_STLP_WCHAR_T_IS_USHORT)
#  ifndef  BOOST_NO_STD_WSTRING
#     define BOOST_NO_STD_WSTRING
#  endif
#  ifndef  BOOST_NO_STD_WSTREAMBUF
#     define BOOST_NO_STD_WSTREAMBUF
#  endif
#endif

//
// We always have SGI style hash_set, hash_map, and slist:
//
#ifndef _STLP_NO_EXTENSIONS
#define BOOST_HAS_HASH
#define BOOST_HAS_SLIST
#endif

//
// STLport does a good job of importing names into namespace std::,
// but doesn't always get them all, define BOOST_NO_STDC_NAMESPACE, since our
// workaround does not conflict with STLports:
//
//
// Harold Howe says:
// Borland switched to STLport in BCB6. Defining BOOST_NO_STDC_NAMESPACE with
// BCB6 does cause problems. If we detect C++ Builder, then don't define 
// BOOST_NO_STDC_NAMESPACE
//
#if !defined(BOOST_BORLANDC) && !defined(__DMC__)
//
// If STLport is using it's own namespace, and the real names are in
// the global namespace, then we duplicate STLport's using declarations
// (by defining BOOST_NO_STDC_NAMESPACE), we do this because STLport doesn't
// necessarily import all the names we need into namespace std::
// 
#  if (defined(__STL_IMPORT_VENDOR_CSTD) \
         || defined(__STL_USE_OWN_NAMESPACE) \
         || defined(_STLP_IMPORT_VENDOR_CSTD) \
         || defined(_STLP_USE_OWN_NAMESPACE)) \
      && (defined(__STL_VENDOR_GLOBAL_CSTD) || defined (_STLP_VENDOR_GLOBAL_CSTD))
#     define BOOST_NO_STDC_NAMESPACE
#     define BOOST_NO_EXCEPTION_STD_NAMESPACE
#  endif
#elif defined(BOOST_BORLANDC) && BOOST_BORLANDC < 0x560
// STLport doesn't import std::abs correctly:
#include <stdlib.h>
namespace std { using ::abs; }
// and strcmp/strcpy don't get imported either ('cos they are macros)
#include <string.h>
#ifdef strcpy
#  undef strcpy
#endif
#ifdef strcmp
#  undef strcmp
#endif
#ifdef _STLP_VENDOR_CSTD
namespace std{ using _STLP_VENDOR_CSTD::strcmp; using _STLP_VENDOR_CSTD::strcpy; }
#endif
#endif

//
// std::use_facet may be non-standard, uses a class instead:
//
#if defined(__STL_NO_EXPLICIT_FUNCTION_TMPL_ARGS) || defined(_STLP_NO_EXPLICIT_FUNCTION_TMPL_ARGS)
#  define BOOST_NO_STD_USE_FACET
#  define BOOST_HAS_STLP_USE_FACET
#endif

//
// If STLport thinks there are no wide functions, <cwchar> etc. is not working; but
// only if BOOST_NO_STDC_NAMESPACE is not defined (if it is then we do the import 
// into std:: ourselves).
//
#if defined(_STLP_NO_NATIVE_WIDE_FUNCTIONS) && !defined(BOOST_NO_STDC_NAMESPACE)
#  define BOOST_NO_CWCHAR
#  define BOOST_NO_CWCTYPE
#endif

//
// If STLport for some reason was configured so that it thinks that wchar_t
// is not an intrinsic type, then we have to disable the support for it as
// well (we would be missing required specializations otherwise).
//
#if !defined( _STLP_HAS_WCHAR_T) || defined(_STLP_WCHAR_T_IS_USHORT)
#  undef  BOOST_NO_INTRINSIC_WCHAR_T
#  define BOOST_NO_INTRINSIC_WCHAR_T
#endif

//
// Borland ships a version of STLport with C++ Builder 6 that lacks
// hashtables and the like:
//
#if defined(BOOST_BORLANDC) && (BOOST_BORLANDC == 0x560)
#  undef BOOST_HAS_HASH
#endif

//
// gcc-2.95.3/STLPort does not like the using declarations we use to get ADL with std::min/max
//
#if defined(__GNUC__) && (__GNUC__ < 3)
#  include <algorithm> // for std::min and std::max
#  define BOOST_USING_STD_MIN() ((void)0)
#  define BOOST_USING_STD_MAX() ((void)0)
namespace boost { using std::min; using std::max; }
#endif

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

#define BOOST_STDLIB "STLPort standard library version " BOOST_STRINGIZE(__SGI_STL_PORT)

/* stlport.hpp
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
*/