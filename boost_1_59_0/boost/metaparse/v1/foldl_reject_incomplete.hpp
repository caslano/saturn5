#ifndef BOOST_METAPARSE_V1_FOLDL_REJECT_INCOMPLETE_HPP
#define BOOST_METAPARSE_V1_FOLDL_REJECT_INCOMPLETE_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/fail_at_first_char_expected.hpp>
#include <boost/metaparse/v1/is_error.hpp>
#include <boost/metaparse/v1/get_position.hpp>
#include <boost/metaparse/v1/get_result.hpp>
#include <boost/metaparse/v1/get_remaining.hpp>

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/equal_to.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class State, class ForwardOp>
      struct foldl_reject_incomplete
      {
      private:
        template <class Res>
        struct apply_unchecked :
          // I need to use apply_wrap, and not apply, because apply would
          // build a metafunction class from foldl<P, State, ForwardOp>
          // when ForwardOp is a lambda expression.
          foldl_reject_incomplete<
            P,
            typename ForwardOp::template apply<
              typename State::type,
              typename get_result<Res>::type
            >,
            ForwardOp
          >::template apply<
            typename get_remaining<Res>::type,
            typename get_position<Res>::type
          >
        {};

      template <class S, class Pos>
      struct accept_state : accept<typename State::type, S, Pos> {};

      template <class S, class Pos>
      struct end_of_folding :
        boost::mpl::eval_if<
          typename boost::mpl::equal_to<
            typename Pos::type,
            typename get_position<typename P::template apply<S, Pos> >::type
          >::type,
          accept_state<S, Pos>,
          typename P::template apply<S, Pos>
        >
      {};
      public:
        typedef foldl_reject_incomplete type;
      
        template <class S, class Pos>
        struct apply :
          boost::mpl::eval_if<
            typename is_error<typename P::template apply<S, Pos> >::type,
            end_of_folding<S, Pos>,
            apply_unchecked<typename P::template apply<S, Pos> >
          >
        {};
      };
    }
  }
}

#endif


/* foldl_reject_incomplete.hpp
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
*/