/*
@Copyright Barrett Adair 2016-2017

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_DETAIL_CONFIG_HPP
#define BOOST_CLBL_TRTS_DETAIL_CONFIG_HPP

#include <type_traits>
#include <tuple>
#include <utility>
#include <cstdint>

#define BOOST_CLBL_TRTS_EMPTY_
#define BOOST_CLBL_TRTS_EMPTY BOOST_CLBL_TRTS_EMPTY_

#ifdef __cpp_transactional_memory
# define BOOST_CLBL_TRTS_ENABLE_TRANSACTION_SAFE
#endif

#ifdef __cpp_inline_variables
# define BOOST_CLBL_TRAITS_INLINE_VAR inline
#else
# define BOOST_CLBL_TRAITS_INLINE_VAR
#endif

#ifdef __cpp_noexcept_function_type
# define BOOST_CLBL_TRTS_ENABLE_NOEXCEPT_TYPES
#endif

#ifdef BOOST_CLBL_TRTS_ENABLE_TRANSACTION_SAFE
#  define BOOST_CLBL_TRTS_TRANSACTION_SAFE_SPECIFIER transaction_safe
#else
#  define BOOST_CLBL_TRTS_TRANSACTION_SAFE_SPECIFIER
#endif

#ifndef __clang__
#  if defined(__GNUC__)
#    define BOOST_CLBL_TRTS_GCC
#    if __GNUC__ >= 6
#        define BOOST_CLBL_TRTS_GCC_AT_LEAST_6_0_0
#    endif
#    if __GNUC__ < 5
#        define BOOST_CLBL_TRTS_GCC_OLDER_THAN_5_0_0
#    endif
#    if __GNUC__ >= 5
#      define BOOST_CLBL_TRTS_GCC_AT_LEAST_4_9_2
#    elif __GNUC__ == 4 && __GNUC_MINOR__ == 9 && __GNUC_PATCHLEVEL__ >= 2
#      define BOOST_CLBL_TRTS_GCC_AT_LEAST_4_9_2
#    else
#      define BOOST_CLBL_TRTS_GCC_OLDER_THAN_4_9_2
#    endif //#if __GNUC__ >= 5
#  endif //#if defined __GNUC__
#endif // #ifndef __clang__

#ifdef _MSC_VER
#  ifdef __clang__
#    define BOOST_CLBL_TRTS_CLANG_C2
#  else
#    define BOOST_CLBL_TRTS_MSVC
#  endif // #ifdef __clang__
#endif // #ifdef _MSC_VER

#define BOOST_CLBL_TRTS_IX_SEQ(...) ::std::index_sequence< __VA_ARGS__ >
#define BOOST_CLBL_TRTS_MAKE_IX_SEQ(...) ::std::make_index_sequence< __VA_ARGS__ >
#define BOOST_CLBL_TRTS_DISJUNCTION(...) ::std::disjunction< __VA_ARGS__ >

#ifndef __cpp_variable_templates
#  define BOOST_CLBL_TRTS_DISABLE_VARIABLE_TEMPLATES
#endif

#ifndef __cpp_lib_logical_traits
#  include <boost/callable_traits/detail/polyfills/disjunction.hpp>
#endif //__cpp_lib_logical_traits

#ifndef __cpp_lib_integer_sequence
#  include <boost/callable_traits/detail/polyfills/make_index_sequence.hpp>
#endif // __cpp_lib_integer_sequence

#if defined(BOOST_CLBL_TRTS_MSVC) && !defined(BOOST_DISABLE_WIN32)
#  define BOOST_CLBL_TRTS_DEFAULT_VARARGS_CC __cdecl
#  define BOOST_CLBL_TRTS_PMF_VARGARGS_CDECL_DEFAULT
#else
#  define BOOST_CLBL_TRTS_DEFAULT_VARARGS_CC
#endif // #if defined(BOOST_CLBL_TRTS_MSVC) && !defined(BOOST_DISABLE_WIN32))

#if (defined(BOOST_CLBL_TRTS_GCC) && !defined(BOOST_CLBL_TRTS_GCC_AT_LEAST_4_9_2)) || defined(__INTEL_COMPILER)
#  define BOOST_CLBL_TRTS_DISABLE_REFERENCE_QUALIFIERS
#  define BOOST_CLBL_TRTS_DISABLE_ABOMINABLE_FUNCTIONS
#endif // #if defined BOOST_CLBL_TRTS_GCC && !defined(BOOST_CLBL_TRTS_GCC_AT_LEAST_4_9_2)

#ifdef BOOST_CLBL_TRTS_DISABLE_ABOMINABLE_FUNCTIONS
#  define BOOST_CLBL_TRTS_ABOMINABLE_CONST BOOST_CLBL_TRTS_EMPTY
#  define BOOST_CLBL_TRTS_ABOMINABLE_VOLATILE BOOST_CLBL_TRTS_EMPTY
#else
#  define BOOST_CLBL_TRTS_ABOMINABLE_CONST const
#  define BOOST_CLBL_TRTS_ABOMINABLE_VOLATILE volatile
#endif // #ifdef BOOST_CLBL_TRTS_DISABLE_ABOMINABLE_FUNCTIONS

#ifdef BOOST_CLBL_TRTS_ENABLE_NOEXCEPT_TYPES
#  define BOOST_CLBL_TRTS_NOEXCEPT_SPECIFIER noexcept
#else
#  define BOOST_CLBL_TRTS_NOEXCEPT_SPECIFIER BOOST_CLBL_TRTS_EMPTY
#endif // #ifdef BOOST_CLBL_TRTS_ENABLE_NOEXCEPT_TYPES

#endif // #ifndef BOOST_CLBL_TRTS_DETAIL_CONFIG_HPP

/* config.hpp
nnvOuae0wJZw1pBg0ptSYLhdCib1hStQ7hpfcDSqrm6Gv6mSV/5BJyyrlJ6DVfUr5ejVCG+hw/QGpiaPirSTj2lJ1O3k0Sws4Et1Z+yAwg3e4IgGXIzb7kFKOxJT3EqO3E3oHlGcV364pFMVomOoHur5vCvcBdCjCeCQuSwfjayOKAiiZqxYokMXt9MXLE3B5Lr5QGC+32tD3wZvYJzdGxyejO0Wor565HFVO1Y+q+C4+nEyWh0GB4SUu4CKQmknFPovHlMG0PJ0Dt0NtjeqNtfETuShkhl2ZuyQybsKfvhkcpNV/T3k37wBojDFOKhjU5jCCC+s4ijnBGEhbtsXZz4RSQMgpwsgkyrxqzy5zievRLvXSfGW0Mo+6J/DdLRsrdroWHGjsyxsLXEw6ZWtwRFWD5porxLHB6IsUFkYS3KQSW7Q9g4eCQY89loP2g9ZGtUumRM6IVV+mzJaeuADb5o4ER2vKYGl4NBMJeVa9OsdqqmI9ZeVpvOKZI1WJxzTpx4W3ZdIrgOkgD2bGUE+3mY1c4ymvP64HxqffcEMy7S0thXSs4/FuC2z/OfPPoa29CWDw2cSZRqJKtXeurEElu5GNmFslE/q68d+ZKJexEQd52r43TbLJ7SbrVV29ScKr8O9DCASGpJswJ1hueBhDZZHAwxLjE/It4hBM/g2GeOn0+1szndi+62CfuERaa0nRUD/41sB+nJAS0ba
*/