/*
 *
 * Copyright (c) 2003
 * John Maddock
 *
 * Use, modification and distribution are subject to the 
 * Boost Software License, Version 1.0. (See accompanying file 
 * LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 */
 
 /*
  *   LOCATION:    see http://www.boost.org for most recent version.
  *   FILE         regex_traits.hpp
  *   VERSION      see <boost/version.hpp>
  *   DESCRIPTION: Declares regular expression traits classes.
  */

#ifndef BOOST_REGEX_TRAITS_HPP_INCLUDED
#define BOOST_REGEX_TRAITS_HPP_INCLUDED

#ifndef BOOST_REGEX_CONFIG_HPP
#include <boost/regex/config.hpp>
#endif
#ifndef BOOST_REGEX_WORKAROUND_HPP
#include <boost/regex/v4/regex_workaround.hpp>
#endif
#ifndef BOOST_REGEX_SYNTAX_TYPE_HPP
#include <boost/regex/v4/syntax_type.hpp>
#endif
#ifndef BOOST_REGEX_ERROR_TYPE_HPP
#include <boost/regex/v4/error_type.hpp>
#endif
#ifndef BOOST_REGEX_TRAITS_DEFAULTS_HPP_INCLUDED
#include <boost/regex/v4/regex_traits_defaults.hpp>
#endif
#ifndef BOOST_NO_STD_LOCALE
#  ifndef BOOST_CPP_REGEX_TRAITS_HPP_INCLUDED
#     include <boost/regex/v4/cpp_regex_traits.hpp>
#  endif
#endif
#if !BOOST_WORKAROUND(BOOST_BORLANDC, < 0x560)
#  ifndef BOOST_C_REGEX_TRAITS_HPP_INCLUDED
#     include <boost/regex/v4/c_regex_traits.hpp>
#  endif
#endif
#if defined(_WIN32) && !defined(BOOST_REGEX_NO_W32)
#  ifndef BOOST_W32_REGEX_TRAITS_HPP_INCLUDED
#     include <boost/regex/v4/w32_regex_traits.hpp>
#  endif
#endif
#ifndef BOOST_REGEX_FWD_HPP_INCLUDED
#include <boost/regex_fwd.hpp>
#endif

#include "boost/mpl/has_xxx.hpp"
#include <boost/static_assert.hpp>

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable: 4103)
#endif
#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif
#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

namespace boost{

template <class charT, class implementationT >
struct regex_traits : public implementationT
{
   regex_traits() : implementationT() {}
};

//
// class regex_traits_wrapper.
// this is what our implementation will actually store;
// it provides default implementations of the "optional"
// interfaces that we support, in addition to the
// required "standard" ones:
//
namespace BOOST_REGEX_DETAIL_NS{
#if !BOOST_WORKAROUND(__HP_aCC, < 60000)
BOOST_MPL_HAS_XXX_TRAIT_DEF(boost_extensions_tag)
#else
template<class T>
struct has_boost_extensions_tag
{
   BOOST_STATIC_CONSTANT(bool, value = false);
};
#endif

template <class BaseT>
struct default_wrapper : public BaseT
{
   typedef typename BaseT::char_type char_type;
   std::string error_string(::boost::regex_constants::error_type e)const
   {
      return ::boost::BOOST_REGEX_DETAIL_NS::get_default_error_string(e);
   }
   ::boost::regex_constants::syntax_type syntax_type(char_type c)const
   {
      return ((c & 0x7f) == c) ? get_default_syntax_type(static_cast<char>(c)) : ::boost::regex_constants::syntax_char;
   }
   ::boost::regex_constants::escape_syntax_type escape_syntax_type(char_type c)const
   {
      return ((c & 0x7f) == c) ? get_default_escape_syntax_type(static_cast<char>(c)) : ::boost::regex_constants::escape_type_identity;
   }
   boost::intmax_t toi(const char_type*& p1, const char_type* p2, int radix)const
   {
      return ::boost::BOOST_REGEX_DETAIL_NS::global_toi(p1, p2, radix, *this);
   }
   char_type translate(char_type c, bool icase)const
   {
      return (icase ? this->translate_nocase(c) : this->translate(c));
   }
   char_type translate(char_type c)const
   {
      return BaseT::translate(c);
   }
   char_type tolower(char_type c)const
   {
      return ::boost::BOOST_REGEX_DETAIL_NS::global_lower(c);
   }
   char_type toupper(char_type c)const
   {
      return ::boost::BOOST_REGEX_DETAIL_NS::global_upper(c);
   }
};

template <class BaseT, bool has_extensions>
struct compute_wrapper_base
{
   typedef BaseT type;
};
#if !BOOST_WORKAROUND(__HP_aCC, < 60000)
template <class BaseT>
struct compute_wrapper_base<BaseT, false>
{
   typedef default_wrapper<BaseT> type;
};
#else
template <>
struct compute_wrapper_base<c_regex_traits<char>, false>
{
   typedef default_wrapper<c_regex_traits<char> > type;
};
#ifndef BOOST_NO_WREGEX
template <>
struct compute_wrapper_base<c_regex_traits<wchar_t>, false>
{
   typedef default_wrapper<c_regex_traits<wchar_t> > type;
};
#endif
#endif

} // namespace BOOST_REGEX_DETAIL_NS

template <class BaseT>
struct regex_traits_wrapper 
   : public ::boost::BOOST_REGEX_DETAIL_NS::compute_wrapper_base<
               BaseT, 
               ::boost::BOOST_REGEX_DETAIL_NS::has_boost_extensions_tag<BaseT>::value
            >::type
{
   regex_traits_wrapper(){}
private:
   regex_traits_wrapper(const regex_traits_wrapper&);
   regex_traits_wrapper& operator=(const regex_traits_wrapper&);
};

} // namespace boost

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable: 4103)
#endif
#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif
#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif // include


/* regex_traits.hpp
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
*/