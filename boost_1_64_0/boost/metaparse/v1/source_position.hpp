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
a4VbmdTpjTzHwZkqXssxXiKYYMpdWM7f7LPsO+T+P9meLLN1sGNS37udU164HPHutVGd1P6uUvTVl8X6b1G0bk/qtcMLWDvsVQm/Kv000s7Xj9yRfX0S/crh1Sc1HvU5jmcr8BqTmv6ycp3u5LR815Z0rs90TQf/F5jyC1m+sDx0Zd8DnpWM2p/Paz2/U0hrdpLbraKK9e/KzsEehT2vtXuSbYRw0F52/yURzEmG/nqPJPvuPZPqrBaV0e+8fDqp58dzk1iDm7ri6xwZ7M28qTsUlrd5jBfKDN0RHLYW4s0X9c9G2wBf7YPshvoXJHlMIzshXMYJfS/5EIUTnqO7e4LeT1kk6t1ltK73LegBNuLrXUz4M+FfQt67fDBZfkvdnYWWZ6O76RsWr/WWxvnYJS2t7fNbVrWwk9XZWOvFnjHeQho+zixsY06Bd//3T4bnqTuRvt3LkhrKrgvHqihm7AopT4G5ziRZl9FRAjqK3gxYpXzy8nlty1tW0KoXVDkt4yAFyfj4pwdQvsaJuZfONko2wH0ka/bUDknmiXtTmMcw7m1SzyU/a3zrYYJP8tuxshwucLbLI2+H8EHkF/Ub9Oy/CGbHGnqDPrnZmKyuSXfzIuqsnG2tE365O6nGRYKJvUajjx7Day/zSjD5LQl7jREcunizTu8jHSXgjg+715ox8LPN96ShUI80H2ae1xueNyQjOTGmI038YB9D7WPD9iQOnakU7UV5ah/khOTmx3pdZuvgxEgu2Hu3mU+flMSYALikad+BP4XtjXxdeHa5ZwftP0/N2yfWkfNwD71GfUKkyVpwV9TKhB/n2buiX8JYtykpz0vGy/LlpN43Pp1lp3EA4wF+1JbqDPoZxh43clugLsu34ZXa4myla41vY3OcK+xgf+Mbvor0/tyfMJ8DHzz2xusOnvT8pD7reDit1ePpMI+gpehciDY4Tcw3xpXpM4ldtaH/vDjpfKo+l/EtyHNRTh7Wk8vDuSmcK9d6uoxtknBDfu1Z6e9oHNiDxvku65twzN7lsD7C9xXOrdD8XBHbn0L8m8ze+pWMCx+fH/dqgdu4GbrXJPW9h9ksP83T4+dGP0nK+9pb1gevl2t8qu9vO3DaroMCo9ubeS1CdmHszsQf4n2QUcGtoFNRxXVIuhOq2BfMKtfza1fGfkP6GevXwXHeOT4Wzp2sT4Fr3vRHn9jO7JncQ+nOcj3O/kKN9fFzknsVTvx3nV8lVT2Ep339/dHcFvCDxbkHjCfgK9TJA2asmAWZus1a4kFKk5yGDuvrIdG3uk37PyLHXdCQ+0WP0b9NBN+WY4s7vvF2rrVPU55qfVzpLSxr9fYHgTMD6ziL8yTzCRx8g4reXjTzD6v7Z3guYOyVx3asD7HWlHzHn934M8oMJKL9R26TVpYj1ob/lhTfrvDmau69QtNG/0Da5dv7XyVJvRcfYB7zEmzl46GtsP9hfNDEWTvg72/wX9P4BEcsVeCTbhT+mxqf4CH+W2YeZPe+3xHwj8fA3xXw/WPg7wu4q9PC/5vUe+n2XU5/h7tej8eVHCeMZOI4EkMxc7MElTW49LP1hLgj65lX6Apw7LHWg1dVr+Z123pO4ywS0vwd2tJ4bgdtv58AjWCsGSdQRp7vKwfuUEzsDCoPvZizaPXhnH3TGJ6z71Bv7krU57/HX8l6EHh6vjte4KzOw0eVaJtqPp8a2y93hA0MiPsnOOOl50axZyM0rUn18PfSJmA7WfzkGDiFZSH7jfeVtZHtAMeeC04aGkFM7I4Gg7M6BqcROOgvsbw0sV4lv7B5rYvpjAt6+XFnKv7i44/MqmcbegZzQUmrsxxxGkUbvFTpxq8Q/x/sA9R+0u4=
*/