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