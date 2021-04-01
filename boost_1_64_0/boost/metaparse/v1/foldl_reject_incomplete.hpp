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
9st5Vpb+Re+3Fiam1Z6dK4qkhygASTHOkftccQnWUP8EWZxhCfz/adVq2ADGkPxyP/VYIkXUWZ1kjvGS73A1zSo3hZsU+8p6vimiwuUtiMqV7bWvcqq0xFh1LqiShS7cxMm6DRuiQ6XA5U91OL5nbHrEVb9LkAt2HBWw941qbVBh4tH04NKIxZftEZ1QNuDWzHkYkvjI05hUbYyvMmGds9jiiJrD8OwXo5/BfWjipwm54nvrjt86ZfV7n1bfBaemaFHvGCJuxqdirnbcRLtTIdHNIveP3LyrJCCoEyw0O/t0XAjyNk8E+AMdaXF2XNic+uaoo9T7+n+IAkUDRKemm0srBo5czhdVrKRquy2EihOEpl9IScGR4+2Qqdo342c/sJVrwMNlPJvOTnNRX661UN/u39/SENHXYAFpOKtOP3bL2egmm8QAD0IdG24gAmm6PgJM4cFFvDBSAfYrFPSHPnuE2jaarNvEfIXrxHZbL/+STC5jDC6nCTWGzansXNMk92tNP/s4lR/FQ2GAjPNS++KVo8p5z+MoEIOilzZNjLijG7FnKq2Glioavg==
*/