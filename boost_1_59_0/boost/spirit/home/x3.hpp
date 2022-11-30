/*=============================================================================
    Copyright (c) 2001-2013 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_SPIRIT_X3_MARCH_04_2007_0852PM)
#define BOOST_SPIRIT_X3_MARCH_04_2007_0852PM

#if defined(_MSC_VER)
#pragma once
#endif

#if !defined BOOST_SPIRIT_X3_HIDE_CXX17_WARNING && !( true \
  && defined __cpp_if_constexpr && __cpp_if_constexpr >= 201606 \
  && defined __cpp_inline_variables && __cpp_inline_variables >= 201606 \
  && defined __cpp_fold_expressions && __cpp_fold_expressions >= 201603 \
  && defined __cpp_variadic_using && __cpp_variadic_using >= 201611 \
  && (defined __cpp_template_auto && __cpp_template_auto >= 201606 \
      || defined __cpp_nontype_template_parameter_auto && __cpp_nontype_template_parameter_auto >= 201606) \
  && defined __cpp_nontype_template_args && __cpp_nontype_template_args >= 201411 \
)
# define BOOST_SPIRIT_X3_STRINGIZE_IMPL(x) #x
# define BOOST_SPIRIT_X3_STRINGIZE(x) BOOST_SPIRIT_X3_STRINGIZE_IMPL(x)
# if defined __GNUC__ || defined __clang__
#  warning "Spirit X3 will soon use C++17 features which your compiler does not support"
#  if (defined __clang__ && __clang_major__ >= 4 || __GNUC__ >= 7) &&  __cplusplus < 201703L
#   warning "Use -std=c++17 or -std=gnu++17 compiler flag to enable C++17 mode"
#  endif
#  warning "Minimal supported compiler versions: Clang 4 / GCC 7 / MSC 1915 (VS 2017 v15.8)"
#  if defined __clang__
#   pragma message "This compiler seems to be Clang " BOOST_SPIRIT_X3_STRINGIZE(__clang_major__) " (__cplusplus=" BOOST_SPIRIT_X3_STRINGIZE(__cplusplus) ")"
#  else
#   pragma message "This compiler seems to be GCC " BOOST_SPIRIT_X3_STRINGIZE(__GNUC__) " (__cplusplus=" BOOST_SPIRIT_X3_STRINGIZE(__cplusplus) ")"
#  endif
#  warning "Define BOOST_SPIRIT_X3_HIDE_CXX17_WARNING to hide the warning"
# elif defined _MSC_VER
#  pragma message (__FILE__ "(" BOOST_SPIRIT_X3_STRINGIZE(__LINE__) "): warning: Spirit X3 will soon use C++17 features which your compiler does not support" )
#  ifdef _MSVC_LANG
#   if _MSC_VER >= 1915 && _MSVC_LANG < 201703L
#    pragma message (__FILE__ "(" BOOST_SPIRIT_X3_STRINGIZE(__LINE__) "): warning: Use /std:c++17 compiler flag to enable C++17 mode" )
#   endif
#   define BOOST_SPIRIT_X3_TMP "_MSVC_LANG=" BOOST_SPIRIT_X3_STRINGIZE(_MSVC_LANG)
#  elif defined _HAS_CXX17
#   define BOOST_SPIRIT_X3_TMP "_HAS_CXX17 defined"
#  else
#   define BOOST_SPIRIT_X3_TMP "__cplusplus=" BOOST_SPIRIT_X3_STRINGIZE(__cplusplus)
#  endif
#  pragma message (__FILE__ "(" BOOST_SPIRIT_X3_STRINGIZE(__LINE__) "): warning: Minimal supported compiler versions: Clang 4 / GCC 7 / MSC 1915 (VS 2017 v15.8)" )
#  pragma message (__FILE__ "(" BOOST_SPIRIT_X3_STRINGIZE(__LINE__) "): warning: This compiler seems to be MSC " BOOST_SPIRIT_X3_STRINGIZE(_MSC_VER) " (" BOOST_SPIRIT_X3_TMP ")" )
#  undef BOOST_SPIRIT_X3_TMP
#  pragma message (__FILE__ "(" BOOST_SPIRIT_X3_STRINGIZE(__LINE__) "): warning: Define BOOST_SPIRIT_X3_HIDE_CXX17_WARNING to hide the warning" )
# else
#  pragma message "warning: Spirit X3 will soon use C++17 features which your compiler does not support"
#  pragma message "warning: Minimal supported compiler versions: Clang 4 / GCC 7 / MSC 1915 (VS 2017 v15.8)"
#  pragma message "warning: Define BOOST_SPIRIT_X3_HIDE_CXX17_WARNING to hide the warning"
# endif
# undef BOOST_SPIRIT_X3_STRINGIZE
# undef BOOST_SPIRIT_X3_STRINGIZE_IMPL
#endif

#include <boost/spirit/home/x3/auxiliary.hpp>
#include <boost/spirit/home/x3/char.hpp>
#include <boost/spirit/home/x3/directive.hpp>
#include <boost/spirit/home/x3/nonterminal.hpp>
#include <boost/spirit/home/x3/numeric.hpp>
#include <boost/spirit/home/x3/operator.hpp>
#include <boost/spirit/home/x3/core.hpp>
#include <boost/spirit/home/x3/string.hpp>

#endif

/* x3.hpp
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
*/