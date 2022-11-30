/*
 *
 * Copyright (c) 1998-2002
 * John Maddock
 *
 * Use, modification and distribution are subject to the
 * Boost Software License, Version 1.0. (See accompanying file
 * LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 */

 /*
  *   LOCATION:    see http://www.boost.org for most recent version.
  *   FILE         config.hpp
  *   VERSION      see <boost/version.hpp>
  *   DESCRIPTION: regex extended config setup.
  */

#ifndef BOOST_REGEX_CONFIG_HPP
#define BOOST_REGEX_CONFIG_HPP

#if !((__cplusplus >= 201103L) || (defined(_MSC_VER) && (_MSC_VER >= 1600)) || defined(BOOST_REGEX_CXX03))
#  define BOOST_REGEX_CXX03
#endif

#if defined(BOOST_REGEX_RECURSIVE) && !defined(BOOST_REGEX_CXX03)
#  define BOOST_REGEX_CXX03
#endif

#if defined(__has_include)
#if !defined(BOOST_REGEX_STANDALONE) && !__has_include(<boost/version.hpp>)
#define BOOST_REGEX_STANDALONE
#endif
#endif

/*
 * Borland C++ Fix/error check
 * this has to go *before* we include any std lib headers:
 */
#if defined(__BORLANDC__) && !defined(__clang__)
#  include <boost/regex/config/borland.hpp>
#endif
#ifndef BOOST_REGEX_STANDALONE
#include <boost/version.hpp>
#endif

/*************************************************************************
*
* Asserts:
*
*************************************************************************/

#ifdef BOOST_REGEX_STANDALONE
#include <cassert>
#  define BOOST_REGEX_ASSERT(x) assert(x)
#else
#include <boost/assert.hpp>
#  define BOOST_REGEX_ASSERT(x) BOOST_ASSERT(x)
#endif

/*****************************************************************************
 *
 *  Include all the headers we need here:
 *
 ****************************************************************************/

#ifdef __cplusplus

#  ifndef BOOST_REGEX_USER_CONFIG
#     define BOOST_REGEX_USER_CONFIG <boost/regex/user.hpp>
#  endif

#  include BOOST_REGEX_USER_CONFIG

#ifndef BOOST_REGEX_STANDALONE
#  include <boost/config.hpp>
#  include <boost/predef.h>
#endif

#else
   /*
    * C build,
    * don't include <boost/config.hpp> because that may
    * do C++ specific things in future...
    */
#  include <stdlib.h>
#  include <stddef.h>
#  ifdef _MSC_VER
#     define BOOST_MSVC _MSC_VER
#  endif
#endif


/****************************************************************************
*
* Legacy support:
*
*******************************************************************************/

#if defined(BOOST_NO_STD_LOCALE) || defined(BOOST_NO_CXX11_HDR_MUTEX) || defined(BOOST_NO_CXX11_HDR_TYPE_TRAITS) \
   || defined(BOOST_NO_CXX11_HDR_ATOMIC) || defined(BOOST_NO_CXX11_ALLOCATOR) || defined(BOOST_NO_CXX11_SMART_PTR) \
   || defined(BOOST_NO_CXX11_STATIC_ASSERT) || defined(BOOST_NO_NOEXCEPT)
#ifndef BOOST_REGEX_CXX03
#  define BOOST_REGEX_CXX03
#endif
#endif

/*****************************************************************************
 *
 *  Boilerplate regex config options:
 *
 ****************************************************************************/

/* Obsolete macro, use BOOST_VERSION instead: */
#define BOOST_RE_VERSION 500

/* fix: */
#if defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif

#define BOOST_REGEX_JOIN(X, Y) BOOST_REGEX_DO_JOIN(X, Y)
#define BOOST_REGEX_DO_JOIN(X, Y) BOOST_REGEX_DO_JOIN2(X,Y)
#define BOOST_REGEX_DO_JOIN2(X, Y) X##Y

#ifdef BOOST_FALLTHROUGH
#  define BOOST_REGEX_FALLTHROUGH BOOST_FALLTHROUGH
#else

#if defined(__clang__) && (__cplusplus >= 201103L) && defined(__has_warning)
#  if __has_feature(cxx_attributes) && __has_warning("-Wimplicit-fallthrough")
#    define BOOST_REGEX_FALLTHROUGH [[clang::fallthrough]]
#  endif
#endif
#if !defined(BOOST_REGEX_FALLTHROUGH) && defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 1800) && (__cplusplus >= 201703)
#  define BOOST_REGEX_FALLTHROUGH [[fallthrough]]
#endif
#if !defined(BOOST_REGEX_FALLTHROUGH) && defined(__GNUC__) && (__GNUC__ >= 7)
#  define BOOST_REGEX_FALLTHROUGH __attribute__((fallthrough))
#endif

