#ifndef BOOST_METAPARSE_V1_CPP11_STRING_HPP
#define BOOST_METAPARSE_V1_CPP11_STRING_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp11/fwd/string.hpp>
#include <boost/metaparse/v1/string_tag.hpp>
#include <boost/metaparse/v1/impl/string_iterator.hpp>
#include <boost/metaparse/v1/cpp11/impl/empty_string.hpp>
#include <boost/metaparse/v1/cpp11/impl/size.hpp>
#include <boost/metaparse/v1/cpp11/impl/pop_front.hpp>
#include <boost/metaparse/v1/cpp11/impl/push_front_c.hpp>
#include <boost/metaparse/v1/cpp11/impl/push_back_c.hpp>
#include <boost/metaparse/v1/cpp11/impl/pop_back.hpp>
#include <boost/metaparse/v1/cpp11/impl/string_at.hpp>

#include <type_traits>

/*
 * The string type
 */

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <char... Cs>
      struct string
      {
        typedef string type;
        typedef string_tag tag;
      };
    }
  }
}

/*
 * Boost.MPL overloads
 */

namespace boost
{
  namespace mpl
  {
    // push_back
    template <class S>
    struct push_back_impl;

    template <>
    struct push_back_impl<boost::metaparse::v1::string_tag>
    {
      typedef push_back_impl type;

      template <class S, class C>
      struct apply :
        boost::metaparse::v1::impl::push_back_c<
          typename S::type,
          C::type::value
        >
      {};
    };

    // pop_back
    template <class S>
    struct pop_back_impl;

    template <>
    struct pop_back_impl<boost::metaparse::v1::string_tag>
    {
      typedef pop_back_impl type;

      template <class S>
      struct apply : boost::metaparse::v1::impl::pop_back<S> {};
    };

    // push_front
    template <class S>
    struct push_front_impl;

    template <>
    struct push_front_impl<boost::metaparse::v1::string_tag>
    {
      typedef push_front_impl type;

      template <class S, class C>
      struct apply :
        boost::metaparse::v1::impl::push_front_c<
          typename S::type,
          C::type::value
        >
      {};
    };

    // pop_front
    template <class S>
    struct pop_front_impl;

    template <>
    struct pop_front_impl<boost::metaparse::v1::string_tag>
    {
      typedef pop_front_impl type;

      template <class S>
      struct apply : boost::metaparse::v1::impl::pop_front<S> {};
    };

    // clear
    template <class S>
    struct clear_impl;

    template <>
    struct clear_impl<boost::metaparse::v1::string_tag>
    {
      typedef clear_impl type;

      template <class S>
      struct apply : boost::metaparse::v1::string<> {};
    };

    // begin
    template <class S>
    struct begin_impl;

    template <>
    struct begin_impl<boost::metaparse::v1::string_tag>
    {
      typedef begin_impl type;

      template <class S>
      struct apply :
        boost::metaparse::v1::impl::string_iterator<typename S::type, 0>
      {};
    };

    // end
    template <class S>
    struct end_impl;

    template <>
    struct end_impl<boost::metaparse::v1::string_tag>
    {
      typedef end_impl type;

      template <class S>
      struct apply :
        boost::metaparse::v1::impl::string_iterator<
          typename S::type,
          boost::metaparse::v1::impl::size<typename S::type>::type::value
        >
      {};
    };

    // equal_to
    template <class A, class B>
    struct equal_to_impl;

    template <>
    struct equal_to_impl<
      boost::metaparse::v1::string_tag,
      boost::metaparse::v1::string_tag
    >
    {
      typedef equal_to_impl type;

      template <class A, class B>
      struct apply : std::is_same<typename A::type, typename B::type> {};
    };

    template <class T>
    struct equal_to_impl<boost::metaparse::v1::string_tag, T>
    {
      typedef equal_to_impl type;
      
      template <class, class>
      struct apply : false_ {};
    };
    
    template <class T>
    struct equal_to_impl<T, boost::metaparse::v1::string_tag> :
      equal_to_impl<boost::metaparse::v1::string_tag, T>
    {};

    // c_str
    template <class S>
    struct c_str;

    template <char... Cs>
    struct c_str<boost::metaparse::v1::string<Cs...>>
    {
      typedef c_str type;
      static constexpr char value[sizeof...(Cs) + 1] = {Cs..., 0};
    };

    template <>
    struct c_str<boost::metaparse::v1::string<>> :
      boost::metaparse::v1::impl::empty_string<>
    {};

    template <char... Cs>
    constexpr char c_str<boost::metaparse::v1::string<Cs...>>::value[];
  }
}

#if __clang__
#  if __has_extension(cxx_string_literal_templates)
#    define BOOST_METAPARSE_V1_STRING(...) ::boost::metaparse::string<__VA_ARGS__>
#  else
#    include <boost/metaparse/v1/cpp11/impl/string.hpp>
#  endif
#else
#  include <boost/metaparse/v1/cpp11/impl/string.hpp>
#endif

#endif


/* string.hpp
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
*/