//  Boost config.hpp configuration header file  ------------------------------//
//  boostinspect:ndprecated_macros -- tell the inspect tool to ignore this file

//  Copyright (c) 2001-2003 John Maddock
//  Copyright (c) 2001 Darin Adler
//  Copyright (c) 2001 Peter Dimov
//  Copyright (c) 2002 Bill Kempf
//  Copyright (c) 2002 Jens Maurer
//  Copyright (c) 2002-2003 David Abrahams
//  Copyright (c) 2003 Gennaro Prota
//  Copyright (c) 2003 Eric Friedman
//  Copyright (c) 2010 Eric Jourdanneau, Joel Falcou
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for most recent version.

//  Boost config.hpp policy and rationale documentation has been moved to
//  http://www.boost.org/libs/config/
//
//  This file is intended to be stable, and relatively unchanging.
//  It should contain boilerplate code only - no compiler specific
//  code unless it is unavoidable - no changes unless unavoidable.

#ifndef BOOST_CONFIG_SUFFIX_HPP
#define BOOST_CONFIG_SUFFIX_HPP

#if defined(__GNUC__) && (__GNUC__ >= 4)
//
// Some GCC-4.x versions issue warnings even when __extension__ is used,
// so use this as a workaround:
//
#pragma GCC system_header
#endif

//
// ensure that visibility macros are always defined, thus symplifying use
//
#ifndef BOOST_SYMBOL_EXPORT
# define BOOST_SYMBOL_EXPORT
#endif
#ifndef BOOST_SYMBOL_IMPORT
# define BOOST_SYMBOL_IMPORT
#endif
#ifndef BOOST_SYMBOL_VISIBLE
# define BOOST_SYMBOL_VISIBLE
#endif

//
// look for long long by looking for the appropriate macros in <limits.h>.
// Note that we use limits.h rather than climits for maximal portability,
// remember that since these just declare a bunch of macros, there should be
// no namespace issues from this.
//
#if !defined(BOOST_HAS_LONG_LONG) && !defined(BOOST_NO_LONG_LONG)                                              \
   && !defined(BOOST_MSVC) && !defined(__BORLANDC__)
# include <limits.h>
# if (defined(ULLONG_MAX) || defined(ULONG_LONG_MAX) || defined(ULONGLONG_MAX))
#   define BOOST_HAS_LONG_LONG
# else
#   define BOOST_NO_LONG_LONG
# endif
#endif

// GCC 3.x will clean up all of those nasty macro definitions that
// BOOST_NO_CTYPE_FUNCTIONS is intended to help work around, so undefine
// it under GCC 3.x.
#if defined(__GNUC__) && (__GNUC__ >= 3) && defined(BOOST_NO_CTYPE_FUNCTIONS)
#  undef BOOST_NO_CTYPE_FUNCTIONS
#endif

//
// Assume any extensions are in namespace std:: unless stated otherwise:
//
#  ifndef BOOST_STD_EXTENSION_NAMESPACE
#    define BOOST_STD_EXTENSION_NAMESPACE std
#  endif

//
// If cv-qualified specializations are not allowed, then neither are cv-void ones:
//
#  if defined(BOOST_NO_CV_SPECIALIZATIONS) \
      && !defined(BOOST_NO_CV_VOID_SPECIALIZATIONS)
#     define BOOST_NO_CV_VOID_SPECIALIZATIONS
#  endif

//
// If there is no numeric_limits template, then it can't have any compile time
// constants either!
//
#  if defined(BOOST_NO_LIMITS) \
      && !defined(BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS)
#     define BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS
#     define BOOST_NO_MS_INT64_NUMERIC_LIMITS
#     define BOOST_NO_LONG_LONG_NUMERIC_LIMITS
#  endif

//
// if there is no long long then there is no specialisation
// for numeric_limits<long long> either:
//
#if !defined(BOOST_HAS_LONG_LONG) && !defined(BOOST_NO_LONG_LONG_NUMERIC_LIMITS)
#  define BOOST_NO_LONG_LONG_NUMERIC_LIMITS
#endif

//
// if there is no __int64 then there is no specialisation
// for numeric_limits<__int64> either:
//
#if !defined(BOOST_HAS_MS_INT64) && !defined(BOOST_NO_MS_INT64_NUMERIC_LIMITS)
#  define BOOST_NO_MS_INT64_NUMERIC_LIMITS
#endif

//
// if member templates are supported then so is the
// VC6 subset of member templates:
//
#  if !defined(BOOST_NO_MEMBER_TEMPLATES) \
       && !defined(BOOST_MSVC6_MEMBER_TEMPLATES)
#     define BOOST_MSVC6_MEMBER_TEMPLATES
#  endif

//
// Without partial specialization, can't test for partial specialisation bugs:
//
#  if defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) \
      && !defined(BOOST_BCB_PARTIAL_SPECIALIZATION_BUG)
#     define BOOST_BCB_PARTIAL_SPECIALIZATION_BUG
#  endif

//
// Without partial specialization, we can't have array-type partial specialisations:
//
#  if defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) \
      && !defined(BOOST_NO_ARRAY_TYPE_SPECIALIZATIONS)
#     define BOOST_NO_ARRAY_TYPE_SPECIALIZATIONS
#  endif

//
// Without partial specialization, std::iterator_traits can't work:
//
#  if defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) \
      && !defined(BOOST_NO_STD_ITERATOR_TRAITS)
#     define BOOST_NO_STD_ITERATOR_TRAITS
#  endif

//
// Without partial specialization, partial
// specialization with default args won't work either:
//
#  if defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) \
      && !defined(BOOST_NO_PARTIAL_SPECIALIZATION_IMPLICIT_DEFAULT_ARGS)
#     define BOOST_NO_PARTIAL_SPECIALIZATION_IMPLICIT_DEFAULT_ARGS
#  endif

//
// Without member template support, we can't have template constructors
// in the standard library either:
//
#  if defined(BOOST_NO_MEMBER_TEMPLATES) \
      && !defined(BOOST_MSVC6_MEMBER_TEMPLATES) \
      && !defined(BOOST_NO_TEMPLATED_ITERATOR_CONSTRUCTORS)
#     define BOOST_NO_TEMPLATED_ITERATOR_CONSTRUCTORS
#  endif

//
// Without member template support, we can't have a conforming
// std::allocator template either:
//
#  if defined(BOOST_NO_MEMBER_TEMPLATES) \
      && !defined(BOOST_MSVC6_MEMBER_TEMPLATES) \
      && !defined(BOOST_NO_STD_ALLOCATOR)
#     define BOOST_NO_STD_ALLOCATOR
#  endif

//
// without ADL support then using declarations will break ADL as well:
//
#if defined(BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP) && !defined(BOOST_FUNCTION_SCOPE_USING_DECLARATION_BREAKS_ADL)
#  define BOOST_FUNCTION_SCOPE_USING_DECLARATION_BREAKS_ADL
#endif

//
// Without typeid support we have no dynamic RTTI either:
//
#if defined(BOOST_NO_TYPEID) && !defined(BOOST_NO_RTTI)
#  define BOOST_NO_RTTI
#endif

//
// If we have a standard allocator, then we have a partial one as well:
//
#if !defined(BOOST_NO_STD_ALLOCATOR)
#  define BOOST_HAS_PARTIAL_STD_ALLOCATOR
#endif

//
// We can't have a working std::use_facet if there is no std::locale:
//
#  if defined(BOOST_NO_STD_LOCALE) && !defined(BOOST_NO_STD_USE_FACET)
#     define BOOST_NO_STD_USE_FACET
#  endif

//
// We can't have a std::messages facet if there is no std::locale:
//
#  if defined(BOOST_NO_STD_LOCALE) && !defined(BOOST_NO_STD_MESSAGES)
#     define BOOST_NO_STD_MESSAGES
#  endif

//
// We can't have a working std::wstreambuf if there is no std::locale:
//
#  if defined(BOOST_NO_STD_LOCALE) && !defined(BOOST_NO_STD_WSTREAMBUF)
#     define BOOST_NO_STD_WSTREAMBUF
#  endif

//
// We can't have a <cwctype> if there is no <cwchar>:
//
#  if defined(BOOST_NO_CWCHAR) && !defined(BOOST_NO_CWCTYPE)
#     define BOOST_NO_CWCTYPE
#  endif

//
// We can't have a swprintf if there is no <cwchar>:
//
#  if defined(BOOST_NO_CWCHAR) && !defined(BOOST_NO_SWPRINTF)
#     define BOOST_NO_SWPRINTF
#  endif

//
// If Win32 support is turned off, then we must turn off
// threading support also, unless there is some other
// thread API enabled:
//
#if defined(BOOST_DISABLE_WIN32) && defined(_WIN32) \
   && !defined(BOOST_DISABLE_THREADS) && !defined(BOOST_HAS_PTHREADS)
#  define BOOST_DISABLE_THREADS
#endif

//
// Turn on threading support if the compiler thinks that it's in
// multithreaded mode.  We put this here because there are only a
// limited number of macros that identify this (if there's any missing
// from here then add to the appropriate compiler section):
//
#if (defined(__MT__) || defined(_MT) || defined(_REENTRANT) \
    || defined(_PTHREADS) || defined(__APPLE__) || defined(__DragonFly__)) \
    && !defined(BOOST_HAS_THREADS)