#if !defined(BOOST_REGEX_FALLTHROUGH)
#  define BOOST_REGEX_FALLTHROUGH
#endif
#endif

#ifdef BOOST_NORETURN
#  define BOOST_REGEX_NORETURN BOOST_NORETURN
#else
#  define BOOST_REGEX_NORETURN
#endif


/*
* Define a macro for the namespace that details are placed in, this includes the Boost
* version number to avoid mismatched header and library versions:
*/
#define BOOST_REGEX_DETAIL_NS BOOST_REGEX_JOIN(re_detail_, BOOST_RE_VERSION)

/*
 * Fix for gcc prior to 3.4: std::ctype<wchar_t> doesn't allow
 * masks to be combined, for example:
 * std::use_facet<std::ctype<wchar_t> >.is(std::ctype_base::lower|std::ctype_base::upper, L'a');
 * returns *false*.
 */
#if defined(__GLIBCPP__) && defined(BOOST_REGEX_CXX03)
#  define BOOST_REGEX_BUGGY_CTYPE_FACET
#endif

/*
 * If there isn't good enough wide character support then there will
 * be no wide character regular expressions:
 */
#if (defined(BOOST_NO_CWCHAR) || defined(BOOST_NO_CWCTYPE) || defined(BOOST_NO_STD_WSTRING))
#  if !defined(BOOST_NO_WREGEX)
#     define BOOST_NO_WREGEX
#  endif
#else
#  if defined(__sgi) && (defined(__SGI_STL_PORT) || defined(_STLPORT_VERSION))
      /* STLPort on IRIX is misconfigured: <cwctype> does not compile
       * as a temporary fix include <wctype.h> instead and prevent inclusion
       * of STLPort version of <cwctype> */
#     include <wctype.h>
#     define __STLPORT_CWCTYPE
#     define _STLP_CWCTYPE
#  endif

#if defined(__cplusplus) && defined(BOOST_REGEX_CXX03)
#  include <boost/regex/config/cwchar.hpp>
#endif

#endif

/*
 * If Win32 support has been disabled for boost in general, then
 * it is for regex in particular:
 */
#if defined(BOOST_DISABLE_WIN32) && !defined(BOOST_REGEX_NO_W32)
#  define BOOST_REGEX_NO_W32
#endif

/* disable our own file-iterators and mapfiles if we can't
 * support them: */
#if defined(_WIN32)
#  if defined(BOOST_REGEX_NO_W32) || BOOST_PLAT_WINDOWS_RUNTIME
#    define BOOST_REGEX_NO_FILEITER
#  endif
#else /* defined(_WIN32) */
#  if !defined(BOOST_HAS_DIRENT_H)
#    define BOOST_REGEX_NO_FILEITER
#  endif
#endif

/* backwards compatibitity: */
#if defined(BOOST_RE_NO_LIB)
#  define BOOST_REGEX_NO_LIB
#endif

#if defined(__GNUC__) && !defined(_MSC_VER) && (defined(_WIN32) || defined(__CYGWIN__))
/* gcc on win32 has problems if you include <windows.h>
   (sporadically generates bad code). */
#  define BOOST_REGEX_NO_W32
#endif
#if defined(__COMO__) && !defined(BOOST_REGEX_NO_W32) && !defined(_MSC_EXTENSIONS)
#  define BOOST_REGEX_NO_W32
#endif

#ifdef BOOST_REGEX_STANDALONE
#  if defined(_MSC_VER) && !defined(__clang__) && !defined(__GNUC__)
#     define BOOST_REGEX_MSVC _MSC_VER
#endif
#elif defined(BOOST_MSVC)
#  define BOOST_REGEX_MSVC BOOST_MSVC
#endif


/*****************************************************************************
 *
 *  Set up dll import/export options:
 *
 ****************************************************************************/

#if (defined(BOOST_REGEX_DYN_LINK) || defined(BOOST_ALL_DYN_LINK)) && !defined(BOOST_REGEX_STATIC_LINK) && defined(BOOST_SYMBOL_IMPORT)
#  if defined(BOOST_REGEX_SOURCE)
#     define BOOST_REGEX_BUILD_DLL
#     define BOOST_REGEX_DECL BOOST_SYMBOL_EXPORT
#  else
#     define BOOST_REGEX_DECL BOOST_SYMBOL_IMPORT
#  endif
#else
#  define BOOST_REGEX_DECL
#endif

