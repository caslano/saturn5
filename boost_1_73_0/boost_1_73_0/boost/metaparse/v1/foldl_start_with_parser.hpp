#ifndef BOOST_METAPARSE_V1_FOLDL_START_WITH_PARSER_HPP
#define BOOST_METAPARSE_V1_FOLDL_START_WITH_PARSER_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/foldl.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class StateP, class ForwardOp>
      class foldl_start_with_parser
      {
      private:
        template <class Res>
        struct apply_unchecked :
          foldl<P, typename get_result<Res>::type, ForwardOp>::template apply<
            typename get_remaining<Res>::type,
            typename get_position<Res>::type
          >
        {};
      public:
        typedef foldl_start_with_parser type;

        template <class S, class Pos>
        struct apply :
          boost::mpl::eval_if<
            typename is_error<typename StateP::template apply<S, Pos> >::type,
            typename StateP::template apply<S, Pos>,
            apply_unchecked<typename StateP::template apply<S, Pos> >
          >
        {};
      };
    }
  }
}

#endif


/* foldl_start_with_parser.hpp
Dnawm+Bgp/sIDuMdsKY4h+ei4wgO81FKcBjvHJKLEhz0cjHBoX83ERzkPURwsNOnCQ7x/m2Cw3x8TnDo3xG/LM7B30YTHPa1ZQQHuzqb4MZKqSM4xKsUwan3agSHuLu+J86LaRdJw1uFG/2w9TtOxJiu1T/l/hoz/tVLiW7XtN9vt34/Qoruq7+o8PtNW6V8J8xjO6zf/0lDu75K91c28Q9/f7B7h+b5p76bkvJy8LePhPvCZg+3OV3XIfpvUu4=
*/