#  define BOOST_HAS_THREADS
#endif

//
// Turn threading support off if BOOST_DISABLE_THREADS is defined:
//
#if defined(BOOST_DISABLE_THREADS) && defined(BOOST_HAS_THREADS)
#  undef BOOST_HAS_THREADS
#endif

//
// Turn threading support off if we don't recognise the threading API:
//
#if defined(BOOST_HAS_THREADS) && !defined(BOOST_HAS_PTHREADS)\
      && !defined(BOOST_HAS_WINTHREADS) && !defined(BOOST_HAS_BETHREADS)\
      && !defined(BOOST_HAS_MPTASKS)
#  undef BOOST_HAS_THREADS
#endif

//
// Turn threading detail macros off if we don't (want to) use threading
//
#ifndef BOOST_HAS_THREADS
#  undef BOOST_HAS_PTHREADS
#  undef BOOST_HAS_PTHREAD_MUTEXATTR_SETTYPE
#  undef BOOST_HAS_PTHREAD_YIELD
#  undef BOOST_HAS_PTHREAD_DELAY_NP
#  undef BOOST_HAS_WINTHREADS
#  undef BOOST_HAS_BETHREADS
#  undef BOOST_HAS_MPTASKS
#endif

//
// If the compiler claims to be C99 conformant, then it had better
// have a <stdint.h>:
//
#  if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
#     define BOOST_HAS_STDINT_H
#     ifndef BOOST_HAS_LOG1P
#        define BOOST_HAS_LOG1P
#     endif
#     ifndef BOOST_HAS_EXPM1
#        define BOOST_HAS_EXPM1
#     endif
#  endif

//
// Define BOOST_NO_SLIST and BOOST_NO_HASH if required.
// Note that this is for backwards compatibility only.
//
#  if !defined(BOOST_HAS_SLIST) && !defined(BOOST_NO_SLIST)
#     define BOOST_NO_SLIST
#  endif

#  if !defined(BOOST_HAS_HASH) && !defined(BOOST_NO_HASH)
#     define BOOST_NO_HASH
#  endif

//
// Set BOOST_SLIST_HEADER if not set already:
//
#if defined(BOOST_HAS_SLIST) && !defined(BOOST_SLIST_HEADER)
#  define BOOST_SLIST_HEADER <slist>
#endif

//
// Set BOOST_HASH_SET_HEADER if not set already:
//
#if defined(BOOST_HAS_HASH) && !defined(BOOST_HASH_SET_HEADER)
#  define BOOST_HASH_SET_HEADER <hash_set>
#endif

//
// Set BOOST_HASH_MAP_HEADER if not set already:
//
#if defined(BOOST_HAS_HASH) && !defined(BOOST_HASH_MAP_HEADER)
#  define BOOST_HASH_MAP_HEADER <hash_map>
#endif

//  BOOST_HAS_ABI_HEADERS
//  This macro gets set if we have headers that fix the ABI,
//  and prevent ODR violations when linking to external libraries:
#if defined(BOOST_ABI_PREFIX) && defined(BOOST_ABI_SUFFIX) && !defined(BOOST_HAS_ABI_HEADERS)
#  define BOOST_HAS_ABI_HEADERS
#endif

#if defined(BOOST_HAS_ABI_HEADERS) && defined(BOOST_DISABLE_ABI_HEADERS)
#  undef BOOST_HAS_ABI_HEADERS
#endif

//  BOOST_NO_STDC_NAMESPACE workaround  --------------------------------------//
//  Because std::size_t usage is so common, even in boost headers which do not
//  otherwise use the C library, the <cstddef> workaround is included here so
//  that ugly workaround code need not appear in many other boost headers.
//  NOTE WELL: This is a workaround for non-conforming compilers; <cstddef>
//  must still be #included in the usual places so that <cstddef> inclusion
//  works as expected with standard conforming compilers.  The resulting
//  double inclusion of <cstddef> is harmless.

# if defined(BOOST_NO_STDC_NAMESPACE) && defined(__cplusplus)
#   include <cstddef>
    namespace std { using ::ptrdiff_t; using ::size_t; }
# endif

//  Workaround for the unfortunate min/max macros defined by some platform headers

#define BOOST_PREVENT_MACRO_SUBSTITUTION

#ifndef BOOST_USING_STD_MIN
#  define BOOST_USING_STD_MIN() using std::min
#endif

#ifndef BOOST_USING_STD_MAX
#  define BOOST_USING_STD_MAX() using std::max
#endif

//  BOOST_NO_STD_MIN_MAX workaround  -----------------------------------------//

#  if defined(BOOST_NO_STD_MIN_MAX) && defined(__cplusplus)

namespace std {
  template <class _Tp>
  inline const _Tp& min BOOST_PREVENT_MACRO_SUBSTITUTION (const _Tp& __a, const _Tp& __b) {
    return __b < __a ? __b : __a;
  }
  template <class _Tp>
  inline const _Tp& max BOOST_PREVENT_MACRO_SUBSTITUTION (const _Tp& __a, const _Tp& __b) {
    return  __a < __b ? __b : __a;
  }
}

#  endif

// BOOST_STATIC_CONSTANT workaround --------------------------------------- //
// On compilers which don't allow in-class initialization of static integral
// constant members, we must use enums as a workaround if we want the constants
// to be available at compile-time. This macro gives us a convenient way to
// declare such constants.

#  ifdef BOOST_NO_INCLASS_MEMBER_INITIALIZATION
#       define BOOST_STATIC_CONSTANT(type, assignment) enum { assignment }
#  else
#     define BOOST_STATIC_CONSTANT(type, assignment) static const type assignment
#  endif

// BOOST_USE_FACET / HAS_FACET workaround ----------------------------------//
// When the standard library does not have a conforming std::use_facet there
// are various workarounds available, but they differ from library to library.
// The same problem occurs with has_facet.
// These macros provide a consistent way to access a locale's facets.
// Usage:
//    replace
//       std::use_facet<Type>(loc);
//    with
//       BOOST_USE_FACET(Type, loc);
//    Note do not add a std:: prefix to the front of BOOST_USE_FACET!
//  Use for BOOST_HAS_FACET is analogous.

#if defined(BOOST_NO_STD_USE_FACET)
#  ifdef BOOST_HAS_TWO_ARG_USE_FACET
#     define BOOST_USE_FACET(Type, loc) std::use_facet(loc, static_cast<Type*>(0))
#     define BOOST_HAS_FACET(Type, loc) std::has_facet(loc, static_cast<Type*>(0))
#  elif defined(BOOST_HAS_MACRO_USE_FACET)
#     define BOOST_USE_FACET(Type, loc) std::_USE(loc, Type)
#     define BOOST_HAS_FACET(Type, loc) std::_HAS(loc, Type)
#  elif defined(BOOST_HAS_STLP_USE_FACET)
#     define BOOST_USE_FACET(Type, loc) (*std::_Use_facet<Type >(loc))
#     define BOOST_HAS_FACET(Type, loc) std::has_facet< Type >(loc)
#  endif
#else
#  define BOOST_USE_FACET(Type, loc) std::use_facet< Type >(loc)
#  define BOOST_HAS_FACET(Type, loc) std::has_facet< Type >(loc)
#endif

// BOOST_NESTED_TEMPLATE workaround ------------------------------------------//
// Member templates are supported by some compilers even though they can't use
// the A::template member<U> syntax, as a workaround replace:
//
// typedef typename A::template rebind<U> binder;
//
// with:
//
// typedef typename A::BOOST_NESTED_TEMPLATE rebind<U> binder;

#ifndef BOOST_NO_MEMBER_TEMPLATE_KEYWORD
#  define BOOST_NESTED_TEMPLATE template
#else
#  define BOOST_NESTED_TEMPLATE
#endif

// BOOST_UNREACHABLE_RETURN(x) workaround -------------------------------------//
// Normally evaluates to nothing, unless BOOST_NO_UNREACHABLE_RETURN_DETECTION
// is defined, in which case it evaluates to return x; Use when you have a return
// statement that can never be reached.

#ifndef BOOST_UNREACHABLE_RETURN
#  ifdef BOOST_NO_UNREACHABLE_RETURN_DETECTION
#     define BOOST_UNREACHABLE_RETURN(x) return x;
#  else
#     define BOOST_UNREACHABLE_RETURN(x)
#  endif
#endif

// BOOST_DEDUCED_TYPENAME workaround ------------------------------------------//
//
// Some compilers don't support the use of `typename' for dependent
// types in deduced contexts, e.g.
//
//     template <class T> void f(T, typename T::type);
//                                  ^^^^^^^^
// Replace these declarations with:
//
//     template <class T> void f(T, BOOST_DEDUCED_TYPENAME T::type);

#ifndef BOOST_NO_DEDUCED_TYPENAME
#  define BOOST_DEDUCED_TYPENAME typename
#else
#  define BOOST_DEDUCED_TYPENAME
#endif

#ifndef BOOST_NO_TYPENAME_WITH_CTOR
#  define BOOST_CTOR_TYPENAME typename
#else
#  define BOOST_CTOR_TYPENAME
#endif

