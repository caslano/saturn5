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
osQUQYQb+IIEzIU3TeSbwBHjfoKDEMJ8nJSQmuvwzvgliLtqX9NK6S1JMIne7+VHt7he/IaLI2o8sDFm/jXZ007bmKLQYjbQCF2KyMbnMXZimVNTkvWE654j5ifctdltfQ7YIcUtqML7Oll9Fg8SIuWjtRmVLqVkj09FgNRs7C2a5lMD/P6QGCPs96PqNVvs0Z8AvQEzBCI1aZZlC7Er0SIvBQf0I+HK53hH1AbIAXwRvD+cm8GGoy9Zk4NqdqBSSmpQOAuuP0tk+UQLZ3sQ/PzoA+wso239M6/lqff/0BcSEtolLMaBR2KuEJ6emgug6Mp5R1RVwznUkz1+1HgLiGsR5+T5OCBFPnFVPCteXIOOaZbzasPRcXbt9Qb+kOkhYRwi0XX3DtHwjOUTIJIqyeElzo4jEJVtmdNtTIHbU2M+Vf7G5YUfhKGTwb7UtTLbmQ0/9Uis+5SlM/yqTfHpxMRZpFvv/eZeE+1kxRRnfy8OWQqjIwMoTc2eaNQMuACm+oN8ZzefXw5QoTT+A5OLXUp7wxbsp9dPfFCQ4iaTwP5J1PNymFMYmUmUFA==
*/