#ifdef BOOST_REGEX_CXX03
#if !defined(BOOST_REGEX_NO_LIB) && !defined(BOOST_REGEX_SOURCE) && !defined(BOOST_ALL_NO_LIB) && defined(__cplusplus)
#  define BOOST_LIB_NAME boost_regex
#  if defined(BOOST_REGEX_DYN_LINK) || defined(BOOST_ALL_DYN_LINK)
#     define BOOST_DYN_LINK
#  endif
#  ifdef BOOST_REGEX_DIAG
#     define BOOST_LIB_DIAGNOSTIC
#  endif
#  include <boost/config/auto_link.hpp>
#endif
#endif

/*****************************************************************************
 *
 *  Set up function call type:
 *
 ****************************************************************************/

#if defined(_MSC_VER) && defined(_MSC_EXTENSIONS)
#if defined(_DEBUG) || defined(__MSVC_RUNTIME_CHECKS) || defined(_MANAGED) || defined(BOOST_REGEX_NO_FASTCALL)
#  define BOOST_REGEX_CALL __cdecl
#else
#  define BOOST_REGEX_CALL __fastcall
#endif
#  define BOOST_REGEX_CCALL __cdecl
#endif

#if defined(__BORLANDC__) && !defined(BOOST_DISABLE_WIN32)
#if defined(__clang__)
#  define BOOST_REGEX_CALL __cdecl
#  define BOOST_REGEX_CCALL __cdecl
#else
#  define BOOST_REGEX_CALL __fastcall
#  define BOOST_REGEX_CCALL __stdcall
#endif
#endif

#ifndef BOOST_REGEX_CALL
#  define BOOST_REGEX_CALL
#endif
#ifndef BOOST_REGEX_CCALL
#define BOOST_REGEX_CCALL
#endif

/*****************************************************************************
 *
 *  Set up localisation model:
 *
 ****************************************************************************/

/* backwards compatibility: */
#ifdef BOOST_RE_LOCALE_C
#  define BOOST_REGEX_USE_C_LOCALE
#endif

#ifdef BOOST_RE_LOCALE_CPP
#  define BOOST_REGEX_USE_CPP_LOCALE
#endif

#if defined(__CYGWIN__)
#  define BOOST_REGEX_USE_C_LOCALE
#endif

/* use C++ locale when targeting windows store */
#if BOOST_PLAT_WINDOWS_RUNTIME
#  define BOOST_REGEX_USE_CPP_LOCALE
#  define BOOST_REGEX_NO_WIN32_LOCALE
#endif

/* Win32 defaults to native Win32 locale: */
#if defined(_WIN32) && \
    !defined(BOOST_REGEX_USE_WIN32_LOCALE) && \
    !defined(BOOST_REGEX_USE_C_LOCALE) && \
    !defined(BOOST_REGEX_USE_CPP_LOCALE) && \
    !defined(BOOST_REGEX_NO_W32) && \
    !defined(BOOST_REGEX_NO_WIN32_LOCALE)
#  define BOOST_REGEX_USE_WIN32_LOCALE
#endif
/* otherwise use C++ locale if supported: */
#if !defined(BOOST_REGEX_USE_WIN32_LOCALE) && !defined(BOOST_REGEX_USE_C_LOCALE) && !defined(BOOST_REGEX_USE_CPP_LOCALE) && !defined(BOOST_NO_STD_LOCALE)
#  define BOOST_REGEX_USE_CPP_LOCALE
#endif
/* otherwise use C locale: */
#if !defined(BOOST_REGEX_USE_WIN32_LOCALE) && !defined(BOOST_REGEX_USE_C_LOCALE) && !defined(BOOST_REGEX_USE_CPP_LOCALE)
#  define BOOST_REGEX_USE_C_LOCALE
#endif

#ifndef BOOST_REGEX_MAX_STATE_COUNT
#  define BOOST_REGEX_MAX_STATE_COUNT 100000000
#endif


/*****************************************************************************
 *
 *  Error Handling for exception free compilers:
 *
 ****************************************************************************/

#ifdef BOOST_NO_EXCEPTIONS
/*
 * If there are no exceptions then we must report critical-errors
 * the only way we know how; by terminating.
 */
#include <stdexcept>
#include <string>
#include <boost/throw_exception.hpp>