// long long workaround ------------------------------------------//
// On gcc (and maybe other compilers?) long long is alway supported
// but it's use may generate either warnings (with -ansi), or errors
// (with -pedantic -ansi) unless it's use is prefixed by __extension__
//
#if defined(BOOST_HAS_LONG_LONG) && defined(__cplusplus)
namespace boost{
#  ifdef __GNUC__
   __extension__ typedef long long long_long_type;
   __extension__ typedef unsigned long long ulong_long_type;
#  else
   typedef long long long_long_type;
   typedef unsigned long long ulong_long_type;
#  endif
}
#endif
// same again for __int128:
#if defined(BOOST_HAS_INT128) && defined(__cplusplus)
namespace boost{
#  ifdef __GNUC__
   __extension__ typedef __int128 int128_type;
   __extension__ typedef unsigned __int128 uint128_type;
#  else
   typedef __int128 int128_type;
   typedef unsigned __int128 uint128_type;
#  endif
}
#endif
// same again for __float128:
#if defined(BOOST_HAS_FLOAT128) && defined(__cplusplus)
namespace boost {
#  ifdef __GNUC__
   __extension__ typedef __float128 float128_type;
#  else
   typedef __float128 float128_type;
#  endif
}
#endif

// BOOST_[APPEND_]EXPLICIT_TEMPLATE_[NON_]TYPE macros --------------------------//

// These macros are obsolete. Port away and remove.

#  define BOOST_EXPLICIT_TEMPLATE_TYPE(t)
#  define BOOST_EXPLICIT_TEMPLATE_TYPE_SPEC(t)
#  define BOOST_EXPLICIT_TEMPLATE_NON_TYPE(t, v)
#  define BOOST_EXPLICIT_TEMPLATE_NON_TYPE_SPEC(t, v)

#  define BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(t)
#  define BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(t)
#  define BOOST_APPEND_EXPLICIT_TEMPLATE_NON_TYPE(t, v)
#  define BOOST_APPEND_EXPLICIT_TEMPLATE_NON_TYPE_SPEC(t, v)

// When BOOST_NO_STD_TYPEINFO is defined, we can just import
// the global definition into std namespace:
#if defined(BOOST_NO_STD_TYPEINFO) && defined(__cplusplus)
#include <typeinfo>
namespace std{ using ::type_info; }
#endif

// ---------------------------------------------------------------------------//

// Helper macro BOOST_STRINGIZE:
// Helper macro BOOST_JOIN:

#include <boost/config/helper_macros.hpp>

//
// Set some default values for compiler/library/platform names.
// These are for debugging config setup only:
//
#  ifndef BOOST_COMPILER
#     define BOOST_COMPILER "Unknown ISO C++ Compiler"
#  endif
#  ifndef BOOST_STDLIB
#     define BOOST_STDLIB "Unknown ISO standard library"
#  endif
#  ifndef BOOST_PLATFORM
#     if defined(unix) || defined(__unix) || defined(_XOPEN_SOURCE) \
         || defined(_POSIX_SOURCE)
#        define BOOST_PLATFORM "Generic Unix"
#     else
#        define BOOST_PLATFORM "Unknown"
#     endif
#  endif

//
// Set some default values GPU support
//
#  ifndef BOOST_GPU_ENABLED
#  define BOOST_GPU_ENABLED
#  endif

// BOOST_RESTRICT ---------------------------------------------//
// Macro to use in place of 'restrict' keyword variants
#if !defined(BOOST_RESTRICT)
#  if defined(_MSC_VER)
#    define BOOST_RESTRICT __restrict
#    if !defined(BOOST_NO_RESTRICT_REFERENCES) && (_MSC_FULL_VER < 190023026)
#      define BOOST_NO_RESTRICT_REFERENCES
#    endif
#  elif defined(__GNUC__) && __GNUC__ > 3
     // Clang also defines __GNUC__ (as 4)
#    define BOOST_RESTRICT __restrict__
#  else
#    define BOOST_RESTRICT
#    if !defined(BOOST_NO_RESTRICT_REFERENCES)
#      define BOOST_NO_RESTRICT_REFERENCES
#    endif
#  endif
#endif

// BOOST_MAY_ALIAS -----------------------------------------------//
// The macro expands to an attribute to mark a type that is allowed to alias other types.
// The macro is defined in the compiler-specific headers.
#if !defined(BOOST_MAY_ALIAS)
#  define BOOST_NO_MAY_ALIAS
#  define BOOST_MAY_ALIAS
#endif

// BOOST_FORCEINLINE ---------------------------------------------//
// Macro to use in place of 'inline' to force a function to be inline
#if !defined(BOOST_FORCEINLINE)
#  if defined(_MSC_VER)
#    define BOOST_FORCEINLINE __forceinline
#  elif defined(__GNUC__) && __GNUC__ > 3
     // Clang also defines __GNUC__ (as 4)
#    define BOOST_FORCEINLINE inline __attribute__ ((__always_inline__))
#  else
#    define BOOST_FORCEINLINE inline
#  endif
#endif

// BOOST_NOINLINE ---------------------------------------------//
// Macro to use in place of 'inline' to prevent a function to be inlined
#if !defined(BOOST_NOINLINE)
#  if defined(_MSC_VER)
#    define BOOST_NOINLINE __declspec(noinline)
#  elif defined(__GNUC__) && __GNUC__ > 3
     // Clang also defines __GNUC__ (as 4)
#    if defined(__CUDACC__)
       // nvcc doesn't always parse __noinline__,
       // see: https://svn.boost.org/trac/boost/ticket/9392
#      define BOOST_NOINLINE __attribute__ ((noinline))
#    else
#      define BOOST_NOINLINE __attribute__ ((__noinline__))
#    endif
#  else
#    define BOOST_NOINLINE
#  endif
#endif

// BOOST_NORETURN ---------------------------------------------//
// Macro to use before a function declaration/definition to designate
// the function as not returning normally (i.e. with a return statement
// or by leaving the function scope, if the function return type is void).
#if !defined(BOOST_NORETURN)
#  if defined(_MSC_VER)
#    define BOOST_NORETURN __declspec(noreturn)
#  elif defined(__GNUC__)
#    define BOOST_NORETURN __attribute__ ((__noreturn__))
#  elif defined(__has_attribute) && defined(__SUNPRO_CC) && (__SUNPRO_CC > 0x5130)
#    if __has_attribute(noreturn)
#      define BOOST_NORETURN [[noreturn]]
#    endif
#  elif defined(__has_cpp_attribute) 
#    if __has_cpp_attribute(noreturn)
#      define BOOST_NORETURN [[noreturn]]
#    endif
#  endif
#endif

#if !defined(BOOST_NORETURN)
#  define BOOST_NO_NORETURN
#  define BOOST_NORETURN
#endif

// Branch prediction hints
// These macros are intended to wrap conditional expressions that yield true or false
//
//  if (BOOST_LIKELY(var == 10))
//  {
//     // the most probable code here
//  }
//
#if !defined(BOOST_LIKELY)
#  define BOOST_LIKELY(x) x
#endif
#if !defined(BOOST_UNLIKELY)
#  define BOOST_UNLIKELY(x) x
#endif

// Type and data alignment specification
//
#if !defined(BOOST_ALIGNMENT)
#  if !defined(BOOST_NO_CXX11_ALIGNAS)
#    define BOOST_ALIGNMENT(x) alignas(x)
#  elif defined(_MSC_VER)
#    define BOOST_ALIGNMENT(x) __declspec(align(x))
#  elif defined(__GNUC__)
#    define BOOST_ALIGNMENT(x) __attribute__ ((__aligned__(x)))
#  else
#    define BOOST_NO_ALIGNMENT
#    define BOOST_ALIGNMENT(x)
#  endif
#endif

// Lack of non-public defaulted functions is implied by the lack of any defaulted functions
#if !defined(BOOST_NO_CXX11_NON_PUBLIC_DEFAULTED_FUNCTIONS) && defined(BOOST_NO_CXX11_DEFAULTED_FUNCTIONS)
#  define BOOST_NO_CXX11_NON_PUBLIC_DEFAULTED_FUNCTIONS
#endif

// Lack of defaulted moves is implied by the lack of either rvalue references or any defaulted functions
#if !defined(BOOST_NO_CXX11_DEFAULTED_MOVES) && (defined(BOOST_NO_CXX11_DEFAULTED_FUNCTIONS) || defined(BOOST_NO_CXX11_RVALUE_REFERENCES))
#  define BOOST_NO_CXX11_DEFAULTED_MOVES
#endif

// Defaulted and deleted function declaration helpers
// These macros are intended to be inside a class definition.
// BOOST_DEFAULTED_FUNCTION accepts the function declaration and its
// body, which will be used if the compiler doesn't support defaulted functions.
// BOOST_DELETED_FUNCTION only accepts the function declaration. It
// will expand to a private function declaration, if the compiler doesn't support
// deleted functions. Because of this it is recommended to use BOOST_DELETED_FUNCTION
// in the end of the class definition.
//
//  class my_class
//  {
//  public:
//      // Default-constructible
//      BOOST_DEFAULTED_FUNCTION(my_class(), {})
//      // Copying prohibited
//      BOOST_DELETED_FUNCTION(my_class(my_class const&))
//      BOOST_DELETED_FUNCTION(my_class& operator= (my_class const&))
//  };
//
#if !(defined(BOOST_NO_CXX11_DEFAULTED_FUNCTIONS) || defined(BOOST_NO_CXX11_NON_PUBLIC_DEFAULTED_FUNCTIONS))
#   define BOOST_DEFAULTED_FUNCTION(fun, body) fun = default;
#else
#   define BOOST_DEFAULTED_FUNCTION(fun, body) fun body
#endif

