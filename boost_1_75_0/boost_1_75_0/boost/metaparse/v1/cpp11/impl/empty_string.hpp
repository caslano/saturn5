#ifndef BOOST_METAPARSE_V1_CPP11_IMPL_EMPTY_STRING_HPP
#define BOOST_METAPARSE_V1_CPP11_IMPL_EMPTY_STRING_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class Ignore = int>
        struct empty_string
        {
          typedef empty_string type;

          static constexpr char value[1] = {0};
        };

        template <class Ignore>
        constexpr char empty_string<Ignore>::value[1];
      }
    }
  }
}

#endif


/* empty_string.hpp
gq7NGm83r2b+jRaRIk7YT67BgaHOgtMixftlHWoqdn3R94A46O4/0NCMSbV1dEJaY35OsYhrZOjd7C9PTLEoV5QaKk4qCjr/lBOpygSgYxcgF5SDL4nbpFEFOeFkyjLsugpaJX+pbboTLbjKNqXDzOJGerS05p56tHgeWEM0XX1wAOB5316wDXP3Any+vCOefAHuRC+jvXYtFcGilDFrRQUAdslGoA0uQm8U1Hr1NW770Xjr8m9hm1+vcl/heBQzXJd6DE/qh/cCLgQUchsoDihH8BN15GvGG0+kfYnOCcBevHUt6oL9hROyAdAUL/1TMPp34nExFHZjSrm3cHh2+GcQ6iZkoy4gE9opFD0VazftZR63OFZNGrmp08h5BpbT5UGhZxz8jrLH8yR1EIUcfRA05AeptsABPdraSReD+nHtAju+zy949QYWVUdAl02wJbVMO9kWdNfzQXZiLja9Kuo+DQ8RUUDF2s49YlRttaRybA8tIob0HwF0LSH5+C8Bc2DqIAr6mRBk9aFIMkDj+0sa+rHoqN5Q3tceS+0+ONMn2rYd835WYRw/duQIciAvp/zhIqgEuSEXGZA7i8YI6xML0ysZAQNyhy9EyP0q94Dc49Pj1Q16p8UhR0WufrEdB3IXQpd/xwDFL2xiZH+YLs531PbgiNQLUwT7+OcvcESh7IrY7RQddJeM2SVhQL+nAc2REyCWiePpM52r
*/