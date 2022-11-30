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

#include <boost/regex/config.hpp>
#include <boost/regex/v5/regex_workaround.hpp>
#include <boost/regex/v5/syntax_type.hpp>
#include <boost/regex/v5/error_type.hpp>
#include <boost/regex/v5/regex_traits_defaults.hpp>
#include <boost/regex/v5/cpp_regex_traits.hpp>
#include <boost/regex/v5/c_regex_traits.hpp>
#if defined(_WIN32) && !defined(BOOST_REGEX_NO_W32)
#     include <boost/regex/v5/w32_regex_traits.hpp>
#endif
#include <boost/regex_fwd.hpp>

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

   template <class T>
   struct has_boost_extensions_tag
   {
      template <class U>
      static double checker(U*, typename U::boost_extensions_tag* = nullptr);
      static char   checker(...);
      static T* get();

      static const bool value = sizeof(checker(get())) > 1;
   };
   

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
      return (char_type(c & 0x7f) == c) ? get_default_syntax_type(static_cast<char>(c)) : ::boost::regex_constants::syntax_char;
   }
   ::boost::regex_constants::escape_syntax_type escape_syntax_type(char_type c)const
   {
      return (char_type(c & 0x7f) == c) ? get_default_escape_syntax_type(static_cast<char>(c)) : ::boost::regex_constants::escape_type_identity;
   }
   std::intmax_t toi(const char_type*& p1, const char_type* p2, int radix)const
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
template <class BaseT>
struct compute_wrapper_base<BaseT, false>
{
   typedef default_wrapper<BaseT> type;
};

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

#endif // include


/* regex_traits.hpp
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
*/