#if !defined(BOOST_NO_CXX11_DELETED_FUNCTIONS)
#   define BOOST_DELETED_FUNCTION(fun) fun = delete;
#else
#   define BOOST_DELETED_FUNCTION(fun) private: fun;
#endif

//
// Set BOOST_NO_DECLTYPE_N3276 when BOOST_NO_DECLTYPE is defined
//
#if defined(BOOST_NO_CXX11_DECLTYPE) && !defined(BOOST_NO_CXX11_DECLTYPE_N3276)
#define BOOST_NO_CXX11_DECLTYPE_N3276 BOOST_NO_CXX11_DECLTYPE
#endif

//  -------------------- Deprecated macros for 1.50 ---------------------------
//  These will go away in a future release

//  Use BOOST_NO_CXX11_HDR_UNORDERED_SET or BOOST_NO_CXX11_HDR_UNORDERED_MAP
//           instead of BOOST_NO_STD_UNORDERED
#if defined(BOOST_NO_CXX11_HDR_UNORDERED_MAP) || defined (BOOST_NO_CXX11_HDR_UNORDERED_SET)
# ifndef BOOST_NO_CXX11_STD_UNORDERED
#  define BOOST_NO_CXX11_STD_UNORDERED
# endif
#endif

//  Use BOOST_NO_CXX11_HDR_INITIALIZER_LIST instead of BOOST_NO_INITIALIZER_LISTS
#if defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST) && !defined(BOOST_NO_INITIALIZER_LISTS)
#  define BOOST_NO_INITIALIZER_LISTS
#endif

//  Use BOOST_NO_CXX11_HDR_ARRAY instead of BOOST_NO_0X_HDR_ARRAY
#if defined(BOOST_NO_CXX11_HDR_ARRAY) && !defined(BOOST_NO_0X_HDR_ARRAY)
#  define BOOST_NO_0X_HDR_ARRAY
#endif
//  Use BOOST_NO_CXX11_HDR_CHRONO instead of BOOST_NO_0X_HDR_CHRONO
#if defined(BOOST_NO_CXX11_HDR_CHRONO) && !defined(BOOST_NO_0X_HDR_CHRONO)
#  define BOOST_NO_0X_HDR_CHRONO
#endif
//  Use BOOST_NO_CXX11_HDR_CODECVT instead of BOOST_NO_0X_HDR_CODECVT
#if defined(BOOST_NO_CXX11_HDR_CODECVT) && !defined(BOOST_NO_0X_HDR_CODECVT)
#  define BOOST_NO_0X_HDR_CODECVT
#endif
//  Use BOOST_NO_CXX11_HDR_CONDITION_VARIABLE instead of BOOST_NO_0X_HDR_CONDITION_VARIABLE
#if defined(BOOST_NO_CXX11_HDR_CONDITION_VARIABLE) && !defined(BOOST_NO_0X_HDR_CONDITION_VARIABLE)
#  define BOOST_NO_0X_HDR_CONDITION_VARIABLE
#endif
//  Use BOOST_NO_CXX11_HDR_FORWARD_LIST instead of BOOST_NO_0X_HDR_FORWARD_LIST
#if defined(BOOST_NO_CXX11_HDR_FORWARD_LIST) && !defined(BOOST_NO_0X_HDR_FORWARD_LIST)
#  define BOOST_NO_0X_HDR_FORWARD_LIST
#endif
//  Use BOOST_NO_CXX11_HDR_FUTURE instead of BOOST_NO_0X_HDR_FUTURE
#if defined(BOOST_NO_CXX11_HDR_FUTURE) && !defined(BOOST_NO_0X_HDR_FUTURE)
#  define BOOST_NO_0X_HDR_FUTURE
#endif

//  Use BOOST_NO_CXX11_HDR_INITIALIZER_LIST
//  instead of BOOST_NO_0X_HDR_INITIALIZER_LIST or BOOST_NO_INITIALIZER_LISTS
#ifdef BOOST_NO_CXX11_HDR_INITIALIZER_LIST
# ifndef BOOST_NO_0X_HDR_INITIALIZER_LIST
#  define BOOST_NO_0X_HDR_INITIALIZER_LIST
# endif
# ifndef BOOST_NO_INITIALIZER_LISTS
#  define BOOST_NO_INITIALIZER_LISTS
# endif
#endif

//  Use BOOST_NO_CXX11_HDR_MUTEX instead of BOOST_NO_0X_HDR_MUTEX
#if defined(BOOST_NO_CXX11_HDR_MUTEX) && !defined(BOOST_NO_0X_HDR_MUTEX)
#  define BOOST_NO_0X_HDR_MUTEX
#endif
//  Use BOOST_NO_CXX11_HDR_RANDOM instead of BOOST_NO_0X_HDR_RANDOM
#if defined(BOOST_NO_CXX11_HDR_RANDOM) && !defined(BOOST_NO_0X_HDR_RANDOM)
#  define BOOST_NO_0X_HDR_RANDOM
#endif
//  Use BOOST_NO_CXX11_HDR_RATIO instead of BOOST_NO_0X_HDR_RATIO
#if defined(BOOST_NO_CXX11_HDR_RATIO) && !defined(BOOST_NO_0X_HDR_RATIO)
#  define BOOST_NO_0X_HDR_RATIO
#endif
//  Use BOOST_NO_CXX11_HDR_REGEX instead of BOOST_NO_0X_HDR_REGEX
#if defined(BOOST_NO_CXX11_HDR_REGEX) && !defined(BOOST_NO_0X_HDR_REGEX)
#  define BOOST_NO_0X_HDR_REGEX
#endif
//  Use BOOST_NO_CXX11_HDR_SYSTEM_ERROR instead of BOOST_NO_0X_HDR_SYSTEM_ERROR
#if defined(BOOST_NO_CXX11_HDR_SYSTEM_ERROR) && !defined(BOOST_NO_0X_HDR_SYSTEM_ERROR)
#  define BOOST_NO_0X_HDR_SYSTEM_ERROR
#endif
//  Use BOOST_NO_CXX11_HDR_THREAD instead of BOOST_NO_0X_HDR_THREAD
#if defined(BOOST_NO_CXX11_HDR_THREAD) && !defined(BOOST_NO_0X_HDR_THREAD)
#  define BOOST_NO_0X_HDR_THREAD
#endif
//  Use BOOST_NO_CXX11_HDR_TUPLE instead of BOOST_NO_0X_HDR_TUPLE
#if defined(BOOST_NO_CXX11_HDR_TUPLE) && !defined(BOOST_NO_0X_HDR_TUPLE)
#  define BOOST_NO_0X_HDR_TUPLE
#endif
//  Use BOOST_NO_CXX11_HDR_TYPE_TRAITS instead of BOOST_NO_0X_HDR_TYPE_TRAITS
#if defined(BOOST_NO_CXX11_HDR_TYPE_TRAITS) && !defined(BOOST_NO_0X_HDR_TYPE_TRAITS)
#  define BOOST_NO_0X_HDR_TYPE_TRAITS
#endif
//  Use BOOST_NO_CXX11_HDR_TYPEINDEX instead of BOOST_NO_0X_HDR_TYPEINDEX
#if defined(BOOST_NO_CXX11_HDR_TYPEINDEX) && !defined(BOOST_NO_0X_HDR_TYPEINDEX)
#  define BOOST_NO_0X_HDR_TYPEINDEX
#endif
//  Use BOOST_NO_CXX11_HDR_UNORDERED_MAP instead of BOOST_NO_0X_HDR_UNORDERED_MAP
#if defined(BOOST_NO_CXX11_HDR_UNORDERED_MAP) && !defined(BOOST_NO_0X_HDR_UNORDERED_MAP)
#  define BOOST_NO_0X_HDR_UNORDERED_MAP
#endif
//  Use BOOST_NO_CXX11_HDR_UNORDERED_SET instead of BOOST_NO_0X_HDR_UNORDERED_SET
#if defined(BOOST_NO_CXX11_HDR_UNORDERED_SET) && !defined(BOOST_NO_0X_HDR_UNORDERED_SET)
#  define BOOST_NO_0X_HDR_UNORDERED_SET
#endif

//  ------------------ End of deprecated macros for 1.50 ---------------------------

//  -------------------- Deprecated macros for 1.51 ---------------------------
//  These will go away in a future release

