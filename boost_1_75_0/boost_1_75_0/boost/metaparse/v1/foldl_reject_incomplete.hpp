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
n1Th7bW52ZDg60X+WxkG/PLBOHep4IBWyp2DvrY/djX0vQQtpj9AeeUAg6ib0jSQ9wgf+9nosTfqxo68RUuRN4zg/qaOL6WI2l1qHMqwHwWsG6DeLgp22N2WYedQrOTJQH8F/rHXXnwp2EtDA13zM53h+83ZMPfPMQzlPoAd/ga+vV5++jiGfUGRGN96YFmOrPkZbulj8DWHcld7Qq3qF5tN5JeQsNhPkew2lIbfjgZhHqUymm6po1vquGX7XbNoQVuG4eKiMnw7wMlvPmRE8VRkNHusmnYXNMsb+7qhjJDolIe3AOygjFA1DAjneIebBGpwE7A6JQU223B8LfQMqRRvbANvvJu9Ed9Xq+3mHm9Y9f1va8X7arX3sb/ZSHAuKladve8oViRDYokFMMv550ZaQcSgpECJkzOEkIleegQ9kmzkiNUXGiLOy+r59bhiQJfZ6fXiNJza6U9kp1brRA6KoDlyBVGG9SYtgmYKxZwnOVVS8K+hvP/1CDp2wWOV/HMW8PCwrWsPm6kcbCnS3EqIjjlmhj31SVp9Uiv4ZQn0ZHwmQQ2W1RxNixnIj9aeWxasOxws6xCxCTtgWjnZZqLHW8vHs8mTW4sbY923zEb3XdrMe89j790ADW3ZI+GrD9uzP5M269+ujmcvvqwdDmUvrmtvIqtgM3NLSBRz220Xc9ONY0vm42SlaOMQH6a7oP7FMbP/KhjjKuO8
*/