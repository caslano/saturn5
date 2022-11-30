#ifndef BOOST_METAPARSE_V1_FOLDL_HPP
#define BOOST_METAPARSE_V1_FOLDL_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2011.
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
      template <class P, class State, class ForwardOp>
      struct foldl
      {
      private:
        template <class Res>
        struct apply_unchecked :
          // foldl never returns error
          // I need to use apply_wrap, and not apply, because apply would
          // build a metafunction class from foldl<P, State, ForwardOp>
          // when ForwardOp is a lambda expression.
          foldl<
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
        struct next_iteration : accept<typename State::type, S, Pos> {};
      public:
        typedef foldl type;
      
        template <class S, class Pos>
        struct apply :
          boost::mpl::eval_if<
            typename is_error<typename P::template apply<S, Pos> >::type,
            next_iteration<S, Pos>,
            apply_unchecked<typename P::template apply<S, Pos> >
          >
        {};
      };
    }
  }
}

#endif


/* foldl.hpp
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
*/