//  Use     BOOST_NO_CXX11_AUTO_DECLARATIONS instead of   BOOST_NO_AUTO_DECLARATIONS
#if defined(BOOST_NO_CXX11_AUTO_DECLARATIONS) && !defined(BOOST_NO_AUTO_DECLARATIONS)
#  define BOOST_NO_AUTO_DECLARATIONS
#endif
//  Use     BOOST_NO_CXX11_AUTO_MULTIDECLARATIONS instead of   BOOST_NO_AUTO_MULTIDECLARATIONS
#if defined(BOOST_NO_CXX11_AUTO_MULTIDECLARATIONS) && !defined(BOOST_NO_AUTO_MULTIDECLARATIONS)
#  define BOOST_NO_AUTO_MULTIDECLARATIONS
#endif
//  Use     BOOST_NO_CXX11_CHAR16_T instead of   BOOST_NO_CHAR16_T
#if defined(BOOST_NO_CXX11_CHAR16_T) && !defined(BOOST_NO_CHAR16_T)
#  define BOOST_NO_CHAR16_T
#endif
//  Use     BOOST_NO_CXX11_CHAR32_T instead of   BOOST_NO_CHAR32_T
#if defined(BOOST_NO_CXX11_CHAR32_T) && !defined(BOOST_NO_CHAR32_T)
#  define BOOST_NO_CHAR32_T
#endif
//  Use     BOOST_NO_CXX11_TEMPLATE_ALIASES instead of   BOOST_NO_TEMPLATE_ALIASES
#if defined(BOOST_NO_CXX11_TEMPLATE_ALIASES) && !defined(BOOST_NO_TEMPLATE_ALIASES)
#  define BOOST_NO_TEMPLATE_ALIASES
#endif
//  Use     BOOST_NO_CXX11_CONSTEXPR instead of   BOOST_NO_CONSTEXPR
#if defined(BOOST_NO_CXX11_CONSTEXPR) && !defined(BOOST_NO_CONSTEXPR)
#  define BOOST_NO_CONSTEXPR
#endif
//  Use     BOOST_NO_CXX11_DECLTYPE_N3276 instead of   BOOST_NO_DECLTYPE_N3276
#if defined(BOOST_NO_CXX11_DECLTYPE_N3276) && !defined(BOOST_NO_DECLTYPE_N3276)
#  define BOOST_NO_DECLTYPE_N3276
#endif
//  Use     BOOST_NO_CXX11_DECLTYPE instead of   BOOST_NO_DECLTYPE
#if defined(BOOST_NO_CXX11_DECLTYPE) && !defined(BOOST_NO_DECLTYPE)
#  define BOOST_NO_DECLTYPE
#endif
//  Use     BOOST_NO_CXX11_DEFAULTED_FUNCTIONS instead of   BOOST_NO_DEFAULTED_FUNCTIONS
#if defined(BOOST_NO_CXX11_DEFAULTED_FUNCTIONS) && !defined(BOOST_NO_DEFAULTED_FUNCTIONS)
#  define BOOST_NO_DEFAULTED_FUNCTIONS
#endif
//  Use     BOOST_NO_CXX11_DELETED_FUNCTIONS instead of   BOOST_NO_DELETED_FUNCTIONS
#if defined(BOOST_NO_CXX11_DELETED_FUNCTIONS) && !defined(BOOST_NO_DELETED_FUNCTIONS)
#  define BOOST_NO_DELETED_FUNCTIONS
#endif
//  Use     BOOST_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS instead of   BOOST_NO_EXPLICIT_CONVERSION_OPERATORS
#if defined(BOOST_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS) && !defined(BOOST_NO_EXPLICIT_CONVERSION_OPERATORS)
#  define BOOST_NO_EXPLICIT_CONVERSION_OPERATORS
#endif
//  Use     BOOST_NO_CXX11_EXTERN_TEMPLATE instead of   BOOST_NO_EXTERN_TEMPLATE
#if defined(BOOST_NO_CXX11_EXTERN_TEMPLATE) && !defined(BOOST_NO_EXTERN_TEMPLATE)
#  define BOOST_NO_EXTERN_TEMPLATE
#endif
//  Use     BOOST_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS instead of   BOOST_NO_FUNCTION_TEMPLATE_DEFAULT_ARGS
#if defined(BOOST_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS) && !defined(BOOST_NO_FUNCTION_TEMPLATE_DEFAULT_ARGS)
#  define BOOST_NO_FUNCTION_TEMPLATE_DEFAULT_ARGS
#endif
//  Use     BOOST_NO_CXX11_LAMBDAS instead of   BOOST_NO_LAMBDAS
#if defined(BOOST_NO_CXX11_LAMBDAS) && !defined(BOOST_NO_LAMBDAS)
#  define BOOST_NO_LAMBDAS
#endif
//  Use     BOOST_NO_CXX11_LOCAL_CLASS_TEMPLATE_PARAMETERS instead of   BOOST_NO_LOCAL_CLASS_TEMPLATE_PARAMETERS
#if defined(BOOST_NO_CXX11_LOCAL_CLASS_TEMPLATE_PARAMETERS) && !defined(BOOST_NO_LOCAL_CLASS_TEMPLATE_PARAMETERS)
#  define BOOST_NO_LOCAL_CLASS_TEMPLATE_PARAMETERS
#endif
//  Use     BOOST_NO_CXX11_NOEXCEPT instead of   BOOST_NO_NOEXCEPT
#if defined(BOOST_NO_CXX11_NOEXCEPT) && !defined(BOOST_NO_NOEXCEPT)
#  define BOOST_NO_NOEXCEPT
#endif
//  Use     BOOST_NO_CXX11_NULLPTR instead of   BOOST_NO_NULLPTR
#if defined(BOOST_NO_CXX11_NULLPTR) && !defined(BOOST_NO_NULLPTR)
#  define BOOST_NO_NULLPTR
#endif
//  Use     BOOST_NO_CXX11_RAW_LITERALS instead of   BOOST_NO_RAW_LITERALS
#if defined(BOOST_NO_CXX11_RAW_LITERALS) && !defined(BOOST_NO_RAW_LITERALS)
#  define BOOST_NO_RAW_LITERALS
#endif
//  Use     BOOST_NO_CXX11_RVALUE_REFERENCES instead of   BOOST_NO_RVALUE_REFERENCES
#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && !defined(BOOST_NO_RVALUE_REFERENCES)
#  define BOOST_NO_RVALUE_REFERENCES
#endif
//  Use     BOOST_NO_CXX11_SCOPED_ENUMS instead of   BOOST_NO_SCOPED_ENUMS
#if defined(BOOST_NO_CXX11_SCOPED_ENUMS) && !defined(BOOST_NO_SCOPED_ENUMS)
#  define BOOST_NO_SCOPED_ENUMS
#endif
//  Use     BOOST_NO_CXX11_STATIC_ASSERT instead of   BOOST_NO_STATIC_ASSERT
#if defined(BOOST_NO_CXX11_STATIC_ASSERT) && !defined(BOOST_NO_STATIC_ASSERT)
#  define BOOST_NO_STATIC_ASSERT
#endif
//  Use     BOOST_NO_CXX11_STD_UNORDERED instead of   BOOST_NO_STD_UNORDERED
#if defined(BOOST_NO_CXX11_STD_UNORDERED) && !defined(BOOST_NO_STD_UNORDERED)
#  define BOOST_NO_STD_UNORDERED
#endif
//  Use     BOOST_NO_CXX11_UNICODE_LITERALS instead of   BOOST_NO_UNICODE_LITERALS
#if defined(BOOST_NO_CXX11_UNICODE_LITERALS) && !defined(BOOST_NO_UNICODE_LITERALS)
#  define BOOST_NO_UNICODE_LITERALS
#endif
//  Use     BOOST_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX instead of   BOOST_NO_UNIFIED_INITIALIZATION_SYNTAX
#if defined(BOOST_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX) && !defined(BOOST_NO_UNIFIED_INITIALIZATION_SYNTAX)
#  define BOOST_NO_UNIFIED_INITIALIZATION_SYNTAX
#endif
//  Use     BOOST_NO_CXX11_VARIADIC_TEMPLATES instead of   BOOST_NO_VARIADIC_TEMPLATES
#if defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) && !defined(BOOST_NO_VARIADIC_TEMPLATES)
#  define BOOST_NO_VARIADIC_TEMPLATES
#endif
//  Use     BOOST_NO_CXX11_VARIADIC_MACROS instead of   BOOST_NO_VARIADIC_MACROS
#if defined(BOOST_NO_CXX11_VARIADIC_MACROS) && !defined(BOOST_NO_VARIADIC_MACROS)
#  define BOOST_NO_VARIADIC_MACROS
#endif
//  Use     BOOST_NO_CXX11_NUMERIC_LIMITS instead of   BOOST_NO_NUMERIC_LIMITS_LOWEST
#if defined(BOOST_NO_CXX11_NUMERIC_LIMITS) && !defined(BOOST_NO_NUMERIC_LIMITS_LOWEST)
#  define BOOST_NO_NUMERIC_LIMITS_LOWEST
#endif
//  ------------------ End of deprecated macros for 1.51 ---------------------------


//
// Helper macro for marking types and methods final
//
#if !defined(BOOST_NO_CXX11_FINAL)
#  define BOOST_FINAL final
#else
#  define BOOST_FINAL
#endif

