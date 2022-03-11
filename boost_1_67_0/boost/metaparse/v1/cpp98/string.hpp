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