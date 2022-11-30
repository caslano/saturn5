#ifndef BOOST_METAPARSE_V1_SOURCE_POSITION_HPP
#define BOOST_METAPARSE_V1_SOURCE_POSITION_HPP

//    Copyright Abel Sinkovics (abel@sinkovics.hu) 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/fwd/source_position.hpp>
#include <boost/metaparse/v1/source_position_tag.hpp>


#include <boost/mpl/bool.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/less.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class Line, class Col, class PrevChar>
      struct source_position
      {
        typedef source_position_tag tag;
        typedef source_position type;
        
        typedef Line line;
        typedef Col col;
        typedef PrevChar prev_char;
      };
    }
  }
}

namespace boost
{
  namespace mpl
  {
    template <class TagA, class TagB>
    struct equal_to_impl;

    template <>
    struct equal_to_impl<
      boost::metaparse::v1::source_position_tag,
      boost::metaparse::v1::source_position_tag
    >
    {
      typedef equal_to_impl type;

      template <class A, class B>
      struct apply :
        bool_<
          A::type::line::value == B::type::line::value
          && A::type::col::value == B::type::col::value
          && A::type::prev_char::value == B::type::prev_char::value
        >
      {};
    };

    template <class TagA, class TagB>
    struct not_equal_to_impl;

    template <>
    struct not_equal_to_impl<
      boost::metaparse::v1::source_position_tag,
      boost::metaparse::v1::source_position_tag
    >
    {
      typedef not_equal_to_impl type;

      template <class A, class B>
      struct apply : bool_<!equal_to<A, B>::type::value> {};
    };

    template <class TagA, class TagB>
    struct less_impl;

    template <>
    struct less_impl<
      boost::metaparse::v1::source_position_tag,
      boost::metaparse::v1::source_position_tag
    >
    {
      typedef less_impl type;

      template <class A, class B>
      struct apply :
        bool_<(
          (A::type::line::value) < (B::type::line::value) || (
            (A::type::line::value) == (B::type::line::value) && (
              (A::type::col::value) < (B::type::col::value) || (
                (A::type::col::value) == (B::type::col::value) &&
                (A::type::prev_char::value) < (B::type::prev_char::value)
              )
            )
          )
        )>
      {};
    };

    template <class TagA, class TagB>
    struct greater_impl;

    template <>
    struct greater_impl<
      boost::metaparse::v1::source_position_tag,
      boost::metaparse::v1::source_position_tag
    >
    {
      typedef greater_impl type;

      template <class A, class B>
      struct apply :
        bool_<!(less<A, B>::type::value || equal_to<A, B>::type::value)>
      {};
    };

    template <class TagA, class TagB>
    struct greater_equal_impl;

    template <>
    struct greater_equal_impl<
      boost::metaparse::v1::source_position_tag,
      boost::metaparse::v1::source_position_tag
    >
    {
      typedef greater_equal_impl type;

      template <class A, class B>
      struct apply : bool_<!less<A, B>::type::value> {};
    };

    template <class TagA, class TagB>
    struct less_equal_impl;

    template <>
    struct less_equal_impl<
      boost::metaparse::v1::source_position_tag,
      boost::metaparse::v1::source_position_tag
    >
    {
      typedef less_equal_impl type;

      template <class A, class B>
      struct apply :
        bool_<less<A, B>::type::value || equal_to<A, B>::type::value>
      {};
    };

  }
}

#endif


/* source_position.hpp
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
*/