//
// Helper macros BOOST_NOEXCEPT, BOOST_NOEXCEPT_IF, BOOST_NOEXCEPT_EXPR
// These aid the transition to C++11 while still supporting C++03 compilers
//
#ifdef BOOST_NO_CXX11_NOEXCEPT
#  define BOOST_NOEXCEPT
#  define BOOST_NOEXCEPT_OR_NOTHROW throw()
#  define BOOST_NOEXCEPT_IF(Predicate)
#  define BOOST_NOEXCEPT_EXPR(Expression) false
#else
#  define BOOST_NOEXCEPT noexcept
#  define BOOST_NOEXCEPT_OR_NOTHROW noexcept
#  define BOOST_NOEXCEPT_IF(Predicate) noexcept((Predicate))
#  define BOOST_NOEXCEPT_EXPR(Expression) noexcept((Expression))
#endif
//
// Helper macro BOOST_FALLTHROUGH
// Fallback definition of BOOST_FALLTHROUGH macro used to mark intended
// fall-through between case labels in a switch statement. We use a definition
// that requires a semicolon after it to avoid at least one type of misuse even
// on unsupported compilers.
//
#ifndef BOOST_FALLTHROUGH
#  define BOOST_FALLTHROUGH ((void)0)
#endif

//
// constexpr workarounds
//
#if defined(BOOST_NO_CXX11_CONSTEXPR)
#define BOOST_CONSTEXPR
#define BOOST_CONSTEXPR_OR_CONST const
#else
#define BOOST_CONSTEXPR constexpr
#define BOOST_CONSTEXPR_OR_CONST constexpr
#endif
#if defined(BOOST_NO_CXX14_CONSTEXPR)
#define BOOST_CXX14_CONSTEXPR
#else
#define BOOST_CXX14_CONSTEXPR constexpr
#endif

//
// C++17 inline variables
//
#if !defined(BOOST_NO_CXX17_INLINE_VARIABLES)
#define BOOST_INLINE_VARIABLE inline
#else
#define BOOST_INLINE_VARIABLE
#endif
//
// C++17 if constexpr
//
#if !defined(BOOST_NO_CXX17_IF_CONSTEXPR)
#  define BOOST_IF_CONSTEXPR if constexpr
#else
#  define BOOST_IF_CONSTEXPR if
#endif

#define BOOST_INLINE_CONSTEXPR  BOOST_INLINE_VARIABLE BOOST_CONSTEXPR_OR_CONST

//
// Unused variable/typedef workarounds:
//
#ifndef BOOST_ATTRIBUTE_UNUSED
#  define BOOST_ATTRIBUTE_UNUSED
#endif
//
// [[nodiscard]]:
//
#if defined(__has_attribute) && defined(__SUNPRO_CC) && (__SUNPRO_CC > 0x5130)
#if __has_attribute(nodiscard)
# define BOOST_ATTRIBUTE_NODISCARD [[nodiscard]]
#endif
#if __has_attribute(no_unique_address)
# define BOOST_ATTRIBUTE_NO_UNIQUE_ADDRESS [[no_unique_address]]
#endif
#elif defined(__has_cpp_attribute)
// clang-6 accepts [[nodiscard]] with -std=c++14, but warns about it -pedantic
#if __has_cpp_attribute(nodiscard) && !(defined(__clang__) && (__cplusplus < 201703L))
# define BOOST_ATTRIBUTE_NODISCARD [[nodiscard]]
#endif
#if __has_cpp_attribute(no_unique_address) && !(defined(__GNUC__) && (__cplusplus < 201100))
# define BOOST_ATTRIBUTE_NO_UNIQUE_ADDRESS [[no_unique_address]]
#endif
#endif
#ifndef BOOST_ATTRIBUTE_NODISCARD
# define BOOST_ATTRIBUTE_NODISCARD
#endif
#ifndef BOOST_ATTRIBUTE_NO_UNIQUE_ADDRESS
# define BOOST_ATTRIBUTE_NO_UNIQUE_ADDRESS
#endif

#define BOOST_STATIC_CONSTEXPR  static BOOST_CONSTEXPR_OR_CONST

//
// Set BOOST_HAS_STATIC_ASSERT when BOOST_NO_CXX11_STATIC_ASSERT is not defined
//
#if !defined(BOOST_NO_CXX11_STATIC_ASSERT) && !defined(BOOST_HAS_STATIC_ASSERT)
#  define BOOST_HAS_STATIC_ASSERT
#endif

//
// Set BOOST_HAS_RVALUE_REFS when BOOST_NO_CXX11_RVALUE_REFERENCES is not defined
//
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && !defined(BOOST_HAS_RVALUE_REFS)
#define BOOST_HAS_RVALUE_REFS
#endif

//
// Set BOOST_HAS_VARIADIC_TMPL when BOOST_NO_CXX11_VARIADIC_TEMPLATES is not defined
//
#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) && !defined(BOOST_HAS_VARIADIC_TMPL)
#define BOOST_HAS_VARIADIC_TMPL
#endif
//
// Set BOOST_NO_CXX11_FIXED_LENGTH_VARIADIC_TEMPLATE_EXPANSION_PACKS when
// BOOST_NO_CXX11_VARIADIC_TEMPLATES is set:
//
#if defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) && !defined(BOOST_NO_CXX11_FIXED_LENGTH_VARIADIC_TEMPLATE_EXPANSION_PACKS)
#  define BOOST_NO_CXX11_FIXED_LENGTH_VARIADIC_TEMPLATE_EXPANSION_PACKS
#endif

// This is a catch all case for obsolete compilers / std libs:
#if !defined(_YVALS) && !defined(_CPPLIB_VER)  // msvc std lib already configured
#if (!defined(__has_include) || (__cplusplus < 201700))
#  define BOOST_NO_CXX17_HDR_OPTIONAL
#  define BOOST_NO_CXX17_HDR_STRING_VIEW
#  define BOOST_NO_CXX17_HDR_VARIANT
#else
#if !__has_include(<optional>)
#  define BOOST_NO_CXX17_HDR_OPTIONAL
#endif
#if !__has_include(<string_view>)
#  define BOOST_NO_CXX17_HDR_STRING_VIEW
#endif
#if !__has_include(<variant>)
#  define BOOST_NO_CXX17_HDR_VARIANT
#endif
#endif
#endif

//
// Finish off with checks for macros that are depricated / no longer supported,
// if any of these are set then it's very likely that much of Boost will no
// longer work.  So stop with a #error for now, but give the user a chance
// to continue at their own risk if they really want to:
//
#if defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) && !defined(BOOST_CONFIG_ALLOW_DEPRECATED)
#  error "You are using a compiler which lacks features which are now a minimum requirement in order to use Boost, define BOOST_CONFIG_ALLOW_DEPRECATED if you want to continue at your own risk!!!"
#endif

#endif