#  define BOOST_REGEX_NOEH_ASSERT(x)\
if(0 == (x))\
{\
   std::string s("Error: critical regex++ failure in: ");\
   s.append(#x);\
   std::runtime_error e(s);\
   boost::throw_exception(e);\
}
#else
/*
 * With exceptions then error handling is taken care of and
 * there is no need for these checks:
 */
#  define BOOST_REGEX_NOEH_ASSERT(x)
#endif


/*****************************************************************************
 *
 *  Stack protection under MS Windows:
 *
 ****************************************************************************/

#if !defined(BOOST_REGEX_NO_W32) && !defined(BOOST_REGEX_V3)
#  if(defined(_WIN32) || defined(_WIN64) || defined(_WINCE)) \
        && !(defined(__GNUC__) || defined(__BORLANDC__) && defined(__clang__)) \
        && !(defined(__BORLANDC__) && (__BORLANDC__ >= 0x600)) \
        && !(defined(__MWERKS__) && (__MWERKS__ <= 0x3003))
#     define BOOST_REGEX_HAS_MS_STACK_GUARD
#  endif
#elif defined(BOOST_REGEX_HAS_MS_STACK_GUARD)
#  undef BOOST_REGEX_HAS_MS_STACK_GUARD
#endif

#if defined(__cplusplus) && defined(BOOST_REGEX_HAS_MS_STACK_GUARD)

namespace boost{
namespace BOOST_REGEX_DETAIL_NS{

BOOST_REGEX_DECL void BOOST_REGEX_CALL reset_stack_guard_page();

}
}

#endif


/*****************************************************************************
 *
 *  Algorithm selection and configuration.
 *  These options are now obsolete for C++11 and later (regex v5).
 *
 ****************************************************************************/

#if !defined(BOOST_REGEX_RECURSIVE) && !defined(BOOST_REGEX_NON_RECURSIVE)
#  if defined(BOOST_REGEX_HAS_MS_STACK_GUARD) && !defined(_STLP_DEBUG) && !defined(__STL_DEBUG) && !(defined(_MSC_VER) && (_MSC_VER >= 1400)) && defined(BOOST_REGEX_CXX03)
#     define BOOST_REGEX_RECURSIVE
#  else
#     define BOOST_REGEX_NON_RECURSIVE
#  endif
#endif

#ifdef BOOST_REGEX_NON_RECURSIVE
#  ifdef BOOST_REGEX_RECURSIVE
#     error "Can't set both BOOST_REGEX_RECURSIVE and BOOST_REGEX_NON_RECURSIVE"
#  endif
#  ifndef BOOST_REGEX_BLOCKSIZE
#     define BOOST_REGEX_BLOCKSIZE 4096
#  endif
#  if BOOST_REGEX_BLOCKSIZE < 512
#     error "BOOST_REGEX_BLOCKSIZE must be at least 512"
#  endif
#  ifndef BOOST_REGEX_MAX_BLOCKS
#     define BOOST_REGEX_MAX_BLOCKS 1024
#  endif
#  ifdef BOOST_REGEX_HAS_MS_STACK_GUARD
#     undef BOOST_REGEX_HAS_MS_STACK_GUARD
#  endif
#  ifndef BOOST_REGEX_MAX_CACHE_BLOCKS
#     define BOOST_REGEX_MAX_CACHE_BLOCKS 16
#  endif
#endif


/*****************************************************************************
 *
 *  Diagnostics:
 *
 ****************************************************************************/

#ifdef BOOST_REGEX_CONFIG_INFO
BOOST_REGEX_DECL void BOOST_REGEX_CALL print_regex_library_info();
#endif

#if defined(BOOST_REGEX_DIAG)
#  pragma message ("BOOST_REGEX_DECL" BOOST_STRINGIZE(=BOOST_REGEX_DECL))
#  pragma message ("BOOST_REGEX_CALL" BOOST_STRINGIZE(=BOOST_REGEX_CALL))
#  pragma message ("BOOST_REGEX_CCALL" BOOST_STRINGIZE(=BOOST_REGEX_CCALL))
#ifdef BOOST_REGEX_USE_C_LOCALE
#  pragma message ("Using C locale in regex traits class")
#elif BOOST_REGEX_USE_CPP_LOCALE
#  pragma message ("Using C++ locale in regex traits class")
#else
#  pragma message ("Using Win32 locale in regex traits class")
#endif
#if defined(BOOST_REGEX_DYN_LINK) || defined(BOOST_ALL_DYN_LINK)
#  pragma message ("Dynamic linking enabled")
#endif
#if defined(BOOST_REGEX_NO_LIB) || defined(BOOST_ALL_NO_LIB)
#  pragma message ("Auto-linking disabled")
#endif
#ifdef BOOST_REGEX_NO_EXTERNAL_TEMPLATES
#  pragma message ("Extern templates disabled")
#endif

#endif

#endif


/* config.hpp
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
*/