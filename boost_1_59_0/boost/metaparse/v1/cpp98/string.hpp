#ifndef BOOST_METAPARSE_V1_CPP98_STRING_HPP
#define BOOST_METAPARSE_V1_CPP98_STRING_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp98/fwd/string.hpp>
#include <boost/metaparse/v1/string_tag.hpp>
#include <boost/metaparse/v1/impl/string_iterator.hpp>
#include <boost/metaparse/v1/cpp98/impl/empty_string.hpp>
#include <boost/metaparse/v1/cpp98/impl/size.hpp>
#include <boost/metaparse/v1/cpp98/impl/pop_front.hpp>
#include <boost/metaparse/v1/cpp98/impl/push_front_c.hpp>
#include <boost/metaparse/v1/cpp98/impl/push_back_c.hpp>
#include <boost/metaparse/v1/cpp98/impl/pop_back.hpp>

#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/tuple/eat.hpp>

#include <boost/type_traits/is_same.hpp>

/*
 * The string type
 */

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <BOOST_PP_ENUM_PARAMS(BOOST_METAPARSE_LIMIT_STRING_SIZE, int C)>
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
      struct apply : boost::is_same<typename A::type, typename B::type> {};
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

    template <BOOST_PP_ENUM_PARAMS(BOOST_METAPARSE_LIMIT_STRING_SIZE, int C)>
    struct c_str<
      boost::metaparse::v1::string<
        BOOST_PP_ENUM_PARAMS(BOOST_METAPARSE_LIMIT_STRING_SIZE, C)
      >
    >
    {
      typedef c_str type;
      static const char value[BOOST_METAPARSE_LIMIT_STRING_SIZE + 1];
    };

    template <BOOST_PP_ENUM_PARAMS(BOOST_METAPARSE_LIMIT_STRING_SIZE, int C)>
    const char
      c_str<
        boost::metaparse::v1::string<
          BOOST_PP_ENUM_PARAMS(BOOST_METAPARSE_LIMIT_STRING_SIZE, C)
        >
      >::value[BOOST_METAPARSE_LIMIT_STRING_SIZE + 1]
        = {BOOST_PP_ENUM_PARAMS(BOOST_METAPARSE_LIMIT_STRING_SIZE, C), 0};

    template <>
    struct c_str<boost::metaparse::v1::string<> > :
      boost::metaparse::v1::impl::empty_string<>
    {
      typedef c_str type;
    };

    #ifdef BOOST_METAPARSE_STRING_CASE
    #  error BOOST_METAPARSE_STRING_CASE is already defined
    #endif
    #define BOOST_METAPARSE_STRING_CASE(z, n, unused) \
      template <BOOST_PP_ENUM_PARAMS(n, int C)> \
      struct \
        c_str< \
          boost::metaparse::v1::string< \
            BOOST_PP_ENUM_PARAMS(n, C) BOOST_PP_COMMA_IF(n) \
            BOOST_PP_ENUM( \
              BOOST_PP_SUB(BOOST_METAPARSE_LIMIT_STRING_SIZE, n), \
              BOOST_NO_CHAR BOOST_PP_TUPLE_EAT(3), \
              ~ \
            ) \
          > \
        > \
      { \
        typedef c_str type; \
        static const char value[n + 1]; \
      }; \
      \
      template <BOOST_PP_ENUM_PARAMS(n, int C)> \
      const char c_str< \
        boost::metaparse::v1::string< \
          BOOST_PP_ENUM_PARAMS(n, C) BOOST_PP_COMMA_IF(n) \
          BOOST_PP_ENUM( \
            BOOST_PP_SUB(BOOST_METAPARSE_LIMIT_STRING_SIZE, n), \
            BOOST_NO_CHAR BOOST_PP_TUPLE_EAT(3), \
            ~ \
          ) \
        > \
      >::value[n + 1] = {BOOST_PP_ENUM_PARAMS(n, C) BOOST_PP_COMMA_IF(n) 0};

    BOOST_PP_REPEAT_FROM_TO(
      1,
      BOOST_METAPARSE_LIMIT_STRING_SIZE,
      BOOST_METAPARSE_STRING_CASE,
      ~
    )

    #undef BOOST_METAPARSE_STRING_CASE
  }
}

#define BOOST_METAPARSE_V1_CONFIG_NO_BOOST_METAPARSE_STRING 1

#endif


/* string.hpp
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
*/