/* suffix.hpp
LXefutu3a9xOPEEAJWtvF7tDkjAehVciS6QbKQAXRGlUIc8hcQBzmaPd4C4EkMTGHV5wQeyCrQVbGaL0yxi9SgO8f74RY9SD05ABUo6eHuKUNwAexSqeIIDW9NW5G7y0De5+dQyDN6IDkvlz987UB9EUMflrLu1K13k7WAMIg0Fx1KZLQOAMo1yUJQiG9hSvB3kPDu54TbNMircUUL5zrEfDTgzfi6AvWfM6V+hJUPN2vkdMqLP9k6KgeEYEHEWuGUjPXW5816TmcyLE+ED2rZAKniCB10pv5wrNwIbtuPTFixvILNwUlwQQXdS3Q2xLDnNZtTMz28tiOEEgh8ReYqRkS1/iGiiB7y/yp6BrFI4Fcrga2/cMLxLQPkpNbmVXFUZdb9XeCdEMkJ7g8g3qy5HgKOV9Td0T8JMq08Fj89bKs3HYv9+IPgVyfg5ogFyloXUTl0wjdXcL0IlYEtJX0KJAxBH8LxMrxHJV0Txc/0H+lBGOQto6mQh4H2R5z1i8i0wdcwwdg4StDQukGVfJ/NbPmDTCO7u/HOEPT1hqjRF+UYq8SupnUC4lRi6lV5AOV8j6hIfGV7g3Vbhh9vJ8RfriTkDm1ZbtnTdh4Clm5GLjf/LmZuAbLfobX63St+gjxt7yjfKbxuTemUcOmuVXxu50FRrUwQi8/YPo7EzIa4roNj7jU7ZYDnNQb9pNOGntOplz7TrS94L0hDX0OI10+fczLaskN4PkMhtsPDPvf6GIQMMQ0FlmaYKO0XrCafOM0YXeqon+Voq21lkGco7W7oLelopGknDCYERefI4W7o/Q4E/38ElXOXcu9U4XK0hvJUtLdTIdbUNLSz+DdU83ZTiLfUFjbU8bp0ZrfUfnp0NXpE3D6WtlfVHLAk/vSXC+51LHgZwOQjz94Wrd9VibmlodclzNoTIr5madYVMD5U1jrjxDvmYlflYb6l53MFr7zl9jZm9J6vpZ6lM7IktrPFGb5kOnu1+b/F7baVPzq6RbQzxHuZxjR7I2/rQ97kwKAQ8UlUsQwLBPXcWGlMoGNR9hAAMKiWp0OcL2jyKiwQjCIHDPB/uuaiyLcGaYMxGk0TWLNV+4SlV/5udOFoOseOSmpWetFHFTNt3/Xr12YhSzbhQQF7AVIsY7CJhw8ST46r/QK7cFSpRaoPYluqUooHvywJN/tAilLYDKAEC1Zugi4gCP2FAHbugpesiC8BFHbeDT29GjJmvpG6G868RiK8P/gJGGrxXPLRNWbBI3r+ftbheJkQ19RhQncX1U7QPngRmd4duP3NaOXhL7XkDaljFL2whv4TS+4Ejf4O4P4Uzq4HGV4T2f0ynf4lSe4lCsXlKu4FoSl5e/4NIT42HP41294Z6/41TfX9IT4G17l3pXcaKRcjl08akvcLtGcGcn8LiesjEa8TZXcUBlqrj08TWCn+Ric8UwnOW/rOVg0+RQnuWQruTsoeGdp6wKUPslm2fdhGaLvw1qYK6cDzOBjCH8sgXRLnOqlLIJF/LU5fKo6XOI5ILV5/TPcHIOifWb13Oq9PGbEfRcNitclq7c73VfwOylIfX2kPWIUHUqB3U6zksM7wFk9WVTnYLRrCHS2urUyurcvmrd3muNvSDiviDinevkvWsTwUT81soLgOwAvFdT9cmYDNDLvMluj7LqYXt+/hHV98+zP2g7JGtTFAo4oBj2o1vZCH9+pi4/rF5z/hMIPXSHIkVKyuduHOyy9yThYHf3oHgF4SYReXgleXk18YRVaXndVWw9s1OqeLq1FPwpfnuAL36BX7qHp/lSvGKGz2aH3xKB57e76TjCB73CDxV4fcUADizx04wvpIA3gYFHyhc39IzCkefZF0QXvy3bvqauGSV/PybH81LJzaU1/u7rsZJ3+FhR9xrGd8PWGh0F746pX1RY9PvuuRFhkt1iKK4w454djP0iRYCxux8Gnu8CIanYIRBy/DeDzB00X5PW0pX2eJkmfLIq8r0K3bG686/ssH3Vxn9wayetuHtVv6cuVMRe4KStOyOtOWd1obuNyXMJ6rdNK+z1Y2O1uLRNLPn15O01JKvN7f31J+NV8PPV7rttP+vVKrkNMTl+J8OfYWV6Wvt+ZqxjeyDbflL5vzLS8h9m+cdPtsRZu+spKgpj+d9Lk5PH6Z/LiLMXnd/L1f40QdDpyHxWLuENUbwzlp9FCDgKPPSgE0KmDAjNgBjCxdH2cXzAIKtzBenx22iwwo3z6h1RGNG96AXhlFncmBHkiVFbK4pEqZFF6x9FT1cmbHmDJb2bJJkP2rQxS3441GMdInWKK/lgzGOlXgWpLJph6UeVXhWx783yzoMKo5KoZtazqBP7Y63t2VBr3O7Symc1bDUW9DhNrwG6tujDosnTyxw8eweEk5PJ6xsDEirgvLhwQU0WmW6o2SNDPChToM6k3eKTnPe8t91dxpWwl2fjLYU5vHtm62rvx2fyVlI2HMHRqtgw7pB/W3CrlzmBt8k8Wbbq4MCRMBebb/y3nWaxHYpnLnn4cOrM1TOIrK9vGQrhI8J8dh88eIKHng8wfr07sxS7UtLX27AiwIaHqI3EDwJ+BBB4nWb+F/nzvdwGETyap52OCCTWXP18yF6Q9qnwiTb7YfiYXhJAiefWg4IEQBmauTRJs9AKLnUmztwoZSPBIh/uTJwN8NuNl3YY6NvWKizjRGYqOKPIu5Yhax3ndiDkKTiyRMvSIZ7ZNMYSihfiV0SLIJ68tkMgsvYN/1iUKTg7UaboN0IbbqH5YJNgnMkmkGWkKWmccIJ1J5l5mNOgF7+4dSWZg/KaMZoG56QJmjkVLyu1RSGZtrWRJnlSgVQWnjTRTTlvysRNQX8qUDiUMAVsK4r5+IShaJTJTaNYCRdUIligQTOi4h6VKqEqhjd1c8Mcy0NGeW0bpF51hxkGM/04nhrDNBvrNjPvGYBWOlE1xTNTJV3jtHtF3W0uwjTxBtpks3B2TlXL1ObVbDf1lJ9dVwfWVmzTKgxpeFfNtV15b92j9L1+HEKwsgTLfeg3CTm8sLpu8vf1P3pFWHHEBmSssEb3sw3xNhuCVtfIHnJx7oVa9UEhJ9bO0TATjZiQOEorCIZYlTUPt1a7cbz5Z/7J2HepP8bsZcK4LCgGEJCA1or2Ht8WstBXRU36w6CFDldeBv3OVrGbVlpfBY5bqUcZlC8E4dFvpsJyA46Drcz1AEg0VC9Yh5JJz57ZaMbFIDOxDsZl7Zi1zxz6DfVtlQX3Jq/HfcdZ6bb5zx0y34gT/+5xxzGGmHPL33d9cszMnx/ixzo/Im/JIUW6d/13OWTXQZc15v6bc/g98tkdglJ72UvZ9e+7G30y/7M5b3z2tR3Vuu7VKylQ6M1N7aH7uFVb+vi0Y+dq59CM2kUaUJSEBTumuIUgDzz8JVwQP9RJkXf21ZNKb1f+MsZq7PZwYGf399gS7ALJHiCiCgEiXhAHQhwbINB9A3wIBkZohTCsdOgmvMT9jhwQ5OCHF/B5F3wF9F93DEDI5hthBqzQHSMM4ps+2FwDyh6A7LtC63nQm1i/wbSwcLEDKN83YWAAuz2RCxxZP/hFdl77NB+FlcrRM3dlnpAb3kddBKEV7RhFLFXRbKoqItjW8Fl0qNCVXwBANKZyDNQ74M04Jb/3jW4xby/gf1gCX6duvtlFUYz7mM938m0dHmV0Skk7y4hyOicg2j5OSiFNioYeJ8MguE5ClbfGB2LTkoy6Ryo0xz5JBVKUokelu6a8Y4wUex6mGyHCKHpj+E0ji2EpCpa2vCWucSl+rniZTG+9Utj9FGXwSVmMI16T6TbMzAS3wRmklkkRxnomNChZDWrekxsB08lNbHAza120pndV2EqLejMcZTzHOlIpznQy0x1tesd6FpoeVZIVHrU8x75xKY878DPv/LzkOAeDytZ806CJ3ShCFKpQCDLyFfEbYzOp2NBz0jQi590oxtOZfoHG/0EoqFCQhVSg/FPUkNrppgKJokX7ZWhJXvFVlqK3IXCDovoMjCzI9q1+yPos1xnnd+H7LxLjIkFHlm9FuiRdqcUHk5goGZgd0a2mQqZzWKplQ7pFajLKEamvsGG/DyyanS0MbAN6xae/8gI/uMWUdfWfP5DYOjoAMhnCykfdQOVRTkRh5BsnQPhlYuTPyXPdABa13pL6UGB+PQWAYEiFHsa8p7VcJi36eK42gEMk8B4yCFY0hQ2tJhvLw3YC1gNjFa3rbosad67VIb8tTcwvo4bNsWllOtXFrydxjNdm/nkG7FPHCdNGXw+Tobx1C8Roz4rVpr+XaSdfe03sDOmT3fZtZ5sb/DVg5bKFpMfvy6QYmvXVJvez3k/5a/PeLoY8oU3vzyL1P10lOs/Vz6D5M+/oHofu9TWgsoWz3YYWd8mYnUC0VYz0fGcG8f33MvWVqGIx9P4PQ4hp7ZUztx5Y1BfGQQ+zkv7fznuVH4ZBO1u8M0PXmIZnxlorj3PwL8eY1xotDB1dzJMyF6mlGRHg+5pB1iA/LtLT4eltyBY4IQVwjSe+9LlMbzQDSSUPMSgBBYXZFUtFLnMCEcO+6cbxzAxO8+3uShEA0AIvuTSlMrL4cbnYdyXdnEer/TPiqF8kz2/YAGQkEsNP0RHgJIyd8D3VY/TTyT3CDmkC1noDY8yDQFBoodrOFhIFwhzZQhPW/xRaYt40GaAbIaQmh2djh8jDQFODmzy2CzSwUQaaF7pWJolyXM7dzhgaAIH3MhKF7CIllzdyzxZvFSD4gvpaPJqX1KbkTlCdDE1eIf1QzK7ckfT3OrvjCbS3Rx8PwH2BQfsRujAIPALAGtKRtc6sfOyf1pVAUw6sUIgGFEQfWBYmgY0EbITCBBUQ7UW2wehxW8vV8aARiuNLrliSHV8Y0aex8VczoDBdMSlEMpiVYIFjNNzkEAkkZE644BCjPwz8L2x8VMQD+Vt5F3AI9i3Ru+YJrGWf+t6APHIhcYjYtlcRcfDHFk6aUR1aywBP6A0GDBj66UcMhkSD7XX1iZ+GJQHs9wnvzIHrWvYeim2IAlXvdBY1xFhUbIPlCwd0z/KGBeMRVXXHxDW2/inr35QabjSpetWm9HRzE56Dte/2/NKQEhdBhZw95C/3EsXrdb1mnL6MX5C1sqx2wSaqRsXSvyKfyIlqQ5wakX6HnSy1x87qnAtJw9uHL5V7r2SEHQsu23Clgrhy76iH2NtcbnuEuQqvnNjqb/mEEuudiOBAh+81BYh5yHoR0oN7yynihp+1CFe67b6fcH6jAuh3xqJ3qPDUB9ns+LfZRrEH9c6MvhLo/QPJCwzalel1hVOUEU7vHVLCZoH3Uk4nNYHAv9vpedyBZhnbnydRWQDuU4cAEzmrYbPGDu+AEr7kDPBEbxFbcpUocS5MdPcid9jDaP4UBxHRAJnp2TsvCC3lUBPgZzO3b3b+PtsMeUt9ApI+QzjxQaTKnlMKRs9bWUOeXxW1W/xJz5sD3AnBZs4HmH88mwc0VTI2HDZ02yygBlw2nfbOXZZTWL3XGI0kBXBOgwOmXxukAob9uCHWgYUHrxqkDVYoOkE4/4U/hzyCfTP/t1wY/wlHgFPAMNcDWJuC4PEMgNaAXQyGaYlBQ5ORYxQ4VDQJVHsy3bmHSqhHimA4V9g2qRpD9xDKLiJAe+YyJUsZlJSZZ4DGQYDJXN25KkqPa6/AyVEW+sEC/UkFqNYxb/PTLxrG/8TeR/6PhuefzZw/eqGvgMbiabxH4NyhVXTO4+xEVLMDZL3eYStEuNoJSu8jfjBmQtAehgUhwFW5AKO6D0pFcKv3zU5jrJRspgcTJE52o9lpoZz0U9L93s3ygJ1DjIcEuKEm7v0eVb4pBCtAX89URIcxjI61uwI67gh3FSowP16xyhae4TxtED487j0tQ5BSkDbRBBkefRfi7504BKO3i3HTjZWFCoSBTf0rD9fgZ6tyRzqum9u0P6oYDYiBwJbXp3Ajg/YZu3uAwqlAFRIOF8DJDcoGOv5IVUT4Qb0zbzo6NSBOFYzUjSiTAFaANJNWBP9Aw7qXNgtF4BuwN0rdA7i5iH66EUTemfgbk5ePb9GROYu+lSl3miA/WocLvm2k+fdcP3wkFbVEdPV//73GQdgVNIH+uNzsK8b8dwh7o5ULMBZjocqRYZn1lq6M1/fffmn6ratqoTy9gdautuNUEFeRoVzwkF6JYm8yp5guUPLE0CFDPjFA0QE/eRm/CSkJqcDsms+KwrTKuhEufj1Umo5X1xy5KI7iQHdezj4cE7D5f4AZmtWIAAzAoR5bMBilLlhAFB3eyI4a+PcBwbfKSHNksRxZowwS4XNAiDxUSISKA9vWlIunlIuvaQ9eFovvWkWRfMcdOUKmXFdAVUVEjIs/w4PYwt1yw8Ro/H32fOPAHaTO2JocLiLEYqQILpig2OA8fChzYdZbHsXmE6NUFqd6jqYGXWEmd+YOygadsih9OyZoLkrmYKL3tSjxhGag40cOuSiS4ec3+Fr4likUYecRdWsDrinlbSCG4R/ORSl+b2rAoiWTXClnkJXztoqZdCnpmZZ9uI4GTW6ME1SvMBRBMGwnJyrJnC7UlNLDL0UpHW1UExreE10p7/nUlL6fB7Hi7xAqlWBmyuOqIqUX0Sajiqaqw3WTmEbSDD6qxa2TGYlemrmlxa1o/2KSzRtVjhJU/E2p/hlUUo2lPobEUVzSkfbSbhHTBGVVWrEpQ6vPWrtVKVnTL8BWXRwnSxb/KLQrsRZT/2uNTSNMZ0/WdevSz3bV1OBNe9tIZmc9VqpEY54vqbG7aI3BVVjXSpc/0FzObbI9UfG3Ag5R0d+vkFetJKqo7Pr8KWXVdZnVdPTW7gSm8Jat4Vik4Xcqf/er3MSkvS2cApur2VClcW6wCqFL2Yh8CfuwSp+rVgi1EjlmCeyNlrJStx5GSvayoR3xszpjLwcnqiSds7S6quLfqSS/tKrMt7ToKi8Zqa2ArrkpszCbTwlZpzOztbTahGj/VUHnWaAxwI3OzWwh05jtWKBAnKcSDTrkObpr0KVH1e1SnqMZW/pIIU7d6dH7aUaTKNNybs6NbVZMqCwQbFC06lQi6USsq0wx7kyMqqD0zV9Dq9IMjFTSrMnhKREVKFjvKdHdpNF67UgUzufNr1of72KyqFyvrvq3X8mL1HWvrdJA7MZc6Q0c7dbYoTn2LfHpqWrtJU3sbO3sJumbIMcu5Mas70K9pGbuKWm8pM5OpIr9KudtK+WrlOpa6U19JnmKJ4Pe7NuynPZYhm/pnaGeu6V6aOBhLe/arKhOv6b6iuLlymq+WSbyWiD3KuTq+S9IXMxkX0rVF/z8lC7pJ+f6Re/fxtDpZNBNXMlFathlnGHlDvXApGdL7/md2/pd3P6y2+p8HFvgD3IL39r9As52bVENn0rtRfRNrWQk31VeyasG8Azpd1WS7npZTs2+rqlMcD4xMAbjt7cVr0HswH7SA2JOQXYNYGkGVb+dPOEYQJcYaIEZ8pgs6Lm0fKt3/OcEwIGHfMhqAIY0aqaD/txSQrXLfVZ2okIl4fE9UO0uUMoWkN/W1quxaWHuNn7IJMmmGJGLGMyYWLkhy3sDd4wGNIrPaCDLlDRpJTi/cezaEJqFgRtH3Kml9ku718l5WaxmQez7UvJ4H9yZaSzoc3L5GbykcKzowQln26uItlnH4svI+amHs2x5XkxJnxloqawEpcwRxWlInwyCiizKzMkwRVsyxRjJURxElezSGarpl0wZuyzLYiacTXuZDJZPuzkOtQz5/m+dKhomYbzCAZ8/C0o1OVuYyv7vWNSRCEoyEw6RmSILF6X23a+0aYkRV6Gu0izYkOr4Lz51Egh/usXPW53AN+BWJGSAcgbOl30K691i1ldx27rb6Zd/Fc1HAypYsFq4/cJvUSPNOsQU3oU7+eOvqmZ8lzLCVmwB26/yKFO0zxT3rTRL31ruhU1PhrLIRDEdgaD8DqbsTwF/zjXH3OFUP/pQmUfviX0w4uS+uMI8Mgd3BACU4A+TU6TedOVS3jy1v2dIhqHkuewZolceZccb6eoQPBAukoHI+2znz9bx7nuu0d6mPELEeZh9Ue9VYOCLEIlLF0nvqbv5ZSL6zwWGIJIg2kgglmRKhxYCaE+ZHcqLsUEKS5Sl1hdBGNr1HEXU+1YRRS7z9aYhBn03mScRttO7XCHL8ZohTpUqpicU+K614sFQhjM+o1ixcWDZLHWXXqfiXKZYgOZJ/U/8uplSg0sRl6yo1TjJ1D8c+FrlYJzphph/PNiI0IM8v9NIKL74JpCPQelCz9csTUkEpr7Sqw0pQa89MU3Z1c8tt5iehhynmF1xSpwlfcwtVH5p7C5zyarwATtUkxenHX7J2O4mamqutXW/5Q0hEXx1rVqlFZVnI0mtkLkJ2nVUWMajVXY6CJUk7DQS6AFCpkbZXVbbcJv5Q5vmaMX2u7APrdb8j41hCOfk/QhwmJIyFWFdPDv1l93l58323KZoOBfdg80d1+AaxkxvPBIlu3BAI5a3V5lTotaglaaVNz97XZsWMMJCeauxCb+NHfjBdUsgWBbvIdvyDHFzfOML+fCsMvXZKrwyj3dV/BD1eTT801E+TaZ4qMNVftlpBVHvFbLh9c/t5YV0l2sjatgr7STxj0T0dIcir+4pIgsoEv+B012QwYZuiuUAjyxxCBn1GH3ScNKFc9KFNcJe5MIeMJWApjYiJmQXfyg+s9QIovuQ3RKjNF5EOgPjiYOCPUITYk4+zJe+TYmhomEU+c132Qr/F9tADxIncRMIfUQN+9BE1DhMIOytBw4xB2bQmv2MKusEMapK1FA+ePAqWCggM0I658oYIfOIv4LovV2b+fpjRdWXkYntcneKexz+TYFkpuDbLW7ILQ4RiWQxgS6Ur63fcKqOL6J436CZ7b1NC1G6s9/CGM6W1UNkprd9gG55HCZGBm+ChtDTgXYbTh7qdty7uMnIfSaViX0HVGNHqKz1VLSs8C5cfTxQEQ+Xj7mtdbiB8nWKNhZ/T4rz4dwI8H5QN5dU59sOYLSPNE4mlA7yShd0OojA6OgS4cRDNuhkdI1YCYiUekkX9aMAL8brk74jPS8xYP64GTGM/5eDGXA3iLZS0mjEtt40wjGML5NdGP977mr3EWcaPP3b83qXg/6wkdE7aJC84lgIBCZyTh2boGLtp8gMJ5MTleTE6VU=
*/