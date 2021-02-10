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
uqcDcokmcHglYUDu0Tx6PEfFsHWWTcV2H85md1eT22DVfBz22F7wqumi+DD4q8sWa9uZt516zb/Af10mIAH5t4TbXKfKYkepvtk3iTzDexyeJWFboRK2cZxtfzZ/AFBLAwQKAAAACAAtZ0pSCzPb7mgDAACiCQAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDEyOTRVVAUAAbZIJGDtVsFu2zgQvQvwPwxS5FJYK8tx0lrxGgjSbJNtEmdjtdcFLY0sIhKpkpRd/f0+SrFz6H5CAMOmyJk3wzfzRl44ti4TlpfBQqpC4+eFu702uV0Gt2n61H/R15s0WERvJ4toMA4+BB9ozWbHJrQy52BhuKk6GOTCiQEhiv+IaTqZ0Opb8EU4TihteUyTOT3qHQ7iCcWzZDZPYPL1IQ0GuIR8ZqHtH6JCvHBwL7DxoHNZSM5fUeIz+rtVHh4o0ySeHFBuUrFN6GQaT6bnYZ59Cs/ms4vpbP75JLjKMm5c+CzUlm1Cmw6RgmutHCsX3rPaujKhC7+jOHNSq4SySls+2qRdwz6/Xy4qXV0Ff7VKdWHJAll1bPEJgrDQOgRPAw+L6JWXnrDrSnqYgbCsf4BJwcK1hsFuzpt2C5+3ncXAwzIonWtwcnhcKFHz
*/