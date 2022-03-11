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