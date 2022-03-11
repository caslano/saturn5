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
#  if !(_STLPORT_VERSION >= 0x500) && !defined(_STLP_OWN_IOSTREAMS) && defined(_STLP_USE_NAMESPACES) && defined(BOOST_NO_USING_TEMPLATE) && !defined(__BORLANDC__)
#     define BOOST_NO_STD_LOCALE
#  endif
#else
#  if !defined(__SGI_STL_OWN_IOSTREAMS) && defined(__STL_USE_NAMESPACES) && defined(BOOST_NO_USING_TEMPLATE) && !defined(__BORLANDC__)
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
#if !defined(__BORLANDC__) && !defined(__DMC__)
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
#elif defined(__BORLANDC__) && __BORLANDC__ < 0x560
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
#if defined(__BORLANDC__) && (__BORLANDC__ == 0x560)
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