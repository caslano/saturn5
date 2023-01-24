#ifndef BOOST_METAPARSE_V1_FOLDR_START_WITH_PARSER_HPP
#define BOOST_METAPARSE_V1_FOLDR_START_WITH_PARSER_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/accept.hpp>
#include <boost/metaparse/v1/is_error.hpp>
#include <boost/metaparse/v1/get_position.hpp>
#include <boost/metaparse/v1/get_result.hpp>
#include <boost/metaparse/v1/get_remaining.hpp>

#include <boost/mpl/eval_if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class StateP, class BackwardOp>
      struct foldr_start_with_parser
      {
      private:
        template <class Res, class Rem>
        struct apply_unchecked1 :
          accept<
            typename BackwardOp::template apply<
              typename get_result<Rem>::type,
              typename get_result<Res>::type
            >::type,
            typename get_remaining<Rem>::type,
            typename get_position<Rem>::type
          >
        {};

        template <class Res>
        struct apply_unchecked;
      public:
        typedef foldr_start_with_parser type;
      
        template <class S, class Pos>
        struct apply :
          boost::mpl::eval_if<
            typename is_error<typename P::template apply<S, Pos> >::type,
            typename StateP::template apply<S, Pos>,
            apply_unchecked<typename P::template apply<S, Pos> >
          >
        {};
      private:
        template <class Res>
        struct apply_unchecked
        {
        private:
          typedef
            typename foldr_start_with_parser::template apply<
              typename get_remaining<Res>::type,
              typename get_position<Res>::type
            >
            parsed_remaining;
        public:
          typedef
            typename boost::mpl::eval_if<
              typename is_error<parsed_remaining>::type,
              parsed_remaining,
              apply_unchecked1<Res, parsed_remaining>
            >::type
            type;
        };
      };
    }
  }
}

#endif


/* foldr_start_with_parser.hpp
cBmaRr1iT+G7HfSu8nm73OqKK9Md7hpPgH65Uz6m2q/VUdDeIEkjwfHcqdhZMvL+y+xYsXm8q+JViNGCRHut9zUYrxxwUXG0XLghP62EErFhR8zXPh1L++kjUST45nsDb1HzbsqG0R+vjb7Qxkj7YyrCHgFGlaBzQWEEirdo6BrBHt1KS8GWHngJa9EG7syHmugeu8K2RPZHKhR+Z8cUsAamgSCeRhtlNKZli6KS7Hu8k9oBP3yP0Id+RsHaQShqpHjslqewFCUm6m+LBK2AhBQv10p4FWvn+fMiFAJ6u+ESG4xkqU1KtGWG0PFUpEU8B2liBZcmMvgtD0fCTLTCi7NkfeTibf4eEGjZ6Tkebtw4ljdmrfEm/DPofGEeBl5CBP/5UqJnBNvfuB3tsk6Puo5+MwrMEhfV7cV7HSWHI0ztNIjdK0W0TqJjWIQOG14VgZ8fOFeMxNAkm2LqgfklK5T/OA5PgN2bP+0NRv38BFUCzkhXv9CeoU+1PSE+tWPA/+VT51k/9a75U0n0qU/lpyb9nz5Vbrd8ao75U6gEBZ1Py0+1Xfx/+dRY66duMH/qFvrUKPmp4P/wKcyS+Ip/7YDNoEdXxaA44kDwSzt8pU02xKPSLWg8/QqaUsUfpLIeQVOpaVEXHUFnG+Aji22SS3m5kB2mes16Bpidwfy+WmJh7ROeRgmdF6U1MfkbnuaiuxgCh9F5KbqXma8Z
*/