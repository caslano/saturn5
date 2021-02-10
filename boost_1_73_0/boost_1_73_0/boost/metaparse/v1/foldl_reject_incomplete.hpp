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
3KKD6KDiv2N9fBUrs7bqwWJP/InggflVVXqEjnl2CLjEHeZJRUHU8Ad9CLo2K+x4wMO2pMKu6eGFtFylujLQmV2tTJ2nQsrGUCGNk6UDDryc4NETpYbjyWx+M02GHnY6uZv3F36joUclDAuz24UOw/jifZx8uryMVBj6U+BPtViT2hbWh/76i6N1U+afV9hnBs4eb/8RPIqiePA8YHmOU+olGlq3yPboDXPKcN2TvAfh7ztv+qWAWRK2bFMEzwoK49ibWMOZKyydCd35mCEYlWxmq1SwM99cJuj9FYixdZTAH5ED8YN9IUePPBObbd1Wanh/fTe7mXwPxCjLsOH0uToPxNRrIZ9b8xaxkaOq3GAggjeYxS/if7HX6rQVrY6rUqf/0W9QSwMECgAAAAgALWdKUo+zIKAjAQAA6wEAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxMjQyVVQFAAG2SCRgRZHNboMwEITv+xSrRDkiK1FPyOJSqWpPoQnq3YVFWAEvtZdEefsaQ5KL/3a+2bGthYLUJlAB2rqW43Sh+419EwqoPqoyDXg6fYNWr4pWixi2sMUz+Sv5LNiGQHsa+3sUNEZMAQbrbnIX5BbmA/Akk3fUAApj3VtyEr0WrVYrm0zf
*/